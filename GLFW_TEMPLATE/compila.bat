@echo off
g++ main.cpp -o main.exe -Iinclude -Llib -lglfw3 -lopengl32 -lgdi32
.\main.exe