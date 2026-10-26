#include <stdio.h>
#include <windows.h>


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

    COLORREF pixel = GetPixel(hdc, cursor.x, cursor.y);
    ReleaseDC(NULL, hdc);
    return pixel;
}

int main(){
    // int x, y;
    // printf("Enter x pixel: ");
    // scanf("%d", &x);
    // printf("Enter y pixel: ");
    // scanf("%d", &y);

    while(1){
        COLORREF pixel = GetMousePixelRGB();

        BYTE red = GetRValue(pixel); 
        BYTE green = GetGValue(pixel); 
        BYTE blue = GetBValue(pixel); 

        printf("(%d, %d, %d)\n", red, green, blue);
    }

    return 0;
}