#ifndef __FILTRES_H__
#define __FILTRES_H__



typedef struct{
    char R;
    char G;
    char B;
} pixel;

picture niveau_de_gris(picture pic, picture masque);
picture floutage(picture pic, char taille_filtre, picture masque);
picture filtrage_median(picture pic, char taille_filtre, picture masque);
picture miroir(picture pic, picture masque, char mode);

#endif