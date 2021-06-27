#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
using namespace std;

const int rep = 70;

double f(double x){
		return pow(2,x) - pow(x,2);
}

double df(double x){
		return log(2)*pow(2,x) - 2*x;
}

int biseccion(double tol,double **res){
		//
		double a = -5, b = 1, p;
		int ind = 0;

		if (f(a)*f(b)>0){
				cout << "Error: f(a) y f(b) tienen el mismo signo." << endl;
				return 0;
		};

		while(b-a>tol){
				p = (a+b)/2;
				
				if (f(p)==0){
						a=p;
						b=p;
						break;
				};
				
				a += (p-a)*(f(p)*f(b)<0);
				b += (p-b)*(f(p)*f(a)<0);
				
				*(*(res+ind)) = f(p);

				ind++;
		};
		
		for (int i = ind + 1; i<rep; i++ )
				*(*(res+i)) = 0;

		return 0;
}

int newton(double tol,double **res){
		//
		double a = 0;
		int ind = 0;

		while ( fabs(f(a))>tol){
				a -= f(a)/df(a);

				*(*(res+ind)+1) = f(a);
				ind++;

		};

		for (int i = ind + 1; i<rep; i++ )
				*(*(res+i)+1) = 0;

		return 0;
}

int secante(double tol,double **res){
		//
		double p0 = 0, p1 = -1, p;
		int ind = 0;

		while(fabs(p1-p0)>tol && fabs(f(p1)-f(p0))>tol ){
				p = p1;
				p1 = p0 - f(p0)/(f(p1)-f(p0))*(p1-p0);
				p0 = p;

				*(*(res+ind)+2) = f(p);
				ind++;
		};

		for (int i = ind + 1; i<rep; i++ )
				*(*(res+i)+2) = 0;

		return 0;
}

int printMatrix(int nfil, int ncol,double **A){
		for (int i=0;i<nfil;i++){
				cout << i + 1 << "\t";
				
				for (int j=0;j<ncol;j++)
						cout << setw(17) << setprecision(5) << A[i][j];
				cout << endl;
		}

		return 0;
}

void creaFicheroMatriz( string fichero, double  **A,int nfil,int ncol){
	  ofstream archivo ( fichero.c_str());

	  archivo << "Comparación de Métodos para Hallar Raices:";
    archivo << endl;
		archivo << "------------------------------------------------------------------------" << endl;
		archivo << "Iteración\tBisección\t    Newton\t    Secante" << endl;


    for (int i = 0; i < nfil; i++){
				archivo << i + 1 << "\t";

        for (int j = 0; j < ncol; j++)
						archivo << setw(17) << setprecision(5) << A[i][j];
        archivo << endl;
    }

    archivo.close();
}

int main()
{
    //
		double tol = 1e-14;
		double **res;

		res = new double *[rep];
		for (int i=0; i<rep; i++)
				res[i] = new double [3];

		biseccion(tol,res);
		newton(tol,res);
		secante(tol,res);

		cout << "Iteración\tBisección\t    Newton\t    Secante" << endl;
		printMatrix(rep,3,res);

		creaFicheroMatriz("compa.txt",res,rep,3);

    return 0;
}
