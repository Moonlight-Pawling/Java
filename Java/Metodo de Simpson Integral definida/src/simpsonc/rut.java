package simpsonc;

import java.util.Scanner;

public class rut {
    public static double cd(String men){
        Scanner sc = new Scanner((System.in));
        System.out.print(men);
        return sc.nextDouble(); 
    }
    
    public static int ci(String men){
        Scanner sc = new Scanner((System.in));
        System.out.print(men);
        return sc.nextInt(); 
    }
    
    public static void ld(String men, double var){
        System.out.println(men+var);
    }

    public static void dld(double vv,String men, double var){
        System.out.println(vv+men+var);
    }

    public static void le(String men){
        System.out.println(men);
    }

    public static void ordvec(int n, double v[]){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(v[i]<v[j]){
                    double t=v[i];
                    v[i] = v[j];
                    v[j] = t;
                }
            }
        }
    }

    public static void impvec(int n,  double v[]){
        for(int i = 0; i < v.length; i++){
            System.out.println(" "+v[i]);
        }
    }
    
    public static double mediana(int n, double v[]){
        if(n%2!=0) return v[(n+1)/2];
        else{
            return (v[n/2]+v[(n/2)+1]/2);
        }
    }

    public static void moda(int n, double v[]){
        int p=1;
        for(int i=1;i<n;i++){
            for(int j=i+1;j<=n;j++)
                if(v[i]==v[j]) p++;
                else break;
            if(p>1){
                dld(v[i],":",p);
                i+=p-1;p=1;
            }
        }
    }

    public static double vari(int n, double v[], double s ){
        float sv=0;
        for(int i=1;i<=n;i++)
            sv=(float) (sv+Math.pow(v[i]-(s/n),2));
        return sv/n;
    }

    public static double capvec(int n, double v[]){
        double s = 0;
        for(int i = 1; i <= n; i++){
            v[i] = cd("Valor: ");
            s+=v[i];
        }
        return s;
    }

}