#include <stdio.h>
#include <windows.h>

/*
TODO:
    1. Find specific pixel to use, and check if its color values are the specific shade of yellow or red
    2. Add mouse double clicking functionality
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

    POINT cursor;
    GetCursorPos(&cursor);

    printf("Press Enter to fetch RGB values and XY coordinates.");
    getc(stdin);

    COLORREF pixel = GetPixel(hdc, cursor.x, cursor.y);
    ReleaseDC(NULL, hdc);

    return pixel;
}

int main(){
    while(true){

        COLORREF yellowValue = RGB(255, 222, 47);
        COLORREF redValue = RGB(255, 85, 85);
        COLORREF pixel = GetMousePixelRGB();

        BYTE red = GetRValue(pixel); 
        BYTE green = GetGValue(pixel); 
        BYTE blue = GetBValue(pixel); 

        printf("(%d, %d, %d)\n", red, green, blue);
    }

    return 0;
}