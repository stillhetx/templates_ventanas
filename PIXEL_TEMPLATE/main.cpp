#ifndef UNICODE
#define UNICODE
#endif 


#define COLUMNS 10
#define ROWS 10

#include <windows.h>
#include <stdint.h>
#include <iostream>
#include <cmath>


#define u32 uint32_t

struct v2
{
    float x, y;
    v2& operator*=(float a);
    v2& operator+=(v2 a);
};

v2 operator*(float a, v2 b)
{
    v2 result;
    result.x = a * b.x;
    result.y = a * b.y;
    return result;
}

v2& v2::operator*=(float a)
{
    *this = a * *this;
    return *this;
}

v2 operator+(v2 a, v2 b)
{
    v2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

v2& v2::operator+=(v2 a)
{
    *this = *this + a;
    return *this;
}

    int globalRunning = 1;

    int client_width = 640;
    int client_height = 640;

    int init_start=0;

    v2 player;
    v2 d_player;

    int moving_left;
    int moving_right;
    int moving_up;
    int moving_down;

    int mov_player=10;
    int tile_size = 25;


    int level[COLUMNS * ROWS] = {
    1,1,0,0,0,0,0,0,0,0,
    0,1,1,0,0,0,0,0,0,0,
    0,0,1,1,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,1,1,1,1,1,
    0,0,0,0,0,2,0,0,0,0,
    0,0,0,0,0,1,0,0,0,0,
    0,0,0,0,0,1,0,0,0,0,
    0,0,0,0,0,1,0,0,0,0,
    0,0,0,0,0,1,0,0,0,0
};


    int character[25] = {
    0,0,2,0,0,
    0,1,1,1,0,
    2,1,2,1,2,
    0,1,1,1,0,
    0,0,2,0,0,
};

void* memory;
BITMAPINFO bitmap_info;


float target_seconds_per_frame = 1.0f / 120.0f;

LARGE_INTEGER frequency;

//Declare Functions 

void draw_rectangle_tile(int rec_x, int rec_y, int rec_width, int rec_height, u32 color);
int player_can_move(int x, int y);
float get_seconds_per_frame(LARGE_INTEGER start_counter,     LARGE_INTEGER end_counter);
void clear_Screen(u32 color);
float distance_point(int x1, int y1, int x2, int y2);
void draw_rectancle(int rec_x, int rec_y, int rec_width, int rec_height, u32 color);
void draw_level(int *level);
void draw_rectangle_tile(int rec_x, int rec_y, int rec_width, int rec_height, u32 color);
void draw_rect_pyxel(int xi, int yi, int width, int height, u32 color);
void draw_pixel(int x, int y,u32 color);


//metodos

//Dibujar circulo
void draw_circle_pyxel(int xi, int yi, int radio, u32 color){
    int diametro = radio * 2;
    for(int y = yi;  y < yi+diametro;  ++y)
    {
        for(int x = xi; x < xi+diametro; ++x)
        {
            if(distance_point(x,y,xi+radio,yi+radio)<radio){
                draw_pixel(x, y, color);
            }
        }        
    }
}


void draw_array_sprite(int xi, int yi, int spr[], int hi, int wi,int size){
    int pos = 0;
    
    for(int y = yi;  y < yi+hi;  ++y)
    {
        for(int x = xi; x < xi+wi; ++x)
        {
            if(spr[pos]==1){
                draw_rect_pyxel(x*size,y*size,size,size,0x323232);
            }
            if(spr[pos]==2){
                draw_rect_pyxel(x*size,y*size,size,size,0x696969);                
            }
            pos++;
        }        
    }

}

void update(float dt){

        float speed = 250.0f;   

        if(moving_right) d_player.x = 1.0f;
        if(moving_left) d_player.x = -1.0f;
        if(moving_up) d_player.y = 1.0f;
        if(moving_down) d_player.y = -1.0f;
        
        d_player *= speed;
        
        if(d_player.x != 0.0f && d_player.y != 0.0f)
        {
            d_player *= 0.707f;
        }

        player += dt * d_player;    
        /*
           if(player_can_move(d_player.x, d_player.y))
            {
                player += dt * d_player;
            }
        */
        d_player.x = 0.0f;
        d_player.y = 0.0f;

}


void draw(float dt){

    clear_Screen(0x111111);

    //draw_rect_pyxel
    
    /*
    draw_rectancle(100,100,50,50,0X222222);
    draw_rectancle(150,150,25,25,0X333333);
    draw_rectancle(175,175,15,15,0X444444);
    */

    draw_rect_pyxel(100,100,50,50,0X222222);
    draw_rect_pyxel(150,150,25,25,0X333333);
    draw_rect_pyxel(175,175,15,15,0X444444);
    
    draw_circle_pyxel(player.x,player.y,30,0xff20f7);


    draw_array_sprite(50,50,character,5,5,5);

      // draw_rect_pyxel(player.x, player.y,15,15,0X444444);


    //draw_rectancle( player.x, player.y, tile_size, tile_size, 0xff00f7);

}


void init(float dt){

}



int player_can_move(int x, int y)
{
    int result = 1;
    
    if(x < 0 | y < 0 | x >= COLUMNS | y >= ROWS) result = 0;
    
    int tile_type = level[(ROWS - 1 - y) * COLUMNS + x];
    
    if(tile_type == 1) result = 0;
    
    return result;
}


float get_seconds_per_frame(LARGE_INTEGER start_counter,
                            LARGE_INTEGER end_counter)
{
    
    return ((float)(end_counter.QuadPart - start_counter.QuadPart) / (float)frequency.QuadPart);
}

void clear_Screen(u32 color){
        u32* pixel=(u32 *)memory;

    for(int pixel_number =0;pixel_number<client_width*client_height;pixel_number++){
        *pixel++=color;
    }

    u32 red=0xFF0000;
    u32 green=0x00FF00;
    u32 blue=0x0000FF;
}

float distance_point(int x1, int y1, int x2, int y2)
{
	// Calculating distance
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

// Dibuja un rectangulo



void draw_rectancle(int rec_x,
                    int rec_y,
                    int rec_width,
                    int rec_height,
                    u32 color){

       u32* pixel=(u32 *)memory;             
       pixel += rec_y * client_width + rec_x;
                                              
       for(int y=0;y<rec_height;++y)         
       {                                     
           for(int x=0;x<rec_width;++x)      
               {                             
                 *pixel++ = color;         
              }                             
          pixel += client_width-rec_width;  
                                              
      }          
}



void draw_pixel(int x, int y, u32 color){
    u32* pixel=(u32 *)memory; 
    pixel += y * client_width + x;
        *pixel++ = color;
}


void draw_rect_pyxel(int xi, int yi, int width, int height, u32 color){
    for (int x=xi; x<xi+width;x++){
        for (int y=yi; y<yi+height;y++){
            draw_pixel(x, y, color);
        }
    }
}

void draw_level(int *level)
{
    for(int y = 0;
        y < ROWS;
        ++y)
    {
        for(int x = 0;
            x < COLUMNS;
            ++x)
        {
            
            int tile_type = level[(ROWS - 1 - y) * COLUMNS + x];
            
            if(tile_type != 0)
            {
                u32 color = 0x222222;
                
                if(tile_type == 2) color = 0x444444;
                
                draw_rectangle_tile(x, y, 
                                    tile_size, tile_size, 
                                    color);
            }
        }
    }
}

void draw_rectangle_tile(int rec_x,
                         int rec_y,
                         int rec_width,
                         int rec_height,
                         u32 color)
{
    u32 *pixel = (u32 *)memory;
    pixel += (rec_y * client_width * tile_size) + (rec_x * tile_size); 
    
    for(int y = 0;
        y < rec_height;
        ++y)
    {
        for(int x = 0;
            x < rec_width;
            ++x)
        {
            *pixel++ = color;
        }
        
        pixel += client_width - rec_width;
    }
}





LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam){
    LRESULT result;
    switch(message)
    {
        case WM_CLOSE:
        {
            globalRunning = 0;
        }break;



        case WM_KEYUP:
        {
            switch(wParam)
            {
                case VK_RIGHT:
                {
                    moving_right = 0;
                } break;
                
                case VK_LEFT:
                {
                    moving_left = 0;
                } break;
                
                case VK_UP:
                {
                    moving_up = 0;
                } break;
                
                case VK_DOWN:
                {
                    moving_down = 0;
                } break;
            }
        } break;
                
        

        case WM_KEYDOWN:
        {
            switch(wParam)
            {
                case VK_RIGHT:
                {
                    if(!moving_right) moving_right = 1;
                } break;
                
                case VK_LEFT:
                {
                    if(!moving_left) moving_left = 1;
                } break;
                
                case VK_UP:
                {
                    if(!moving_up) moving_up = 1;
                } break;
                
                case VK_DOWN:
                {
                    if(!moving_down) moving_down = 1;
                } break;
            }
        } break;

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
    //Inicia La ventana
  WNDCLASS window_class= {0};

  wchar_t CLASS_NAME[]=L"GameWindowClass";

  window_class.lpfnWndProc = WindowProc;
  window_class.hInstance = Instance;
  window_class.lpszClassName=CLASS_NAME;
  window_class.hCursor = LoadCursor(0,IDC_CROSS); //Cursor

RECT window_rect;
window_rect.left = 0;
window_rect.top = 0;
window_rect.right = client_width;
window_rect.bottom = client_height;

  AdjustWindowRectEx(
  &window_rect,
  WS_EX_OVERLAPPEDWINDOW,
  0,
  0);

int window_width = window_rect.right - window_rect.left;
int window_height = window_rect.bottom - window_rect.top;

int screen_width = GetSystemMetrics(SM_CXSCREEN);
int screen_height = GetSystemMetrics(SM_CYSCREEN);

int window_X = (screen_width/2) - (window_width/2);
int window_y = (screen_height/2) - (window_height/2);


  RegisterClass(&window_class);

  HWND window = CreateWindowEx(
                        0,
                        CLASS_NAME,
                        L"game",
                        WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        window_width,
                        window_height,
                        0,
                        0,
                        Instance,
                        0);
    RECT rect;
    GetClientRect(window, &rect);
    client_width = rect.right-rect.left;
    client_height = rect.bottom-rect.top;

    memory=  VirtualAlloc(0,
                            client_width*client_height*4,
                            MEM_RESERVE|MEM_COMMIT,
                            PAGE_READWRITE);



    bitmap_info.bmiHeader.biSize=sizeof(bitmap_info.bmiHeader);
    bitmap_info.bmiHeader.biWidth=client_width;
    bitmap_info.bmiHeader.biHeight=client_height;
    bitmap_info.bmiHeader.biPlanes=1;
    bitmap_info.bmiHeader.biBitCount=32;
    bitmap_info.bmiHeader.biCompression=BI_RGB;
   

  HDC hdc = GetDC (window); 


    LARGE_INTEGER start_counter, end_counter, counts, fps, ms;
    
    QueryPerformanceCounter(&start_counter);
    
    QueryPerformanceFrequency(&frequency);           
  
  while(globalRunning)
  {
    MSG message;
        while(PeekMessage(&message,window,0,0,PM_REMOVE)){
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        //Calculate y limitar frame
        
        QueryPerformanceCounter(&end_counter);
        
        float seconds_per_frame = get_seconds_per_frame(start_counter,
                                                        end_counter);
        
        if(seconds_per_frame < target_seconds_per_frame)
        {
            DWORD sleep_ms;            
            sleep_ms = (DWORD)(1000 * (target_seconds_per_frame - seconds_per_frame));            
            Sleep(sleep_ms);
            
            while(seconds_per_frame < target_seconds_per_frame)
            {
                QueryPerformanceCounter(&end_counter);
                
                seconds_per_frame = get_seconds_per_frame(start_counter,
                                                          end_counter);
            }
        }
        
        QueryPerformanceCounter(&end_counter);
        
        seconds_per_frame = get_seconds_per_frame(start_counter,
                                                  end_counter);
        
        start_counter = end_counter;

        float dt = seconds_per_frame;

        // kaslasl

        //   draw_level(level);
        
       /* 
       draw_rectangle_tile(player.x, 
                            player.y, 
                            tile_size, 
                            tile_size, 
                            0xff00f7);
        */
        // Movimiento
        if(init_start==0){
            init_start=1;
            init(dt);
        }

        update(dt);
        draw(dt);                    

    StretchDIBits(
                    hdc,
                    0,
                    0,
                    client_width,
                    client_height,
                    0,
                    0,
                    client_width,
                    client_height,
                    memory,
                    &bitmap_info,
                    DIB_RGB_COLORS,
                    SRCCOPY
                    );    
  }
return 0;

}
