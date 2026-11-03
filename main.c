#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/*
TODO:
    Add randomness elements to avoid macro detection (duty cycle, speed variation by %) 
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
    POINT cursor;
    GetCursorPos(&cursor);
    return cursor; 
}

void LeftClick() {
    // Create array for INPUT structure with space for 2 characters
    INPUT inputs[2] = {};

    // Assign character one the LeftDown flag
    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    // Assign character one the LeftUp flag
    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    
    // Sends the 'inputs' buffer with the SendInput function
    SendInput(2, inputs, sizeof(INPUT));
}

void RightClick() {
    // See LeftClick() for details
    INPUT inputs[2] = {};

    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    
    SendInput(2, inputs, sizeof(INPUT));
}

int GetRandomNumber(int min, int max){
    srand(time(NULL));
    int num = rand() % (max - min + 1) + min;
    return num;
}

int main(){
    COLORREF yellowValue = RGB(255, 222, 47);
    COLORREF redValue = RGB(255, 85, 85);

    printf("Press Enter with your mouse hovered over the pixel you'd lock to lock on.");
    getc(stdin);
    POINT cursor = GetMouseXYPos();
    printf("(%ld, %ld)\n", cursor.x, cursor.y);

    // Countdown
    printf("Starting AutoFisher in 5...\n");
    Sleep(1000);
    for (int i = 4; i > 0; i--){
        printf("%d...\n", i);
        Sleep(1000);
    }

    // Main loop
    while(true) {
        // Regrabs the chosen pixels RGB 
        COLORREF pixelColor = GetPixelRGB(cursor.x, cursor.y);

        if (pixelColor == yellowValue){
            printf("Yellow detected!\n");
        } 
        else if (pixelColor == redValue){
            printf("Red detected!\n");
        }
        Sleep(250); // Limits the program to checking every quarter second, can be changed to account for lag.
    }
    return 0;
}

// gcc main.c -o main.exe -lgdi32; .\main.exe