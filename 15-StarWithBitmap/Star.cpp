#include<windows.h>
#include"MyWindow.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE ghinstance;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, LPSTR lpszCmdShow, int iCmdShow) {

	ghinstance = hInstance;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("Star");
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
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;

	RegisterClassEx(&wndclass);

	
	hwnd = CreateWindow(szAppName, TEXT("Aries"), WS_OVERLAPPEDWINDOW, 10, 10, 700, 700, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static int height, width, imgHeight, imgWidth;
	static RECT rc;
	HDC hdc;
	PAINTSTRUCT ps;
	static HDC hdcMem;
	static BITMAP bitmap;
	static HBITMAP hbitmap;
	static POINT pt[4];
	static HBRUSH hBrush;
	static HPEN pen;

	switch (iMsg) {
		case WM_CREATE:
			GetClientRect(hWnd, &rc);
			hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
			pen = CreatePen(PS_SOLID, 3, RGB(255,0,0));
			hbitmap = LoadBitmap(ghinstance, MAKEINTRESOURCE(MYBITMAP));
			hdcMem = CreateCompatibleDC(NULL);
			SelectObject(hdcMem, hbitmap);
			GetObject(hbitmap, sizeof(BITMAP), &bitmap);
			height = (rc.bottom - rc.top)/10;
			width = (rc.right - rc.left) / 10;
			imgHeight = height / 3;
			imgWidth = width / 3;
			
			pt[0].x = rc.left + width;
			pt[0].y = rc.top + height;

			pt[1].x = rc.left + 5 * width;
			pt[1].y = rc.top + 4 * height;

			pt[2].x = rc.left + 7 * width;
			pt[2].y = rc.top + 7 * height;

			pt[3].x = rc.left + width * 8.5;
			pt[3].y = rc.top + height * 9;
			
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			StretchBlt(hdc, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
			SelectObject(hdc, pen);
			SelectObject(hdc, hBrush);
			MoveToEx(hdc, pt[0].x, pt[0].y, NULL);
			LineTo(hdc, pt[1].x, pt[1].y);
			MoveToEx(hdc, pt[1].x, pt[1].y, NULL);
			LineTo(hdc, pt[2].x, pt[2].y);
			MoveToEx(hdc, pt[2].x, pt[2].y, NULL);
			LineTo(hdc, pt[3].x, pt[3].y);
			
			
			Ellipse(hdc, pt[0].x - imgWidth, pt[0].y - imgHeight, pt[0].x + imgWidth, pt[0].y + imgHeight);

			Ellipse(hdc, pt[1].x - imgWidth, pt[1].y - imgHeight, pt[1].x + imgWidth, pt[1].y + imgHeight);

			Ellipse(hdc, pt[2].x - imgWidth, pt[2].y - imgHeight, pt[2].x + imgWidth, pt[2].y + imgHeight);

			Ellipse(hdc, pt[3].x - imgWidth, pt[3].y - imgHeight, pt[3].x + imgWidth, pt[3].y + imgHeight);

			EndPaint(hWnd, &ps);
			break;
		case WM_SIZE:
			GetClientRect(hWnd, &rc);
			height = (rc.bottom - rc.top) / 10;
			width = (rc.right - rc.left) / 10;
			imgHeight = height / 10;
			imgWidth = width / 10;

			pt[0].x = rc.left + width;
			pt[0].y = rc.top + height;

			pt[1].x = rc.left + 5 * width;
			pt[1].y = rc.top + 4 * height;

			pt[2].x = rc.left + 8 * width;
			pt[2].y = rc.top + 7 * height;

			pt[3].x = rc.left + width * 8.5;
			pt[3].y = rc.top + height * 9;

			break;
		case WM_DESTROY:
			DeleteObject(hdcMem);
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}