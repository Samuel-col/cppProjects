#include <iostream>

using namespace std;

int main(){
    // Project Euler problem 10

    cout << "Ingrese la cota superior: ";
    int N;
    cin >> N;

    bool * is_prime;
    is_prime = new bool [N];
    for(int i = 0; i<N; i++) *(is_prime+i) = 1;

    for(int k = 1; k<N; k++){
        if(*(is_prime+k) == 1){
            for(int j = 2; j <= N/(k+1); j++){
                *(is_prime+(k+1)*j-1) = 0;
            }
        }
    }

    long int S = 0;
    for(int i = 1; i < N; i++)
        if(*(is_prime+i)==1)
            S += i+1;

    cout << S << endl;


    return 0;
}