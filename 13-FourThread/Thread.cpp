#include<windows.h>
#include<stdlib.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);
DWORD WINAPI ThreadProcThree(LPVOID);
DWORD WINAPI ThreadProcFour(LPVOID);

BOOL gbDone = FALSE;
RECT gRect;

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

	
	hwnd = CreateWindow(szAppName, TEXT("Thread"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
	static HANDLE hThreadThree = NULL;
	static HANDLE hThreadFour = NULL;

	switch (iMsg) {
		case WM_CREATE:
			GetClientRect(hwnd, &gRect);
			hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID) hwnd, 0, NULL);
			hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID) hwnd, 0, NULL);
			hThreadThree = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcThree, (LPVOID)hwnd, 0, NULL);
			hThreadFour = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcFour, (LPVOID)hwnd, 0, NULL);
			break;

		case WM_SIZE:
			GetClientRect(hwnd, &gRect);
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
			if (hThreadThree) {
				CloseHandle(hThreadThree);
				hThreadThree = NULL;
			}
			if (hThreadFour) {
				CloseHandle(hThreadFour);
				hThreadFour = NULL;
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
	SetBkColor(hdc, RGB(0,0,0));
	SetTextColor(hdc, RGB(0,255,0));
	for (int i = 0; i < 2147483647;i++) {
		wsprintf(str, TEXT("Thread 1: Incrementing: %d"), i);
		TextOut(hdc, 5, 5, str, wcslen(str));
		wsprintf(str, TEXT("Thread 2: Decrementing: %d"),2147483647 - i);
		TextOut(hdc, 5, 25, str, wcslen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID param) {
	HDC hdc;
	HBRUSH hBrush;
	RECT rc;
	
	hdc = GetDC((HWND)param);
	
	while (gbDone == FALSE) {
		rc.left = gRect.right / 2 + (rand() % gRect.right / 2);
		rc.top = rand()% gRect.bottom / 2;
		rc.right = gRect.right / 2 + (rand() % gRect.right / 2);
		rc.bottom = rand() % gRect.bottom / 2;
		hBrush = CreateSolidBrush(RGB(rand()%255, rand() % 255, rand() % 255));
		FillRect(hdc , &rc ,hBrush);
		DeleteObject(hBrush);
	}

	ReleaseDC((HWND)param, hdc);
	return 0;
}

DWORD WINAPI ThreadProcThree(LPVOID param) {
	HDC hdc;
	HBRUSH hBrush;
	RECT rc;

	hdc = GetDC((HWND)param);

	while (gbDone == FALSE) {
		rc.left = gRect.right / 2 + (rand() % gRect.right / 2);
		rc.top = gRect.bottom / 2 + rand() % gRect.bottom / 2;
		rc.right = gRect.right / 2 + (rand() % gRect.right / 2);
		rc.bottom = gRect.bottom / 2 + rand() % gRect.bottom / 2;
		hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		//FillRect(hdc, &rc, hBrush);
		SelectObject(hdc,hBrush);
		Ellipse(hdc , rc.left, rc.top, rc.right, rc.bottom);
		DeleteObject(SelectObject(hdc,GetStockObject(WHITE_BRUSH)));
	}

	ReleaseDC((HWND)param, hdc);
	return 0;
}

DWORD WINAPI ThreadProcFour(LPVOID param) {
	HDC hdc;
	HBRUSH hBrush;
	RECT rc;

	hdc = GetDC((HWND)param);

	while (gbDone == FALSE) {
		rc.left = gRect.left / 2 + (rand() % gRect.right / 2);
		rc.top = gRect.bottom / 2 + rand() % gRect.bottom / 2;
		rc.right = gRect.left / 2 + (rand() % gRect.right / 2);
		rc.bottom = gRect.bottom / 2 + rand() % gRect.bottom / 2;
		hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		//FillRect(hdc, &rc, hBrush);
		SelectObject(hdc, hBrush);
		RoundRect(hdc, rc.left, rc.top, rc.right, rc.bottom, rand()%20,rand()%20);
		DeleteObject(SelectObject(hdc, GetStockObject(WHITE_BRUSH)));
	}

	ReleaseDC((HWND)param, hdc);
	return 0;
}