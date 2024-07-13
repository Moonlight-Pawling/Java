#include<stdio.h>
#define T 30
int divisores[T];
int sumadedivisores(int x);
int resultado;
int numero;
float mod;
int originalnumber;

int main() {
	//printf("128 mod 128 = %d.\n",128%128); char[] max value 1 byte = 128.
	//printf("Por limitaciones de variable tipo entero, el numero maximo es 127\n"); corregido: resuelto cambiando char[] a int[].
    printf("Ingrese un numero: ");
    scanf("%d",&numero);
    puts("");
    resultado=sumadedivisores(numero);
    puts("");
    printf("La suma de todos los divisores es: %d.",resultado);

return 0;
}


int sumadedivisores(int x) {
	originalnumber=numero;
    int i=0;
    puts("Los divisores de su numero son:");
    //printf("numero original %d\n",numero);
    while(numero>0) {
    mod=originalnumber%numero;
    //printf("originalnumber mod numero %d\n",mod);
    //printf("originalnumber %d\n",originalnumber);
    if (mod==0){
    	divisores[i]=numero;
    	printf("%d\n",divisores[i]);
    	i++;
	}
    numero=numero-1;
    //printf("Numero-1: %d\n",numero);
    }
    int cantidaddedivisores=i+1;
    int sumdiv=0;
    for (i=0;i<cantidaddedivisores;i++){
       sumdiv+=divisores[i];
    }   
return sumdiv;
}
