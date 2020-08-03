#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, LPSTR lpszCmdShow, int iCmdShow) {

	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("Timer");
	WNDCLASSEX wndclass;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_CROSS);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.hIconSm = LoadIcon(NULL, IDI_ASTERISK);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;

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
	
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rcSafron, rcWhite, rcGreen,rcWheel;
	static int x,y;
	switch (iMsg) {
		case WM_SIZE:
		case WM_CREATE:
			GetClientRect(hWnd, &rcSafron);
			x = (rcSafron.bottom - rcSafron.top) / 3;
			rcWhite.left = rcSafron.left;
			rcWhite.right = rcSafron.right;
			rcWhite.top = rcSafron.top + x;
			rcWhite.bottom = rcSafron.top + (2 * x);

			rcGreen.left = rcSafron.left;
			rcGreen.right = rcSafron.right;
			rcGreen.top = rcSafron.top + (2*x);
			rcGreen.bottom = rcSafron.top + (3 * x);

			rcSafron.bottom = rcSafron.top + x;
			y = (rcWhite.right - rcWhite.left) / 3;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			//GetClientRect(hWnd,&rcSafron);
			//SelectObject(hdc, CreateSolidBrush(RGB(128,128,128)));
			
			FillRect(hdc, &rcSafron, CreateSolidBrush(RGB(255, 128, 0)));
			FillRect(hdc, &rcWhite, CreateSolidBrush(RGB(255, 255, 255)));
			FillRect(hdc, &rcGreen, CreateSolidBrush(RGB(0, 255, 0)));
			SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 200)));
			Ellipse(hdc, rcWhite.left + y, rcWhite.top, rcWhite.right - y, rcWhite.bottom);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}