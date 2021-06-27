#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    int n,k,np=0;
    cout << "¿Hasta qué cantidad desea buscar números primos?   ";
    cin >>  n;
    int p[(int)((1.25506*n)/log(n))];
    bool A[n+1];
    A[0] = false;
    A[1] = false;
    for (int i=2;i<=n;i++)
	A[i]=true;
    for (int p=2;p<n/2;p++)
	for (int k=2*p;k<=n;k+=p)
	    A[k]=false;
    for (int i=0;i<=n;i++)
	if (A[i]){
	    p[np]=i;
	    np++;
	};
    for (int i=0; i<np;i++)
	cout << p[i] << endl;
    cout << "Se encontraron " << np << " números primos." << endl;
    return 0;
}
