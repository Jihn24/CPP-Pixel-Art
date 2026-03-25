#include <windows.h>
#include <string>
#include <thread>
#include <vector>
#include <filesystem>
#include <direct.h>
#include "utilities.cpp"

global_variable bool running = true;

struct Render_State {
	int height, width;
	void* memory;

	BITMAPINFO bitmap_info;
};

global_variable Render_State render_state;


#include "platform_common.cpp"
#include "numbers_and_letters.cpp"
#include "renderer.cpp"
#include "classes.cpp"
#include "global_functions.cpp"
#include "instantiate_objects.cpp"
#include "save_and_load.cpp"
#include "inputs.cpp"
#include "buttons.cpp"
#include "graphics.cpp"





LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;

	// close the window when the cross is selected
	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY: {
		running = false;
	} break;

				   // if the window changes size, store the new size
	case WM_SIZE: {
		RECT rect;
		GetClientRect(hwnd, &rect);
		render_state.width = rect.right - rect.left;
		render_state.height = rect.bottom - rect.top;

		SetScreenWidth(render_state.width);
		SetScreenHeight(render_state.height);
		CreateInitialButtons();
		CreateUserColourButtons();
		CreateInitialSliders();
		CreateInitialTextMenus();
		CreateInitialNewColourBoxes();
		CreateInitialConfirmation();
		CreateBrush();
		CreateBrushOptions();
		CreateSelectOptions();
		paint_brush.RestoreBrush();
		int size = render_state.width * render_state.height * sizeof(u32);

		if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
		render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
		render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
		render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
		render_state.bitmap_info.bmiHeader.biPlanes = 1;
		render_state.bitmap_info.bmiHeader.biBitCount = 32;
		render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;
	} break;

	default: {
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
		   return result;
	}
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR	lpCmdLine, int nShowCmd) {
	// Create Window Class

	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = "Graphics Window Class";
	window_class.lpfnWndProc = window_callback;
	
	SetMatrixWidth(100);
	SetMatrixHeight(100);
	CreateMatrix();
	SetCursorOn(false);
	

	// Register Window
	RegisterClass(&window_class);

	// Create Window
	HWND window = CreateWindow(window_class.lpszClassName, "JS Paint", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	Input input = {};

	float delta_time = 0.01666666f;
	LARGE_INTEGER frame_begin_time;
	QueryPerformanceCounter(&frame_begin_time);

	float performance_frequency;
	{
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		performance_frequency = (float)perf.QuadPart;
	}

	//Create Save File Folder
	_mkdir("..\\Save_Files");

	while (running) {
		// Input
		MSG message;
		paint_brush.StoreBrush();
	

		if (GetCursorOn()) {
			ShowCursor(TRUE);
		}
		else {
			ShowCursor(FALSE);
		}

		SetScreenWidth(render_state.width);
		SetScreenHeight(render_state.height);

		for (int i = 0; i < BUTTON_COUNT; i++) {
			input.buttons[i].changed = false;
			while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {

				switch (message.message) {
					case WM_KEYUP:
					case WM_KEYDOWN: {
						u32 vk_code = (u32)message.wParam;
						bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b, vk)\
case vk: {\
input.buttons[b].changed = is_down != input.buttons[b].is_down;\
input.buttons[b].is_down = is_down;\
} break;

						switch (vk_code) {
							process_button(BUTTON_SPACE, VK_SPACE);
							process_button(BUTTON_LEFTCLICK, VK_LBUTTON);
							process_button(BUTTON_RIGHTCLICK, VK_RBUTTON);
							process_button(BUTTON_SHIFT, VK_SHIFT);
							process_button(BUTTON_BACKSPACE, VK_BACK);
							process_button(BUTTON_A, 'A');
							process_button(BUTTON_B, 'B');
							process_button(BUTTON_C, 'C');
							process_button(BUTTON_D, 'D');
							process_button(BUTTON_E, 'E');
							process_button(BUTTON_F, 'F');
							process_button(BUTTON_G, 'G');
							process_button(BUTTON_H, 'H');
							process_button(BUTTON_I, 'I');
							process_button(BUTTON_J, 'J');
							process_button(BUTTON_K, 'K');
							process_button(BUTTON_L, 'L');
							process_button(BUTTON_M, 'M');
							process_button(BUTTON_N, 'N');
							process_button(BUTTON_O, 'O');
							process_button(BUTTON_P, 'P');
							process_button(BUTTON_Q, 'Q');
							process_button(BUTTON_R, 'R');
							process_button(BUTTON_S, 'S');
							process_button(BUTTON_T, 'T');
							process_button(BUTTON_U, 'U');
							process_button(BUTTON_V, 'V');
							process_button(BUTTON_W, 'W');
							process_button(BUTTON_X, 'X');
							process_button(BUTTON_Y, 'Y');
							process_button(BUTTON_Z, 'Z');	
							process_button(BUTTON_0, '0');
							process_button(BUTTON_1, '1');
							process_button(BUTTON_2, '2');
							process_button(BUTTON_3, '3');
							process_button(BUTTON_4, '4');
							process_button(BUTTON_5, '5');
							process_button(BUTTON_6, '6');
							process_button(BUTTON_7, '7');
							process_button(BUTTON_8, '8');
							process_button(BUTTON_9, '9');
						} 
					} break;

					default: {
						TranslateMessage(&message);
						DispatchMessage(&message);
					}
				}
			}
		}

		// Simulate		
		SimulateGraphics(&input, delta_time);
		// Render
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
	
		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);
		delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performance_frequency;
		frame_begin_time = frame_end_time;
	}
}