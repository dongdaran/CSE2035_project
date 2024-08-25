
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <string.h>

#define PNG_SETJMP_NOT_SUPPORTED
#include <png.h>
#define COLOR_DEPTH 8
#define WIDTH 500
#define HEIGHT 700

using namespace std;

class Draw{
private:
    struct Pixel{
        png_byte r, g, b, a;
    };
    struct Pixel hex_go_RGB(const char* hex) {
        struct Pixel color;
        if (strlen(hex) != 7 || hex[0] != '#') {
        color.r = 255;
        color.g = 255;
        color.b = 255;
        return color;
        }
        sscanf(hex + 1, "%02hhx%02hhx%02hhx", &color.r, &color.g, &color.b);
        color.a = 255;
        return color;
    }

    struct Point {
        int x;
        int y;
    };

public:
    void draw_perfect_Tri(Pixel** row_pointer_input, int x_center, int y_center, int length, Pixel color_input);
    void draw_Circle(Pixel** row_pointer_input, int x_center, int y_center, int radius, Pixel color_input);
    void draw_Rectangle(Pixel** row_pointer_input, int x_center, int y_center, int x_length, int y_length, Pixel color_input);
    void draw_tree(Pixel** row_pointer_input);
    void draw_ballon(Pixel** row_pointer_input,int x_center, int y_center);
    void draw_bear(Pixel** row_pointer_input,int x_center, int y_center);
    void draw_cat(Pixel** row_pointer_input,int x_center, int y_center);
    void draw_cross(Pixel** row_pointer_input,int x_center, int y_center);
    void draw_present(Pixel** row_pointer_input,int x_center, int y_center);
    void draw_Santa(Pixel** row_pointer_input,int x_center, int y_center);
    void draw_start();
    void select_deco(Pixel ** row_pointer_input);

};