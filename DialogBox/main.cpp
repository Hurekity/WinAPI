#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//hwnd - ���� (Handler to Window - ���������� ����)
	//uMsg - ���������, ������� ���������� ����
	//wParam, lParam - ��������� ���������
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		//����� ����� ��������� �������� ����������.
		//��� ������ ������������ ���� ��� ��� ������� ����.
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
	}
	break;
	case WM_COMMAND:
		//����� �������������� ������� ������� ������, ��������� ������ � �.�.
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		case IDOK:		MessageBox(hwnd, "���� ������ ������ OK", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL:	EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:
		//����������� ��� ������� ������ "�������" (X)
		EndDialog(hwnd, 0);
	}
	return FALSE;
}