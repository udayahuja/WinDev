#include<windows.h>
#define MY_TIMER 105
#define MY_TIMER1 100


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK TimerProc(HWND, UINT, UINT_PTR, DWORD);
COLORREF rgb(int i) {
	switch (i) {
		case 0:
			return RGB(255, 0, 0);

		case 1:
			return RGB(0, 255, 0);

		case 2:
			return RGB(0, 0, 255);

		case 3:
			return RGB(255, 0, 255);

		case 4:
			return RGB(0, 255, 255 );

		case 5:
			return RGB(255, 0, 255);

		case 6:
			return RGB(255, 128, 255);

		case 7:
			return RGB(128, 128,128);
	}
	return RGB(128, 255, 255);
}

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
			hBrush[0] = CreateSolidBrush(rgb(0));
			hBrush[1] = CreateSolidBrush(rgb(1));
			hBrush[2] = CreateSolidBrush(rgb(2));
			hBrush[3] = CreateSolidBrush(rgb(3));
			hBrush[4] = CreateSolidBrush(rgb(4));
			hBrush[5] = CreateSolidBrush(rgb(5));
			hBrush[6] = CreateSolidBrush(rgb(6));
			hBrush[7] = CreateSolidBrush(rgb(7));
			SetTimer(hWnd, MY_TIMER, 2000, NULL);
			SetTimer(hWnd, MY_TIMER1, 50, &TimerProc);
			
		break;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			SetBkColor(hdc, rgb(iPaintFlag));
			SetTextColor(hdc, RGB(0,0,0));
			DrawText(hdc, TEXT("This Text Is Falling Down"), -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hWnd, &ps);
			break;

		case WM_TIMER:
			KillTimer(hWnd, MY_TIMER);
			iPaintFlag++;
			iPaintFlag %= 8;
			GetClientRect(hWnd, &rc);
			rc.top = 10;
			rc.bottom = 30;
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
			if (rc.bottom < 700) {
				rc.top += 5;
				rc.bottom += 5;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			SetTimer(hWnd, MY_TIMER1, 10, &TimerProc);
			break;
	}
}
