#include <iostream>

using namespace std;

int main(){

		// Variables
		int f0 = 1;
		int f1 = 1;
		int f2;
		int s = 0;

		while (f2 <= 4000000){

				// Sucesión
				f2 = f0 + f1;
				f0 = f1;
				f1 = f2;

				// Suma
				s += (f2%2==0)*f2;
		}

		cout << s << endl;

		return 0;
}

