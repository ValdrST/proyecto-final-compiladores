#include "cMips.h"

int genCod(char* res,char * operacion,char * op1,char * op2,FILE *arch,FILE * arch2,int contador){
	int aux1,aux2;
	float auxf1,auxf2;
	//aqui comienza el switch
	if (strcmp(operacion,"label")==0){
		fprintf(arch,"%s:\n",op1);
		return 0;
	}
	if (strcmp(operacion,"goto")==0){
		fprintf(arch,"\tgoto %s\n",op1);
		return 0;	
	}
	if (strcmp(operacion,"+")==0){
		if (definirTipo(op1)==0 && definirTipo(op2)==0)
			fprintf(arch, "\tli %s,%d\n",getDirr(res),atoi(op1)+atoi(op2));
		else if (definirTipo(op1)==1 && definirTipo(op2)==1)
			fprintf(arch, "\tli %s,%.4f\n",getDirr(res),atof(op1)+atof(op2));
		else if (definirTipo(op1)==0)
			fprintf(arch,"\taddi %s,%s,%s\n",getDirr(res),getDirr(op2),op1);
		else if (definirTipo(op1)==1)
			fprintf(arch,"\taddi %s,%s,%.4f\n",getDirr(res),getDirr(op2),atof(op1));
		else if (definirTipo(op2)==0)
			fprintf(arch,"\taddi %s,%s,%s\n",getDirr(res),getDirr(op1),op2);
		else if (definirTipo(op2)==1)
			fprintf(arch,"\taddi %s,%s,%.4f\n",getDirr(res),getDirr(op1),atof(op2));
		else
			fprintf(arch,"\tadd %s,%s,%s\n",getDirr(res),getDirr(op1),getDirr(op2));
		return 0;
	}
	if (strcmp(operacion,"=")==0){
		if (definirTipo(op1)==0)
			fprintf(arch, "\tli %s,%s\n",getDirr(res),op1);
		if (definirTipo(op1)==1)
			fprintf(arch, "\tli %s,%.4f\n",getDirr(res),atof(op1));
		else
			fprintf(arch,"\tmove %s,%s\n",getDirr(res),getDirr(op1));
		return 0;
	}
	if (strcmp(operacion,"print")==0){
		if (op1[0]=='\"' || op1[0]=='\''){
			fprintf(arch2, "string%d\t.asciiz %s\n",contador,op1);
			fprintf(arch, "\tli $v0, 4\n" );
			fprintf(arch, "\tla $a0, string%d\n",contador);
			fprintf(arch, "\tsyscall\n");
		}
		else if (definirTipo(op1)==0){
			fprintf(arch, "\tli $v0, 1\n" );
			fprintf(arch, "\tli $a0, %s\n",op1);
			fprintf(arch, "\tsyscall\n" );
		}
		else if (definirTipo(op1)==1){
			fprintf(arch, "\tli $v0, 2\n" );
			fprintf(arch, "\tli $a0, %.4f\n",atof(op1));
			fprintf(arch, "\tsyscall\n" );
		}
		return 0;
	}
	if (strcmp(operacion,"return")==0){
		if (definirTipo(op1)==0)
			fprintf(arch, "\tli $v1,%s\n",op1 );
		else if (definirTipo(op1)==1)
			fprintf(arch, "\tli $v1,%.4f\n",atof(op1) );
		else
			fprintf(arch, "\tmove $v1,%s\n",getDirr(op1) );
		fprintf(arch, "\tjr $ra\n");
		return 0;
	}
	if (strcmp(operacion,"%")==0){
		if (definirTipo(op1)==0 && definirTipo(op2)==0){
			fprintf(arch, "\tli %s,%d\n",getDirr(res),atoi(op1)%atoi(op2));
		}
		else if (definirTipo(op1)==0){
			fprintf(arch, "\tli $t0,%s\n",op1);
			fprintf(arch, "\tDIV $t0,%s\n",getDirr(op2));
		}else if (definirTipo(op2)==0){
			fprintf(arch, "\tli $t0,%s\n",op2);
			fprintf(arch, "\tDIV %s,%t0\n",getDirr(op1));
		}
		else
			fprintf(arch, "\tDIV %s,%s\n",getDirr(op1),getDirr(op2));
		fprintf(arch, "\tMFHI %s\n",getDirr(res));
		return 0;
	}
	if (strcmp(operacion,"-")==0){
		if (definirTipo(op1)==0 && definirTipo(op2)==0)
			fprintf(arch, "\tli %s,%d\n",getDirr(res),atoi(op1)-atoi(op2));
		else if (definirTipo(op1)==1 && definirTipo(op2)==1)
			fprintf(arch, "\tli %s,%.4f\n",getDirr(res),atof(op1)-atof(op2));
		else if (definirTipo(op1)==0)
			fprintf(arch,"\tsubu %s,%s,%s\n",getDirr(res),getDirr(op2),op1);
		else if (definirTipo(op1)==1)
			fprintf(arch,"\tsubu %s,%s,%.4f\n",getDirr(res),getDirr(op2),atof(op1));
		else if (definirTipo(op2)==0)
			fprintf(arch,"\tsubu %s,%s,%s\n",getDirr(res),getDirr(op1),op2);
		else if (definirTipo(op2)==1)
			fprintf(arch,"\tsubu %s,%s,%.4f\n",getDirr(res),getDirr(op1),atof(op2));
		else
			fprintf(arch,"\tsub %s,%s,%s\n",getDirr(res),getDirr(op1),getDirr(op2));
		return 0;
	}
	if (strcmp(operacion,"/")==0){
		if (definirTipo(op1)==0 && definirTipo(op2)==0)
			fprintf(arch, "\tli %s,%d\n",getDirr(res),atoi(op1)/atoi(op2));
		else if (definirTipo(op1)==1 && definirTipo(op2)==1)
			fprintf(arch, "\tli %s,%.4f\n",getDirr(res),atof(op1)/atof(op2));
		else if (definirTipo(op1)==0)
			fprintf(arch,"\tdiv %s,%s\n",getDirr(op2),op1);
		else if (definirTipo(op1)==1)
			fprintf(arch,"\tdiv %s,%.4f\n",getDirr(op2),atof(op1));
		else if (definirTipo(op2)==0)
			fprintf(arch,"\tdiv %s,%s\n",getDirr(op1),op2);
		else if (definirTipo(op2)==1)
			fprintf(arch,"\tdiv %s,%.4f\n",getDirr(op1),atof(op2));
		else
			fprintf(arch,"\tdiv %s,%s\n",getDirr(op1),getDirr(op2));
		fprintf(arch, "\tMFLO %s\n",getDirr(res));
		return 0;
	}
	if (strcmp(operacion,"*")==0){
		if (definirTipo(op1)==0 && definirTipo(op2)==0)
			fprintf(arch, "\tli %s,%d\n",getDirr(res),atoi(op1)*atoi(op2));
		else if (definirTipo(op1)==1 && definirTipo(op2)==1)
			fprintf(arch, "\tli %s,%.4f\n",getDirr(res),atof(op1)*atof(op2));
		else if (definirTipo(op1)==0){
			fprintf(arch, "\tli $t0,%d\n",atoi(op1));
			fprintf(arch,"\tmult $t0,%s\n",getDirr(op2));
		}
		else if (definirTipo(op1)==1){
			fprintf(arch, "\tli $t0,%.4f\n",atof(op1));
			fprintf(arch,"\tmult $t0,%s\n",getDirr(op2));
		}
		else if (definirTipo(op2)==0){
			fprintf(arch, "\tli $t0,%d\n",atoi(op2));
			fprintf(arch,"\tmult $t0,%s\n",getDirr(op1));
		}
		else if (definirTipo(op2)==1){
			fprintf(arch, "\tli $t0,%.4f\n",atof(op2));
			fprintf(arch,"\tmult $t0,%s\n",getDirr(op1));
		}
		else
			fprintf(arch,"\tmult %s,%s\n",getDirr(op1),getDirr(op2));
		fprintf(arch, "\tMFHI %s\n",getDirr(res) );
		fprintf(arch, "\tsll %s,%s,16\n",getDirr(res),getDirr(res));
		fprintf(arch, "\tMFLO %s\n",getDirr(res));
		return 0;
	}
	if (strcmp(operacion,"<")==0){
		if (definirTipo(op1)==0 && definirTipo(op2)==0)
			if (atoi(op1)<atoi(op2))
				fprintf(arch, "\tli %s,%d\n",getDirr(res),1);
			else
				fprintf(arch, "\tli %s,%d\n",getDirr(res),0);
		else if (definirTipo(op1)==1 && definirTipo(op2)==1)
			if (atof(op1)<atof(op2))
				fprintf(arch, "\tli %s,%d\n",getDirr(res),1);
			else
				fprintf(arch, "\tli %s,%d\n",getDirr(res),0);
		else if (definirTipo(op1)==0)
			fprintf(arch,"\tslti %s,%s,%s\n",getDirr(res),getDirr(op2),op1);
		else if (definirTipo(op1)==1)
			fprintf(arch,"\tslti %s,%s,%.4f\n",getDirr(res),getDirr(op2),atof(op1));
		else if (definirTipo(op2)==0)
			fprintf(arch,"\tslti %s,%s,%s\n",getDirr(res),getDirr(op1),op2);
		else if (definirTipo(op2)==1)
			fprintf(arch,"\tslti %s,%s,%.4f\n",getDirr(res),getDirr(op1),atof(op2));
		else
			fprintf(arch,"\tslt %s,%s,%s\n",getDirr(res),getDirr(op1),getDirr(op2));
		return 0;
	}
	if (strcmp(operacion,">")==0){
		if (definirTipo(op1)==0 && definirTipo(op2)==0)
			if (atoi(op1)>atoi(op2))
				fprintf(arch, "\tli %s,%d\n",getDirr(res),1);
			else
				fprintf(arch, "\tli %s,%d\n",getDirr(res),0);
		else if (definirTipo(op1)==1 && definirTipo(op2)==1)
			if (atof(op1)>atof(op2))
				fprintf(arch, "\tli %s,%d\n",getDirr(res),1);
			else
				fprintf(arch, "\tli %s,%d\n",getDirr(res),0);
		else if (definirTipo(op1)==0)
			fprintf(arch,"\tslti %s,%s,%s\n",getDirr(res),op1,getDirr(op2));
		else if (definirTipo(op1)==1)
			fprintf(arch,"\tslti %s,%s,%.4f\n",getDirr(res),atof(op1),atof(op2));
		else if (definirTipo(op2)==0)
			fprintf(arch,"\tslti %s,%s,%s\n",getDirr(res),op2,getDirr(op1));
		else if (definirTipo(op2)==1)
			fprintf(arch,"\tslti %s,%s,%.4f\n",getDirr(res),atof(op2),atof(op1));
		else
			fprintf(arch,"\tslt %s,%s,%s\n",getDirr(res),getDirr(op2),getDirr(op1));
		return 0;
	}
	if (strcmp(operacion,"&&")==0){
		if (definirTipo(op1)==0 && definirTipo(op2)==0)
			fprintf(arch, "\tli %s,%d\n",getDirr(res),atoi(op1)&atoi(op2));
		else if (definirTipo(op1)==0)
			fprintf(arch,"\tandi %s,%s,%s\n",getDirr(res),getDirr(op2),op1);
		else if (definirTipo(op2)==0)
			fprintf(arch,"\tandi %s,%s,%s\n",getDirr(res),getDirr(op1),op2);
		else
			fprintf(arch,"\tand %s,%s,%s\n",getDirr(res),getDirr(op1),getDirr(op2));
		return 0;	
	}
	if (strcmp(operacion,"||")==0){
		if (definirTipo(op1)==0 && definirTipo(op2)==0)
			fprintf(arch, "\tli %s,%d\n",getDirr(res),atoi(op1)|atoi(op2));
		else if (definirTipo(op1)==0)
			fprintf(arch,"\tori %s,%s,%s\n",getDirr(res),getDirr(op2),op1);
		else if (definirTipo(op2)==0)
			fprintf(arch,"\tori %s,%s,%s\n",getDirr(res),getDirr(op1),op2);
		else
			fprintf(arch,"\tor %s,%s,%s\n",getDirr(res),getDirr(op1),getDirr(op2));
		return 0;	
	}
	if (strcmp(operacion,"if")==0){
		fprintf(arch, "\t#No se que hacer con un if :(\n");
		return 1;
	}
	else{
		fprintf(arch, "\tnop\n");
		return 1;
	}
}

char * getDirr(char * etc){
	return etc;
}

int definirTipo(char * cadena){
	return 2;
	//regresa 
		// 0 -> entero
		// 1 -> flotante
		// 2 -> cadena
	int i;
	int punto=0; //punto es falso
	int entero=0;
	int cad=0;
	for(i=0;i<strlen(cadena);i++){
		if(cadena[i]<58 &&  cadena[i]>47 && cad==0)
			entero=1;
		else if(cadena[i]=='.' && entero==1)
			punto=1;
		else
			cad=1;
	}
	if(punto==1)
		return 1;
	else if (entero==1)
		return 0;
	else
		return 2;
}
