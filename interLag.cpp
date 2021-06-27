#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

double Lagrange(int n,double x,double *Preim,double *Im){

		double s = 0;
		for(int k=0;k<n;k++){
				double p = 1, xk = *(Preim+k);

				for(int i=0;i<n;i++){
						if(i==k)
								continue;
						
						double xi = *(Preim+i);
						p *= (x-xi)/(xk-xi);
				};
				s += *(Im+k)*p;
		};

		return s;
}

double factorial(int k){
		if (k==0){
				return 1;
		}else{
				return k*factorial(k-1);
		};
}

double df(double x,int ord){
		if (ord==0){
				return log(x);
		}else{
				return pow(-1,ord+1)/pow(x,ord)*factorial(ord-1);
		}
}

double Taylor(int grad,double c,double x){
		
		double s = 0;
		for (int k=0;k<=grad;k++){
				//
				s += df(c,k)*pow(x-c,k)/factorial(k);
		}

		return s;
}

int main()
{
    //
		int n = 10;
		double *x,*y;
		
		x = new double [n];
		y = new double [n];
		
		double val[n] = {0.1,0.9,1.1,2.7,2.1,1.4,0.5,0.3,3.0,2.4};
		for (int i=0;i<n;i++)
				*(x+i) = val[i];

		for (int j=0;j<n;j++)
				*(y+j) = log(*(x+j));
		
		double x0 = 1.8;

		cout << "Original: " << log(x0) << endl;
		cout << "Lagrange: " << Lagrange(n,x0,x,y) << endl;
		cout << "Taylor:   " << Taylor(4,1,x0) << endl;

    return 0;
}
