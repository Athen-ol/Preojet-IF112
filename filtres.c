#include "filtres.h"


char niveaux_de_gris(pixel pixel){
    return pixel.R/3 + pixel.G/3 + pixel.B/3;
}

