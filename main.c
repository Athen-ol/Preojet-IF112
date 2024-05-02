#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int opt;
    char *type = NULL;
    char *nom_entree = NULL;
    char *nom_sortie = NULL;
    while ((opt = getopt(argc, argv, "t:i:o:s:")) != -1){
        switch (opt){
            case 't' : 
                type = optarg;
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
                printf("La taille du filtre est :  '%s'\n", optarg);
                break;
            case '?':
                printf("Option inconnue ou manquante\n");
                break;

        }
    }
    return 0;
}

// Lancer le programme ainsi par exmple : ./a.out -i intput.ppm -t blur -s 3 -o output.ppm


