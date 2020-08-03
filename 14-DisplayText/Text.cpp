#include<windows.h>
#include"MyWindow.h"
#include"Pledge.h"
#define MY_TIMER 10101
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	HDC hdc,hdcMem;
	static HBITMAP hBitmap;
	BITMAP bitmap;
	static HDC hdcBitmap;
	PAINTSTRUCT ps;
	TEXTMETRIC tm;
	static int cxChar, cyChar, cvChar, chChar;	//cvChar is for vertical division of the page and chChar is horizontal
	static RECT rc;
	static int iActualLineNo, iCurrentLineNo;
	static COLORREF hBrush[3];
	static int hBrushIndex;
	static BOOL flag;
	switch (iMsg) {

		case WM_CREATE:
			flag = TRUE;
			hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(FLAG_IMG));
			iActualLineNo = 0;
			hBrushIndex = 0;
			hBrush[0] = RGB(244,196,48);
			hBrush[1] = RGB(255, 255, 255);
			hBrush[2] = RGB(0, 196, 0);
			iCurrentLineNo = 3;
			hdc = GetDC(hwnd);
			GetTextMetrics(hdc, &tm);
			cxChar = tm.tmAveCharWidth; 
			cyChar = tm.tmExternalLeading + tm.tmHeight;
			ReleaseDC(hwnd, hdc);
			
			GetClientRect(hwnd, &rc);
			cvChar = (rc.bottom - rc.top) / 20;
			chChar = (rc.right - rc.left) / 5;
			InvalidateRect(hwnd, NULL, TRUE);
			SetTimer(hwnd, MY_TIMER, 1500, NULL);
			break;
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			//SelectObject(hdc, hBrush[hBrushIndex]);
			if (flag) {
				flag = false;
				hdcMem = CreateCompatibleDC(NULL);
				SelectObject(hdcMem, hBitmap);
				GetObject(hBitmap, sizeof(BITMAP), &bitmap);
				StretchBlt(hdc, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
				DeleteObject(hdcMem);

			}
			SetTextColor(hdc, hBrush[hBrushIndex]);
			SetBkColor(hdc, RGB(0, 0, 255));
			TextOut(hdc, chChar* 2, cvChar * iCurrentLineNo, str[iActualLineNo], wcslen(str[iActualLineNo]));
			iActualLineNo++;
			iCurrentLineNo++;
			if (iActualLineNo%4 == 0) {
				hBrushIndex++;
				iCurrentLineNo++;
			}
			
			EndPaint(hwnd, &ps);
			break;
		case WM_TIMER:
			KillTimer(hwnd, MY_TIMER);
			InvalidateRect(hwnd, NULL, FALSE);
			if(iActualLineNo!=11)
				SetTimer(hwnd, MY_TIMER, 1500, NULL);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}