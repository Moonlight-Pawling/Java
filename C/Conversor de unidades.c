// Angelo Vera Pawling - S19009354 - Conversor de unidades

#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

void gotoxy(int x,int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y= y;
	SetConsoleCursorPosition(hcon,dwPos);
}

using namespace std;
int op, deci, bin,rd, secs;
char hc,restart;
char chexa[2];
int bina[8];
int hexa;
int rhexa[5];
int i,j,z,s,w, hn,k;

int main() {

	do {
start:
		cout<<"		Bienvenido al conversor de numeros \n";
		cout<<"\n	teclea	0	para salir";
		cout<<"\n	teclea	1	para convertir decimal 		a 	binario";
		cout<<"\n	teclea	2	para convertir decimal		a 	hexadecimal";
		cout<<"\n	teclea	3	para convertir binario 		a	hexadecimal";
		cout<<"\n	teclea	4	para convertir hexadecimal 	a 	decimal";
		cout<<"\n	teclea	5	para convertir binario 		a 	decimal";
		cout<<"\n	teclea	6	para convertir hexadecimal 	a 	binario";

		gotoxy(8,9);
		cout<<"[ ]";
		gotoxy(9,9);
		cin>>op;

		switch(op) {
			//Decimal a binario
			case(0):
				cout<<"\n	Programa finalizado.";
				goto exit;
				break;
			case(1):
				cout<<"\n	Introduce tu numero decimal menor o igual a 255 \n";
				gotoxy(8,12);
				cin>>deci;
				j=0;
				cout<<"	El resultado es: ";
				for(i=0; i<8; i++) {
					j++;
					rd=deci%2;
					bina[j]=rd;
					deci=deci/2;
				}
				for(i=8; i>0; i--) {
					bin=bina[i];
					cout<<bin<<" ";
				}
				break;
			//Decimal a hexadecimal
			case(2):
				cout<<"\n	Introduce tu numero decimal menor a 999\n";
				gotoxy(8,12);
				cin>>deci;
				i=0;
				cout<<"	El resultado es: ";
				while (deci>0) {
					rd=deci%16;
					i++;
					rhexa[i]=rd;
					deci=deci/16;
				}
				for(i=4; i>0; i--) {
					hexa=rhexa[i];
					if(hexa<=9) {
						cout<<hexa;
					} else {
						switch(hexa) {
							case(10):
								cout<<"A";
								break;
							case(11):
								cout<<"B";
								break;
							case(12):
								cout<<"C";
								break;
							case(13):
								cout<<"D";
								break;
							case(14):
								cout<<"E";
								break;
							case(15):
								cout<<"F";
								break;
						}
					}
				}
				break;
			//Binario a hexadecimal
			case(3):
				cout<<"\n	Introduce tu numero binario maximo de 8 digitos, solo desde comienza el primer 1, ejemplo: 10, 101\n";
				gotoxy(8,13);
				cin>>bin;
				z=bin/10000;
				w=bin-(z*10000);
				cout<<"	El resultado es: ";
				for(s=0; s<2; s++) {
					switch(z) {
						case(0):
							cout<<"0";
							break;
						case(1):
							cout<<"1";
							break;
						case(10):
							cout<<"2";
							break;
						case(11):
							cout<<"3";
							break;
						case(100):
							cout<<"4";
							break;
						case(101):
							cout<<"5";
							break;
						case(110):
							cout<<"6";
							break;
						case(111):
							cout<<"7";
							break;
						case(1000):
							cout<<"8";
							break;
						case(1001):
							cout<<"9";
							break;
						case(1010):
							cout<<"A";
							break;
						case(1011):
							cout<<"B";
							break;
						case(1100):
							cout<<"C";
							break;
						case(1101):
							cout<<"D";
							break;
						case(1110):
							cout<<"E";
							break;
						case(1111):
							cout<<"F";
							break;
					}
					z=bin-(z*10000);
				}
				break;
			//hexadecimal a decimal
			case(4):
				cout<<"\n	Introduce tu numero hexadecimal de 2 digitos, si solo tiene 1 inicia con 0\n";
				s=3;
				j=0;
				while(s>0) {
					gotoxy(9,14);
					cin>>hc;
					switch(hc) {
						case('0'):
							i=0;
							break;//convertira los valores de string a decimal
						case('1'):
							i=1;
							break;
						case('2'):
							i=2;
							break;
						case('3'):
							i=3;
							break;
						case('4'):
							i=4;
							break;
						case('5'):
							i=5;
							break;
						case('6'):
							i=6;
							break;
						case('7'):
							i=7;
							break;
						case('8'):
							i=8;
							break;
						case('9'):
							i=9;
							break;
						case('A'):
							i=10;
							break;
						case('a'):
							i=10;
							break;
						case('B'):
							i=11;
							break;
						case('b'):
							i=11;
							break;
						case('C'):
							i=12;
							break;
						case('c'):
							i=12;
							break;
						case('D'):
							i=13;
							break;
						case('d'):
							i=13;
							break;
						case('E'):
							i=14;
							break;
						case('e'):
							i=14;
							break;
						case('F'):
							i=15;
							break;
						case('f'):
							i=15;
							break;
					}
					s--;
					j++;
					w=i*pow(16,s);//
					rhexa[j]=w;
				}
				hexa=rhexa[1]+rhexa[2]+rhexa[3];
				cout<<hexa;
				break;
			case(5):
				cout<<"\n	Introduce tu numero binario menor a 8 caracteres \n";
				gotoxy(8,12);
				cin>>bin;
				i=0;
				rd=0;
				deci=0;
				while(bin!=0) {
					rd=bin%10;
					bin/=10;
					deci+=rd*pow(2,i);
					i++;
				}
				cout<<"	El resultado es: "<<deci;
				break;
			case(6):

				cout<<"\n	Introduce tu numero hexadecimal de 2 digitos \n";
				s=2;
				j=0;
				k=0;
				while(s>0) {
					/*	if(s==1){
							gotoxy(11,12);
							cin>>hc;
						}*/
					//else{
					gotoxy(8,12);
					cin>>hc,'\n';
					//}
					cout<<"\n	El resultado es: ";
					switch(hc) {
						case('0'):
							i=0;
							break;
						case('1'):
							i=1;
							break;
						case('2'):
							i=2;
							break;
						case('3'):
							i=3;
							break;
						case('4'):
							i=4;
							break;
						case('5'):
							i=5;
							break;
						case('6'):
							i=6;
							break;
						case('7'):
							i=7;
							break;
						case('8'):
							i=8;
							break;
						case('9'):
							i=9;
							break;
						case('A'):
							i=10;
							break;
						case('a'):
							i=10;
							break;
						case('B'):
							i=11;
							break;
						case('b'):
							i=11;
							break;
						case('C'):
							i=12;
							break;
						case('c'):
							i=12;
							break;
						case('D'):
							i=13;
							break;
						case('d'):
							i=13;
							break;
						case('E'):
							i=14;
							break;
						case('e'):
							i=14;
							break;
						case('F'):
							i=15;
							break;
						case('f'):
							i=15;
							break;
					}
					s--;
					j++;
					w=i*pow(16,s);
					rhexa[j]=w;
				}
				hexa=rhexa[1]+rhexa[2];
				deci =hexa;

				for(z=0; z<8; z++) {
					k++;
					rd=deci%2;
					bina[k]=rd;
					deci=deci/2;
				}
				for(z=8; z>0; z--) {
					bin=bina[z];
					cout<<bin<<" ";
				}
				break;

			default:
				cout<<"	Ups! Introduce una opcion valida";
				secs=1000;
				Sleep(secs);
				system("cls");
				goto start;
		}
		cout<<"\n	Quiere iniciar otro calculo";
		cout<<"\n	Si = Y / No = X\n";
		cout<<"	";
		cin>>restart;
		if(restart=='y' or restart=='Y') {
			cout<<"\n	Nueva operacion, introduce tu nuevo comando";
			secs=1500;
			Sleep(secs);
			system("cls");
			goto start;
		} else {
			cout<<"\n	Fin del programa";
			op=0;
		}

	} while(op!=0);
	exit:
	return(0);
}