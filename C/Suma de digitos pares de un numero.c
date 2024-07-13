#include<stdio.h>
#define T 30
char digitos[T];
int sumadedigitospares(int x);
int resultado;
int numero, nummod,mod;
int main() {
    printf("Ingrese un numero: ");
    scanf("%d",&numero);
    puts("");
    resultado=sumadedigitospares(numero);
    puts("");
    printf("La suma de los digitos pares es: %d.",resultado);
return 0;
}

int sumadedigitospares(int x) {
    int i=0;
    puts("Los digitos pares de su numero son:");
    while(numero>0) {
    nummod=numero%10;
//    printf("nummod %d\n",nummod);
    mod=nummod%2;
//    printf("mod %d\n",mod);
    if (mod==0) {
    	digitos[i]=nummod;
    	printf("%d\n", digitos[i]);
    	i++;
	}
    numero=numero/10;
    }
    
    int sumadepares=0;
    int cantidaddedigitos=i+1;
    int numeromayor=0;
    for (i=0;i<cantidaddedigitos;i++){
       sumadepares+=digitos[i];
    }   
return sumadepares;
}