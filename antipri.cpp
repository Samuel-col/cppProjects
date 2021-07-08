// Librerias
#include <iostream>
#include <iomanip>
#include <math.h>
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


long int * cribae(int n){

		bool *cri; //booleano, true->primo, false->compuesto.
		cri = new bool [n+1];

		*cri = false;
		*(cri+1) = false;
		for (int i=2;i<=n;i++)
				*(cri+i) = true;

		for (int p=2;p<=n/2;p++) // ejecusión de la criba.
				for (int k=2*p;k<=n;k+=p)
						*(cri+k) = false;


		long int *pri; // vector de primos.
		int k;
		if (n<56){
				k = 56;
		}else{
				k = (int)(n/(log(n)-4));
		}
		pri = new long int [k];

		long int np = 1;
		for (int i=2;i<=n;i++) // recatar primos
				if(*(cri+i)){
						*(pri+np) = i;
						np++;
				};

		delete cri;

		*pri = np;

		return pri;

}


int maxPot(long int n,long int k){

		int pot = 0;
		while ( n % (long int)pow(k,pot) == 0 ){
				pot++;
		};
		pot--;

		return pot;
}


long int ** desFactPri(long int n,long int *pri){

		long int k = n/2; 
		int np = 1;
		while(*(pri+np)<=k) // número de primos menores o iguales a n/2
				np++;
		np++;

		long int **des;
		des = new long int *[2];
		*des = new long int [np]; // primos
		*(des+1) = new long int [np]; // potencias

		for (int i=1;i<np;i++)
				*(*des+i) = *(pri+i); // copiar primos necesarios

		for (int i=1;i<np;i++)
				*(*(des+1)+i) = (long int)maxPot(n,*(*des+i)); // hallar potencias

		**des = np; // guardar np.
		
		return des;
}

int nDiv(long int n,long int *pri){

		long int **des = desFactPri(n,pri); // calcular descomposición en factores primos.
		long int np = **des; // extraer cantidad de primos distintos menores a n/a.

		int ndiv = 1;

		for (int i=1;i<np;i++){ // calcular cantidad de divisores.
				ndiv *= *(*(des+1)+i) + 1;
		};

		delete *des;
		delete *(des+1);
		delete des;

		if (ndiv==1 & n>1) // excepción de primos.
				ndiv++;

		return ndiv;
}
		

long int antiPri(int k,long int *pri){
		
		long int bus = k;
		while(nDiv(bus,pri)<k){ // busca antiprimo.
				bus += 2;
		}

		return bus;
}


int main()
{
    cout << "¿Al menos qué cantidad de divisores debe tener el antiprimo?\t";
		int k; // numero de divisores objetivo.
		cin >> k;

		const long int top = 5e5;
		long int *primos = cribae(top); // lista de primos.


		long int antpri = antiPri(k,primos); // busca el antiprimo.

		cout << BOLDGREEN << antpri << YELLOW << " tiene " << BOLDGREEN << nDiv(antpri,primos) << YELLOW << " divisores." << endl;


		return 0;
}



