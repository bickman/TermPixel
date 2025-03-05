#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>

void image_to_terminal_blocks(const char *image_path) {
    int width, height, channels;
    unsigned char *image = stbi_load(image_path, &width, &height, &channels, 0);
    if (!image) {
        printf("%s not found!\n",image_path);
        return;
    }
    char location[30];
    snprintf(location,sizeof(location),"%s.txt",image_path);
    FILE *output=fopen(location,"a");
    for (int y = 0; y < height; y+=2) {
        for (int x = 0; x < width; x++) {
            unsigned char *pixel_top = image + ( y * width + x) * channels;
            unsigned char *pixel_bottom = image + (( y  + 1) * width + x) * channels;

            int r1 = pixel_top[0], g1 = pixel_top[1], b1 = pixel_top[2], a1 = pixel_top[3];
            int r2 = pixel_bottom[0], g2 = pixel_bottom[1], b2 = pixel_bottom[2], a2 = pixel_bottom[3];
            if( channels==3 ){
                fprintf(output,"\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm▀\033[0m", r1, g1, b1, r2, g2, b2);
            }
            else if( channels==4 ){
                if( a1!=0 && a2==0) {
                    fprintf(output,"\033[38;2;%d;%d;%dm▀\033[0m",r1,g1,b1);
                    //printf("▀");
                }
                else if( a1==0 && a2!=0 ) {
                    fprintf(output,"\033[38;2;%d;%d;%dm▄\033[0m",r2,g2,b2);
                    //printf("▄");
                }
                else if( a1!=0 && a2!=0) {
                    fprintf(output,"\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm▀\033[0m", r1, g1, b1, r2, g2, b2);
                    //printf("█");
                }
                else {
                    fprintf(output," ");
                    //printf(" ");
                }
            }
        }
        fprintf(output,"\n");
        //printf("\n");
    }

    fclose(output);
    stbi_image_free(image);
}

int main(int argc, const char *argv[]) {
    for(int i=1;i<argc;i++){
        image_to_terminal_blocks(argv[i]); 
    }
    return 0;
}
