#include "graphics.h"
int rgb(int r, int g, int b) {
    return r << 11 | g << 5 | b;
}

void Draw(int x, int y, int r, int g, int b) {
    VBEInfoBlock* VBE = (VBEInfoBlock*) VBEInfoAddress;
    int index = y * VBE->x_resolution + x;
    *((unsigned short*) VBE->screen_ptr + index) = rgb(r, g, b);
}

void ClearScreen(int r, int g, int b) {
    VBEInfoBlock* VBE = (VBEInfoBlock*) VBEInfoAddress;
    for (int y = 0; y < VBE->y_resolution; y++) {
        for (int x = 0; x < VBE->x_resolution; x++) {
            Draw(x, y, r, g, b);
        }
    }

}

void DrawRect(int x, int y, int width, int height, int r, int g, int b) {
    for(int j = y; j < (j + height); j++) {
        for (int i = x; i < (i + width); i++) {
            Draw(i, j, r, g, b);
        }
    }
}

void DrawCharacter(int (*f)(int, int), int font_width, int font_height, char character, int x, int y, int r, int g, int b) {
    for (int j = 0; j < font_monospace_height; j++) {
        unsigned int row = getMonospaceCharacter((int) (character), j);
        int shift = font_width - 1;
        int bit_val = 0;

        for (int i = 0; i < font_monospace_width; i++) {
            bit_val = (row >> shift) & 0b00000000000000000000000000000001;
            if (bit_val == 1) 
                Draw(x + i, y + j, r, g, b);
            
            shift -=1;
        }
    }
}

void DrawString(int (*f)(int, int), int font_width, int font_height, char* string, int x, int y, int r, int g, int b) {
    int i = 0;
    int j = 0;

    for (int k = 0; *(string + k) != 0; k++) {
        if (*(string + k) != '\n') {
            DrawCharacter(f, font_width, font_height, *(string + k), x + i, y + j, r, g, b);
        }
        i += font_width;
        
        if (*(string + k) == '\n') {
            i = 0;
            j += font_height;
        }
    }
}