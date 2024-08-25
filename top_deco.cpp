#include "top_deco.hpp"
#include "merge.hpp"


void Deco::read_file(char *load_png, DecorationInfo *decoInfo) {
    FILE *load_pic = fopen(load_png, "rb");

    png_structp load_struct = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop load_info = png_create_info_struct(load_struct);

    fclose(load_pic);

    png_destroy_read_struct(&load_struct, &load_info, NULL);
}



void Deco::outcome_file(char *outcome_png, DecorationInfo *decoInfo) {

    FILE *outcome_pic = fopen(outcome_png, "wb");

    png_structp outcome_struct = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop outcome_info = png_create_info_struct(outcome_struct);

    png_destroy_write_struct(&outcome_struct, &outcome_info);

    fclose(outcome_pic);
}



void Deco::deco_start() {

    int answer2;
    DecorationInfo decoInfo;

    printf("\n↟ 꼭대기 장식을 골라보세요! ↟\n");
    printf("1. 알바트로스\n2. 별\n3. 하트\n");

    char output_filename[] = "top_deco.png";

    Merge merge;

    while(true){
        printf("\n원하는 장식을 선택하세요! : ");
        scanf("%d", &answer2);

        if(answer2==1){
            char input_filename[] = "deco_aloss.png";
            read_file(input_filename, &decoInfo);
            outcome_file(output_filename, &decoInfo);
            merge.merge_pic("result1.png", "deco_aloss.png", "result2.png");
            break;
        }
        else if(answer2==2){
            char input_filename[] = "deco_star.png";
            read_file(input_filename, &decoInfo);
            outcome_file(output_filename, &decoInfo);
            merge.merge_pic("result1.png", "deco_star.png", "result2.png");
            break;
        }
        else if(answer2==3){
            char input_filename[] = "deco_heart.png";
            read_file(input_filename, &decoInfo);
            outcome_file(output_filename, &decoInfo);
            merge.merge_pic("result1.png", "deco_heart.png", "result2.png");
            break;
        }
        else{
            printf("위 보기 중에서 선택해주세요 ᕦ(ò_óˇ)ᕤ\n");
            continue;
        }
    }

}