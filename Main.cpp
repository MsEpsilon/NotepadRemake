#include <Windows.h>

LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CLOSE:
		exit(0);
		return 0;
	default:
		return DefWindowProcA(hwnd, msg, wparam, lparam);
	}
}

constexpr const char* ClassName = "NotepadRemakeClass";

HWND window;
HWND textbox;


int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdArgs, int showWindow)
{
	WNDCLASSA wndclass{};
	wndclass.hInstance = instance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = ClassName;

	if (RegisterClassA(&wndclass) == 0) return -1;
	
	HMENU fileMenu = CreateMenu();
	if (fileMenu == nullptr) return -2;

	AppendMenuA(fileMenu, 0, 100, "New (Ctrl+N)");
	AppendMenuA(fileMenu, 0, 101, "New Window (Ctrl+Shift+N)");
	AppendMenuA(fileMenu, 0, 102, "Open (Ctrl+O)");
	AppendMenuA(fileMenu, 0, 103, "Save (Ctrl+S)");
	AppendMenuA(fileMenu, 0, 104, "Save As (Ctrl+Shift+S)");
	AppendMenuA(fileMenu, MF_MENUBARBREAK, 0, nullptr);
	
	HMENU mainMenu = CreateMenu();
	if (mainMenu == nullptr) return -3;

	AppendMenuA(mainMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(fileMenu), "File");
	AppendMenuA(mainMenu, MF_POPUP, 0, "Edit");
	AppendMenuA(mainMenu, MF_POPUP, 0, "Format");
	AppendMenuA(mainMenu, MF_POPUP, 0, "View");
	AppendMenuA(mainMenu, MF_POPUP, 0, "Help");

	window = CreateWindowExA(0, ClassName, "Notepad Remake", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, mainMenu, instance, nullptr);
	ShowWindow(window, SW_NORMAL);

	MSG msg;
	while (GetMessageA(&msg, window, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	return 0;
}