#include <iostream>
#include <vector>

using namespace std;

// Prime numbers until n
vector<int> prime_n(int n){

    if (n < 2){
        cout << "n must be greater than 1" << endl;
        return {};
    }

    bool div = 0;
    vector<int> pr = {2};
    for(int k = 3; k<=n; k++){
        div = 0;
        for(int j = 2; j<k; j++){
            if(k%j == 0){
                div = 1;
                break;
            }
        }
        if(!div) pr.push_back(k);
    }

    return pr;
}

int main(){
    // Project Euler problem 5

    cout << "Ingrese el mayor de los divisores:\t";
    int k;
    cin >> k;

    // Productoria de los primos menores o iguales a k
    vector<int> pr = prime_n(k);
    cout << "Primes collected" << endl;
    int prod = 1;
    for(int p : pr) prod *= p;

    // MCM de 1:k
    bool div;
    int proposal = prod;
    do{
        div = 1;
        for(int i = 2;i<=k; i++){
            if(proposal%i != 0){
                div = 0;
                proposal += prod;
                break;
            }
        }
    }while(!div);

    cout << proposal << " is the answer" << endl;    

    return 0;

};