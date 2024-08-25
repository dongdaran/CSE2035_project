#include "draw.hpp"
#include "top_deco.hpp"
#include "merge.hpp"

int main(int argc, char *argv[]){
    Draw draw;
    draw.draw_start();

    Deco deco;
    deco.deco_start();

    Merge merge;
    merge.merge_pic("result2.png", "mas_text.png", "complete_result.png");

    printf("완성되었습니다! 해피 크리스마스 ദ്ദി*ˊᗜˋ*)\n");


    return 0;

}