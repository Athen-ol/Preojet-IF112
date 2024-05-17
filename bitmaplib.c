#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bitmaplib.h"



picture new_pic(int width, int height){
    char *pixels = malloc(width*height*3*sizeof(char));
    picture picture = {width, height, pixels};
    return picture;
}

void save_pic(picture picture, const char* filename){
    FILE* image = NULL;
    image = fopen(filename, "w");
    fprintf(image, "P6\n%d %d\n255\n", picture.width, picture.height); // Écriture des en-têtes en une seule fois
    for(int i=0; i<picture.height*picture.width*3; i++){
        fputc(picture.pixels_tab[i], image);
    }
    fclose(image);
    free(picture.pixels_tab);
}

int max(int x, int y){
    if(x>=y) return x;
    return y;
}

void set_pixel(int x, int y, color color, picture picture){
    picture.pixels_tab[3*(x + picture.width*y)] = color.red;
    picture.pixels_tab[3*(x + picture.width*y) + 1] = color.green;
    picture.pixels_tab[3*(x + picture.width*y) + 2] = color.blue;
}

void draw_line(picture picture, int x1, int y1, int x2, int y2, color color){
    int n = max(abs(x1-x2), abs(y1-y2));
    for (int i=0; i<=n; i++){
        int xi = x1 + i*(x2 - x1)/n;
        int yi = y1 + i*(y2 - y1)/n;
        set_pixel(xi, yi, color, picture);
    }
}

picture read_pic(const char* filename){
    FILE* image = NULL;
    image = fopen(filename, "r");
    // if(image == NULL) printf("image nulle\n");
    char str[10];
    fscanf(image, "%s\n", str);
    // printf("%s\n", str);
    unsigned int width=0, height = 0;
    fscanf(image, "%u %u", &width, &height);
    picture pic = new_pic(width, height);
    fscanf(image, "%s\n", str);
    // printf("%s\n", str);
    // printf("width : %u, height : %u\n", pic.width, pic.height);
    for(int i=0; i<(pic.height)*(pic.width)*3; i++){
        pic.pixels_tab[i] = (unsigned char) fgetc(image);
        // printf("%hhu %d\n", pic.pixels[i], i);
    }
    // printf("yo\n");
    return pic;
}


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void tri_tab(int* tab, int len){
    char fonction_a_trier = 1;

    while(fonction_a_trier){
        fonction_a_trier = 0;
        for(int i = 0; i < len; i++){
            if(tab[i] > tab[i+1]){
                swap( &tab[i], &tab[i+1]);
                fonction_a_trier = 1;
            }
        }
    }
}

bool est_impair(int nombre) {
    return (nombre % 2 != 0);
}