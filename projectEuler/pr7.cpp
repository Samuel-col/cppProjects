#include <iostream>
#include <vector>

using namespace std;

int main(){
    // Project Euler problem 7

    int N = 130000;
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

    vector<int> primes;
    for(int i = 1; i < N; i++)
        if(*(is_prime+i)==1)
            primes.push_back(i+1);

    if (primes.size()>10000){
        cout << "El 10001-ésimo primo es " << primes[10000] << endl;
    }


    return 0;
}