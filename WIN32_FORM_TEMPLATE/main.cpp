#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#define ID_BUTTON 1

int globalRunning = 1;


LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam){
    LRESULT result;
    switch(message)
    {
        case WM_CREATE:
        {
            CreateWindow(TEXT("BUTTON"),TEXT("button"),
            WS_CHILD|WS_VISIBLE,
            10,10,80,20,
            window,(HMENU)ID_BUTTON,NULL, NULL);

        }break;
        case WM_COMMAND:
        {
            if(LOWORD(wParam)==ID_BUTTON){

                MessageBoxA(window,"boton", "titulo Boton",MB_ICONINFORMATION);
            }
        }
        case WM_CLOSE:
        {
            globalRunning = 0;
        }break;
        default:
        {
            result = 
                DefWindowProc(window,message, wParam,lParam);
        }break;
    }
    return result;
}


int WINAPI wWinMain(HINSTANCE Instance,
                     HINSTANCE PrevInstance, 
                     PWSTR CmdLine, 
                     int CmdShow)
{
  WNDCLASS window_class= {0};

  wchar_t CLASS_NAME[]=L"GameWindowClass";

  window_class.lpfnWndProc = WindowProc;
  window_class.hInstance = Instance;
  window_class.lpszClassName=CLASS_NAME;

  RegisterClass(&window_class);

  HWND window = CreateWindowEx(
                        0,
                        CLASS_NAME,
                        L"game",
                        WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        0,
                        0,
                        Instance,
                        0);

  while(globalRunning)
  {
    MSG message;
        while(PeekMessage(&message,window,0,0,PM_REMOVE)){
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
  }
return 0;

}