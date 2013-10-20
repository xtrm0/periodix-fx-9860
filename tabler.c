#include "tabler.h"
#include "elements.h"
int c, l; //coluna e linha da tabela periodica representativa selecionadas
int l0, c0; //posicao do elemento que esta mais acima e a esquerda no ecra.
int menu; //especifica em que menu esta (1=tabela,2=menu1,3-menu2(informacao), 4-informacao sobre o elemento)
int l1, l2, l3, l4; //indica em que opcao esta nesse menu. l1 representa o modo em que esta a tabela (normal ou l3)
int showtype; //escrever o Z ou o valor
int drawmode; //desenhar o nome ou o valor
void tabler_start() {
	l=1; c=1;
	l0=1; c0=1;
	menu = 1;
	showtype = 0;
	drawmode = 0;
	l1=0; l2=0; l3=0; l4=0;
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
			drawmode=0;
		}
		if ((*key)==KEY_CTRL_F4) {
			l1 = (l1-1);
			if (l1==-1) l1=PROPER_N-1;
			drawmode=0;
		}
		if ((*key)==KEY_CTRL_F5) {
			if (l>=1 && l<=7) c=1;
			else c=3;
		}
		if ((*key)==KEY_CTRL_F6) {
			if (l>=1 && l<=7) c=18;
			else c=17;
		}
		if ((*key)==KEY_CTRL_EXE) {
			//TODO: mostrar a informacao sobre o elemento
			menu = 4;
		}
		if ((*key)==KEY_CTRL_OPTN) {
			if (drawmode==0 && (l1==0 || l1==1)) {
				drawmode=1;
			} else {
				drawmode=0;
			}
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
			drawmode=0;
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
	float mi, ma;//minimos e maximos para o valor a representar
	int x1,x2,x3;
	unsigned char E;
	int z;
	unsigned char verb[23];
	ML_clear_screen();
	ML_rectangle(0,0,127,127,0,0,ML_WHITE);
		
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
	if (drawmode==0) {
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
	} else if(drawmode==1) {
		mi = 1000000;
		ma = -1000000;
		for (i=1; i<=118; i++) {
			if (l1==0) {
				mi = min(mi, ptable[i].Z);
				ma = max(ma, ptable[i].Z);
			} else if (l1==1) {
				mi = min(mi, ptable[i].a_w);
				ma = max(ma, ptable[i].a_w);
			}
		}
		for (i=1; i<=6; i++) { //para cada periodo
			locate(1,i+1);
			E='0'+l0+i-1; PrintC(&E);
			for (j=1; j<=7; j++) { //para cada grupo
				z = find_elem(c0+j-1, l0+i-1);
				if(z!=0) {
					ML_rectangle(8+(j-1)*17,8+(i-1)*8,8+j*17,8+i*8,1,ML_BLACK,ML_WHITE); 
					if (l1==0) {
						if (ptable[z].Z>0) {
							x1 = (ptable[z].Z/ma)*343; //antes de mais normalizar o valor que temos para um valor inteiro entre 0 e 7*7*7=343
							x3 = (x1%49)%7;
							x2 = (x1%49)/7;
							x1 = x1/49;
						} else if (ptable[z].Z<0){
							x1 = (ptable[z].Z/mi)*343; //antes de mais normalizar o valor que temos para um valor inteiro entre 0 e 7*7*7=343
							x3 = (x1%49)%7;
							x2 = (x1%49)/7;
							x1 = x1/49;
						}	
					} else if (l1==1) {
						if (ptable[z].Z>0) {
							x1 = (ptable[z].Z/ma)*343; //antes de mais normalizar o valor que temos para um valor inteiro entre 0 e 7*7*7=343
							x3 = (x1%49)%7;
							x2 = (x1%49)/7;
							x1 = x1/49;
						} else if (ptable[z].Z<0){
							x1 = (ptable[z].Z/mi)*343; //antes de mais normalizar o valor que temos para um valor inteiro entre 0 e 7*7*7=343
							x3 = (x1%49)%7;
							x2 = (x1%49)/7;
							x1 = x1/49;
						}
					}
					
					ML_rectangle(8+(j-1)*17,8+(i-1)*8,8+(j-1)*17+4,8+(i-1)*8+4,0,0,ML_BLACK);
					ML_rectangle(8+(j-1)*17+5,8+(i-1)*8+(8-x1),8+(j-1)*17+8,8+(i-1)*8+8,0,0,ML_BLACK);
					ML_rectangle(8+(j-1)*17+9,8+(i-1)*8+(8-x2),8+(j-1)*17+12,8+(i-1)*8+8,0,0,ML_BLACK);
					ML_rectangle(8+(j-1)*17+13,8+(i-1)*8+(8-x3),8+(j-1)*17+17,8+(i-1)*8+8,0,0,ML_BLACK);
				} else {
					ML_rectangle(9+(j-1)*17,9+(i-1)*8,8+j*17-1,8+i*8-1,0,0,ML_WHITE);  
				}
				if (l0+i-1==l && c0+j-1==c) {
					ML_rectangle(8+(j-1)*17,8+(i-1)*8,8+j*17,8+i*8,2,ML_XOR,ML_TRANSPARENT); 
				} 
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
			sprintf(verb, "%s\0", elemconfig[find_elem(c,l)]);
		} else if (l1==3) {
			sprintf(verb, "Ei(%d) = %.6f\0", find_elem(c,l), ptable[find_elem(c,l)].Ei);
		} else if (l1==4) {
			sprintf(verb, "Eae(%d) = %.6f\0", find_elem(c,l), ptable[find_elem(c,l)].Eae);
		} else if (l1==5) {
			sprintf(verb, "En(%d) = %.6f\0", find_elem(c,l), ptable[find_elem(c,l)].En);
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
	sprintf(verb, "%c%c%d:%*s\0", ptable[find_elem(c,l)].X, ptable[find_elem(c,l)].x, ptable[find_elem(c,l)].Z, 13, elemnames[find_elem(c,l)]);
	Print(verb);
	locate(2,3);
	sprintf(verb, "Ar  = %.8f\0", ptable[find_elem(c,l)].a_w);
	Print(verb);
	locate(2,4);
	sprintf(verb, "E_i = %.6f\0", ptable[find_elem(c,l)].Ei);
	Print(verb);
	locate(2,5);
	sprintf(verb, "Eae = %.6f\0", ptable[find_elem(c,l)].Eae);
	Print(verb);
	locate(2,6);
	sprintf(verb, "E_n = %.6f\0", ptable[find_elem(c,l)].En);
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