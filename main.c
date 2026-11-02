#include <stdio.h>
#include <windows.h>

/*
TODO:
    Add randomness elements to avoid macro detection (duty cycle, speed variation by %) 
*/ 
COLORREF GetPixelRGB(int x, int y){
    HWND hwnd = FindWindow(NULL, "Minecraft*");
    HDC hdc = GetDC(hwnd);
    if (hdc == NULL){
        printf("Failed to get device context");
        return -1;
    }

    COLORREF pixel = GetPixel(hdc, x, y);
    ReleaseDC(hwnd, hdc);

    return pixel;

} 

COLORREF GetMousePixelRGB(){
    HDC hdc = GetDC(NULL);
    if (hdc == NULL){
        printf("Failed to get device context");
        return -1;
    }

    // printf("Press Enter to fetch RGB values.");
    // getc(stdin);

    POINT cursor;
    GetCursorPos(&cursor);

    COLORREF pixel = GetPixel(hdc, cursor.x, cursor.y);
    ReleaseDC(NULL, hdc);

    return pixel;
}

POINT GetMouseXYPos(){
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

void RightClick() {
    INPUT inputs[2] = {};

    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    
    SendInput(2, inputs, sizeof(INPUT));
}

int main(){
    COLORREF yellowValue = RGB(255, 222, 47);
    COLORREF redValue = RGB(255, 85, 85);

    printf("Press Enter with your mouse hovered over the pixel you'd lock to lock on.");
    getc(stdin);
    POINT cursor = GetMouseXYPos();
    printf("(%ld, %ld)\n", cursor.x, cursor.y);

    printf("Starting AutoFisher in 5...\n");
    Sleep(1000);
    for (int i = 4; i > 0; i--){
        printf("%d...\n", i);
        Sleep(1000);
    }


    while(true) {
        COLORREF pixelColor = GetPixelRGB(cursor.x, cursor.y);
        BYTE red = GetRValue(pixelColor); 
        BYTE green = GetGValue(pixelColor); 
        BYTE blue = GetBValue(pixelColor);

        printf("RGB values for (%d,%d) are (%d, %d, %d)\n",cursor.x, cursor.y, red, green, blue);
        if (pixelColor == yellowValue){
            printf("Yellow detected!\n");
        } 
        else if (pixelColor == redValue){
            printf("Red detected!\n");
        }
        Sleep(250);
    }
    return 0;
}

// PASS -lgdi32 FLAG TO THE COMPILER OR GetPixel() WONT WORKK