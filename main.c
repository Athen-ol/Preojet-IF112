#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bitmaplib.h"
#include "filtres.h"
#include "jpg_io.h"

int main(int argc, char *argv[]){
    int opt;
    char *nom_entree = "image.ppm"; // par défaut on cherche une image nommée "image.ppm"
    char *nom_sortie = "output.jpg"; // par défault on exporte l'image de sortie "output.jpg"
    char *nom_masque = NULL;

    char gray_active = 0;
    char blur_active = 0;
    char median_active = 0;


    char taille_filtre = 10;
    
    while ((opt = getopt(argc, argv, "t:i:o:s:m:")) != -1){
        switch (opt){
            case 't' : 
                char *type = optarg;
                if(type[0] == 'g') {
                    gray_active = 1;
                }
                else if(type[0] == 'b'){
                    blur_active = 1;
                }
                else if(type[0] == 'm') {
                    median_active = 1;
                }
                else printf("argument de type inconnu\n");

                printf("Le type de filtre est : '%s'\n", type);
                break;
            case 'i' :
                nom_entree = optarg;
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
            case 'm' : 
                nom_masque = optarg ;
                printf("Le masque %s est utilisé\n", nom_masque);
                break;
            case '?':
                printf("Option inconnue ou manquante\n");
                break;

        }
    }

    if(nom_entree == "image.ppm") printf("Attention vous avez laissé le nom d'image d'entrée par defaut : image.ppm\n");

    int k = 0;
    while (nom_entree[k]) k++;

    picture pic;
    if(nom_entree[k-1] == 'm'){
        pic = read_pic(nom_entree); // lecture de l'image ppm
    }
    else if(nom_entree[k-1] == 'g'){
        pic = read_jpeg(nom_entree); // lecture de l'image jpg
    }
    else printf("Extension de fichier non reconnue\n");

    picture masque;
    if(nom_masque != NULL){
        int k = 0;
        while (nom_masque[k]) k++;

        if(nom_masque[k-1] == 'm'){
            masque = read_pic(nom_masque); // lecture du masque ppm
        }
        else if(nom_masque[k-1] == 'g'){
            masque = read_jpeg(nom_masque); // lecture du masque jpg
        }
        else printf("Extension de fichier non reconnue\n");
    }
    else {
        masque = new_pic(pic.width, pic.height);
        for(int i=0; i<masque.width*masque.height*3; i++){
            masque.pixels_tab[i] = 255;
        }
    }

    if(gray_active) pic = niveau_de_gris(pic, masque); // conversion en niveaux de gris

    if(blur_active) pic = floutage(pic, taille_filtre, masque); // floutage de l'image

    if(median_active) pic = filtrage_median(pic, taille_filtre); // application du filtre moyenneur de l'image

    k = 0;
    while (nom_sortie[k]) k++;

    if(nom_sortie[k-1] == 'm'){
        save_pic(pic, nom_sortie); // sauvegarde de l'image ppm
    }
    else if(nom_sortie[k-1] == 'g'){
        save_jpeg(nom_sortie, pic); // sauvegarde de l'image jpg
    }

    return 0;
}

// Lancer le programme ainsi par exmple : ./projet -i intput.ppm -t blur -s 3 -o output.ppm

