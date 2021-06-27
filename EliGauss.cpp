#include <math.h>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <time.h>
using namespace std;


void printMat(int nfil,int ncol,double **A){
		
		for (int i=0;i<nfil;i++){

				for (int j=0;j<ncol;j++)
						cout << setw(14) << setprecision(6) << *(*(A+i)+j);
				cout << endl;

		};
}


void printVec(int len, double *V){

		for (int i=0;i<len;i++)
				cout << setw(18) << setprecision(10) << *(V+i);

}


double ** copyMat(int nfil,int ncol,double **A){

		double **B;
		B = new double *[nfil];
		for(int i=0;i<nfil;i++)
				*(B+i) = new double [ncol];

		for(int i=0;i<nfil;i++)
				for(int j=0;j<ncol;j++)
						*(*(B+i)+j) = *(*(A+i)+j);

		return B;
}


double prodVec(int len,double *v1,double *v2){
		
		double r = 0;
		for (int i=0;i<len;i++)
				r += *(v1+i) * *(v2+i);

		return r;
}


double * mCol(int nrow,int col,double **A){
		
		double *colum;
		colum = new double [nrow];

		for (int i=0;i<nrow;i++)
				*(colum+i) = *(*(A+i)+col);

		return colum;
}


double ** matProd(int nrow,int n, int ncol,double **A1,double **A2){

		double **res;

		res = new double *[nrow];
		for (int i=0;i<nrow;i++)
				*(res+i) = new double [ncol];

		for (int i=0;i<nrow;i++)
				for (int j=0;j<ncol;j++)
						*(*(res+i)+j) = prodVec(n,*(A1+i),mCol(n,j,A2));

		return res;
}


double * matVec(int nrow,int ncol, double **A,double *c){

		double *vec;
		vec = new double [nrow];

		for (int i=0;i<nrow;i++)
				*(vec+i) = prodVec(ncol,*(A+i),c);

		return vec;
}


void FilaPerm(int i, int j, double **A){

		double *tmp = *(A+i);
		*(A+i) = *(A+j);
		*(A+j) = tmp;

}


void FilaEsca(int ncol,int i, double k, double **A){

		for (int j=0;j<ncol;j++)
				*(*(A+i)+j) = (*(*(A+i)+j))*k;

}


void FilaSuma(int ncol, int i, int j, double k, double **A){

		for (int l=0;l<ncol;l++)
				*(*(A+i)+l) += *(*(A+j)+l)*k;

}


double ** Escalon(int nrow, int ncol, double **B){

		double **A = copyMat(nrow,ncol,B);

		int nFilLd = 0; // Número de filas linealmente dependientes.

		for (int j=0;j<(ncol-1);j++){

				if (*(*(A+j-nFilLd)+j)==0){ // Verificar que el pivote no sea cero.
						nFilLd++;

				}else{

						for(int i=j+1-nFilLd;i<nrow;i++){ // Recorrer las filas.

								double k = (*(*(A+i)+j))/(*(*(A+j-nFilLd)+j));
								FilaSuma(ncol,i,j-nFilLd,-k,A); // Hacer cero debajo del pivote.

						};

				};
		};

		return A;
}


double ** EliGauss(int nrow, int ncol, double **B){

		double **A = copyMat(nrow,ncol,B);

		for (int j=0;j<(nrow);j++){

				if (*(*(A+j)+j)!=0){ // Verificar que el pivote no sea cero.

						for(int i=0;i<nrow;i++){ // Recorrer las filas.

								if(i!=j){

										double k = (*(*(A+i)+j))/(*(*(A+j)+j));
										FilaSuma(ncol,i,j,-k,A); // Hacer cero debajo del pivote.
								};
						};
				}else{
						exit(EXIT_FAILURE);
				};
		};

		return A;
}


double * solve(int nrow,int ncol,double **A){

		if (nrow+1 != ncol){
				cout << "Esta no es la matriz extendida de un sistema de ecuaciones con igual cantidad de ecuaciones qe incógnitas.";
				exit(EXIT_FAILURE);
		}else{

				double *sol;
				sol = new double [nrow];

				for (int i=0;i<nrow;i++)
						*(sol+i) = *(*(A+i)+ncol-1) / *(*(A+i)+i);
				
				return sol;
		}
}

double * constant(int nrow,int ncol,double **A){

		double *c;
		c = new double [nrow];

		for (int i=0;i<nrow;i++)
				*(c+i) = *(*(A+i)+ncol-1);

		return c;

}


double deter(int nfil,int ncol,double **A){

		if(nfil!=ncol){	// Verificar que la matriz sea cuadrada

				cout << "La matriz no es cuadrada" << endl;
				exit(EXIT_FAILURE);

		}else if (nfil==1){ // Caso 1x1
				
				return **A;

		}else{ // Caso general

				double det = 0; // Crear la variable en la que se va a hacer la sumatoria sobre filas

				for (int i=0;i<nfil;i++){
						
						double **Ai; // Crear la submatriz adecuada
						Ai = new double *[nfil-1];

						for (int j=0; j<(nfil-1);j++)
								Ai[j] = new double [ncol-1];

						for (int k=0;k<nfil;k++){

								if (k==i) // Evitar fila i
										continue;

								for (int l=1;l<ncol;l++){

										int tk;

										tk = k - (k>i); // Corregir los índices

										*(*(Ai+tk)+(l-1)) = *(*(A+k)+l); // Asignación

								};
						};					

						det += pow(-1.0,i)*(**(A+i))*deter(nfil-1,ncol-1,Ai); // Calcular el i-ésimo sumando

				}
				
				return det;
		}
}

double ** inversa(int nrow,int ncol, double **A){

		if (nrow!=ncol){
				cout << "La matriz no es cuadrada: " << endl;
				exit(EXIT_FAILURE);
		};

		// Crear la matriz doble

		double **doble;
		doble = new double *[nrow];
		for(int i=0;i<nrow;i++)
				*(doble+i) = new double [2*ncol];

		// Llenar la matriz doble
		for (int i=0;i<nrow;i++)
				for (int j=0;j<ncol;j++){
						*(*(doble+i)+j) = *(*(A+i)+j);
						*(*(doble+i)+j+nrow) = i==j;
				};

		// Resolver el sistema

		doble = EliGauss(nrow,2*nrow,doble);

		double *diag;
		diag = new double [nrow];

		for (int i=0;i<nrow;i++)
				*(diag+i) = *(*(doble+i)+i);

		for (int i=0;i<nrow;i++){
				FilaEsca(2*ncol,i,1/(*(diag+i)),doble);
		}


		// Extraer la inversa
		
		double **inver;
		inver = new double *[nrow];
		for(int i=0;i<nrow;i++)
				*(inver+i) = new double [nrow];

		for (int i=0;i<nrow;i++)
				for (int j=0;j<nrow;j++)
						*(*(inver+i)+j) = *(*(doble+i)+nrow+j);

		return inver;
}


int main(){
		srand (time(NULL)); // Establecer semilla
		
		cout << "Ingrese el rango de la matriz:\t";
		int n;
		cin >> n;
		
		
		// Crear la matriz de prueba.
		
		double **A; 

		A = new double *[n];
		for(int i=0;i<n;i++)
				*(A+i) = new double [n+1];

		for(int i=0;i<n;i++) // LLenar la matriz
				for(int j=0;j<=n;j++)
						*(*(A+i)+j) = (rand()%210)*0.1-10;
		

		// Imprimir resultados:

		cout << "\n" << "Matriz original generada aleatoriamente: " << endl; 
		printMat(n,n,A);

		if ( n <= 10 ){
				cout << "\n" << "Determinante de la matriz: " << endl;
				cout << deter(n,n,A) << endl;
		};

		cout << "\n" << "Vector de constantes: " << endl;
		printVec(n,constant(n,n+1,A));

		double **B1 = Escalon(n,n+1,A);
		cout << "\n" << "Matriz escalonada: " << endl;
		printMat(n,n,B1);

		double **B2 = EliGauss(n,n+1,A);
		cout << "\n" << "Matriz diagonal: " << endl;
		printMat(n,n,B2);

		double **B3 = inversa(n,n,A);
		cout << "\n" << "Matriz inversa: " << endl;
		printMat(n,n,B3);

		double *S1 = solve(n,n+1,B2);
		cout << "\n" << "Solución por eliminación gaussiana: " << endl;
		printVec(n,S1);

		double *S2 = matVec(n,n,B3,constant(n,n+1,A));
		cout << "\n" << "Solución por matriz inversa: " << endl;
		printVec(n,S2);
		

		// Factorizar LU
}
