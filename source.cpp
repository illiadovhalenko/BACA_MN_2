//Illia Dovhaelnko
#include <cmath>
#include<iostream>
//Funkcja signum zwracająca znak liczby
int sgn(double val){
    return (0. < val) - (val < 0.);
}


double SecantMethod(double(*f)(double), double a, double b, int M, double eps, double delta, const double tab[]){
    double x0, x1, x2, f0, f1, f2;
    x0=a;
    x1=b;
    int iter=0;
    f0=tab[0];
    f1=tab[1];
    while(true){
        if(fabs(f0)<eps) {
            return x0;
        }
        if(fabs(f1)<eps) {
            return x1;
        }
        x2 = x1 - (f1*(x1-x0))/(f1-f0);
        f2 =f(x2);
        if(std::fabs(f2)<eps|| fabs(x2-x1)<delta) {
            return x2;
        }
        x0 = x1;
        f0 = f1;
        x1 = x2;
        f1 = f2;
        iter++;
    }
    return x2;
}

double findZero(double(*f)(double), double a, double b, int M, double eps, double delta){
    double tab[3];
    tab[0]=f(a);
    tab[1]=f(b);
    if(std::fabs(tab[0])<eps) return a;
    if(std::fabs(tab[1])<eps) return b;
    double e=b-a;
    double c, fc;
    if(tab[0]*tab[1]>0){
        return SecantMethod(f, a, b, M, eps, delta, tab);
    }else {
        double fa=tab[0];
        double fb=tab[1];
        int i;
        for (i = 3; i <= M; i++){
            e = e / 2;
            c = a + e;
            fc = f(c);
            if (std::fabs(e) <delta || std::fabs(fc) < eps) {
                break;
                return c;
            }
            if (sgn(fc)!=sgn(fa)) {
                b = c;
                fb = fc;
                if(e<0.1) {
                    tab[0]=fa;
                    tab[1]=fb;
                    return SecantMethod(f, a, b, M, eps, delta, tab);
                    break;
                }
            } else {
                a = c;
                fa = fc;
                if(e<0.1) {
                    tab[0]=fa;
                    tab[1]=fb;
                    return SecantMethod(f, a, b, M, eps, delta, tab);
                    break;
                }
            }
       }
        return c;
   }
}
