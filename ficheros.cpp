#include<fstream>
#include<string>
#include<math.h>
#include<iomanip>
using namespace std;

#define nC 20

int impMat(A[][nC]){
    //
    for
}

int leerFichero(string fichero,double A[][nC],int m){
    ifstream archivo (fichero.c_str());
    int c;int n=m;
    string linea;
    getline(archivo,line);
    archivo >> c;

    for (int i=0; i<m; i++)
	for (int j=0;j<n;j++)
	    if(c!=EOF){	    // EOF: End Of File
		A[i][j]=c;
		archivo >> c;
	    };
	    cout << linea << "-----------------------" << endl;
}

int crearFichero(string fichero,double A[][nC],int m){
    ofstream archivo (fichero.c_str());
    int c;int n=m;
    string linea;
    getline(archivo,line);
    archivo >> c;

    for (int i=0; i<m; i++)
	for (int j=0;j<n;j++)
	    if(c!=EOF){	    // EOF: End Of File
		A[i][j]=c;
		archivo >> c;
	    };
	    cout << linea << "-----------------------" << endl;
}
