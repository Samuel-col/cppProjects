// Librerías
#include <math.h>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <time.h>
using namespace std;

// Colores
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      // Black 
#define RED     "\033[31m"      // Red 
#define GREEN   "\033[32m"      // Green 
#define YELLOW  "\033[33m"      // Yellow 
#define BLUE    "\033[34m"      // Blue 
#define MAGENTA "\033[35m"      // Magenta 
#define CYAN    "\033[36m"      // Cyan 
#define WHITE   "\033[37m"      // White 
#define BOLDBLACK   "\033[1m\033[30m"      // Bold Black 
#define BOLDRED     "\033[1m\033[31m"      // Bold Red 
#define BOLDGREEN   "\033[1m\033[32m"      // Bold Green 
#define BOLDYELLOW  "\033[1m\033[33m"      // Bold Yellow 
#define BOLDBLUE    "\033[1m\033[34m"      // Bold Blue 
#define BOLDMAGENTA "\033[1m\033[35m"      // Bold Magenta 
#define BOLDCYAN    "\033[1m\033[36m"      // Bold Cyan 
#define BOLDWHITE   "\033[1m\033[37m"      // Bold White 


void printMat(int nfil,int ncol,double **A){ // Imprime matrices.
		
		for (int i=0;i<nfil;i++){

				for (int j=0;j<ncol;j++)
						cout << setw(14) << setprecision(6) << *(*(A+i)+j);
				cout << endl;

		};
}


void printVec(int len, double *V){ // Imprime vectores.

		for (int i=0;i<len;i++)
				cout << setw(18) << setprecision(10) << *(V+i);

}


double ** copyMat(int nfil,int ncol,double **A){ // Copia una matriz.

		double **B;
		B = new double *[nfil];
		for(int i=0;i<nfil;i++)
				*(B+i) = new double [ncol];

		for(int i=0;i<nfil;i++)
				for(int j=0;j<ncol;j++)
						*(*(B+i)+j) = *(*(A+i)+j);

		return B;
}


double prodVec(int len,double *v1,double *v2){ // Producto entre dos vectores.
		
		double r = 0;
		for (int i=0;i<len;i++)
				r += *(v1+i) * *(v2+i);

		return r;
}


double * mCol(int nrow,int col,double **A){ // Extrae una columna de una matriz.
		
		double *colum;
		colum = new double [nrow];

		for (int i=0;i<nrow;i++)
				*(colum+i) = *(*(A+i)+col);

		return colum;
}


double ** matProd(int nrow,int n, int ncol,double **A1,double **A2){ // Producto matricial.

		double **res;

		res = new double *[nrow];
		for (int i=0;i<nrow;i++)
				*(res+i) = new double [ncol];

		for (int i=0;i<nrow;i++)
				for (int j=0;j<ncol;j++)
						*(*(res+i)+j) = prodVec(n,*(A1+i),mCol(n,j,A2));

		return res;
}


double * matVec(int nrow,int ncol, double **A,double *c){  // Si A es matriz y v es vector, entonces esta función halla A*v.

		double *vec;
		vec = new double [nrow];

		for (int i=0;i<nrow;i++)
				*(vec+i) = prodVec(ncol,*(A+i),c);

		return vec;
}


void FilaPerm(int i, int j, double **A){ // Fi <-> Fj

		double *tmp = *(A+i);
		*(A+i) = *(A+j);
		*(A+j) = tmp;

}


void FilaEsca(int ncol,int i, double k, double **A){ // Fi -> k*Fi

		for (int j=0;j<ncol;j++)
				*(*(A+i)+j) = (*(*(A+i)+j))*k;

}


void FilaSuma(int ncol, int i, int j, double k, double **A){ // Fi -> Fi + k*Fj

		for (int l=0;l<ncol;l++)
				*(*(A+i)+l) += *(*(A+j)+l)*k;

}


double ** Escalon(int nrow, int ncol, double **B){ // Escalona una matriz.

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


double * solTriSup(int nrow,int ncol,double **A){ // Soluciona un sistema de ecuaciones con una matriz triangular superior.

		if ( (nrow+1) != ncol){
				cout << "\n" << BOLDRED << "Esta no es la matriz extendida de un sistema de ecuaciones con solución única." << RESET << endl;
				exit(EXIT_FAILURE);
		};

		double *sol;
		sol = new double [nrow];

		double *cons = mCol(nrow,ncol-1,A);

		for (int i=(nrow-1);i>=0;i--){

				double res = 0;
				for (int k=i+1;k<nrow;k++)
						res += *(sol+k)*(*(*(A+i)+k));

				*(sol+i) = ( *(cons+i) - res )/( *(*(A+i)+i) );

		};

		return sol;

}


double * solTriInf(int nrow,int ncol,double **A){ // Soluciona un sistema de ecuaciones con una matriz triangular inferior.

		if ( (nrow+1) != ncol){
				cout << "\n" << BOLDRED << "Esta no es la matriz extendida de un sistema de ecuaciones con solución única." << RESET << endl;
				exit(EXIT_FAILURE);
		};

		double *sol;
		sol = new double [nrow];

		double *cons = mCol(nrow,ncol-1,A);

		for (int i=0;i<nrow;i++){

				double res = 0;
				for (int k=0;k<i;k++)
						res += *(sol+k)*(*(*(A+i)+k));

				*(sol+i) = ( *(cons+i) - res )/( *(*(A+i)+i) );

		};

		return sol;

}


double *** LUFact(int nrow, int ncol, double **B){ // Calcula la factorización LU de una matriz no singular.

		// Declaración de matrices

		double **U = copyMat(nrow,ncol,B);

		double **L;
		L = new double *[nrow];

		for (int i=0;i<nrow;i++)
				*(L+i) = new double [nrow];

		for (int i=0;i<nrow;i++)
				for(int j=0;j<nrow;j++)
						*(*(L+i)+j) = i==j;



		for (int j=0;j<(ncol-1);j++){

				if (*(*(U+j)+j)==0){ // Verificar que el pivote no sea cero.
						cout << BOLDRED << "Pivote " << j << " es nulo." << RESET << endl;
						exit(EXIT_FAILURE);

				}else{

						for(int i=j+1;i<nrow;i++){ // Recorrer las filas.

								double k = (*(*(U+i)+j))/(*(*(U+j)+j));
								FilaSuma(ncol,i,j,-k,U); // Hacer cero debajo del pivote.
								*(*(L+i)+j) = k; // Actualizar matriz L.


						};

				};
		};

		// Crear array de resultados.

		double ***res;
		res = new double **[2];

		*(res) = L;
		*(res+1) = U;

		return res;
}


double * solveLU(int nrow,int ncol,double **A){ // Soluciona un sistema de ecuaciones utilizando la factorización LU.

		double *cons = mCol(nrow,ncol-1,A); // Vector de constantes.

		double **B;  // Matriz asociada.

		B = new double *[nrow];
		for ( int i=0;i<nrow;i++)
				*(B+i) = new double [ncol-1];

		for (int i=0;i<nrow;i++)
				for(int j=0;j<(ncol-1);j++)
						*(*(B+i)+j) = *(*(A+i)+j);

		double ***LU = LUFact(nrow,nrow,B); // Factorización LU de la matriz asociada.

		double **LE; // Matrices extendidas para los sistemas de ecuaciones.
		double **UE;

		LE = new double *[nrow];
		UE = new double *[nrow];

		for (int i=0;i<nrow;i++){
				*(LE+i) = new double [ncol];
				*(UE+i) = new double [ncol];
		};

		for (int i=0;i<nrow;i++)
				for (int j=0;j<(ncol-1);j++){
						*(*(LE+i)+j) = *(*(*(LU)+i)+j);
						*(*(UE+i)+j) = *(*(*(LU+1)+i)+j);
				};

		for (int i=0;i<nrow;i++) // Agregar vector de constantes.
				*(*(LE+i)+ncol-1) = *(cons+i);

		// Solución del sistema Ly=b

		double *y = solTriInf(nrow,ncol,LE);

		for (int i=0;i<nrow;i++) // Agregar vector de constantes.
				*(*(UE+i)+ncol-1) = *(y+i);

		double *sol = solTriSup(nrow,ncol,UE);

		return sol;

}


double ** EliGauss(int nrow, int ncol, double **B){ // Hace diagonal la matriz.

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
						cout << BOLDRED << "Pivote " << j << " es nulo." << RESET << endl;
						exit(EXIT_FAILURE);
				};
		};

		return A;
}


double * solve(int nrow,int ncol,double **A){ // Encuentra la solución al sistema de ecuaciones cuando ya se ha hech diagonal la matriz.

		if (nrow+1 != ncol){
				cout << BOLDRED << "Esta no es la matriz extendida de un sistema de ecuaciones con igual solución única." << RESET << endl;
				exit(EXIT_FAILURE);
		}else{

				double *sol;
				sol = new double [nrow];

				for (int i=0;i<nrow;i++)
						*(sol+i) = *(*(A+i)+ncol-1) / *(*(A+i)+i);
				
				return sol;
		}
}

double * constant(int nrow,int ncol,double **A){ // Extrae el vector de constantes a partir de la matriz extendida.

		double *c;
		c = new double [nrow];

		for (int i=0;i<nrow;i++)
				*(c+i) = *(*(A+i)+ncol-1);

		return c;

}


double deter(int nfil,int ncol,double **A){ // Calcula el determinante utilizando cofactores.

		if(nfil!=ncol){	// Verificar que la matriz sea cuadrada

				cout << BOLDRED << "La matriz no es cuadrada" << RESET << endl;
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

						for (int j=0;j<(nfil-1);j++)
								delete *(Ai+j);

				}
				
				return det;
		}
}


double detDiag(int n,double **A){ // Halla el determinante de una matriz diagonal.

		double det = 1;
		for (int i=0;i<n;i++)
				det *= *(*(A+i)+i);

		return det;
}


double ** inversa(int nrow,int ncol, double **A){ // Invierte matrices no singulares.

		if (nrow!=ncol){
				cout << BOLDRED << "La matriz no es cuadrada: " << RESET << endl;
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
						// *(*(A+i)+j) = (rand()%210)*0.1-10;
						*(*(A+i)+j) = (rand()%210)*0.1-10;
		

		// Imprimir resultados:

		cout << "\n" << BOLDRED << "Matriz original generada aleatoriamente: " << RESET << endl; 
		printMat(n,n,A);

		cout << "\n" << BOLDBLUE << "Vector de constantes: " << RESET << endl;
		printVec(n,constant(n,n+1,A));

		double **B1 = Escalon(n,n+1,A);
		cout << "\n" << BOLDBLUE << "Matriz escalonada: " << RESET << endl;
		printMat(n,n,B1);

		double **B2 = EliGauss(n,n+1,A);
		cout << "\n" << BOLDBLUE << "Matriz diagonal: " << RESET << endl;
		printMat(n,n,B2);

		double **B3 = inversa(n,n,A);
		cout << "\n" << BOLDBLUE << "Matriz inversa: " << RESET << endl;
		printMat(n,n,B3);

		double ***LU = LUFact(n,n,A);
		double **L = *(LU);
		double **U = *(LU+1);
		cout << "\n" << BOLDBLUE << "Factorización LU: " << RESET << endl;
		cout << "\n" << BOLDYELLOW << "\t" << "L: " << RESET << endl;
		printMat(n,n,L);
		cout << "\n" << BOLDYELLOW << "\t" << "U: " << RESET << endl;
		printMat(n,n,U);

		if ( n<11 ){
				cout << "\n" << BOLDBLUE << "Determinante de la matriz hallado por cofactores: " << RESET << endl;
				cout << deter(n,n,A) << endl;
		};

		cout << "\n" << BOLDBLUE << "Determinante de la matriz hallado por la factorización LU: " << RESET << endl;
		cout << detDiag(n,U) << endl;

		double *S1 = solve(n,n+1,B2);
		cout << "\n" << BOLDGREEN << "Solución por eliminación gaussiana: " << RESET << endl;
		printVec(n,S1);

		double *S2 = matVec(n,n,B3,constant(n,n+1,A));
		cout << "\n\n" << BOLDGREEN << "Solución por matriz inversa: " << RESET << endl;
		printVec(n,S2);

		double *S3 = solTriSup(n,n+1,B1);
		cout << "\n\n" << BOLDGREEN << "Solución por Gauss-Jordan: " << RESET << endl;
		printVec(n,S3);

		double *S4 = solveLU(n,n+1,A);
		cout << "\n\n" << BOLDGREEN << "Solución por Factorización LU: " << RESET << endl;
		printVec(n,S4);


		cout << "\n\n" << BOLDYELLOW << "¡¡Las Cuatro Soluciones son Iguales!!" << RESET << endl;
		cout << endl << endl;
		

}
