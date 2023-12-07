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