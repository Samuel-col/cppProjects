#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector<bool> primos(long int n){
		vector<bool> pr(n+1,1);

		long int tope = (n+1)/2;
		long int q = 2;

		for(long int k = 2; k <= tope; k++){
				while(k*q <= n){
						pr[k*q] = 0;
						q++;
				}
				q = 2;
		}

		return pr;
}

int main(){

		long int n;
		cout << "Ingrese en número: " << endl;
		cin >> n;

		int np = ceil(sqrt(n)) + 1;
		vector<bool> pr = primos(np);
		cout << "Lista de números primos generada." << endl;

		for (long int i = np; i > 0; i--)
				if(pr[i] == 1 && n%i==0){
						cout << i << endl;
						break;
				}

		return 0;
}



