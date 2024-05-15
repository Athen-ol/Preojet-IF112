#ifndef __FILTRES_H__
#define __FILTRES_H__



typedef struct{
    char R;
    char G;
    char B;
} pixel;

picture grayLevels(picture pic);
picture f(picture pic, int taille_filtre);

#endif