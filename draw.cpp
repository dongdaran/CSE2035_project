#include "draw.hpp"
#include "merge.hpp"
#include <iostream>
#include <string>


void Draw::draw_perfect_Tri(Pixel** row_pointer_input, int x_center, int y_center, int length_div2, Pixel color_input) {
    int height =length_div2 * sqrt(3) ; 
    int y_top = y_center - height / 2; 
    int y_bottom = y_center + height / 2; 

    for (int x = x_center - length_div2 / 2; x <= x_center + length_div2 / 2; x++) {
        for (int y = y_bottom; y >= y_top; y--) {

            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                if ((y - y_top) * (x_center - x_center - length_div2 / 2) <= (x - x_center - length_div2 / 2) * (y_center - y_top) &&
                    (y - y_top) * (x_center - x_center + length_div2/ 2) >= (x - x_center + length_div2 / 2) * (y_center - y_top) &&
                    (y - y_bottom) * (x_center - x_center + length_div2 / 2) >= (x - x_center + length_div2 / 2) * (y_center - y_bottom)) {
                    row_pointer_input[y][x].r = color_input.r;
                    row_pointer_input[y][x].g = color_input.g;
                    row_pointer_input[y][x].b = color_input.b;
                    row_pointer_input[y][x].a = color_input.a;
                }
            }
        }
    }
}


void Draw::draw_Circle(Pixel** row_pointer_input, int x_center, int y_center, int rad, Pixel color_input) {
   for (int y = 0; y < 1000; y++) {
      for (int x = 0; x < 500; x++) {
         int dx = x - x_center;
         int dy = y - y_center;
         if (dx * dx + dy * dy <= rad * rad) {
            row_pointer_input[y][x].r = color_input.r;
            row_pointer_input[y][x].b = color_input.b;
            row_pointer_input[y][x].g = color_input.g;
            row_pointer_input[y][x].a = 255;
         }
      }
   }

}

void Draw::draw_Rectangle(Pixel** row_pointer_input, int x_center, int y_center, int x_length, int y_length, Pixel color_input) {
   Point start = {x_center - (x_length / 2), y_center - (y_length / 2)};
   Point end = {x_center + (x_length / 2), y_center + (y_length / 2)};

   for (int y = start.y; y < end.y; y++) {
      for (int x = start.x; x < end.x; x++) {
          if (x >= 0 && x < 500 && y >= 0 && y < 700){
         row_pointer_input[y][x].r = color_input.r; 
         row_pointer_input[y][x].b = color_input.b;
         row_pointer_input[y][x].g = color_input.g;
         row_pointer_input[y][x].a = 255;
          }
      }
   }
}

void Draw::draw_tree(Pixel** row_pointer_input) {
   printf("↟↟↟↟ 트리 꾸미기 ↟↟↟↟\n");
   printf("1. 나무 기둥은 무슨 색으로 하실건가요?(헥스코드로 써주세요)\n");
   char tree_wood_color[10];
   scanf("%s", tree_wood_color);
   draw_Rectangle(row_pointer_input,250, 500, 60, 80,hex_go_RGB(tree_wood_color));

   printf("2. 나무 잎은 무슨 색으로 하실건가요?(헥스코드로 써주세요)\n");
   char tree_leaf_color[10];
   scanf("%s", tree_leaf_color);
   
   draw_perfect_Tri(row_pointer_input, 250, 283, 225, hex_go_RGB(tree_leaf_color));
   draw_perfect_Tri(row_pointer_input,250, 188, 184,hex_go_RGB(tree_leaf_color));
   draw_perfect_Tri(row_pointer_input,250, 100, 154,hex_go_RGB(tree_leaf_color));
}

void Draw::draw_ballon(Pixel** row_pointer_input,int x_center, int y_center) {
   char want_color[10];
   printf("풍선의 색깔은 무엇으로 하고 싶나요?(헥사 코드로 써주세요) : ");
   scanf("%s", want_color);
   Pixel white = hex_go_RGB("#F2F3F0");
   Pixel black = hex_go_RGB("#3B3B3B");
   
   draw_Circle(row_pointer_input, x_center, y_center, 15,  hex_go_RGB(want_color));
   draw_perfect_Tri(row_pointer_input, x_center, y_center + 15, 9, hex_go_RGB(want_color));
   draw_Rectangle(row_pointer_input, x_center, y_center + 9, 3, 9, black);
   draw_Circle(row_pointer_input, x_center - 7, y_center, 3, black);
   draw_Circle(row_pointer_input, x_center +7, y_center, 3, black);
   draw_Circle(row_pointer_input, x_center - 7, y_center, 1, white);
   draw_Circle(row_pointer_input, x_center + 7, y_center, 1, white);   

}

void Draw::draw_bear(Pixel** row_pointer_input,int x_center, int y_center){
   Pixel black = hex_go_RGB("#3B3B3B");
   struct Pixel red = hex_go_RGB("#dc0025");
   char want_color[10];
   printf("곰돌이의 색깔은 무엇으로 하고 싶나요?(헥사 코드로 써주세요) : ");
   scanf("%s", want_color);
   
   draw_Circle(row_pointer_input, x_center, y_center, 15,  hex_go_RGB(want_color));
   draw_Circle(row_pointer_input,x_center-10, y_center-13, 5,hex_go_RGB(want_color) );
   draw_Circle(row_pointer_input,x_center+10, y_center-13, 5,hex_go_RGB(want_color) );
   draw_Rectangle(row_pointer_input, x_center-7, y_center-6, 4, 2, black);
   draw_Rectangle(row_pointer_input, x_center+7, y_center-6, 4, 2, black);
   draw_perfect_Tri(row_pointer_input, x_center, y_center+9,3,red );
}

void Draw::draw_cat(Pixel** row_pointer_input,int x_center, int y_center){
   Pixel black = hex_go_RGB("#3B3B3B");
   Pixel red = hex_go_RGB("#dc0025");
   Pixel white = hex_go_RGB("#F2F3F0");
   char want_color[10];
   printf("고양의 색깔은 무엇으로 하고 싶나요?(헥사 코드로 써주세요) : ");
   scanf("%s", want_color);

   draw_Circle(row_pointer_input, x_center, y_center, 15,  hex_go_RGB(want_color));
   draw_perfect_Tri(row_pointer_input,x_center-7, y_center-18, 10,hex_go_RGB(want_color) );
   draw_perfect_Tri(row_pointer_input,x_center+7, y_center-18, 10,hex_go_RGB(want_color) );
   draw_Circle(row_pointer_input, x_center - 7, y_center, 3, black);
   draw_Circle(row_pointer_input, x_center +7, y_center, 3, black);
   draw_Circle(row_pointer_input, x_center - 7, y_center, 1, white);
   draw_Circle(row_pointer_input, x_center + 7, y_center, 1, white);
   draw_perfect_Tri(row_pointer_input, x_center, y_center+9,3,red );
}

void Draw::draw_cross(Pixel** row_pointer_input,int x_center, int y_center){
   char want_color[10];
   printf("십자가의 색깔은 무엇으로 하고 싶나요?(헥사 코드로 써주세요) : ");
   scanf("%s", want_color);

   draw_Rectangle(row_pointer_input, x_center,y_center, 8,30, hex_go_RGB(want_color));
   draw_Rectangle(row_pointer_input, x_center,y_center-5, 20,8, hex_go_RGB(want_color));
}

void Draw::draw_present(Pixel** row_pointer_input,int x_center, int y_center){
   Pixel black = hex_go_RGB("#3B3B3B");
   char want_color_box[10];
   printf("선물상자의 상자 색깔은 무엇으로 하고 싶나요?(헥사 코드로 써주세요) : ");
   scanf("%s", want_color_box);
   char want_color_ri[10];
   printf("선물상자의 끈 색깔은 무엇으로 하고 싶나요?(헥사 코드로 써주세요) : ");
   scanf("%s", want_color_ri);
   
   draw_Rectangle(row_pointer_input,x_center,y_center,32,32,black);
   draw_Rectangle(row_pointer_input,x_center,y_center,30,30,hex_go_RGB(want_color_box));
   draw_Rectangle(row_pointer_input, x_center,y_center,12,32,black);
   draw_Rectangle(row_pointer_input, x_center,y_center,32,12,black);
   draw_Rectangle(row_pointer_input, x_center,y_center,10,30,hex_go_RGB(want_color_ri));
   draw_Rectangle(row_pointer_input, x_center,y_center,30,10,hex_go_RGB(want_color_ri));

}

void Draw::draw_Santa(Pixel** row_pointer_input,int x_center, int y_center){
   Pixel black = hex_go_RGB("#3B3B3B");
   Pixel red = hex_go_RGB("#dc0025");
   Pixel white = hex_go_RGB("#F2F3F0");
   Pixel yellow = hex_go_RGB("#FFD700");

   char want_color[10];
   printf("산타의 모자 색깔은 무엇으로 하고 싶나요?(헥사 코드로 써주세요) : ");
    scanf("%s", want_color);

   draw_Circle(row_pointer_input, x_center, y_center, 15, yellow);
   draw_Circle(row_pointer_input, x_center - 7, y_center, 3, black);
   draw_Circle(row_pointer_input, x_center +7, y_center, 3, black);
   draw_Circle(row_pointer_input, x_center - 7, y_center, 1, white);
   draw_Circle(row_pointer_input, x_center + 7, y_center, 1, white);
   draw_perfect_Tri(row_pointer_input,x_center, y_center-25, 15,hex_go_RGB(want_color) );
   draw_Rectangle(row_pointer_input,x_center,y_center-12,18,3, white);
   draw_Circle(row_pointer_input,x_center,y_center-26,2, white );
   draw_Circle(row_pointer_input, x_center,y_center+10,7, white );
   draw_Circle(row_pointer_input,x_center,y_center+7,3, red );
   

   
}

void Draw::select_deco(Pixel ** row_pointer_input){
   printf("\n↟ 장식을 골라보세요! ↟\n");
   printf("첫번째 장식에서 원하시는 것은 무엇인가요?(숫자로 써주세요)\n");
   printf("1. 고양이\n2. 곰돌이\n3. 산타\n4. 풍선\n5. 십자가\n6. 선물\n");
   int deco1;
   printf("답변: ");
   scanf("%d", &deco1);
   switch(deco1){
      case 1:
      draw_cat(row_pointer_input,235,170);
      break;
      case 2:
      draw_bear(row_pointer_input,235,170);
      break;
      case 3:
      draw_Santa(row_pointer_input,235,170);
      break;
      case 4:
      draw_ballon(row_pointer_input,235,170);
      break;
      case 5:
      draw_cross(row_pointer_input,235,170);
      break;
      case 6:
      draw_present(row_pointer_input,235,170);
      break;
   }

   printf("\n두번째 장식에서 원하시는 것은 무엇인가요?(숫자로 써주세요)\n");
   printf("1. 고양이\n2. 곰돌이\n3. 산타\n4. 풍선\n5. 십자가\n6. 선물\n");
   int deco2;
   printf("답변: ");
   scanf("%d", &deco2);
   switch(deco2){
      case 1:
      draw_cat(row_pointer_input,210,300);
      break;
      case 2:
      draw_bear(row_pointer_input,210,300);
      break;
      case 3:
      draw_Santa(row_pointer_input,210,300);
      break;
      case 4:
      draw_ballon(row_pointer_input,210,300);
      break;
      case 5:
      draw_cross(row_pointer_input,210,300);
      break;
      case 6:
      draw_present(row_pointer_input,210,300);
      break;
   }

   printf("\n세번째 장식에서 원하시는 것은 무엇인가요?(숫자로 써주세요)\n");
   printf("1. 고양이\n2. 곰돌이 \n3. 산타\n4. 풍선\n5. 십자가\n6. 선물\n");
   int deco3;
   printf("답변: ");
   scanf("%d", &deco3);
   switch(deco3){
      case 1:
      draw_cat(row_pointer_input,290, 270);
      break;
      case 2:
      draw_bear(row_pointer_input,290, 270);
      break;
      case 3:
      draw_Santa(row_pointer_input,290, 270);
      break;
      case 4:
      draw_ballon(row_pointer_input,290, 270);
      break;
      case 5:
      draw_cross(row_pointer_input,290, 270);
      break;
      case 6:
      draw_present(row_pointer_input,290, 270);
      break;
   }

   printf("\n네번째 장식에서 원하시는 것은 무엇인가요?(숫자로 써주세요)\n");
   printf("1. 고양이\n2. 곰돌이 \n3. 산타\n4. 풍선\n5. 십자가\n6. 선물\n");
   int deco4;
   printf("답변: ");
   scanf("%d", &deco4);
   switch(deco4){
      case 1:
      draw_cat(row_pointer_input,170, 435);
      break;
      case 2:
      draw_bear(row_pointer_input,170, 435);
      break;
      case 3:
      draw_Santa(row_pointer_input,170, 435);
      break;
      case 4:
      draw_ballon(row_pointer_input,170, 435);
      break;
      case 5:
      draw_cross(row_pointer_input,170, 435);
      break;
      case 6:
      draw_present(row_pointer_input,170, 435);
      break;
   }
   

   printf("\n다섯번째 장식에서 원하시는 것은 무엇인가요?(숫자로 써주세요)\n");
   printf("1. 고양이\n2. 곰돌이\n3. 산타\n4. 풍선\n5. 십자가\n6. 선물\n");
   int deco_what;
   printf("답변: ");
   scanf("%d" ,&deco_what);
   switch(deco_what){
      case 1:
      draw_cat(row_pointer_input,245,390);
      break;
      case 2:
      draw_bear(row_pointer_input,245,390);
      break;
      case 3:
      draw_Santa(row_pointer_input,245,390);
      break;
      case 4:
      draw_ballon(row_pointer_input,245,390);
      break;
      case 5:
      draw_cross(row_pointer_input,245,390);
      break;
      case 6:
      draw_present(row_pointer_input,245,390);
      break;
   }
   

   printf("\n마지막 장식에서 원하시는 것은 무엇인가요?(숫자로 써주세요)\n");
   printf("1. 고양이\n2. 곰돌이 \n3. 산타\n4. 풍선\n5. 십자가\n6. 선물\n");
   int deco6;
   printf("답변: ");
   scanf("%d", &deco6);
   switch(deco6){
      case 1:
      draw_cat(row_pointer_input,310,415);
      break;
      case 2:
      draw_bear(row_pointer_input,310,415);
      break;
      case 3:
      draw_Santa(row_pointer_input,310,415);
      break;
      case 4:
      draw_ballon(row_pointer_input,310,415);
      break;
      case 5:
      draw_cross(row_pointer_input,310,415);
      break;
      case 6:
      draw_present(row_pointer_input,310,415);
      break;
   }
   
   

   
}

void Draw::draw_start() {

   srand(time(NULL));

   const char* result_filename = "result.png";
   
   FILE* f = fopen(result_filename, "wb");
   if (!f) {
      fprintf(stderr, "could not open out.png\n");
      abort();
   }

   png_structp png_ptr;
   png_infop info_ptr;


   png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   if (!png_ptr) {
      fprintf(stderr, "could not initialize png struct\n");
      abort();
   }

   info_ptr = png_create_info_struct(png_ptr);
   if (!info_ptr) {
      png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
      fclose(f);
      abort();
   }


   png_init_io(png_ptr, f);
   png_set_IHDR(png_ptr, info_ptr, WIDTH, HEIGHT, COLOR_DEPTH,
   PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
   PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
   png_write_info(png_ptr, info_ptr);


   Pixel* row_pointers[700];
   for (int row = 0; row < 700; row++) {
      row_pointers[row] = (Pixel*)calloc(500, sizeof(Pixel));
      
   }


   


   draw_tree(row_pointers);

   select_deco(row_pointers);
   
   /* write image data to disk */
   png_write_image(png_ptr, (png_byte**)row_pointers);

   /* finish writing PNG file */
   png_write_end(png_ptr, NULL);

   /* clean up PNG-related data structures */
   png_destroy_write_struct(&png_ptr, &info_ptr);

   
   for (int y = 0; y < 700; y++) {
      free(row_pointers[y]);
   }

   fclose(f);

   /* close the file */
   Merge merge;
   merge.merge_pic("background.png", result_filename, "result1.png");

}