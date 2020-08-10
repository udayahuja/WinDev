#include<windows.h>
#include<time.h>
#define MYTIMER 147
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, LPSTR lpszCmdShow, int iCmdShow) {
	srand(time(0));
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("Ganpati");
	WNDCLASSEX wndclass;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	//wndclass.hbrBackground = CreateSolidBrush(RGB(135, 206, 235));
	wndclass.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wndclass.hCursor = LoadCursor(NULL, IDC_CROSS);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;

	RegisterClassEx(&wndclass);

	
	hwnd = CreateWindow(szAppName, TEXT("Ganpati"), WS_OVERLAPPEDWINDOW, 10, 10, 700, 700, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static POINT leftTop[4], leftBottom[4], rightTop[4], rightBottom[4], eye1[2], eye2[2], curve1[3];
	static RECT rc;
	RECT temp;
	static int height, width, eyeheight, eyewidth;
	HDC hdc;
	PAINTSTRUCT ps;
	static HBRUSH hbrush[10];
	static HPEN pen[4];
	static int i;
	int xwid, yhig;
	switch (iMsg) {
		case WM_CREATE:
			GetClientRect(hWnd, &rc);
			i = 1;
			for(int j=0; j < 5; j++)
				pen[j] = CreatePen(PS_SOLID, 4, RGB(rand() % 255, rand() % 255, rand() % 255));
			hbrush[9] = CreateSolidBrush(RGB(0,0,0));	//BKcolor
			for (int j = 0; j < 9;j++) {
				hbrush[j] = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			}
			width = (rc.right - rc.left) / 12;
			height = (rc.bottom - rc.top) / 11;
			/*-----------------------------------------------*/
			leftTop[0].x = rc.left + 2.5 * width;
			leftTop[0].y = rc.top + 2.5 * height;
			
			leftTop[1].x = rc.left + 4 * width;
			leftTop[1].y = rc.top + 2.5 * height;
			
			leftTop[2].x = rc.left + 4 * width;
			leftTop[2].y = rc.top + 4 * height;
			
			leftTop[3].x = rc.left + 2.5 * width;
			leftTop[3].y = rc.top + 4 * height;
			/*-----------------------------------------------*/
			rightTop[0].x = rc.left + 8 * width;
			rightTop[0].y = rc.top + 2.5 * height;

			rightTop[1].x = rc.left + 9.5 * width;
			rightTop[1].y = rc.top + 2.5 * height;

			rightTop[2].x = rc.left + 9.5 * width;
			rightTop[2].y = rc.top + 4 * height;

			rightTop[3].x = rc.left + 8 * width;
			rightTop[3].y = rc.top + 4 * height;
			/*-----------------------------------------------*/
			leftBottom[0].x = rc.left + 2.5 * width;
			leftBottom[0].y = rc.top + 7 * height;

			leftBottom[1].x = rc.left + 4 * width;
			leftBottom[1].y = rc.top + 7 * height;

			leftBottom[2].x = rc.left + 4 * width;
			leftBottom[2].y = rc.top + 8.5 * height;

			leftBottom[3].x = rc.left + 2.5 * width;
			leftBottom[3].y = rc.top + 8.5 * height;
			/*-----------------------------------------------*/
			rightBottom[0].x = rc.left + 8 * width;
			rightBottom[0].y = rc.top + 7 * height;

			rightBottom[1].x = rc.left + 9.5 * width;
			rightBottom[1].y = rc.top + 7 * height;

			rightBottom[2].x = rc.left + 9.5 * width;
			rightBottom[2].y = rc.top + 8.5 * height;
			
			rightBottom[3].x = rc.left + 8 * width;
			rightBottom[3].y = rc.top + 8.5 * height;
			/*-----------------------------------------------*/

			eyewidth = (4 * width) / 5;
			eyeheight = height / 3;

			eye1[0].x = leftTop[1].x + eyewidth;
			eye1[0].y = leftTop[1].y + eyeheight;

			eye1[1].x = leftTop[1].x + 2*eyewidth;
			eye1[1].y = leftTop[1].y + 2*eyeheight;
			
			eye2[0].x = leftTop[1].x + 3*eyewidth;
			eye2[0].y = leftTop[1].y + eyeheight;

			eye2[1].x = leftTop[1].x + 4 * eyewidth;
			eye2[1].y = leftTop[1].y + 2 * eyeheight;
			InvalidateRect(hWnd, NULL, TRUE);
			SetTimer(hWnd, MYTIMER, 1000, NULL);
			break;
		case WM_TIMER:
			KillTimer(hWnd, MYTIMER);
			InvalidateRect(hWnd, NULL, TRUE);
			SetTimer(hWnd, MYTIMER, 1000, NULL);
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			
			SelectObject(hdc,pen[0]);
			Arc(hdc, leftTop[3].x - 0.5*width , leftTop[3].y, leftBottom[3].x + 0.5*width, leftBottom[3].y, 
				leftTop[3].x, leftTop[3].y, leftBottom[3].x + 0.5 * width, leftBottom[3].y);

			Arc(hdc, leftTop[0].x - 0.5 * width, leftTop[0].y, leftBottom[0].x + 0.5 * width, leftBottom[0].y,
				leftTop[0].x, leftTop[0].y, leftBottom[0].x + 0.5 * width, leftBottom[0].y);
			SelectObject(hdc, pen[1]);
			Arc(hdc, rightTop[1].x - 0.5 * width, rightTop[1].y, rightBottom[1].x + 0.5 * width, rightBottom[1].y,
				rightBottom[1].x, rightBottom[1].y,rightTop[1].x - 0.5 * width, rightTop[1].y);

			Arc(hdc, rightTop[2].x - 0.5 * width, rightTop[2].y, rightBottom[2].x + 0.5 * width, rightBottom[2].y,
				rightBottom[2].x, rightBottom[2].y, rightTop[2].x - 0.5 * width, rightTop[2].y);
			SelectObject(hdc, pen[2]);
			Arc(hdc, leftTop[0].x, leftTop[0].y - 0.5 * height, rightTop[0].x, rightTop[0].y+ 0.5 * height,
				rightTop[0].x, rightTop[0].y + 0.5 * height,leftTop[0].x, leftTop[0].y);

			Arc(hdc, leftTop[1].x, leftTop[1].y - 0.5 * height, rightTop[1].x, rightTop[1].y + 0.5 * height,
				rightTop[1].x, rightTop[1].y + 0.5 * height, leftTop[1].x, leftTop[1].y);
			SelectObject(hdc, pen[3]);
			Arc(hdc, leftBottom[3].x, leftBottom[3].y - 0.5 * height, rightBottom[3].x, rightBottom[3].y + 0.5 * height,
				leftBottom[3].x, leftBottom[3].y, rightBottom[3].x, rightBottom[3].y - 0.5 * height);

			Arc(hdc, leftBottom[2].x, leftBottom[2].y - 0.5 * height, rightBottom[2].x, rightBottom[2].y + 0.5 * height,
				leftBottom[2].x, leftBottom[2].y, rightBottom[2].x, rightBottom[2].y - 0.5 * height);
			SelectObject(hdc, pen[4]);
			//SelectObject(hdc, CreateSolidBrush(RGB(0, 255, 255)));
			//Rectangle(hdc, leftTop[1].x, leftTop[1].y, rightTop[3].x, rightTop[3].y);
			temp.left = leftTop[1].x; temp.top = leftTop[1].y; temp.right = rightTop[3].x; temp.bottom = rightTop[3].y;
			FillRect(hdc, &temp, hbrush[9]);
			temp.left = leftTop[3].x; temp.top = leftTop[3].y; temp.right = leftBottom[1].x; temp.bottom = leftBottom[1].y;
			FillRect(hdc, &temp, hbrush[9]);
			temp.left = leftBottom[1].x; temp.top = leftBottom[1].y; temp.right = rightBottom[3].x; temp.bottom = rightBottom[3].y;
			FillRect(hdc, &temp, hbrush[9]);
			temp.left = rightTop[3].x; temp.top = rightTop[3].y; temp.right = rightBottom[1].x; temp.bottom = rightBottom[1].y;
			FillRect(hdc, &temp, hbrush[9]);

			SelectObject(hdc, hbrush[rand()%10]);
			Rectangle(hdc, leftTop[0].x, leftTop[0].y, leftTop[2].x, leftTop[2].y);
			Rectangle(hdc, rightTop[0].x, rightTop[0].y, rightTop[2].x, rightTop[2].y);
			Rectangle(hdc, leftBottom[0].x, leftBottom[0].y, leftBottom[2].x, leftBottom[2].y);
			Rectangle(hdc, rightBottom[0].x, rightBottom[0].y, rightBottom[2].x, rightBottom[2].y);

			//SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0)));
			//temp.left = leftTop[1].x; temp.top = leftTop[1].y; temp.right = rightTop[0].x; temp.bottom = rightTop[0].y;
			//FillRect(hdc, &temp, CreateSolidBrush(RGB(0, 0, 0)));
			//Rectangle(hdc, leftTop[1].x, leftTop[1].y, rightTop[0].x, rightTop[0].y);
			
			Ellipse(hdc, eye1[0].x, eye1[0].y, eye1[1].x, eye1[1].y);
			Ellipse(hdc, eye2[0].x, eye2[0].y, eye2[1].x, eye2[1].y);

			xwid = (rightTop[0].x - leftTop[1].x) / 22;
			yhig = (rightBottom[0].y - rightTop[3].y) / 9;
			MoveToEx(hdc, leftTop[1].x + 3 * xwid , rightTop[3].y +  yhig, NULL);
			LineTo(hdc, leftTop[1].x + 14 * xwid + 6 * xwid, rightTop[3].y + yhig);
			MoveToEx(hdc, leftTop[1].x + 5 * xwid , rightTop[3].y + 2* yhig, NULL);
			LineTo(hdc, leftTop[1].x + 14 * xwid + 4 * xwid, rightTop[3].y + 2 * yhig);
			for (int a = 2; a < 8;a++) {
				MoveToEx(hdc, leftTop[1].x + 3*xwid + a*2*xwid, rightTop[3].y + (a+1)*yhig, NULL);
				LineTo(hdc, leftTop[1].x + 14 * xwid + a*xwid, rightTop[3].y + (a + 1) * yhig);
			}

			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}