#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bitmaplib.h"
#include "filtres.h"

int main(int argc, char *argv[]){
    int opt;
    char *nom_entree = NULL;
    char *nom_sortie = NULL;

    char gray_active = 0;
    char blur_active = 0;
    char median_active = 0;

    char taille_filtre = 0;
    
    while ((opt = getopt(argc, argv, "t:i:o:s:")) != -1){
        switch (opt){
            case 't' : 
                char *type = optarg;
                if(type = "gray") gray_active = 1;
                else if(type = "blur") blur_active = 1;
                else if(type = "median") median_active = 1;
                else printf("argument de type inconnu\n");

                printf("Le type de l'image est : '%s'\n", type);
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
                taille_filtre = parseChar(optarg);
                printf("La taille du filtre est :  '%hhi'\n", taille_filtre);
                break;
            case '?':
                printf("Option inconnue ou manquante\n");
                break;

        }
    }
        picture pic = read_pic("input_image.ppm"); // lecture de l'im

    // floutage :
    int taille_filtre = 1; // pour filtre 3x3
    picture blurred_pic = f(pic, taille_filtre);
    
    save_pic(blurred_pic, "blurred_image.ppm"); // sauvegarder l'image floutée
    
    free(blurred_pic.pixels_tab); // libérer mém allouée
    return 0;
}

// Lancer le programme ainsi par exmple : ./a.out -i intput.ppm -t blur -s 3 -o output.ppm


