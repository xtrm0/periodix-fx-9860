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
	char e_config[30];
	int g, p; //grupo e periodo
	char b; //bloco
};

struct elem ptable[120]; //0 e 119 sao para offset


//E no proximo include que esta funcao void gen_elements(), que gera a data da tabela periodica
#include "elemz.h"
//fazer uma data de assignments hardcoded, na querida linguagem que e python
void initialize_elements() {
	struct elem elem0;
	struct elem elem119;
	//elem0 tem os minimizantes e elem119 os maximizantes
	elem0.Z = 0;
	elem0.X = ' ';
	elem0.x = ' '; 
	ptable[0] = elem0;

	elem119.Z = 119;
	elem119.X = ' ';
	elem119.x = ' ';
	ptable[119] = elem119;
	gen_elements();
}



#endif