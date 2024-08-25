#include "merge.hpp"
#include <cstring>

int Merge::merge_pic(const char* first_png, const char* second_png, const char* outcome_png) {

    //기존 이미지 정보 읽기
    FILE *origin = fopen(first_png, "rb");
    FILE *newone = fopen(second_png, "rb");

    png_structp origin_pic = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_structp newone_pic = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    png_infop origin_info = png_create_info_struct(origin_pic);
    png_infop newone_info = png_create_info_struct(newone_pic);


    png_init_io(origin_pic, origin);
    png_init_io(newone_pic, newone);

    png_read_info(origin_pic, origin_info);
    png_read_info(newone_pic, newone_info);

    origin_width = png_get_image_width(origin_pic, origin_info);
    origin_height = png_get_image_height(origin_pic, origin_info);



    // 이미지 합성하기
    row_pointers_origin = (png_bytep*)malloc(sizeof(png_bytep) * origin_height);
    row_pointers_new = (png_bytep*)malloc(sizeof(png_bytep) * origin_height);

    for (int y = 0; y < origin_height; y++) {
        row_pointers_origin[y] = (png_bytep)png_malloc(origin_pic, png_get_rowbytes(origin_pic, origin_info));
    }
    png_read_image(origin_pic, row_pointers_origin);

    for (int y = 0; y < origin_height; y++) {
        row_pointers_new[y] = (png_bytep)png_malloc(newone_pic, png_get_rowbytes(newone_pic, newone_info));
    }
    png_read_image(newone_pic, row_pointers_new);


    for (int y = 0; y < origin_height; y++) {
        row_origin = row_pointers_origin[y];
        row_new = row_pointers_new[y];
        for (int x = 0; x < origin_width * 4; x++) {
            if(row_new[x]!=0){
            row_origin[x] = row_new[x];}
        }
    }


    // 이미지 닫기
    png_destroy_read_struct(&origin_pic, &origin_info, NULL);
    png_destroy_read_struct(&newone_pic, &newone_info, NULL);
    fclose(origin);
    fclose(newone);



    // <new 이미지 저장하기>
    // new 이미지 열기
    FILE *outcome = fopen(outcome_png, "wb");
    if (!outcome) {
        printf("파일이 없습니다\n");
        return 1;
    }

    png_structp outcome_pic = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop outcome_info = png_create_info_struct(outcome_pic);


    png_init_io(outcome_pic, outcome);



    // new 이미지 쓰기

    png_set_IHDR(
        outcome_pic,
        outcome_info,
        origin_width, origin_height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );

    png_write_info(outcome_pic, outcome_info);

    for (int y = 0; y < origin_height; y++) {
        png_bytep row = row_pointers_origin[y];
        png_write_row(outcome_pic, row);
    }


    //new 이미지 닫기
    png_write_end(outcome_pic, NULL);
    png_destroy_write_struct(&outcome_pic, &outcome_info);

    for (int y = 0; y < origin_height; y++) {
        png_free(origin_pic, row_pointers_origin[y]);
        png_free(newone_pic, row_pointers_new[y]);
    }

    free(row_pointers_origin);
    free(row_pointers_new);

    fclose(outcome);

    return 0;
}