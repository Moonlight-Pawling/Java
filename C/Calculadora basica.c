#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <windows.h>  
using namespace std;
char r;
float num1, num2;

int main(){

   cout<<"\n                         CALCULADORA  ";
   cout<<"\n                            Menu        ";
   cout<<"\n Esta calculadora te permite hacer varias operaciones";
   cout<<"\n Suma						+ ";
   cout<<"\n Resta     					- ";
   cout<<"\n Multiplicacion					* ";
   cout<<"\n Division  					/ ";
   cout<<"\n Potencia					^ ";
   cout<<"\n Raiz cuadrada					v ";
   cout<<"\n Porcentaje					%\n";
   cout<<"\n Empezar otra operacion	o salir			= \n";
      
   cout<<"\n Introduce tu numero: ";
   bucle:
   cin>>num1;
   cout<<"\n Introduce el operador: ";
   cin>>r;
   	do{
	   do{
	   switch(r)
	   {
	   	case '+':
		cout<<"\n Introduce el otro sumando: ";
	   	cin>>num2;
	   	num1=num1+num2;
	   	cout<<"\n El resultado es "<<num1<<"\n";
	   	break;
   	
   		case '-':
   		cout<<"\n Introduce el sustraendo: ";
   		cin>>num2;
   		num1=num1-num2;
   		cout<<"\n El resultado es "<<num1<<"\n";
   		break;
   	
   		case '*':
   		cout<<"\n Introduce el otro factor: ";
   		cin>>num2;
   		num1=num1*num2;
   		cout<<"\n El resultado es "<<num1<<"\n";
   		break;
   	
   		case '/':
   		cout<<"\n Introduce el divisor: ";
   		cin>>num2;
   		num1=num1/num2;
   		cout<<"\n El resultado es "<<num1<<"\n";
   		break;
   		
   		case '%':
   		cout<<"\n Introduce el porcentaje que quieres sacar: ";
   		cin>>num2;
   		num1=num2*num1/100;
   		cout<<"\n El resultado es "<<num1<<"\n";
   		break;
   		
   		case 'V':
   		case 'v':  			
   		num1=sqrt(num1);
   		cout<<"\n El resultado es "<<num1<<"\n";
   		break;
   		
   		case '^':
   		cout<<"\n Introduce el exponente: ";
   		cin>>num2;
   		num1=pow(num1,num2);
   		cout<<"\n El resultado es "<<num1<<"\n";
   		break;
   	
   		cout<<num1;
   		default:
		    cout<<"\n Operador invalido\n";
   		
   		}
   		cout<<"\n Siguiente operador: ";
		cin>>r;
		}while(r!='=');
	cout<<"\n\n El resultado final es: "<<num1<<"\n";
	
	cout<<"\n Quiere iniciar otro calculo";
	cout<<"\n Si = Y\n No = X\n ";
	cin>>r;
	if(r=='y' or r=='Y'){
		cout<<"\n Nueva operacion \n Introduce tu nuevo numero: ";	
		goto bucle;
		}
	 	else{
	 	cout<<" Fin del programa\n";
		 }
	}while(r=='Y' or r=='y');
	
	system("pause");
	return(0);

}
