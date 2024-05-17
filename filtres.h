#ifndef __FILTRES_H__
#define __FILTRES_H__



typedef struct{
    char R;
    char G;
    char B;
} pixel;

picture niveau_de_gris(picture pic, picture masque);
picture f(picture pic, char taille_filtre, picture masque);

#endif