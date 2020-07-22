#include<windows.h>
#define MY_TIMER 105

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, LPSTR lpszCmdShow, int iCmdShow) {

	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("Timer");
	WNDCLASSEX wndclass;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = szAppName;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadIcon(NULL, IDC_HELP);
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpszMenuName = NULL;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.style = CS_VREDRAW | CS_HREDRAW; 

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("Timer"), WS_OVERLAPPEDWINDOW, 10, 10, 1000, 2500, NULL, NULL, hInstance, NULL);

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
	RECT rc;
	switch (iMsg) {

		case WM_CREATE:
			hBrush[0] = CreateSolidBrush(RGB(255,0,0));
			hBrush[1] = CreateSolidBrush(RGB(0, 255, 0));
			hBrush[2] = CreateSolidBrush(RGB(0, 0, 255));
			hBrush[3] = CreateSolidBrush(RGB(255, 0, 255));
			hBrush[4] = CreateSolidBrush(RGB(255, 255, 0));
			hBrush[5] = CreateSolidBrush(RGB(255, 128, 0));
			hBrush[6] = CreateSolidBrush(RGB(0, 255, 255));
			hBrush[7] = CreateSolidBrush(RGB(0, 0, 0));
			SetTimer(hWnd, MY_TIMER, 1000, NULL);
		break;

		case WM_PAINT:
			GetClientRect(hWnd, &rc);
			hdc = BeginPaint(hWnd, &ps);
			SelectObject(hdc, hBrush[iPaintFlag]);
			FillRect(hdc, &rc, hBrush[iPaintFlag]);
			EndPaint(hWnd, &ps);
			break;

		case WM_TIMER:
			KillTimer(hWnd, MY_TIMER);
			iPaintFlag++;
			iPaintFlag %= 8;
			InvalidateRect(hWnd, NULL, TRUE);
			SetTimer(hWnd, MY_TIMER, 1000, NULL);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}