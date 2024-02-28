#include <iostream>
#include <fstream>
#include <string>

using namespace std;

unsigned long long int sucessor(unsigned long long int n){
    return (n/2)*(n%2==0) + (3*n+1)*(n%2==1);
}

int chain_length(int n){
    int counter = 1;
    unsigned long long int k = n;
    while(k!=1){
        k = sucessor(k);
        counter++;
    }
    return counter;
}

int find_argmax(int N){

    int max = 0;
    int argmax = 0;
    int current_length = 0;
    for(int k = 1; k <= N; k++){
        current_length = chain_length(k);
        argmax = argmax + (current_length > max)*(k - argmax);
        max = max + (current_length > max)*(current_length - max);
    }
    return argmax;
}

void collazt_seq(int n){
    string file_name = "collatz_sequence_";
    string file_extension = ".txt";
    ofstream out(file_name + to_string(n) + file_extension);
    unsigned long long int k = n;
    int id = 1;
    while(k!=1){
        out << id << " | " << k << endl;
        k = sucessor(k);
        id++;
    }
    out << id << " | " << 1;
    out.close();
}

int main(){
    // Project Euler problem 14
    cout << "Insert the upper bound: ";
    int N;
    cin >> N;

    
    int argmax = find_argmax(N);

    cout << argmax << " gives a chain of length " << chain_length(argmax) << endl;
    cout << string(30,'-') << endl;
    collazt_seq(argmax);
    

    return 0;
}