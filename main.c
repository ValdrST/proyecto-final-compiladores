#include <stdio.h>
#include "tablaSimbol.h"
#include "pilaTablaSimbol.h"
#include "tablaTipo.h"
#include "pilaTablaTipo.h"




int main(int argc, char *argv[]){
    typestack *ptt = crearTypeStack();
    symstack *pts = crearSymStack();
    insertarTypeTab(ptt,crearTypeTab()); //Insertar tabla de tipos y crearla
    printf("%d\n",insertarTipo(getCimaType(ptt),crearTipo(1,"int",4,1)));
    printTablaTipos(getCimaType(ptt));
    return 0;
}