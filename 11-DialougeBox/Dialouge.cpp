#include<windows.h>
#include"MyWindow.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE ghInstance;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, LPSTR lpszCmdShow, int iCmdShow) {

	ghInstance = hInstance;
	HMENU hMenu;
	hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(MYMENU));


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

	
	hwnd = CreateWindow(szAppName, TEXT("Dialog"), WS_OVERLAPPEDWINDOW, 10, 10, 700, 700, NULL, hMenu, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HBRUSH hBrush;
	static int idColor[] = {WHITE_BRUSH, LTGRAY_BRUSH, GRAY_BRUSH, DKGRAY_BRUSH, BLACK_BRUSH};
	
	switch (iMsg) {

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDM_WHITE:
					hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
					SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)hBrush);
					InvalidateRect(hWnd, NULL, TRUE);
					break;

				case IDM_LTGRAY:
					hBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
					SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)hBrush);
					InvalidateRect(hWnd, NULL, TRUE);
					break;
				case IDM_GRAY:
					hBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
					SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)hBrush);
					InvalidateRect(hWnd, NULL, TRUE);
					break;
				case IDM_DKGRAY:
					hBrush = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
					SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)hBrush);
					InvalidateRect(hWnd, NULL, TRUE);
					break;
				case IDM_BLACK:
					hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
					SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)hBrush);
					InvalidateRect(hWnd, NULL, TRUE);
					break;
					
				
				case IDM_APP_ABOUT:
					DialogBox(ghInstance, TEXT("about"), hWnd, AboutDlgProc);
					break;
			}
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	switch (iMsg) {
		case WM_INITDIALOG : 
			return TRUE;

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDOK:
				case IDCANCEL:
					EndDialog(hDlg,false);
					return TRUE;
			}
			break;

	}
	return FALSE;
}