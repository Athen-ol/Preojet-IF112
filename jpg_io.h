#ifndef __JPEGIO_H__
#define __JPEGIO_H__


#include "bitmaplib.h"

picture read_jpeg(char *name);
void    save_jpeg(char *name, picture img);

#endif
