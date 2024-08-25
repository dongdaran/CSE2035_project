#include "merge.hpp"
#include <cstring>

int Merge::merge_pic(const char* base_png, const char* top_png, const char* output_file) {

    char base_file[256];  // 기존 이미지
    char top_file[256]; // 위에 덧씌울 이미지

    strncpy(base_file, base_png, sizeof(base_file) - 1);
    base_file[sizeof(base_file) - 1] = '\0';  // 문자열 끝에 NULL 문자 추가

    strncpy(top_file, top_png, sizeof(top_file) - 1);
    top_file[sizeof(top_file) - 1] = '\0';


    FILE *base = fopen(base_file, "rb");
    FILE *top = fopen(top_file, "rb");

    if (!base || !top) {
        printf("파일이 없습니다\n");
        return 1;
    }

    png_structp base_pic = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_structp top_pic = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!base_pic || !top_pic) {
        printf("png_create_read_struct 오류\n");
        fclose(base);
        fclose(top);
        return 1;
    }

    png_infop base_info = png_create_info_struct(base_pic);
    png_infop top_info = png_create_info_struct(top_pic);

    if (!base_info || !top_info) {
        printf("png_create_info_struct 오류\n");
        png_destroy_read_struct(&base_pic, NULL, NULL);
        png_destroy_read_struct(&top_pic, NULL, NULL);
        fclose(base);
        fclose(top);
        return 1;
    }

    if (setjmp(png_jmpbuf(base_pic)) || setjmp(png_jmpbuf(top_pic))) {
        printf("오류 발생\n");
        png_destroy_read_struct(&base_pic, &base_info, NULL);
        png_destroy_read_struct(&top_pic, &top_info, NULL);
        fclose(base);
        fclose(top);
        return 1;
    }

    png_init_io(base_pic, base);
    png_init_io(top_pic, top);

    png_read_info(base_pic, base_info);
    png_read_info(top_pic, top_info);

    int base_width = png_get_image_width(base_pic, base_info);
    int base_height = png_get_image_height(base_pic, base_info);

    int top_height = png_get_image_height(top_pic, top_info);


    // 이미지 합성
    int max_height = (base_height > top_height) ? base_height : top_height;
    png_bytep* row_pointers_base = (png_bytep*)malloc(sizeof(png_bytep) * max_height);
    png_bytep* row_pointers_top = (png_bytep*)malloc(sizeof(png_bytep) * max_height);

    for (int y = 0; y < base_height; y++) {
        row_pointers_base[y] = (png_bytep)png_malloc(base_pic, png_get_rowbytes(base_pic, base_info));
        png_read_row(base_pic, row_pointers_base[y], NULL);
    }

    for (int y = 0; y < top_height; y++) {
        row_pointers_top[y] = (png_bytep)png_malloc(top_pic, png_get_rowbytes(top_pic, top_info));
        png_read_row(top_pic, row_pointers_top[y], NULL);
    }



    // 이미지 합성
    for (int y = 0; y < base_height && y < top_height; y++) {
        png_bytep row_base = row_pointers_base[y];
        png_bytep row_top = row_pointers_top[y];

        // 여기서 각 픽셀 값을 조절하여 합성합니다.
        for (int x = 0; x < base_width * 4; x++) {
            if(row_top[x]!=0){
            // 이미지 합성: 두 이미지의 픽셀 값을 합산 (범위를 벗어나지 않도록 조심)
            row_base[x] = row_top[x];}
        }
    }

    // 파일 닫기
    png_destroy_read_struct(&base_pic, &base_info, NULL);
    png_destroy_read_struct(&top_pic, &top_info, NULL);
    fclose(base);
    fclose(top);

    // 합성된 이미지 저장
    FILE *output_fp = fopen(output_file, "wb");
    if (!output_fp) {
        printf("결과 파일 열기 오류\n");
        return 1;
    }

    png_structp output_png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop output_info = png_create_info_struct(output_png);

    if (!output_png || !output_info) {
        printf("결과 png_create_write_struct 또는 png_create_info_struct 오류\n");
        fclose(output_fp);
        return 1;
    }

    if (setjmp(png_jmpbuf(output_png))) {
        printf("결과 오류 발생\n");
        png_destroy_write_struct(&output_png, &output_info);
        fclose(output_fp);
        return 1;
    }

    png_init_io(output_png, output_fp);

    png_set_IHDR(
        output_png,
        output_info,
        base_width, base_height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );

    png_write_info(output_png, output_info);

    // 합성된 이미지를 파일에 쓰기
    for (int y = 0; y < base_height; y++) {
        png_bytep row = row_pointers_base[y];
        png_write_row(output_png, row);
    }

    png_write_end(output_png, NULL);

    // 파일 닫기
    png_destroy_write_struct(&output_png, &output_info);
    fclose(output_fp);

    // 할당된 메모리 해제
    for (int y = 0; y < base_height; y++) {
        png_free(base_pic, row_pointers_base[y]);
    }
    for (int y = 0; y < top_height; y++) {
        png_free(top_pic, row_pointers_top[y]);
    }
    free(row_pointers_base);
    free(row_pointers_top);

    

    return 0;
}