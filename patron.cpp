#include <iostream>
#include <vector>
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


char randSymbol(string symbols){
		unsigned int n_str = symbols.length();
		unsigned int index = rand()%n_str;
		return symbols[index];
}

string randCol(vector<string> colors){
		unsigned int n_str = colors.size();
		unsigned int index = rand()%n_str;
		return colors[index];
}


float randU(){
		return (float)rand()/RAND_MAX;
}


void printMat(unsigned int nfil,unsigned int ncol,char **A, vector<string> colors){ // Imprime matrices.
		for (int i = 0;i < nfil;i++){
				for (int j = 0;j < ncol;j++)
						cout << randCol(colors) <<  *(*(A+i)+j);
				cout << endl;
		};
}


int main(){

		// Semilla aleatoria
		srand(time(NULL));

		// Matrix
		unsigned int n = 8, m = 50;
		char ** pat;
		pat = new char *[n];
		for (int i = 0; i < n; i++)
				*(pat + i) = new char [m];

		// Llenar
		string symbols = "\\/";
		for(int i = 0; i < n; i++)
				for(int j = 0; j < m; j++)
						*(*(pat + i) + j) = randSymbol(symbols);

		// Poner asteriscos
		float delta1 = 0.08;
		for (int i = 0; i < n; i++){
				for (int j = 0; j < m; j++){
						if (randU()<delta1){
								*(*(pat + i) + j) = '*';
						}
				}
		}

		// Poner numerales
		float delta2 = 0.12;
		for (int i = 0; i < n; i++){
				for (int j = 0; j < m; j++){
						if (randU()<delta2){
								*(*(pat + i) + j) = '#';
						}
				}
		}

		// Imprimir
		vector<string> colors = {RESET,BLACK,RED,GREEN,YELLOW,BLUE,MAGENTA,CYAN,WHITE,BOLDBLACK,BOLDRED,BOLDGREEN,BOLDYELLOW,BOLDBLUE,BOLDMAGENTA,BOLDCYAN,BOLDWHITE};
		printMat(n,m,pat,colors);

		cout << RESET << endl;

		return 0;
}


