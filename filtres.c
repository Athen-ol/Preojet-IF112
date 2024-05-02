#include "filtres.h"
#include "bitmaplib.h"
#include <stdio.h>
#include <stdlib.h>


char niveaux_de_gris(pixel pixel){
    return pixel.R/3 + pixel.G/3 + pixel.B/3;
}


// struct picture{
//     int width, height;
//     char* pixels;
// };

picture f(picture pic, int taille_filtre){

    int length = taille_filtre * 3;
    char *new_tab_pixels = NULL;
    int somme_R = 0;
    int somme_B = 0;
    int somme_V = 0;

    for(int i = 0; i < pic.width; i++){
        for(int j = 0; j < pic.height; j++ ){
            for(int k = i-1 ; k < i+2 ; k++){
                for (int l = j-1; l < j+2; l++){
                    somme_R += ... .pixels_tab[]->R;
                    somme_B += ...->B;
                    somme_V += ...->V;


//pixel->R


                }
            }
        }
    }


}

// parcourt le tab de pixel