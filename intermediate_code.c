#include <stdio.h>
#include <stdlib.h>
#include "intermediate_code.h"
#include "cMips.h"
/* Funcion encargada de inicializar la tabla de cuadruplas. */
void init_code(){
	CODE = *crea_code();
}

int gen_code(char *op , char *arg1, char *arg2, char *res){
	quad *q = crea_quad(op,arg1,arg2,res);
	code *c;
	c = &CODE;
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
	quad *q, *q_temp;
	q = crea_quad(op,arg1,arg2,res);
	if(c->root == NULL)
		c->root = q;
	else{
		q_temp = c->root;
		while(q_temp->next != NULL)
			q_temp = q_temp->next;
		q_temp->next = q;
		q->next = NULL;
	}
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
label *create_list(int l){
	
	label *list = malloc(sizeof(label));
	list->items = malloc(sizeof(int) * 100);
	list->i = 0;
	list->items[list->i] = l;
	list->i++;
	return list;
}

/* Funcion encargadad de copiar las listas de ambas etiquetas. */
label *merge(label *l1, label *l2){
	label *l = malloc(sizeof(label));
	l = l1;
	for(int i = 0; i < l2->i; i++){
		l->items[l->i] = l2->items[i];
		l->i++;
	}
	return l;
}

/* Funcion encargada de cambiar la localizacion donde se almacenara el resultado. */
void backpatch(label *l, label *l2){
	char res[100];
	int inst;
	if(l2){
		inst = l2->i;
		for(int i = 0; i < l->i ; i++){
			sprintf(res, "%d", inst);
			(CODE.root[l->items[i]]).res = res;
		}
	}
	
}
void concat_code(code *c1,code *c2){
	printf("kekekekkee");
	printf("%d",c2->num_instrucciones);
	for(int i = 0; i<c2->num_instrucciones; i++){
		agregar_cuadrupla(c1,c2->root[i].op,c2->root[i].arg1,c2->root[i].arg2,c2->root[i].res);
	}
}

/* Funcion que imprime las cuadruplas. */
void print_code(code *c){
    printf("\n*** CODIGO INTERMEDIO ***\n");
    printf("inst\top\targ1\targ2\tres\n");
	printf("%d\t%s\t%s\t%s\t%s\n",0, c->root->op, c->root->arg1, c->root->arg2, c->root->res);
	quad *q = c->root->next;
	int i = 1;
	FILE *arch1, *arch2;
	arch1 = fopen("out.s","w");
	arch2 = fopen("ascii.s","w");
	while(q != NULL){
		printf("%i\t%s\t%s\t%s\t%s\n",i, q->op, q->arg1, q->arg2, q->res);
		genCod(q->res,q->op,q->arg1,q->arg2,arch1,arch2,i);
		q = q->next;
		i++;
	}
	fclose(arch1);
	fclose(arch2);
}