#include <stdlib.h>
#include <stdio.h>
#include <png.h>

class Merge{
    private:
        int origin_width;
        int origin_height;
        png_bytep* row_pointers_origin;
        png_bytep* row_pointers_new;
        png_bytep row_origin;
        png_bytep row_new;
    public:
        int merge_pic(const char* first_png, const char* second_png, const char* outcome_png);
};