#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include<CommCtrl.h>
#include"resource.h"

#pragma comment(lib, "comctl32.lib")

CONST CHAR g_sz_WINDOW_CLASS[] = "My first Window";

TOOLINFO g_toolItem;
HWND g_hwndTrackingTT;
BOOL g_trackingMouse = FALSE;

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND CreateTrackingToolTip(INT	toolID, HWND hwnd, LPSTR lp_text);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) ����������� ������ ����:
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	//cb - Count Bytes
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = 0;
	//cb - Count Bites
	//wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	//wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hIcon = (HICON)LoadImage(hInstance, "earth.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "moon.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wc.hCursor = (HCURSOR)LoadImage(hInstance, "Background.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.lpszClassName = g_sz_WINDOW_CLASS;
	if (RegisterClassEx(&wc) == NULL)
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) �������� ����:
	//SM_ - System Metric;
	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);
	INT window_width = screen_width * 3 / 4;
	INT window_height = screen_height * 3 / 4;
	INT window_start_x = screen_width / 8;
	INT window_start_y = screen_height / 8;
	HWND hwnd = CreateWindowEx
	(
		NULL,	//ExStyles
		g_sz_WINDOW_CLASS,	//Class name
		g_sz_WINDOW_CLASS,	//��������� ����
		WS_OVERLAPPEDWINDOW,//����� ����� �������� �������� ����. ���� ����� ���������� ,
		//��� � ���� ����� ������ ���������, ������ ���������� �����, 
		//� ��c����������� �������.
		window_start_x, window_start_y,	//��������� ���� �� ������
		window_width, window_height,	//��������� ���� �� ������
		//CW_USEDEFAULT, CW_USEDEFAULT,	//������ ����
		//CW_USEDEFAULT, CW_USEDEFAULT,	//������ ����
		NULL,	//������������ ����
		NULL,	//��� �������� ���� ���� �������� ������ ����,
		//� ��� ��������� ���� - ID-������� ��������� ���� (IDC_BUTTON_COPY, IDC_EDIT...)
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//3) ������ ����� ���������:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		InitCommonControls();
		g_hwndTrackingTT = CreateTrackingToolTip(IDC_TOOLTIP, hwnd, (LPSTR)"");
		return TRUE;
	case WM_MOUSELEAVE:
		SendMessage(g_hwndTrackingTT, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)&g_toolItem);
		g_trackingMouse = FALSE;
		return FALSE;
	case WM_MOUSEMOVE:
		static INT oldX, oldY;
		INT newX, newY;
		if (!g_trackingMouse)
		{
			TRACKMOUSEEVENT tme = { sizeof(TRACKMOUSEEVENT) };
			tme.hwndTrack = hwnd;
			tme.dwFlags = TME_LEAVE;

			TrackMouseEvent(&tme);

			SendMessage(g_hwndTrackingTT, TTM_TRACKACTIVATE, (WPARAM)TRUE, (LPARAM)&g_toolItem);
			g_trackingMouse = TRUE;
		}
		newX = LOWORD(lParam);
		newY = HIWORD(lParam);

		if (newX != oldX || newY != oldY)
		{
			oldX = newX;
			oldY = newY;

			CHAR coords[12]{};
			sprintf(coords, "%ix%i", oldX, oldY);
			g_toolItem.lpszText = coords;
			SendMessage(g_hwndTrackingTT, TTM_SETTOOLINFO, 0, (LPARAM)&g_toolItem);

			POINT pt = { oldX, oldY };
			ClientToScreen(hwnd, &pt);
			SendMessage(g_hwndTrackingTT, TTM_TRACKPOSITION, 0, (LPARAM)MAKELONG(pt.x + 10, pt.y - 20));
		}
		return FALSE;
	case WM_SIZE:
	case WM_MOVING:
	{
		CONST INT SIZE = 256;
		CHAR sz_title[SIZE]{};
		RECT rect;
		GetWindowRect(hwnd, &rect);
		sprintf(sz_title, "%s Position:%ix%i, Size: %ix%i", g_sz_WINDOW_CLASS,
			rect.left, rect.top,
			rect.right - rect.left, rect.bottom - rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_title);
	}
	break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:PostQuitMessage(0); break;
	case WM_CLOSE:	DestroyWindow(hwnd); break;
	default:		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
HWND CreateTrackingToolTip(INT	toolID, HWND hwnd, LPSTR lpszText)
{
	HWND hwndTT = CreateWindowEx(
		WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
		WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		hwnd,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);
	if (hwndTT == NULL)
	{
		MessageBox(hwnd, "Tooltip creation failed", "Error", MB_OK | MB_ICONERROR);
		return NULL;
	}

	g_toolItem.cbSize = sizeof(TOOLINFO);
	g_toolItem.uFlags = TTF_IDISHWND | TTF_TRACK | TTF_ABSOLUTE;
	g_toolItem.hwnd = hwnd;
	g_toolItem.hinst = GetModuleHandle(NULL);
	g_toolItem.lpszText = lpszText;
	g_toolItem.uId = (UINT_PTR)hwnd;
	GetClientRect(hwnd, &g_toolItem.rect);

	//Associate the tooltip with the tool window.
	SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO)&g_toolItem);
	return hwndTT;
}