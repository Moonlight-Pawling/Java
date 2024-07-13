/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
fun a + fun b
 */
package simpsonc;

import static java.lang.Math.exp;
//import static java.lang.Math.pow;

/**
 *
 * @author Angelo Vera Pawling
 */
public class SimpsonC {
    /**
     * @param args the command line arguments
     */
    
    public static void main(String[] args) {
        // TODO code application logic here
        System.out.println("Calculadora de integral definida de e^2x");
        int n=rut.ci("Ingrese el valor entero de subintervalos: ");
        double a=rut.cd("Ingrese el límite inferior: ");
        double b=rut.cd("Ingrese el límite superior: ");
        
        double h=(b-a)/n;
        double si=0, sp=0;
        double sa = fun(a)+fun(b);
        int counter = 1;
        
        for (double x=h;x<=b-h;x=x+h){
            if ((counter%2)==0){
                sp = sp +(2*fun(x));
            } else{
               si = si + (4*fun(x)); 
            }
            counter++;
        }
        double sum=sa+si+sp;
        double resultado = sum*(h/3);
        System.out.println("El resultado es: "+resultado);
    }
    
    /**
     *
     * @param x
     * @return
     */
    private static double fun (double x){
    return exp(Math.pow(x,2));
    }
}
