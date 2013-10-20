#include "tabler.h"
#include "elements.h"
int c, l; //coluna e linha da tabela periodica representativa selecionadas
int l0, c0; //posicao do elemento que esta mais acima e a esquerda no ecra.
int menu; //especifica em que menu esta (1=tabela,2=menu1,3-menu2(informacao), 4-informacao sobre o elemento)
int l1, l2, l3; //indica em que opcao esta nesse menu. l1 representa o modo em que esta a tabela (normal ou l3)
int showtype; //escrever o Z ou o valor
int drawmode; //desenhar o nome ou o valor
void tabler_start() {
	l=1; c=1;
	l0=1; c0=1;
	menu = 1;
	showtype = 0;
	drawmode = 0;
	l1=0; l2=0; l3=0;
	Bdisp_AllClr_DDVRAM();
	ML_clear_vram();
	ML_clear_screen();
	initialize_elements();
}

void usekey(unsigned int * key) {
	if (menu==1) {
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
		if ((*key)==KEY_CTRL_F1) {
			//TODO: muda o display dos elementos
			showtype = (showtype+1)%2; 
		}
		if ((*key)==KEY_CTRL_F2) {
			//TODO: mostra o menu2
			menu = 2;
			l2 = 0;
		}
		if ((*key)==KEY_CTRL_F3) {
			l1 = (l1+1)%PROPER_N;
		}
		if ((*key)==KEY_CTRL_F4) {
			l1 = (l1-1)%PROPER_N;
		}
		if ((*key)==KEY_CTRL_EXE) {
			//TODO: mostrar a informacao sobre o elemento
			menu = 4;
		}
		if ((*key)==KEY_CTRL_EXIT) {
			*key = KEY_CHAR_FRAC;
			return;
		}
		//ML_pixel(c,l,ML_BLACK);
		if (c < c0) c0=c;
		if (l < l0) l0=l;
		while (l >= l0+6) l0++;
		while (c >= c0+7) c0++;
	} else if (menu==2) {
		if ((*key)==KEY_CTRL_UP) {
			l2++;
			if (l2==PROPER_N) l2--;
		}
		if ((*key)==KEY_CTRL_DOWN) {
			l2--;
			if (l2==-1) l2++;
		}	
		if ((*key)==KEY_CTRL_EXIT) {
			//TODO (esta feito?)
			menu = 1;
		}
		if ((*key)==KEY_CTRL_EXE) {
			//TODO
			menu = 3;
			l3 = 0;
		}
	} else if (menu==3) {
		if ((*key)==KEY_CTRL_UP) {
			//TODO
		}
		if ((*key)==KEY_CTRL_DOWN) {
			//TODO
		}	
		if ((*key)==KEY_CTRL_EXIT) {
			//TODO (esta feito?)
			menu = 2;
		}
		if ((*key)==KEY_CTRL_EXE) {
			//TODO
			menu = 1;
			l1 = l2; // atualiza a propriedade a mostrar
		}
	} else if (menu==4) {
		if ((*key)==KEY_CTRL_UP) {
			//TODO
		}
		if ((*key)==KEY_CTRL_DOWN) {
			//TODO
		}	
		if ((*key)==KEY_CTRL_EXIT) {
			//TODO (esta feito?)
			menu = 1;
		}
	}
	draw_table();
	if (menu==2) {
		//TODO
		draw_menu2();
	}
	if (menu==3) {
		//TODO
		draw_menu3();
	}
	if (menu==4) {
		draw_elem();
	}
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
	
	if (showtype==0) {
		if (l1==0) {
			sprintf(verb, "Z = %d\0", ptable[find_elem(c,l)].Z);
		} else if (l1==1) {
			sprintf(verb, "Ar(%d) = %.6f\0", find_elem(c,l), ptable[find_elem(c,l)].a_w);
		} else if (l1==2) {
			sprintf(verb, "%*s\0", 21, ptable[find_elem(c,l)].e_config);
		} 	
	} else if (showtype==1) {
		sprintf(verb, "Z = %d\0", ptable[find_elem(c,l)].Z);
	}
	Print(verb);
	
}

void draw_elem() {
	unsigned char verb[22];
	ML_rectangle(5, 6, 121, 57, 1, ML_BLACK, ML_WHITE);
	locate(2,2);
	sprintf(verb, "%c%c: %*s\0", ptable[find_elem(c,l)].X, ptable[find_elem(c,l)].x, 14, elemnames[find_elem(c,l)]);
	Print(verb);
	locate(2,3);
	sprintf(verb, "Z = %d\0", ptable[find_elem(c,l)].Z);
	Print(verb);
	locate(2,4);
	sprintf(verb, "W = %.6f\0", ptable[find_elem(c,l)].a_w);
	Print(verb);
	ML_rectangle(5, 6, 121, 57, 1, ML_BLACK, ML_TRANSPARENT);
	return;
}

void draw_menu2() {
	return;
}

void draw_menu3() {
	return;
}