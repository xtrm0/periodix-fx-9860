#ifndef TABLERH
#define TABLERH

#include <stdlib.h>
#include "fxlib.h"
#include "MonochromeLib.h"
#define PROPER_N 3

void tabler_start();
void draw_table();
void usekey(unsigned int * key);
void draw_elem();
void draw_menu2();
void draw_menu3();
int find_elem(int x, int y);


#endif