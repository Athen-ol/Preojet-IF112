#ifndef __BITMAPLIB_H__
#define __BITMAPLIB_H__

struct picture{
    int width, height;
    char* pixels;
};

typedef struct picture picture;

struct color{
    char red;
    char green;
    char blue;
};

typedef struct color color;

picture new_pic(int width, int height);

void save_pic(picture picture, const char* filename);

void set_pixel(int x, int y, color color, picture picture);

void draw_line(picture picture, int x1, int y1, int x2, int y2, color color);

picture read_pic(const char* filename);

#endif