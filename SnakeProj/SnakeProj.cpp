#include <iostream>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#include "Painter.h"
#include "Game.h"

using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")

#define GameSpeed 200

void RedrawGame(HDC hdc);
void InitializeGame(HWND hwnd);

Painter* p;
Game game;
int Tick = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	ULONG_PTR token;
	GdiplusStartupInput input = { 0 };
	input.GdiplusVersion = 1;
	GdiplusStartup(&token, &input, NULL);

	const wchar_t CLASS_NAME[] = L"Sample Window Class";
	WNDCLASS wc = {};
	wc.lpfnWndProc = &WindowProc;  // attach this callback procedure
	wc.hInstance = hInstance;      // handle to application instance
	wc.lpszClassName = CLASS_NAME;
	RegisterClass(&wc);  // register wc
	// Create the window.
	HWND hwnd = CreateWindowEx(0,     // Optional window styles.
		CLASS_NAME,                   // Window class
		L"Snake",  // Window text
		WS_OVERLAPPEDWINDOW,          // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, Field::WIDTH* Field::BLOCK_WIDTH,
		Field::HEIGHT* Field::BLOCK_HEIGHT,

		NULL,       // Parent window
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd != NULL)
	{
		ShowWindow(hwnd, nCmdShow);
		InitializeGame(hwnd);

		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(token);
	return 0;
}

// callback procedure for this window, takes in all the window details
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE: SetTimer(hwnd, 1, GameSpeed, NULL); break;
	case WM_TIMER: InvalidateRect(hwnd, NULL, FALSE); break;
	case WM_DESTROY: PostQuitMessage(0); return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		RedrawGame(hdc);
		EndPaint(hwnd, &ps);
		return 0;
	}

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT: game.keyEvent(Snake::LEFT); break;
		case VK_RIGHT: game.keyEvent(Snake::RIGHT); break;
		case VK_UP: game.keyEvent(Snake::UP); break;
		case VK_DOWN: game.keyEvent(Snake::DOWN); break;
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void RedrawGame(HDC hdc)
{
	p->background(0, 0, Field::WIDTH, Field::HEIGHT);
	game.tick();
	game.draw(*p);
}

void InitializeGame(HWND hwnd)
{
	p = new Painter(GetDC(hwnd));
}