package anfiteatro;

import java.util.Scanner;

public class Anfiteatro {

    static Scanner keyboard = new Scanner(System.in);
    static String matrizAsientos[][] = new String [10][10];
    static int asientosLibres;
    
    public static void main(String[] args) {
        for (int f=0;f<10;f++){
            for (int a=0;a<10;a++){
                matrizAsientos[f][a]="L";
            }
        }
        
        asientosLibres = freeChairs(matrizAsientos);
        
        while (asientosLibres!=0){
            greetings();
            System.out.println("Asientos disponibles: "+asientosLibres);
            escogerAsiento(matrizAsientos); 
        }
            
        greetings();
        System.out.println("Ya no tenemos asientos disponibles.");
        System.out.println("Agradecemos su interes.");
        
    }
    
    public static void greetings(){
        System.out.println("Bienvenido al Anfiteatro.");
        imprimirAsientos(matrizAsientos);
    }
    
    public static void escogerAsiento(String matrizAsientos[][]){
        int fila, asiento;
        System.out.println("\nL = Libre, X = Reservado.");
        System.out.println("Indique el asiento que le gustaria apartar");
        System.out.print("Fila: ");
        fila = keyboard.nextInt();
        System.out.print("Asiento: ");
        asiento = keyboard.nextInt();
        
        if (matrizAsientos[fila-1][asiento-1].equalsIgnoreCase("L")){
            matrizAsientos[fila-1][asiento-1]="X";
            System.out.println("Asiento reservado correctamente.");
            System.out.println("Excelente dia.\n");
            asientosLibres = freeChairs(matrizAsientos);
        } else {
            System.out.println("Este asiento ya está reservado.\n");
            asientosLibres = freeChairs(matrizAsientos);
        }  
    }
    
    public static void imprimirAsientos(String matrix[][]) {
        for (int f=0;f<=10;f++){
            if (f==0){
                System.out.print("   ");
            } else if (f>0&&f<10){
                System.out.print(" "+(f)+" ");
            } else if (f==10){
                System.out.print((f)+" ");
            }
            
            if (f==0){
                for (int a=1;a<=10;a++){
                    System.out.print((a)+" ");
                }
            } else if (f>0 && f<10){
                for (int a=0;a<10;a++){
                    System.out.print(matrix[f-1][a]+" ");
                }
            } else if (f==10){
                for (int a=0;a<10;a++){
                        System.out.print(matrix[f-1][a]+" ");
                }
            }
            System.out.println("");
        }
    }
    
    public static int freeChairs(String matrizAsientos[][]){
        int counter=0;
        
        for (int f=0;f<10;f++){
            for (int a=0;a<10;a++){
                if (matrizAsientos[f][a].equalsIgnoreCase("L")){
                    counter++;
                }
            }
        }
    return counter;
    }
}
