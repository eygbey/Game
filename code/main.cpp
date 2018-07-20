#define _WINSOCKAPI_

#pragma comment(lib, "ws2_32.lib")

#include <Windows.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>   // Needed for _wtoi

#include "opengl/ogllibrary.h"
#include "common/camera.h"
#include "common/input.h"

u32 running = 1;

typedef struct 
{
	GLWindow window;
	Input input;
	Mouse mouse;
} ApplicationState;

void process_application_inputs(ApplicationState* state)
{
	//unsigned int* key = &state->keys;
	//unsigned int* lock = &state->locks;

	MSG Message;

	while( PeekMessage(&Message, 0, 0, 0, PM_REMOVE) )
	{	
		ProcessInputFromPlatform(&state->input, &state->mouse, Message.message, Message.wParam, Message.lParam, state->window);

		switch(Message.message)
		{
			case WM_MOUSEMOVE:
			{
				POINT p;
				GetCursorPos(&p);
				ScreenToClient(state->window.handle_to_window, &p);

			} break;
			case WM_LBUTTONDOWN:
			{

			} break;
			case WM_LBUTTONUP:
			{

			} break;
			case WM_RBUTTONDOWN:
			{

			} break;
			case WM_RBUTTONUP:
			{

			} break;
			case WM_MOUSEWHEEL:
			{
				(float)GET_WHEEL_DELTA_WPARAM(Message.wParam);
			} break;
			case WM_CHAR:
			{

			}
			case WM_KEYDOWN:
		    {
		    	
		    } break;
		    case WM_KEYUP:
		    {
				
		    } break;
			default:
			{

			} break;
		}

		TranslateMessage(&Message);
	    DispatchMessageA(&Message);
	}
}

LRESULT CALLBACK MyWindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	LRESULT Result = 0;


	switch(Message)
    {
    	case WM_CREATE:
    	{
    		HDC dc = GetDC(Window);
    		SetupPixelFormat(dc);
    	} break;
    	case WM_DESTROY:
    	{
    		running = 0;
	        PostQuitMessage(WM_QUIT);
	        break;
	    }
		case WM_SIZE:
		{

			RECT ClientRect;
			GetClientRect(Window, &ClientRect);
			{
				unsigned int width = ClientRect.right - ClientRect.left;
				unsigned int height = ClientRect.bottom - ClientRect.top;

				glViewport(0, 0, width, height);
			}
		} break;
        default:
        {
			Result = DefWindowProc(Window, Message, WParam, LParam);
        } break;
    }

	return Result;
}

#include "game.h"

int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine, int ShowFlags)
{
	GLPlatform platform;
	platform.instance = Instance;

	ApplicationState state = {0};

	init_application();

	run_application(&state, platform);

	return 0;
}