#include<windows.h>
#define MY_TIMER 105
#define MY_TIMER1 100


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK TimerProc(HWND, UINT, UINT_PTR, DWORD);

RECT rc;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, LPSTR lpszCmdShow, int iCmdShow) {

	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("Timer");
	WNDCLASSEX wndclass;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = szAppName;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadIcon(NULL, IDC_HELP);
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpszMenuName = NULL;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.style = CS_VREDRAW | CS_HREDRAW; 

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("Timer"), WS_OVERLAPPEDWINDOW, 10, 10, 700, 700, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static HBRUSH hBrush[8];
	static int iPaintFlag = 0;
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMsg) {

		case WM_CREATE:
			GetClientRect(hWnd,&rc);
			hBrush[0] = CreateSolidBrush(RGB(255,0,0));
			hBrush[1] = CreateSolidBrush(RGB(0, 255, 0));
			hBrush[2] = CreateSolidBrush(RGB(0, 0, 255));
			hBrush[3] = CreateSolidBrush(RGB(255, 0, 255));
			hBrush[4] = CreateSolidBrush(RGB(255, 255, 0));
			hBrush[5] = CreateSolidBrush(RGB(255, 128, 0));
			hBrush[6] = CreateSolidBrush(RGB(0, 255, 255));
			hBrush[7] = CreateSolidBrush(RGB(0, 128, 255));
			SetTimer(hWnd, MY_TIMER, 2000, NULL);
			SetTimer(hWnd, MY_TIMER1, 50, &TimerProc);
		break;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			ps.fErase = 0;
			ps.rcPaint = rc;
			SelectObject(hdc, hBrush[iPaintFlag]);
			FillRect(hdc, &rc, hBrush[iPaintFlag]);
			EndPaint(hWnd, &ps);
			break;

		case WM_TIMER:
			KillTimer(hWnd, MY_TIMER);
			iPaintFlag++;
			iPaintFlag %= 8;
			GetClientRect(hWnd, &rc);
			InvalidateRect(hWnd, NULL, TRUE);
			SetTimer(hWnd, MY_TIMER, 2000, NULL);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

void CALLBACK TimerProc(HWND hWnd, UINT timerMsg, UINT_PTR timerIdentifier, DWORD time) {
	switch (timerMsg) {
		case WM_TIMER:
			KillTimer(hWnd, MY_TIMER1);
			if (rc.top < rc.bottom) {
				rc.top += 5;
				rc.left += 5;
				rc.right -= 5;
				rc.bottom -= 5;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			SetTimer(hWnd, MY_TIMER1, 10, &TimerProc);
			break;
	}
}
