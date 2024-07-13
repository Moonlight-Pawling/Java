#include<stdio.h>
//#include<math.h>
#include<stdlib.h>
#define T 30
int primos[T];
float rangesumadeprimos(int x, int y);
int numdivisores(int z);
int resultado;
int limiteinferior;
int limitesuperior;

int main() {
    printf("Ingrese el limite inferior: ");
    scanf("%d",&limiteinferior);
    printf("Ingrese el limite superior: ");
    scanf("%d",&limitesuperior);
    puts("");
    if(limiteinferior<=0 && limitesuperior<=0) {
	 printf("Los numeros menores o iguales a 1 no son primos.\n");
	 printf("Ajuste el rango e intente nuevamente.\n");
	} else if (limitesuperior<limiteinferior){
	 printf("Ha colocado mal los limites.\n");	
	 printf("Ajuste el rango e intente nuevamente.\n");
	} else {
    resultado=rangesumadeprimos(limiteinferior,limitesuperior);
    puts("");
    printf("La suma de todos los numeros primos de %d a %d es: %d.",limiteinferior,limitesuperior,resultado);
    }
return 0;
}


float rangesumadeprimos(int x, int y) {
	int sumadeprimos=0;
    int i=0;
    int lugar=0;
    int divisores=0;
    if (x==y && x==1) {
		printf("El unico numero en ese rango es el %d y no es primo",x);
	}
    else if (x==y && numdivisores(x)>2){
    	printf("El unico numero en ese rango es %d y no es primo.\n",x);   	
	} 
	else if (x==y && numdivisores(x)==2) {
		printf("El unico numero en ese rango es el %d y es primo.\n",x);
		sumadeprimos=x;
	}
    else {
    puts("Los numeros primos en ese rango de numeros son:");
	while(x<=y) {
		divisores=numdivisores(x);
		if (divisores==2 && x>1) {
		primos[lugar]=x;
		printf("Es primo: %d\n",primos[lugar]);
		lugar=lugar+1;
		}
		x++;
		}
	for (i=0;i<lugar;i++) {
		sumadeprimos=sumadeprimos+primos[i];
	}
	}
return sumadeprimos;
}

int numdivisores(int z) {
	int div=0;
	int i=0;
	for (i=1;i<=z;i++) {
		 	if (z%i==0) {
		 		div=div+1;	
		 	}
			}
	return div;
}           		
