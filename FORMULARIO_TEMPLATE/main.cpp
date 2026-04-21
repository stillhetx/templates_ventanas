#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>

#define ID_BUTTON 1
#define ID_BUTTON_CLEAR 2
#define ID_TEXTBOX 3
#define ID_BUTTON_CLEAR_TEXT 4


static HWND windowTextBox;
static HWND windowTextStatic;


int globalRunning = 1;


LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam){
    LRESULT result;
    switch(message)
    {
        case WM_CREATE:
        {
            //Menu

            HMENU hMenuBar = CreateMenu();
            HMENU hFile = CreateMenu();
            HMENU hOption = CreateMenu();

            AppendMenu(hMenuBar,MF_POPUP,(UINT_PTR)hFile,L"File");
            AppendMenu(hMenuBar,MF_POPUP,2,L"Edit");
            AppendMenu(hMenuBar,MF_POPUP,(UINT_PTR)hOption,L"Options");

            AppendMenu(hFile,MF_STRING,2,L"Options");

            AppendMenu(hOption,MF_STRING,2,L"Option 1");
            AppendMenu(hOption,MF_STRING,2,L"Option 2");
            SetMenu(window,hMenuBar);

            // Text
            
            windowTextBox = CreateWindow(L"EDIT",L"valores",
            WS_VISIBLE | WS_CHILD | WS_BORDER  | ES_AUTOHSCROLL,
            10,50,200,20,
            window, (HMENU)NULL,NULL,NULL);
            
           windowTextStatic = CreateWindow(TEXT("STATIC"),TEXT("VALUE"),
            WS_CHILD | WS_VISIBLE| WS_BORDER,
            10,10,200,25,
            window,(HMENU)NULL,NULL,NULL);
          
            // EDIT

            // Boton
            CreateWindow(TEXT("BUTTON"),TEXT("ADD"),
            WS_CHILD|WS_VISIBLE,
            10,90,80,20,
            window,(HMENU)ID_BUTTON,NULL, NULL);

            CreateWindow(L"BUTTON",L"CLEAR",
            WS_CHILD|WS_VISIBLE,
            100,90,80,20,
            window,(HMENU)ID_BUTTON_CLEAR,NULL, NULL);

            CreateWindow(L"BUTTON",L"RESET",
            WS_CHILD|WS_VISIBLE,
            190,90,80,20,
            window,(HMENU)ID_BUTTON_CLEAR_TEXT,NULL, NULL);
            
        }break;
        case WM_COMMAND:
        {
            if(LOWORD(wParam)==ID_BUTTON){

                int len = GetWindowTextLength(windowTextBox)+1;
                static char title[500];
                GetWindowTextA(windowTextBox, title,len);
                SetWindowTextA(windowTextStatic,title);
                //MessageBoxA(windowTextBox,title, "Message Box",MB_OK);
            }

                if(LOWORD(wParam)==ID_BUTTON_CLEAR){

                int len = GetWindowTextLength(windowTextBox)+1;
                static char title[500];
                SetWindowTextA(windowTextStatic,title);
                //MessageBoxA(windowTextBox,title, "Message Box",MB_OK);
            }

                if(LOWORD(wParam)==ID_BUTTON_CLEAR_TEXT){

                int len = GetWindowTextLength(windowTextBox)+1;
                static char title[500];
                SetWindowTextA(windowTextBox,title);
                //MessageBoxA(windowTextBox,title, "Message Box",MB_OK);
            }

        }
        case WM_DESTROY:
        {

        }break;
        case WM_QUIT:
        {

        }
        break;
        case WM_CLOSE:
        {
            globalRunning = 0;
            
        }break;
        default:
        {
            result =    DefWindowProc(window,message, wParam,lParam);
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
  window_class.style=CS_DBLCLKS;

  window_class.hIcon=LoadIcon(NULL,IDI_APPLICATION);
  //window_class.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
  //window_class.hCursor=LoadIcon(NULL,IDI_APPLICATION);
  window_class.lpszMenuName= NULL;
  window_class.cbClsExtra =0;
  window_class.cbWndExtra =0;

  window_class.hbrBackground=(HBRUSH) COLOR_BACKGROUND;

  RegisterClass(&window_class);

  HWND window = CreateWindowEx(
                        0,
                        CLASS_NAME,
                        L"game",
                        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
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
        while(PeekMessage(&message,NULL,0,0,PM_REMOVE)){
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
  }
return 0;

//  MSG message;

// while(GetMessage(&message,NULL,0,0)){

//     TranslateMessage(&message);
//     DispatchMessage(&message);
// }
// return 0;

}