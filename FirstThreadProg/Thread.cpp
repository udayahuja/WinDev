#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, LPSTR lpszCmdShow, int iCmdShow) {

	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("Thread");
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

	
	hwnd = CreateWindow(szAppName, TEXT("Thread"), WS_OVERLAPPEDWINDOW, 10, 10, 700, 700, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	
	static HANDLE hThreadOne = NULL;
	static HANDLE hThreadTwo = NULL;

	switch (iMsg) {
		case WM_CREATE:
			hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID) hwnd, 0, NULL);
			hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID) hwnd, 0, NULL);
			break;

		case WM_LBUTTONDOWN:
			MessageBox(hwnd, TEXT("My First Multi Threaded Program"), TEXT("MultiThreading"), MB_OK);
			break;

		case WM_DESTROY:
			if (hThreadOne) {
				CloseHandle(hThreadOne);
				hThreadOne = NULL;
			}
			if (hThreadTwo) {
				CloseHandle(hThreadTwo);
				hThreadTwo = NULL;
			}
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

DWORD WINAPI ThreadProcOne(LPVOID param) {
	HDC hdc;
	TCHAR str[255];
	hdc = GetDC((HWND)param);
	for (int i = 0; i < 2147483647;i++) {
		wsprintf(str, TEXT("Thread 1: Incrementing: %d"), i);
		TextOut(hdc, 0, 5, str, wcslen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}
DWORD WINAPI ThreadProcTwo(LPVOID param) {
	HDC hdc;
	TCHAR str[255];
	hdc = GetDC((HWND)param);
	for (int i = 2147483647; i > 0; i--) {
		wsprintf(str, TEXT("Thread 2: Decrementing: %d"), i);
		TextOut(hdc, 5, 25, str, wcslen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}