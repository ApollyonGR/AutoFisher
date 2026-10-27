#include <stdio.h>
#include <windows.h>

/*
TODO:
    1. Add mouse double clicking functionality 
    2. Change program to establish click-spot by waiting for user to click themselves in desired area 
    3. Add randomness elements to avoid macro detection (duty cycle, speed variation by %) 
*/ 
 COLORREF GetPixelRGB(int x, int y){
    HDC hdc = GetDC(NULL);
    if (hdc == NULL){
        printf("Failed to get device context");
        return -1;
    }

    COLORREF pixel = GetPixel(hdc, x, y);
    ReleaseDC(NULL, hdc);

    return pixel;

} 

COLORREF GetMousePixelRGB(){
    HDC hdc = GetDC(NULL);
    if (hdc == NULL){
        printf("Failed to get device context");
        return -1;
    }

    printf("Press Enter to fetch RGB values.");
    getc(stdin);

    POINT cursor;
    GetCursorPos(&cursor);

    COLORREF pixel = GetPixel(hdc, cursor.x, cursor.y);
    ReleaseDC(NULL, hdc);

    return pixel;
}

POINT GetMouseXYPos(){
    printf("Press Enter to fetch XY coordinates.");
    getc(stdin);

    POINT cursor;
    GetCursorPos(&cursor);
    
    return cursor; 
}

void LeftClick() {
    INPUT inputs[2] = {};

    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    
    SendInput(2, inputs, sizeof(INPUT));
}

int main(){
    
    while(true){
        COLORREF yellowValue = RGB(255, 222, 47);
        COLORREF redValue = RGB(255, 85, 85);

        // GetMouseXYPos();
        LeftClick();

        // COLORREF pixel = GetMousePixelRGB();
        // BYTE red = GetRValue(pixel); 
        // BYTE green = GetGValue(pixel); 
        // BYTE blue = GetBValue(pixel); 
        // printf("(%d, %d, %d)\n", red, green, blue);
    }

    return 0;
}