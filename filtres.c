#include "filtres.h"
#include "bitmaplib.h"
#include "bitmaplib.c"
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

    picture new_picture = new_pic(pic.width, pic.height); // nv im avec mm dimensions que im originale
    
    // parcours de chaque pixels de l'im originale
    for(int i = 0; i < pic.width; i++){
        for(int j = 0; j < pic.height; j++ ){
            // initialisation des sommes pr comp R B et G
            int somme_R = 0;
            int somme_B = 0;
            int somme_G = 0;
            int compteur = 0; // compteur pour le nb de pixels dans le voisinage 
            
            // parcours des pixels dans le voisinage defpar la taille du filtre 
            for(int k = i-taille_filtre ; k < i + taille_filtre ; k++){
                for (int l = j-taille_filtre ; l < j + taille_filtre ; l++){
                    
                    if (k >= 0 && k < pic.width && l >= 0 && l < pic.height) { // verif que les indices sont dans les limites de l'im
                        int index = 3 * (k + l*pic.width); //calcul de l'indice du pixel ds tab de pixel
                        // somme des valeurs des composantes R B et G
                        somme_R += pic.pixels_tab[index];;
                        somme_B += pic.pixels_tab[index + 1];
                        somme_G += pic.pixels_tab[index + 2];
                        compteur ++; //incrementation du compteur
                    }
                }
            }

            int index = 3 * (i + j * pic.width); //calcul de l'indice du pixel dans l'im floutée
            //affectation de nv valeurs moyennes des comp R G et V
            new_picture.pixels_tab[index] = somme_R / compteur;
            new_picture.pixels_tab[index + 1] = somme_G / compteur;
            new_picture.pixels_tab[index + 2] = somme_B / compteur;
            }
        }

    return new_picture;
}

// int main() {
    
//     picture pic = read_pic("input_image.ppm"); // lecture de l'im

//     // floutage :
//     int taille_filtre = 1; // pour filtre 3x3
//     picture blurred_pic = f(pic, taille_filtre);
    
//     save_pic(blurred_pic, "blurred_image.ppm"); // sauvegarder l'image floutée
    
//     free(blurred_pic.pixels_tab); // libérer mém allouée
//     return 0;
// }