#ifndef ELEMH
#define ELEMH
#include "stdio.h"
//aqui irao ser definidas todas as propriedades sobre os elementos da tabela.
//Vamos usar python + a base de dados que ja temos para isso
//Struct base:
struct elem{
	int Z; 
	double a_w;
	char X, x; // letras do nome
	char e_config[22];
	int g, p; //grupo e periodo
	char b; //bloco
	long int a,c,d,e; //TODO: REMOVE THIS TO COMPILE RELEASES; servem so para avisar quando estiver a ficar com pouco espaco para alocar
};

char ** elemnames;
struct elem ptable[120]; //0 e 119 sao para offset


//E no proximo include que esta funcao void gen_elements(), que gera a data da tabela periodica
#include "elemz.h"
//fazer uma data de assignments hardcoded, na querida linguagem que e python
void initialize_elements() {
	struct elem elem0;
	struct elem elem119;
	int i;
	//elem0 tem os minimizantes e elem119 os maximizantes
	elemnames = (char **)malloc(120 * sizeof(char *));
	for(i=0; i<120; i++ ) {
		elemnames[i] = (char*)malloc(17 * sizeof(char));
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