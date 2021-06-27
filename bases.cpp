#include <iostream>
#include <math.h>
using namespace std;

int aBase10(int num,int base){
    int R = 0,i = 0;
    while (num > 0){
	R += (num%10)*pow(base,i);
	num = num/10;
	i++;
    }
    return R;
}

int deBase10(int num,int base){
    int i=0,dig;
    long int R=0;
    while ( pow(base,i) < num )
        i++;
    while ( i>0 ){
	i--;
	dig = num/pow(base,i);
	R += dig*pow(10,i);
	num -= dig*pow(base,i);
    }
    return R;
}

int main()
{
    //Módulos
    int deBase,aBase;
    long int n;
    
    cout << "¿En qué base está el número? ";
    cin >> deBase;
    cout << "¿A qué base? ";
    cin >> aBase;
    cout << "El número es... ";
    cin >> n;
    cout << "En base " << deBase << ": " << n << endl;
    cout << "En base " << aBase << ": " << deBase10(aBase10(n,deBase),aBase) << endl;
    return 0;
}
