#ifndef JPEGIO_H
#define JPEGIO_H

#include"img.h"

picture read_jpeg(char *name);
void    save_jpeg(char *name, picture img);

#endif
