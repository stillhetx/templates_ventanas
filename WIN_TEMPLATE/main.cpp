#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

int globalRunning = 1;

//int main(){return 0;}

LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam){
    LRESULT result;
    switch(message)
    {
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