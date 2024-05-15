#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bitmaplib.h"
#include "filtres.h"
#include "jpg_io.h"

int main(int argc, char *argv[]){
    int opt;
    char *nom_entree = "image.ppm"; // par défaut on cherche une image nommée "image.ppm"
    char *nom_sortie = "image_transformee.ppm"; // par défault on exporte l'image de sortie "image_transformee.ppm"

    char gray_active = 0;
    char blur_active = 0;
    char median_active = 0;

    char ppm_jpg = 0;

    char taille_filtre = 0;
    
    while ((opt = getopt(argc, argv, "t:i:o:s:")) != -1){
        switch (opt){
            case 't' : 
                char *type = optarg;
                if(type == "gray") gray_active = 1;
                else if(type == "blur"){
                    blur_active = 1;
                    printf("blur_active");
                }
                else if(type == "median") median_active = 1;
                else printf("argument de type inconnu\n");

                printf("Le type de filtre est : '%s'\n", type);
                break;
            case 'i' :
                nom_entree = optarg ;
                printf("Le nom de l'image en entrée est : '%s'\n", nom_entree);
                break;
            case 'o' : 
                nom_sortie = optarg;
                printf("Le nom de l'image en sortie sera :  '%s'\n", nom_sortie);
                break;
            case 's' : 
                taille_filtre = atoi(optarg);
                printf("La taille du filtre est :  '%hhi'\n", taille_filtre);
                break;
            case '?':
                printf("Option inconnue ou manquante\n");
                break;

        }
    }

    if(nom_entree == "image.ppm") printf("Attention vous avez laissé le nom d'image d'entrée par defaut\n");



    picture pic = read_pic(nom_entree); // lecture de l'image

    // if(gray_active) pic == g(pic); // conversion en niveaux de gris

    if(blur_active) pic = f(pic, taille_filtre); // floutage de l'image

    // if(median_active) pic = m(pic, taille_filtre); // application du filtre moyenneur de l'image
    
    save_pic(pic, nom_sortie); // sauvegarder l'image floutée
    
    return 0;
}

// Lancer le programme ainsi par exmple : ./a.out -i intput.ppm -t blur -s 3 -o output.ppm


