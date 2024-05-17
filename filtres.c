#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bitmaplib.h"
#include "filtres.h"


// char niveaux_de_gris(pixel pix){
//     char moyenne = pix.R/3 + pix.G/3 + pix.B/3;
//     pixel pix_gris = {moyenne, moyenne, moyenne};
//     return pix_gris;
// }

picture niveau_de_gris(picture pic){

    picture new_picture = new_pic(pic.width, pic.height); // nv im avec mm dimensions que im originale

    // parcours de chaque pixels de l'im originale
    for(int i = 0; i < pic.width; i++){
        for(int j = 0; j < pic.height; j++ ){ 
            int index = 3 * (i + j*pic.width) ; // *3 car on a 3 cases par pixel
            int moyenne = (pic.pixels_tab[index] + pic.pixels_tab[index + 1] + pic.pixels_tab[index + 2])/3 ; // on fait la moyenne des couleurs de chaque pixel
            new_picture.pixels_tab[index] = moyenne; // on met la moyenne de pic aux 3 pixels de new_picture
            new_picture.pixels_tab[index + 1] = moyenne;
            new_picture.pixels_tab[index + 2] = moyenne;
        }
    }
    return new_picture;

}

// picture grayLevels(picture pic){
//     // TODO
// }


// struct picture{
//     int width, height;
//     char* pixels;
// };

picture floutage(picture pic, char taille_filtre){

    picture new_picture = new_pic(pic.width, pic.height); // nv im avec mm dimensions que im originale
    
    // parcours de chaque pixels de l'im originale
    for(int i = 0; i < pic.width; i++){
        for(int j = 0; j < pic.height; j++ ){
            // initialisation des sommes pr comp R B et G
            int somme_R = 0;
            int somme_B = 0;
            int somme_G = 0;
            int nb_de_voisins = 0; // compteur pour le nb de pixels dans le voisinage 
            
            // parcours des pixels dans le voisinage defpar la taille du filtre 
            for(int k = i-taille_filtre ; k < i + taille_filtre ; k++){
                for (int l = j-taille_filtre ; l < j + taille_filtre ; l++){
                    
                    if (k >= 0 && k < pic.width && l >= 0 && l < pic.height) { // verif que les indices sont dans les limites de l'im
                        int index = 3 * (k + l*pic.width); //calcul de l'indice du pixel ds tab de pixel RQ *3 car on a 3 'cases' par pixel
                        // somme des valeurs des composantes R B et G
                        somme_R += pic.pixels_tab[index];;
                        somme_G += pic.pixels_tab[index + 1];
                        somme_B += pic.pixels_tab[index + 2];
                        nb_de_voisins ++; //incrementation du compteur pour savoir une moyenne sur combien de pixels on fait !
                    }
                }
            }

            int index = 3 * (i + j * pic.width); //calcul de l'indice du pixel dans l'im floutée
            //affectation de nv valeurs moyennes des comp R G et V
            new_picture.pixels_tab[index] = somme_R / nb_de_voisins; // on divise par compteur et pas par 9 car sur les côtés on somme moins de 9 pixels ! 
            new_picture.pixels_tab[index + 1] = somme_G / nb_de_voisins;
            new_picture.pixels_tab[index + 2] = somme_B / nb_de_voisins;
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


picture filtrage_median(picture pic, char taille_filtre){
    
    picture new_picture = new_pic(pic.width, pic.height); // nv im avec mm dimensions que im originale
    
    // parcours de chaque pixels de l'im originale
    for(int i = 0; i < pic.width; i++){
        for(int j = 0; j < pic.height; j++ ){
            // initialisation des tab pr comp R B et G
            int tab_rouge[taille_filtre*taille_filtre]; // on prend cette taille car taille max de notre tab souhaité
            int tab_vert[taille_filtre*taille_filtre];
            int tab_bleu[taille_filtre*taille_filtre];
            int nb_de_voisins = 0; // compteur pour le nb de pixels dans le voisinage 
            
            // parcours des pixels dans le voisinage def par la taille du filtre 
            for(int k = i-taille_filtre ; k < i + taille_filtre ; k++){
                for (int l = j-taille_filtre ; l < j + taille_filtre ; l++){
                    
                    if (k >= 0 && k < pic.width && l >= 0 && l < pic.height) { // verif que les indices sont dans les limites de l'im
                        int index = 3 * (k + l*pic.width);
                        nb_de_voisins ++; //incrementation du compteur pour savoir une moyenne sur combien de pixels on fait !
                        // ajout des comp R B et G dans 3 tab pour tous les voisins
                        tab_rouge[nb_de_voisins] = pic.pixels_tab[index];
                        tab_vert[nb_de_voisins] = pic.pixels_tab[index + 1];
                        tab_bleu[nb_de_voisins] = pic.pixels_tab[index + 2];  
                    }
                }
            }
                tri_tab(tab_rouge, nb_de_voisins);
                tri_tab(tab_vert, nb_de_voisins);
                tri_tab(tab_bleu, nb_de_voisins);

                int indice_mediane = nb_de_voisins / 2;
                if (est_impair(nb_de_voisins)) {
                    indice_mediane = (nb_de_voisins - 1) / 2;
                }
                int mediane_rouge = tab_rouge[indice_mediane];
                int mediane_vert = tab_vert[indice_mediane];
                int mediane_bleu = tab_bleu[indice_mediane];

                int index = 3 * (i + j * pic.width);
                new_picture.pixels_tab[index] = mediane_rouge;
                new_picture.pixels_tab[index + 1] = mediane_vert;
                new_picture.pixels_tab[index + 2] = mediane_bleu;

            }

        }
    return new_picture;
}  
