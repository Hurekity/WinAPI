// CTRL+T useful
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "resource.h"


CONST CHAR* g_sz_VALUES[] = { "This", "is", "my", "first", "Combo", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
		}
		SendMessage(hCombo, CB_SETCURSEL, 0, 0); // Choose zero element ComboBox
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0); // Number of chosen element in ComboBox
			CHAR sz_buffer[MAX_PATH]{};
			CHAR sz_message[MAX_PATH]{};
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
			sprintf(sz_message, "You chosed the case %i with value %s.", i, sz_buffer);
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
		}
			break;
		case IDC_BUTTON_ADD:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			// idk how to srite into file smth. do later;
			MessageBox(hwnd, 0, "Add text", MB_OKCANCEL);
		}
		case IDC_BUTTON_DELETE:
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
            // function to remove smth?
		}
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;
}