#define _CRT_SECURE_NO_WARNINGS

// �C���N���[�h�t�@�C��
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>
#include "Manager.h"

static constexpr TCHAR szClassName[] = _T("�G���~�[�g�Ȑ�");

// �v���g�^�C�v
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int iCmdShow)
{
	HWND	hWnd;
	MSG		msg;
	int		frx, fry, cpy;

	// �E�B���h�E�N���X�̓o�^
	WNDCLASSEX wc;
	wc.cbSize			= sizeof(WNDCLASSEX);
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= WindowProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= szClassName;
	wc.hIconSm			= NULL;
	if (RegisterClassEx(&wc) == 0) return false;	// �E�B���h�E�N���X��o�^

	// �E�B���h�E���쐬
	frx = GetSystemMetrics(SM_CXFIXEDFRAME);
	fry = GetSystemMetrics(SM_CYFIXEDFRAME);
	cpy = GetSystemMetrics(SM_CYCAPTION);
	hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW, szClassName, _T("�G���~�[�g�Ȑ�"),
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH + frx * 2, SCREEN_HEIGHT + fry * 2 + cpy,
		NULL, NULL, hInstance, NULL);
	if (hWnd == NULL) return false;
	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Sleep(1);
	}
	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static auto manager = new Manager();

	switch (uMsg) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 20, NULL);
		return 0;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_TIMER:
		manager->update();
		InvalidateRect(hWnd, NULL, true);
		return 0;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			delete manager;
			DestroyWindow(hWnd);
		}
		else
		{
			manager->input(wParam);
		}
		break;
	case WM_PAINT:
		manager->draw(hWnd);
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}