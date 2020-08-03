#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, LPSTR lpszCmdShow, int iCmdShow) {

	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("App");
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
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;

	RegisterClassEx(&wndclass);

	
	hwnd = CreateWindow(szAppName, TEXT("App"), WS_OVERLAPPEDWINDOW, 10, 10, 700, 700, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static COLORREF hBrush[5];
	static int iBrushNo;
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rc;
	switch (iMsg) {
		case WM_CREATE:
			hBrush[0] = RGB(255, 0, 0);
			hBrush[1] = RGB(0, 255, 0);
			hBrush[2] = RGB(0, 0, 255);
			hBrush[3] = RGB(255, 0, 255);
			hBrush[4] = RGB(255, 255, 0); 
			iBrushNo = 0;
			GetClientRect(hWnd, &rc);
			break;
		case WM_KEYDOWN:
			switch (wParam) {
				case 0x52:
					iBrushNo = 0;
					//MessageBox(hWnd,TEXT("RButton Down"), TEXT("xc"), MB_OK );
					InvalidateRect(hWnd, NULL, TRUE);
					break;
				case 0x47:
					iBrushNo = 1;
					InvalidateRect(hWnd, NULL, TRUE);
					break;
				case 0x42:
					iBrushNo = 2;
					InvalidateRect(hWnd, NULL, TRUE);
					break;
				case 0x50:
					iBrushNo = 3;
					InvalidateRect(hWnd, NULL, TRUE);
					break;
				case 0x59:
					iBrushNo = 4;
					InvalidateRect(hWnd, NULL, TRUE);
					break;
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			//SelectObject(hdc, hBrush[iBrushNo]);
			SetBkColor(hdc, hBrush[iBrushNo]);
			SetTextColor(hdc, RGB(0, 0, 0));
			DrawText(hdc, TEXT("This Text changes color on pressing R,G,B,Y,P!!!"), -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}