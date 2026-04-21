@echo off
g++.exe -fdiagnostics-color=always -g main.cpp -o main.exe -Wl,-subsystem,windows -lglfw3 -lopengl32
.\main
