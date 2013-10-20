#ifndef ELEMH
#define ELEMH
#include "stdio.h"
//aqui irao ser definidas todas as propriedades sobre os elementos da tabela.
//Vamos usar python + a base de dados que ja temos para isso
//Struct base:
struct elem{
	int Z; 
	float a_w;
	float Ei;
	float Eae;
	float En;
	float r;
	char X, x; // letras do nome
	int g, p; //grupo e periodo
	char b; //bloco
	long int a; //TODO: REMOVE THIS TO COMPILE RELEASES; servem so para avisar quando estiver a ficar com pouco espaco para alocar
};

char ** elemnames;
char ** elemconfig;
struct elem ptable[120]; //0 e 119 sao para offset


//O seguinte e gerado por gen/gen.py. Temos de mudar o ficheiro gen.py para passar a ser um repositorio partilhado com este projeto e com o original
#include "elemz.h"

void initialize_elements() {
	struct elem elem0;
	struct elem elem119;
	int i;
	//elem0 tem os minimizantes e elem119 os maximizantes
	elemnames = (char **)malloc(120 * sizeof(char *));
	elemconfig = (char **)malloc(120 * sizeof(char *));
	for(i=0; i<120; i++ ) {
		elemnames[i] = (char*)malloc(17 * sizeof(char));
	}
	for(i=0; i<120; i++ ) {
		elemconfig[i] = (char*)malloc(22 * sizeof(char));
	}
	
	elem0.Z = 0;
	elem0.X = ' ';
	elem0.x = ' '; 
	ptable[0] = elem0;

	elem119.Z = 119;
	elem119.X = ' ';
	elem119.x = ' ';
	ptable[119] = elem119;
	gen_elements1();
}



#endif