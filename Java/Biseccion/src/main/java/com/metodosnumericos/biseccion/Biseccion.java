/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package com.metodosnumericos.biseccion;

import java.util.Scanner;
/**
 *
 * @author Angelo Vera Pawling
 */
public class Biseccion {

    public static void main(String[] args) {
        Scanner sc = new Scanner((System.in));
        double ls, li, iteraciones;
        
        System.out.println("Calculadora de raíz por el método de bisección.");
        System.out.println("La ecuación es 2x + 0.5x - 40.\n");
        
        System.out.println("Ingrese el límite inferior: ");
        li = sc.nextDouble();
        
        System.out.println("\nIngrese el límite superior: ");
        ls = sc.nextDouble();
        
        System.out.println("\nIngrese el numero de iteraciones: ");
        iteraciones = sc.nextDouble();

        //Al ser función lineal, los límites al ser sustituidos en la función deben tener
        //signo contrario para demostrar que existe una intersección en el eje x
        //entre los límites y así garantizar que funcionará el método.
        if (sustituirfuncion(li)>=0 && sustituirfuncion(ls)<=0) {   
            metododebiseccion(li, ls, iteraciones);
        }
        else if (sustituirfuncion(li)<=0 && sustituirfuncion(ls)>=0){
            metododebiseccion(li, ls, iteraciones);
        } 
        else if (li==ls){
            System.out.println("\nEl límite inferior y superior son iguales y no es la raíz, no es posible aplicar el método.\n");
        }
        else {
            System.out.println("\nNo es posible aplicar el método con los límites seleccionados, no existe intersección con el eje x.\n");
        }
    }
    
    static void metododebiseccion(double li, double ls, double iteraciones){
        double fc=0;
        double fi=sustituirfuncion(li);
        double fs=sustituirfuncion(ls);
        fc = (li+ls)/2;
        System.out.println("\nValores iniciales - Li: " + li + ". Ls: " + ls + ". Fi: " + fi + ". Fs: " + fs + ". Fc: "+ fc +".\n\n");

        int i;
        for (i=1;i<=iteraciones;i++){
            fc = (li+ls)/2;
            if (sustituirfuncion(fc)*sustituirfuncion(li)>0) {
                li=fc;
            } else if (sustituirfuncion(fc)==0.0){
                break;
            } else {
                ls=fc;
            } 
         System.out.println("Resultados de la iteración número "+i+":\n");
         System.out.println("Li: " + li + ". Ls: " + ls + ". Fi: " + fi + ". Fs: " + fs + ". Fc: " + fc + ".\n\n");  
         
        }
        
        System.out.print("Después de "+(i-1)+" iteracion(es), se ha aproximado la raíz a: "+fc+".\n\n");
        
    }
    
    static double sustituirfuncion(double f) {
        //This function can be replaced with other function and must be specified at the start of this program;
        return 2*f+0.5*f-40;
    }
}
