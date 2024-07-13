//Estructuras
#include<stdio.h>
#include<windows.h>
#include<string.h>
#define T 30

void menu ();
int cambiarclave(int *n1, int *n2);
//char cambiarnombre(char *n1[30], char *n2[30]);
float cambiarprecio(float *n1, float *n2);
int cambiarcantidad(int *n1, int *n2);

typedef struct{
	int clave;
	char nombre[30];
	float precio;	
	int cantidad;
		
}datos;

int ultimoproducto=0, selector, i, upmascp, unidadesacomprar; //ultimoproducto marca el primer espacio en blanco en la estructura, al inicializarse el programa, la primera posicion no es 1, sino 0;
int cantidaddeproductosaingresar;
datos golosina[T];

int main(){
	do {
	menu();
	scanf("%d",&selector);
	puts("\n");
	switch(selector) {
			case 1: 
				puts("-------------------------------------------------------");
				puts("Por favor, rellene todos los campos de forma cuidadosa.");
				puts("-------------------------------------------------------");
				printf("Ingrese la cantidad de golosinas que desea agregar: ");
				scanf("%d",&cantidaddeproductosaingresar);
				if (cantidaddeproductosaingresar>=1) {
					//i=ultimoproducto;
					upmascp=ultimoproducto+cantidaddeproductosaingresar; //establece el limite superior para el ciclo for de escritura de datos en la estructura, es el numero total de productos
																		 //pero debido a que el primer espacio del vector es [0], esto significa que siempre estara 1 numero por encima.
					//printf("upmascp=%d",upmascp);							
					puts("\n");
					for(i=ultimoproducto;i<upmascp;i++){ // El i maximo debe ser un digito menor a la suma total de productos, debido a que el vector empieza en posicion 0
					fflush(stdin);
			    	printf("Ingrese la clave de la golosina Num %d: ",i+1); //debido a que el primer registro es 0 y en ese orden se almacenan los datos, se muestra al usuario
			    															//el inmediato superior, para no confundirlo.
					scanf("%d",&golosina[i].clave);
					fflush(stdin);
			    	printf("Ingrese el nombre de la golosina Num %d: ",i+1);
					gets(golosina[i].nombre);	
					printf("Ingrese el precio de la golosina Num %d: ",i+1);
					scanf("%f",&golosina[i].precio);
					printf("Ingrese la cantidad de la golosina Num %d: ",i+1);
					scanf("%d",&golosina[i].cantidad);
					puts("\n");
					}
					ultimoproducto=ultimoproducto+cantidaddeproductosaingresar; //este valor indica la posicion del ultimo registro escrito + 1
																				// Ej: al inicio se ingresa 1 solo producto
																				//este se escribira en golosina[0], debido a que el primer espacio del vector golosina es 0;
																				//0 (el valor de inicializacion)+1=1, 1 se vuelve el nuevo espacio en blanco en la estructura para el proximo ingreso
																				//este valor tambien muestra el numero real del total de productos, que va de 1 a 30.
					//printf("ultimoproducto=%d",ultimoproducto);
					puts("\n");
					if (cantidaddeproductosaingresar>=2) {
						puts("Los productos fueron correctamente agregados.\n\n");
					}
					else {
						puts("El producto fue correctamente agregado.\n\n");
					}
				}
				else{
					puts("Numero invalido, regrese al menu e intente nuevamente.\n\n");
					Sleep(1000);
				}
				break;
				
			case 2:
				if (ultimoproducto>=1) {
					puts("-------------------------------------------------------");
					puts("---------Modificador de registros de golosinas---------");
					puts("(Consulte la opcion 5 para saber el numero de producto)");
					puts("-------------------------------------------------------");
					i=0;
					siono:
					printf("Ingrese el numero de golosina a modificar: ");
					scanf("%d",&i);
					i=i-1;
					if (golosina[i].clave=='\0') {
						puts("El numero ingresado no es valido, favor de corroborar.");
						puts("\n");
					}
					else {
						char yesornot;
						YyNn:
						printf("El producto a editar es %s, desea continuar? (y/n): ",golosina[i].nombre);
						scanf(" %c",&yesornot);
						if (yesornot == 'y' || yesornot == 'Y') {
							printf("Modifique la clave de la golosina Num %d (actualmente %d): ",i+1,golosina[i].clave);
							scanf("%d",&golosina[i].clave);
							fflush(stdin);
					    	printf("Modifique el nombre de la golosina Num %d (actualmente %s): ",i+1,golosina[i].nombre);
							gets(golosina[i].nombre);	
							printf("Modifique el precio de la golosina Num %d (actualmente %f): ",i+1,golosina[i].precio);
							scanf("%f",&golosina[i].precio);
							printf("Modifique la cantidad de la golosina Num %d (actualmente %d): ",i+1,golosina[i].cantidad);
							scanf("%d",&golosina[i].cantidad);
							puts("\n");
							puts("Datos actualizados exitosamente.");
							puts("\n");
						}
						else if (yesornot == 'n' || yesornot == 'N') {
							int intentaroirse;
							unodos:
							puts("[1] Intentar nuevamente.");
							puts("[2] Regresar al menu.");
							puts("Intentar nuevamente o regresar al menu: ");
							scanf("%d", intentaroirse);
							if (intentaroirse==1) {
								goto siono;
							} else if (intentaroirse==2) {
								//break;
							} else {
								puts("Opcion invalida, solo se admite 1 y 2.\n");
								goto unodos;
							}
						}
						else {
							puts("Opcion invalida, intente de nuevo.");
							puts("Y/n no distingue mayusculas o minusculas.\n");
							goto YyNn;
						}
					}
				}
				else {
					puts("No hay productos a modificar. Regresando al menu...");
					puts("\n");
					Sleep(1000);
				}
				break;
				
			case 3:
				if (ultimoproducto>=1) {
					puts("-------------------------------------------------------");
					puts("-----------Supresor de registro de golosinas-----------");
					puts("(Consulte la opcion 5 para saber el numero de producto)");
					puts("-------------------------------------------------------");
						int registroaborrar;
						int registrosiguiente;
						reintentar:
						i=0;
						printf("Ingrese el numero de golosina a eliminar: ");
						scanf("%d",&i);
						i=i-1;
						registroaborrar=i;
						if (golosina[i].clave=='\0') {
							puts("El registro ingresado no existe, favor de corroborar.");
							puts("\n");
						}
						else {
							registrosiguiente=i+1;
							char yesornot;
							printf("El registro a eliminar es %s, desea continuar? (y/n): ",golosina[i].nombre);
							scanf(" %c",&yesornot);
							if (yesornot == 'y' || yesornot == 'Y') {
								for(i=registroaborrar;i<ultimoproducto;i++){
									cambiarclave(&golosina[i].clave,&golosina[registrosiguiente].clave);
									strcpy(golosina[i].nombre,golosina[registrosiguiente].nombre);
									cambiarprecio(&golosina[i].precio,&golosina[registrosiguiente].precio);
									cambiarcantidad(&golosina[i].cantidad,&golosina[registrosiguiente].cantidad);
									registrosiguiente=registrosiguiente+1;
								}
								printf("Registro %d eliminado exitosamente.\n",registroaborrar+1);
								ultimoproducto=ultimoproducto-1;
								puts("\n");
							} else if (yesornot == 'n' || yesornot == 'N') {
									int intentaroirse;
									unoydos:
									puts("[1] Intentar nuevamente.");
									puts("[2] Regresar al menu.");
									puts("Intentar nuevamente o regresar al menu: ");
									scanf("%d", intentaroirse);
									if (intentaroirse==1) {
										goto reintentar;
									} else if (intentaroirse==2) {
									//break;
									} else {
									puts("Opcion invalida, solo se admite 1 y 2.\n");
									goto unoydos;
									}
							}
						}
						
				}
				else {
				puts("No existen registros, regresando al menu.\n");
				Sleep(1000);
				}
				break;
				
			case 4: 
				//int registroamostrar;
				if (ultimoproducto>=1) {
					puts("-------------------------------------------------------");
					puts("-----------Consulta de registro de golosinas-----------");
					puts("(Consulte la opcion 5 para saber el numero de producto)");
					puts("-------------------------------------------------------");
				 	printf("Ingrese el numero de golosina a mostrar: ");
					scanf("%d",&i);
					i=i-1;
					//registroamostrar=i;
					if (golosina[i].clave=='\0') {
							puts("El registro ingresado no existe, favor de corroborar.");
							puts("\n");
						}
					else {
					puts("\n");
					puts("-----------------Mostrando el registro-----------------");
					printf("Clave del producto %d:\t%d\n",i+1, golosina[i].clave);
					printf("Nombre del producto %d:\t%s\n",i+1,golosina[i].nombre);
					printf("Precio del producto %d:\t%f\n",i+1,golosina[i].precio);
					printf("Cantidad del producto %d:\t%d\n",i+1,golosina[i].cantidad);
					puts("\n");
					}
				}
				else {
					puts("No hay productos para mostrar. Regresando al menu...\n");
					Sleep(1000);
				}
				break;
			case 5:
				if (ultimoproducto>=1) {
					printf("Esta maquina le proporciona ahora mismo, %d golosina(s).\n",ultimoproducto);
					  puts("-------------------------------------------------------");
					puts("Mostrando todos los productos de la maquina. Espere....");
					puts("-------------------------------------------------------");
					puts("\n");
					for(i=0;i<ultimoproducto;i++){
					//printf("Clave producto %d:\t%d\n",i+1, golosina[i].clave);
					printf("Nombre producto %d:\t%s\n",i+1,golosina[i].nombre);
					//printf("Precio producto %d:\t%f\n",i+1,golosina[i].precio);
					//printf("Cantidad producto %d:\t%d\n",i+1,golosina[i].cantidad);
					puts("\n");
					}
					Sleep(1000);
				}
				else {
					puts("No hay productos para mostrar. Regresando al menu...\n");
					Sleep(1000);
				}
				break;
			
			case 6: 
				if (ultimoproducto>=1) {
					puts("-------------------------------------------------------");
					puts("------------Maquina expendedora en servicio------------");
					puts("(Consulte la opcion 5 para saber el numero de producto)");
					puts("-------------------------------------------------------");
				 	printf("Ingrese el numero de golosina a comprar: ");
					scanf("%d",&i);
					i=i-1;
					puts("\n");
					if (golosina[i].clave=='\0') {
							puts("El registro ingresado no existe, favor de corroborar.");
							puts("\n");
						}
					else {
						printf("%s tiene un precio de %f c/u.\n",golosina[i].nombre,golosina[i].precio);
						printf("Cantidad de unidades a comprar: ");
						scanf("%d",&unidadesacomprar);
						puts("\n");
							if (unidadesacomprar<=golosina[i].cantidad) {
							float totalapagar=unidadesacomprar*golosina[i].precio;
							printf("El total a pagar es: %f\n",totalapagar);
							float pago;
							printf("Cantidad con la que se va a pagar: ");
							scanf("%f",&pago);
							if (pago==totalapagar){
								puts("Su pago ha sido exacto. Que tenga un excelente dia.\n\n");
								golosina[i].cantidad=golosina[i].cantidad-unidadesacomprar;
								Sleep(1000);
							}
							else if (pago<totalapagar) {
								printf("Necesita %f mas para pagar.\n",totalapagar-pago);
								printf("Regresando al menu...\n\n");
								Sleep(1000);	
							}
							else if (pago>totalapagar) {
								int cambio;
								cambio=pago-totalapagar;
								printf("Tu cambio es de %d.\n\n",cambio);
								float cociente10;
								cociente10=cambio/10;
								int residuo10;
								residuo10=cambio%10;
								float cociente5;
								cociente5=residuo10/5;
								int residuo5;
								residuo5=residuo10%5;
								float cociente2;
								cociente2=residuo5/2;
								int residuo2;
								residuo2=residuo5%2;
								float cociente1;
								cociente1=residuo2/1;
								printf("El cambio sera otorgado de la siguiente forma:\n\n");
								printf("%f monedas de 10.\n",cociente10);
								printf("%f monedas de 5.\n",cociente5);
								printf("%f monedas de 2.\n",cociente2);
								printf("%f monedas de 1.\n",cociente1);
								puts("\n");
								printf("Gracias por tu compra!\n");
								golosina[i].cantidad=golosina[i].cantidad-unidadesacomprar;
								puts("\n");
								Sleep(1000);
							}
						}
						else {
						puts("No disponemos de esa cantidad de golosinas. Disculpe.\n");
						Sleep(1000);
						}
					}
				}
				else {
					puts("No hay productos para vender. Regresando al menu...\n");
					Sleep(1000);
				}	
				break;	
					
			case 9: //usado para comprobar que el case 3 funcionara correctamente.
					puts("-------------------------------------------------------");
					puts("Mostrando todos los datos almacenados, espere..........");
					puts("-------------------------------------------------------");
					puts("\n");
					for(i=0;i<31;i++){
					printf("Clave producto %d:\t\t%d\n",i+1, golosina[i].clave);
					printf("Nombre producto %d:\t\t%s\n",i+1,golosina[i].nombre);
					printf("Precio producto %d:\t\t%f\n",i+1,golosina[i].precio);
					printf("Cantidad producto %d:\t\t%d\n",i+1,golosina[i].cantidad);
					puts("\n");
					}
				break;
			case 0: puts("Vuelva pronto!\n");
			break;
			default: puts("Opcion no valida.\n");
			break;	
			}
	}while(selector!=0);
	Sleep(1000);
    return 0;	
}

void menu() {
	puts("-------------------------------------------------------");
	puts("---------Bienvenidos a la maquina de golosinas---------");
	puts("-------------------------------------------------------");
	puts("	[1] Agregar producto");
	puts("	[2] Actualizar producto ");
	puts("	[3] Eliminar producto");
	puts("	[4] Consultar producto");
	puts("	[5] Mostrar todos los productos");
	puts("	[6] Comprar producto");
	puts("	[0] Salir");
	printf(" Opcion: ");
}

int cambiarclave(int *n1, int *n2)
{
    int aux = *n1;
    *n1 = *n2;
    *n2 = aux;
}

//char cambiarnombre(char n1, char n2)
//{
//    char auxi = *n1;
//    *n1 = *n2;
//    *n2 = auxi;
//}

float cambiarprecio(float *n1, float *n2)
{
    float auxiliar = *n1;
    *n1 = *n2;
    *n2 = auxiliar;
}

int cambiarcantidad(int *n1, int *n2)
{
    int auxilia = *n1;
    *n1 = *n2;
    *n2 = auxilia;
}