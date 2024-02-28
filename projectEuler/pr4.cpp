#include <iostream>
#include <math.h>

using namespace std;

int no_digitos(int n){

		int k = 0;

		while (n/(int)pow(10,k) > 0)
				k++;

		return k;
}

int digit(int n, int k){

		int a = n/(int)pow(10,k-1)*(int)pow(10,k-1);
		int b = n/(int)pow(10,k)*(int)pow(10,k);

		return (a-b)/(int)pow(10,k-1);
}

bool es_palindromo(int n){

		int nd = no_digitos(n);
		bool res = 1;

		for (int i = 1; i<=nd/2; i++)
				res *= digit(n,i) == digit(n,nd - i + 1);
				
		return res;
}

int main(){

		int maximo = 1;
		for(int i = 0; i<1000; i++)
				for(int j = 0; j<1000; j++)
						if(i*j > maximo && es_palindromo(i*j))
								maximo = i*j;

		cout << maximo << endl;

		return 0;
}
