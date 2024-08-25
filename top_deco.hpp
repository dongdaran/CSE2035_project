#include <stdlib.h>
#include <stdio.h>
#include <png.h>

class Deco{
    private:
        typedef struct {
            int x;
            int y;
            int size;
        }DecorationInfo;
    public:
        void read_file(char *load_png, DecorationInfo *decoInfo);
        void outcome_file(char *outcome_png, DecorationInfo *decoInfo);
        void deco_start();
};