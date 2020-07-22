#include<windows.h>
#define MYTIMER 12345
#define MYTIMER1 12435

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK TimerProc(HWND, UINT, UINT_PTR, DWORD);

RECT rc;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, LPSTR lpszCmdShow, int iCmdShow) {

	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("Elipse");
	WNDCLASSEX wndclass;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_CROSS);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.hIconSm = LoadIcon(NULL, IDI_ASTERISK);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;

	RegisterClassEx(&wndclass);

	
	hwnd = CreateWindow(szAppName, TEXT("Ellipse"), WS_OVERLAPPEDWINDOW, 10, 10, 700, 700, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	static HBRUSH hBrush[8];
	static int iPaintFlag = 0;
	switch (iMsg) {
		case WM_CREATE:
			hBrush[0] = CreateSolidBrush(RGB(255, 0, 0));
			hBrush[1] = CreateSolidBrush(RGB(0, 255, 0));
			hBrush[2] = CreateSolidBrush(RGB(0, 0, 255));
			hBrush[3] = CreateSolidBrush(RGB(255, 0, 255));
			hBrush[4] = CreateSolidBrush(RGB(255, 255, 0));
			hBrush[5] = CreateSolidBrush(RGB(255, 128, 0));
			hBrush[6] = CreateSolidBrush(RGB(0, 255, 255));
			hBrush[7] = CreateSolidBrush(RGB(0, 128, 255));
			GetClientRect(hWnd, &rc);
			InvalidateRect(hWnd, NULL, TRUE);
			SetTimer(hWnd, MYTIMER1, 2000, NULL);
			SetTimer(hWnd, MYTIMER, 50, &TimerProc);
			break;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			SelectObject(hdc, hBrush[iPaintFlag]);
			Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
			EndPaint(hWnd, &ps);
			break;
		case WM_TIMER:
			KillTimer(hWnd, MYTIMER1);
			iPaintFlag++;
			iPaintFlag %= 8;
			GetClientRect(hWnd, &rc);
			InvalidateRect(hWnd, NULL, TRUE);
			SetTimer(hWnd, MYTIMER1, 2000, NULL);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

void CALLBACK TimerProc(HWND hWnd, UINT timeMsg, UINT_PTR timerIdentifier, DWORD time) {
	switch (timeMsg) {
		case WM_TIMER:
			KillTimer(hWnd, MYTIMER);
			rc.top += 10;
			rc.left += 10;
			rc.bottom -= 10;
			rc.right -= 10;
			InvalidateRect(hWnd, NULL, TRUE);
			if (rc.left >= rc.right || rc.top >=rc.bottom) {
				
			}
			SetTimer(hWnd, MYTIMER, 50, &TimerProc);
		
			break;
	}
}