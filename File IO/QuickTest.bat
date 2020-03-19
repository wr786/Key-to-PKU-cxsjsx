@echo off
echo [INFO] Test Started.
g++ rotatebmp.cpp -o rotatebmp
echo [INFO] Compile Finished.
pause;
rotatebmp 1.bmp 1_rotated.bmp
rotatebmp 24.bmp 24_rotated.bmp
rotatebmp 32.bmp 32_rotated.bmp
echo [INFO] Test Finished.
pause;