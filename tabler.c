#include "tabler.h"
#include "elements.h"
int c, l;
int l0, c0; //posicao do elemento que esta mais acima e a esquerda no ecra.

void tabler_start() {
	l=1; c=1;
	l0=1; c0=1;
	Bdisp_AllClr_DDVRAM();
	ML_clear_vram();
	ML_clear_screen();
	initialize_elements();
}

void usekey(unsigned int * key) {
	if ((*key) == KEY_CTRL_UP) {
		l--;
		if (l==0) l=1;
		else if (l==1 && c>=2 && c<= 17) l=2;
		else if ((l==2 || l==3) &&  c>=3 && c<=12) l++;
		else if (l==7 && c==3) l=5; 
	}
	if ((*key) == KEY_CTRL_DOWN) {
		l++;
		if (l==6 && c==3) l=8;
		if (l==8 && (c==1 || c==2 || c==18)) l--;
		if (l==10) l=9;
	}	
	if ((*key) == KEY_CTRL_LEFT) {
		c--;
		if (l==1) c=1;
		else if (l==2 || l==3) {
			if (c==0) {l--; c=18;}
			else if (c==12) c=2;
		}
		else if (l==4 || l==5) {
			if (c==0) {c=18; l--;}
		}
		else if (l==6 || l==7) {
			if (c==0) {c=18; l--;}
			else if (c==3) c--;
		}
		else if (l==8) {
			if (c==2) {c=18; l--;}
		}
		else if (l==9) {
			if (c==2) {c=17; l--;}
		}
	}
	if ((*key) == KEY_CTRL_RIGHT) { 
		c++;
		if (l==1) {
			if (c==2) c=18;
			else if (c==19) {c=1; l=2;}
		}
		else if (l==2 || l==3) {
			if (c==3) c=13;
			else if (c==19) {c=1; l++;}
		}
		else if (l==4 || l==5) {
			if (c==19) {c=1; l++;}
		}
		else if (l==6) {
			if (c==3) c=4;
			else if (c==19) {c=1; l++;}
		}
		else if (l==7) {
			if (c==3) c=4;
			else if (c==19) {c=3; l++;}
		}
		else if (l==8) {
			if (c==18) {c=3; l++;}
		}
		else if (l==9) {
			if (c==18) c=17;
		}
	}
	//ML_pixel(c,l,ML_BLACK);
	if (c < c0) c0=c;
	if (l < l0) l0=l;
	while (l >= l0+6) l0++;
	while (c >= c0+7) c0++;
	draw_table();
}

int find_elem(int x, int y) {
	int i;
	for (i=1; i<=118; i++) {
		if (ptable[i].g==x && ptable[i].p==y) return i;
	}
	return 0;
}

void draw_table() {
	int i, j;
	unsigned char E;
	int z;
	unsigned char verb[22];
	ML_clear_screen();
	
	locate(1,1);
	for (j=0; j<7; j++) {
		if (j+c0<10) {
			E=' '; PrintC(&E);
			E=' '; PrintC(&E);
			E='0'+j+c0; PrintC(&E);
		} else {
			E=' '; PrintC(&E);
			E='1'; PrintC(&E);
			E='0'+((j+c0)%10); PrintC(&E);
		}
	}
	for (i=1; i<=6; i++) { //para cada periodo
		locate(1,i+1);
		E='0'+l0+i-1; PrintC(&E);
		for (j=1; j<=7; j++) { //para cada grupo
			//usar isto depois para o coiso selecionado:
			//ML_rectangle((i-1)*16,(j-1)*8,i*16,j*8,0,0,ML_XOR); 
			if (j!=1) {E=' '; PrintC(&E);}
			z = find_elem(c0+j-1, l0+i-1);
			if (l0+i-1==l && c0+j-1==c) {
				E=ptable[z].X; PrintRevC(&E);
				E=ptable[z].x; PrintRevC(&E);
			} else {
				E=ptable[z].X; PrintC(&E);
				E=ptable[z].x; PrintC(&E);
			}
		}
	}
	locate(1,8);
	Print("                     ");
	locate(1,8);
	sprintf(verb, "%*s", 21, ptable[find_elem(c,l)].e_config);
	Print(verb);
}