#include "iostream"
#include "fstream"
#include "string"

using namespace std;

int main(){
    // Nombres de los archivos
    string nF1,nF2;
    cout << "Ingrese el nombre del primer archivo (con extensión): ";
    cin >> nF1;
    cout << "Ingrese el nombre del segundo archivo (con extensión): ";
    cin >> nF2;

    // Abrir archivos
    ifstream f1(nF1);
    ifstream f2(nF2);

    // Inicializar coordenadas, lectores y resultados
    int l1=0,l2=0,c1=0,c2=0;
    string line1,line2;
    bool res = true;

    // Comparación de líneas
    while(getline(f1,line1) && getline(f2,line2)){
        l1++;l2++;
        if(line1.size()!=line2.size()){ // Si las líneas son de distinta longitud
            cout << "En la línea " << l1 << " los archivos no contienen la misma cantidad de caracteres:" << endl;
            cout << "Primer archivo:\t" << line1 << endl;
            cout << "Segundo archivo:\t" << line2 << endl;
            res = false;
        }else{
            for (int i =0;i<line1.size();i++){ // Si las líneas difieren en un caracter
                if(line1[i]!=line2[i]){
                    cout << "EL caracter " << i+1 << " de la línea " << l1 << " es " << line1[i] << " en el pirmer archivo, mientras que en el segundo es " << line2[i] << endl;
                    res = false;
                }
            }
        }
    }
    if(getline(f1,line1) && !getline(f2,line2)){ // Si a un archivo le sobran líneas
        cout << "El primer archivo tiene más líneas que el segundo, el cuál tiene solo " << l1 << endl;
        res = false;
    }
    if(!getline(f1,line1) && getline(f2,line2)){ // Si al otro archivo le sobran líneas
        cout << "El segundo archivo tiene más líneas que el primero, el cuál tiene solo " << l1 << endl;
        res = false;
    }

    string resS = res ? "iguales" : "diferentes";
    cout << "\nLos archivos son " << resS << "." << endl;
    return 0;
}
