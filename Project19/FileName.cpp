#include <windows.h>
#include "windowsx.h"
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CheckForWin(HWND hWnd);
BOOL IsWinner(HWND hWnd, int b1, int b2, int b3);
BOOL IsBoardFull(HWND hWnd);
BOOL IsXWinner(HWND hWnd, int b1, int b2, int b3);
BOOL IsOWinner(HWND hWnd, int b1, int b2, int b3);
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	static HBITMAP hBitmap;
	static HBITMAP hBitmap2;
	static BOOL bTurn = true;
	static INT count = 0;
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wp) >= IDC_BUTTON1 && LOWORD(wp) <= IDC_BUTTON9 && HIWORD(wp) == BN_CLICKED)
		{
			if (!IsBoardFull(hWnd))
			{
				HWND hButton = GetDlgItem(hWnd, LOWORD(wp));
				HBITMAP hCurrentBitmap = (HBITMAP)SendMessage(hButton, BM_GETIMAGE, IMAGE_BITMAP, 0);
				if (!hCurrentBitmap)
				{
					if (bTurn)
					{
						hBitmap2 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP3));
						SendDlgItemMessage(hWnd, LOWORD(wp), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap2);
						EnableWindow(GetDlgItem(hWnd, LOWORD(wp)), FALSE);
						count++;
						bTurn = false;
					}
					else
					{
						hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));
						SendDlgItemMessage(hWnd, LOWORD(wp), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
						EnableWindow(GetDlgItem(hWnd, LOWORD(wp)), FALSE);
						count++;
						bTurn = true;
					}

					if (count >= 6)
					{
						if (IsXWinner(hWnd, IDC_BUTTON1, IDC_BUTTON2, IDC_BUTTON3) ||
							IsXWinner(hWnd, IDC_BUTTON4, IDC_BUTTON5, IDC_BUTTON6) ||
							IsXWinner(hWnd, IDC_BUTTON7, IDC_BUTTON8, IDC_BUTTON9) ||
							IsXWinner(hWnd, IDC_BUTTON1, IDC_BUTTON4, IDC_BUTTON7) ||
							IsXWinner(hWnd, IDC_BUTTON2, IDC_BUTTON5, IDC_BUTTON8) ||
							IsXWinner(hWnd, IDC_BUTTON3, IDC_BUTTON6, IDC_BUTTON9) ||
							IsXWinner(hWnd, IDC_BUTTON1, IDC_BUTTON5, IDC_BUTTON9) ||
							IsXWinner(hWnd, IDC_BUTTON3, IDC_BUTTON5, IDC_BUTTON7))
						{
							MessageBox(hWnd, L"Победа крестиков!", L"Победа", MB_OK | MB_ICONINFORMATION);
							EndDialog(hWnd, 0);
						}
						else if (IsOWinner(hWnd, IDC_BUTTON1, IDC_BUTTON2, IDC_BUTTON3) ||
							IsOWinner(hWnd, IDC_BUTTON4, IDC_BUTTON5, IDC_BUTTON6) ||
							IsOWinner(hWnd, IDC_BUTTON7, IDC_BUTTON8, IDC_BUTTON9) ||
							IsOWinner(hWnd, IDC_BUTTON1, IDC_BUTTON4, IDC_BUTTON7) ||
							IsOWinner(hWnd, IDC_BUTTON2, IDC_BUTTON5, IDC_BUTTON8) ||
							IsOWinner(hWnd, IDC_BUTTON3, IDC_BUTTON6, IDC_BUTTON9) ||
							IsOWinner(hWnd, IDC_BUTTON1, IDC_BUTTON5, IDC_BUTTON9) ||
							IsOWinner(hWnd, IDC_BUTTON3, IDC_BUTTON5, IDC_BUTTON7))
						{
							MessageBox(hWnd, L"Победа кружков!", L"Победа", MB_OK | MB_ICONINFORMATION);
							EndDialog(hWnd, 0);
						}
						else if (IsBoardFull(hWnd))
						{
							MessageBox(hWnd, L"Ничья!", L"Результат", MB_OK | MB_ICONINFORMATION);
							EndDialog(hWnd, 0);
						}
					}
				}
			}
			return TRUE;
		}
		break;

	}
	return FALSE;
}

BOOL CheckForWin(HWND hWnd)
{
	if (IsWinner(hWnd, IDC_BUTTON1, IDC_BUTTON2, IDC_BUTTON3) ||
		IsWinner(hWnd, IDC_BUTTON4, IDC_BUTTON5, IDC_BUTTON6) ||
		IsWinner(hWnd, IDC_BUTTON7, IDC_BUTTON8, IDC_BUTTON9) ||
		IsWinner(hWnd, IDC_BUTTON1, IDC_BUTTON4, IDC_BUTTON7) ||
		IsWinner(hWnd, IDC_BUTTON2, IDC_BUTTON5, IDC_BUTTON8) ||
		IsWinner(hWnd, IDC_BUTTON3, IDC_BUTTON6, IDC_BUTTON9) ||
		IsWinner(hWnd, IDC_BUTTON1, IDC_BUTTON5, IDC_BUTTON9) ||
		IsWinner(hWnd, IDC_BUTTON3, IDC_BUTTON5, IDC_BUTTON7))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL IsWinner(HWND hWnd, int b1, int b2, int b3)
{
	HWND hButton1 = GetDlgItem(hWnd, b1);
	HWND hButton2 = GetDlgItem(hWnd, b2);
	HWND hButton3 = GetDlgItem(hWnd, b3);

	HBITMAP hBitmap1 = (HBITMAP)SendMessage(hButton1, BM_GETIMAGE, IMAGE_BITMAP, 0);
	HBITMAP hBitmap2 = (HBITMAP)SendMessage(hButton2, BM_GETIMAGE, IMAGE_BITMAP, 0);
	HBITMAP hBitmap3 = (HBITMAP)SendMessage(hButton3, BM_GETIMAGE, IMAGE_BITMAP, 0);

	if (hBitmap1 && hBitmap2 && hBitmap3 &&
		hBitmap1 == hBitmap2 && hBitmap1 == hBitmap3)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL IsBoardFull(HWND hWnd)
{
	for (int i = IDC_BUTTON1; i <= IDC_BUTTON9; ++i)
	{
		HWND hButton = GetDlgItem(hWnd, i);
		HBITMAP hBitmap = (HBITMAP)SendMessage(hButton, BM_GETIMAGE, IMAGE_BITMAP, 0);
		if (!hBitmap)
		{
			return FALSE;
		}
	}
	return TRUE;
}
BOOL IsXWinner(HWND hWnd, int b1, int b2, int b3)
{
	HWND hButton1 = GetDlgItem(hWnd, b1);
	HWND hButton2 = GetDlgItem(hWnd, b2);
	HWND hButton3 = GetDlgItem(hWnd, b3);

	HBITMAP hBitmap1 = (HBITMAP)SendMessage(hButton1, BM_GETIMAGE, IMAGE_BITMAP, 0);
	HBITMAP hBitmap2 = (HBITMAP)SendMessage(hButton2, BM_GETIMAGE, IMAGE_BITMAP, 0);
	HBITMAP hBitmap3 = (HBITMAP)SendMessage(hButton3, BM_GETIMAGE, IMAGE_BITMAP, 0);

	if (hBitmap1 && hBitmap2 && hBitmap3 &&
		hBitmap1 == hBitmap2 && hBitmap1 == hBitmap3 && hBitmap1 == hBitmap2)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL IsOWinner(HWND hWnd, int b1, int b2, int b3)
{
	HWND hButton1 = GetDlgItem(hWnd, b1);
	HWND hButton2 = GetDlgItem(hWnd, b2);
	HWND hButton3 = GetDlgItem(hWnd, b3);

	HBITMAP hBitmap1 = (HBITMAP)SendMessage(hButton1, BM_GETIMAGE, IMAGE_BITMAP, 0);
	HBITMAP hBitmap2 = (HBITMAP)SendMessage(hButton2, BM_GETIMAGE, IMAGE_BITMAP, 0);
	HBITMAP hBitmap3 = (HBITMAP)SendMessage(hButton3, BM_GETIMAGE, IMAGE_BITMAP, 0);

	if (hBitmap1 && hBitmap2 && hBitmap3 &&
		hBitmap1 == hBitmap2 && hBitmap1 == hBitmap3 && hBitmap1 == hBitmap2)
	{
		return TRUE;
	}

	return FALSE;
}
