//Biblioteca
#include <stdio.h>
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

using namespace std;
void gotoxy(int x,int y)
{  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos); 
}

int main(){
	string clave[6]={"Clave",	"HGTER","P2OMNT","LOUVRT","VFROP","TRRADE"}; 
	string descripcion[6]={"Descripcion","Laptop Sony",	"Audifono NB","HD-externo XT","Bocinas Champ","Celular Zeta M45"}; 
	int precio[6]={0,17500,1200,19080,2340,4790};
	int compra[6]={0,0,0,0,0,0};
	int producto,i,j,total,y,d, cantidadtotal, preciodescuento;

	gotoxy(12,1); cout<<"Electronica 'Luz de Luna'";
	for(i=0; i<6; i++){//imprime las listas
		d=i+2;
		gotoxy(1,i+3);
		cout<<i+1;
		gotoxy(5,d);
		cout<<clave[i];
		gotoxy(16,d);
		cout<<descripcion[i];	
		gotoxy(34,d);
		cout<<precio[i];
	}

	do{
		gotoxy(1,8);cout<<"Escoge un producto      [ ]\n";
		gotoxy(26,8);cin>>producto;
		cout<<"\n Teclea 0 para terminar o salir\n"; 
		if(producto>=1&producto<=5){
			cout<<"\n";
			compra[producto]+=1;
			gotoxy(1,12);
			cout<<"Cantidad";	
			gotoxy(13,12);
			cout<<"Clave";	
			gotoxy(21,12);
			cout<<"Descripcion";	
			gotoxy(40,12);
			cout<<"Precio";
			for(j=1;j<6;j++){//recorre la lista
				if (compra[j]>0){
					y=10+(3*j);
					gotoxy(1,y);
					cout<<compra[j];
					gotoxy(13,y);
					cout<<clave[j];
					gotoxy(21,y);
					cout<<descripcion[j];
					gotoxy(41,y);
					cout<<compra[j]*precio[j];	
				}
			}
			
		}
		if (producto==0){
			system("cls");
			gotoxy(1,6);
			cout<<"Cantidad";	
			gotoxy(13,6);
			cout<<"Descripcion";	
			gotoxy(26,6);
			cout<<"Precio";	
			gotoxy(45,6);
			cout<<"Total";
			for(i=1;i<6;i++){
				if (compra[i]>0){
					y=5+(4*i);
					gotoxy(1,y);
					cout<<compra[i];
					gotoxy(13,y);
					cout<<clave[i];
					gotoxy(26,y);
					cout<<descripcion[i];
					if (compra[i]==2){
						gotoxy(45,y);
					    cout<<compra[i]*precio[i];
						gotoxy(26,y+1);
						cout<<"15% de descuento";
						preciodescuento=(compra[i]*precio[i])-(0.15*(compra[i]*precio[i]));
						gotoxy(45,y+1);
						cout<<preciodescuento;
						total=total+preciodescuento;
					}
					else {
						if (compra[i]==3){
							gotoxy(45,y);
					    	cout<<compra[i]*precio[i];
							gotoxy(26,y+1);
							cout<<"20% de descuento";
							preciodescuento=(compra[i]*precio[i])-(0.20*(compra[i]*precio[i]));
							gotoxy(45,y+1);
							cout<<preciodescuento;
							total=total+preciodescuento;
						}
						else{
							if (compra[i]>3){
								gotoxy(45,y);
					    		cout<<compra[i]*precio[i];
								gotoxy(26,y+1);
								cout<<"25% de descuento";
								preciodescuento=(compra[i]*precio[i])-(0.25*(compra[i]*precio[i]));
								gotoxy(45,y+1);
								cout<<preciodescuento;
								total=total+preciodescuento;
							}
							else{
								if (compra[i]=1){
									total=total+(compra[i]*precio[i]);
									gotoxy(45,y);
									cout<<compra[i]*precio[i];	
								}
							}
						}
					
					}
				}
			}
			gotoxy(26,y+3);
			cout<<"Cant. total:	     "<<total;
		}   
	}while(producto!=0);
}