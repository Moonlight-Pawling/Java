#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
int main()
{
    printf("\n				EXAMEN ORDINARIO DE INTRODUCCION A LA PROGRAMACION\n\n");
    printf("						Angelo Vera Pawling\n\n");
    printf("  Indicacion: El alumno escribira un codigo en lenguaje C++, que calcule la factorial (F) de 5 numeros cualquiera.\n");
    printf("  Una vez obtenido F de cada numero, el programa debe:\n");
    printf("  1. Determinar si F de cada uno de los numeros es par o non, enviando un mensaje del tipo del que se trate.\n"); 
    printf("  2. Determinar cual de las cinco F es la mayor y cual la menor.\n\n");
    int numerosaordenar;
    printf("  Diga a cuantos numeros desea obtenerles su factorial:  ");
    scanf(" %d", &numerosaordenar);
    printf("\n  Diga, en el orden que quiera, cuales son...\n");
    int vector_numeros[numerosaordenar];
    int i, j, k=1;
    for(i=0;i<numerosaordenar;i++)
    {
        printf("  %d: ", k);
        scanf(" %d", &j);
        vector_numeros[i] = j;
        k++;
    }
   
    int x, y;
    for(i=0;i<numerosaordenar;i++)
    {
        for(j=i+1;j<numerosaordenar;j++)
        {
            x = vector_numeros[i] - vector_numeros[j];
            if(x>0)
            {
                y = vector_numeros[j];
                vector_numeros[j] = vector_numeros[i];
                vector_numeros[i] = y;
            }
        }
    }
    
    printf("\n  Bien. Ahora sus numeros estarian ordenados de esta forma:  \n");
    printf("  ");
    for(i=0;i<numerosaordenar;i++)
    {
        printf("%d  ", vector_numeros[i]);
    }
    
    int vector_factoriales[numerosaordenar], f;
    for(i=0;i<numerosaordenar;i++)
    {
        if(vector_numeros[i]<0) vector_factoriales[i]=0;
        else {
		if(vector_numeros[i]==0) vector_factoriales[i]=1;
             else{
             vector_factoriales[i]=1;
             for (f=1; f<=vector_numeros[i]; f++){
             vector_factoriales[i]=vector_factoriales[i]*f;
              }
			}
        }
    }
    
    printf("\n\n  Estos son sus factoriales:  \n");
    printf("  ");
    for(i=0;i<numerosaordenar;i++)
    {
        printf("%d  ", vector_factoriales[i]);
    }
    
    printf("\n\n  Estos son los pares e impares:  \n");
    for(i=0;i<numerosaordenar;i++)
    {
    	printf("  ");
    	if (vector_factoriales[i]%2==0) {
    		printf("%d es par\n", vector_factoriales[i]);
		}
		else{
			printf("%d es impar\n", vector_factoriales[i]);
		}
    }
    
    int maximo, minimo;
    maximo=vector_factoriales[0];
    minimo=vector_factoriales[0];
    
    for(i=0;i<numerosaordenar;i++){
    if(vector_factoriales[i]> maximo){
      maximo = vector_factoriales[i];
    }
    if(vector_factoriales[i]<minimo){
      minimo = vector_factoriales[i];
    }
   } 
    
    printf("\n  El mayor numero factorial es: %d",maximo);
    printf("\n  El menor numero factorial es: %d\n\n",minimo);
    printf("  ");
    system("pause");
    return 0;
}