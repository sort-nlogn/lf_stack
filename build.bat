
@echo Compile programm...
@echo off
C:/TDM-GCC-64/bin/g++.exe -g .\LockFreeStack.cpp -g .\main.cpp -o .\main.exe
if %errorlevel% == 0 (@echo Build complete. Run application... && @echo off && .\main.exe)