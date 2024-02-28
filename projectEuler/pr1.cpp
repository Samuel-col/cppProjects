#include<iostream>

using namespace std;

int main(){
		
		int s = 0;

		for (int i = 1; i<1000; i++)
				s += (i%3==0 || i%5==0)*i;

		cout << s << endl;

		return 0;
}
				
