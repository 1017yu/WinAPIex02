#include <windows.h>
#include "resource.h"
#include <iostream>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstanc, LPSTR lpCmdLine, int nShowCmd)

{
	char szTitle[] = "My First Window Program";
	char szClass[] = "Class";

	// 1. Declare window class -----------------------------------------------------

	WNDCLASSEX WndEx;
	WndEx.style = NULL; // window style
	WndEx.lpfnWndProc = WndProc; //window procedure(function) pointer
	WndEx.cbClsExtra = 0; //additional memory size for widow class
	WndEx.cbWndExtra = 0; // additional memory size for window
	WndEx.hInstance = hInstance; // intance handle of the window procdeure
	WndEx.hIcon = LoadIcon(NULL, ""); //big icon
	WndEx.hIconSm = LoadIcon(hInstance, ""); //small icon
	WndEx.hCursor = LoadCursor(NULL, IDC_ARROW);//cursor
	WndEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//background
	WndEx.lpszMenuName = "IDR_MENU";//menui
	WndEx.lpszClassName = szClass;//window class name
	WndEx.cbSize = sizeof(WndEx); //size of window class structure

	// 2. Register window calss -----------------------------------------------------

	RegisterClassEx(&WndEx);

	// 3. Create window -------------------------------------------------------------
	HWND hWnd;
	hWnd = CreateWindowEx(NULL, szClass, szTitle,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		320 * 2, 240 * 2, NULL, NULL, hInstance, NULL);

	// 4. Show and Update window-----------------------------------------------------

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	// 5. Message loop --------------------------------------------------------------

	MSG mSg;
	while (TRUE)
	{
		if (PeekMessage(&mSg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&mSg, NULL, 0, 0))
				break;
			TranslateMessage(&mSg);
			DispatchMessage(&mSg);
		}
	}
	return mSg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC = GetDC(hWnd);
	char szText1[] = "Left mouse button down";
	char szText2[] = "Left mouse button up";
	char szText3[] = "Right mouse button down";
	char szText4[] = "Right mouse button up";
	char szNewTitle[] = "This is a new title example";
	char szTextc[100];

	static char a = 0;
	static int x = 100, y = 100;
	static int keyflag = 0;
	static int nX, nY;

	PAINTSTRUCT pS;


	switch (uMsg)
	{
	case WM_MOUSEMOVE:
		nX = LOWORD(lParam);
		nY = HIWORD(lParam);
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);

		sprintf_s(szTextc, "Mouse X-Position: %d, Y-Position: %d", nX, nY);
		TextOut(hDC, nX, nY, szTextc, lstrlen(szTextc));
		//TextOut(hDC, 5, 100, szTextc, lstrlen(szTextc));
		return FALSE; // break

	case WM_LBUTTONDOWN:
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		TextOut(hDC, 5, 20, szText1, lstrlen(szText1)); 
		return FALSE;
		break;

	case WM_LBUTTONUP:
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		TextOut(hDC, 5, 20, szText2, lstrlen(szText2));
		return FALSE;
		break;

	case WM_RBUTTONDOWN:
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		TextOut(hDC, 5, 20, szText3, lstrlen(szText3));
		return FALSE;
		break;

	case WM_RBUTTONUP:
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		TextOut(hDC, 5, 20, szText4, lstrlen(szText4));
		return FALSE;
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case ID_FILE_BLACK:
			SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)GetStockObject(BLACK_BRUSH));
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case ID_FILE_WHITE:
			SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)GetStockObject(WHITE_BRUSH));
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;

		case ID_HELP_ABOUT:
			MessageBox(hWnd, "Window Menu Test message", "Output", NULL);
			break;
		}
		return FALSE;

	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
