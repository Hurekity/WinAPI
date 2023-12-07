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
	//hwnd - окно (Handler to Window - обработчик окна)
	//uMsg - сообщение, которое передается окну
	//wParam, lParam - параметры сообщения
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		//Здесь можно создавать элементы интерфейса.
		//Эта секция отрабатывает один раз при запуске окна.
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
	}
	break;
	case WM_COMMAND:
		//Здесь обрабатываются команды нажатия кнопок, сочетания клавиш и т.д.
		switch (LOWORD(wParam))
		{
		case IDOK:		MessageBox(hwnd, "Была нажата кнопка OK", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL:	EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:
		//Отабатывает при нажатии кнопки "Закрыть" (X)
		EndDialog(hwnd, 0);
	}
	return FALSE;
}