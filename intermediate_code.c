#include "intermediate_code.h"
#include <stdio.h>
#include <stdlib.h>

/* Funcion encargada de inicializar la tabla de cuadruplas. */
void init_code(){
	CODE = *crea_code();
}

int gen_code(char *op , char *arg1, char *arg2, char *res){
	quad *q = crea_quad(op,arg1,arg2,res);
	code *c;
	*c = CODE;
	agregar_cuadrupla(c,op,arg1,arg2,res);
	return c->num_instrucciones -1;
}

/* Funcion encargada de llenar la tabla con cuadruplas. */
quad* crea_quad(char *op , char *arg1, char *arg2, char *res){
	quad *q;
	q = malloc(sizeof(quad));
	q->op = op;
	q->arg1 = arg1;
	q->arg2 = arg2;
	q->res = res;
	return q;
}

void agregar_cuadrupla(code* c, char *op, char* arg1, char *arg2, char* res){
	quad *q;
	q = crea_quad(op,arg1,arg2,res);
	*(c->root + c->num_instrucciones) = *q;
		c->num_instrucciones++;
}

code* crea_code(){
	code *c;
	c = malloc(sizeof(code));
	c->root = malloc(sizeof(quad));
	c->num_instrucciones = 0;
	return c;
}

void elimina_quad(quad *q){
	while(q != NULL){
		elimina_quad(q->next);
	}
	free(q);
}

void elimina_code(code *c){
	free(c);
	elimina_quad(c->root);
}


/* Funcion que crea una lista dentro de una etiqueta. */
label create_list(int l){
	label list;
	list.items = malloc(sizeof(int) * 100);
	list.i = 0;
	list.items[list.i] = l;
	list.i++;
	return list;
}

/* Funcion encargadad de copiar las listas de ambas etiquetas. */
label merge(label l1, label l2){
	label l;
	l = l1;
	for(int i = 0; i < l2.i; i++){
		l.items[l.i] = l2.items[i];
		l.i++;
	}
	return l;
}

/* Funcion encargada de cambiar la localizacion donde se almacenara el resultado. */
void backpatch(label l, int inst){
	char* res = malloc(sizeof(char) * 100);
	for(int i = 0; i < l.i ; i++){
		sprintf(res, "%d", inst);
		(CODE.root[l.items[i]]).res = res;
	}
}

/* Funcion que imprime las cuadruplas. */
void print_code(){
    printf("\n*** CODIGO INTERMEDIO ***\n");
    printf("inst\top\targ1\targ2\tres\n");
    for(int i = 0; i < CODE.num_instrucciones; i++){
        printf("%d\t%s\t%s\t%s\t%s\n",i, CODE.root[i].op, CODE.root[i].arg1, CODE.root[i].arg2, CODE.root[i].res);
    }
}