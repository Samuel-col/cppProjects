#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
    // Project Euler problem 8

    cout << "Ingrese el número de dígitos consecutivos a considerar: ";
    int n;
    cin >> n;

    ifstream file("pr8_data.txt");
    vector<int> serie;
    char c;
    while(file.get(c)){
        if(c != '\n')
            serie.push_back((int)c - (int)'0');
    }

    /**
    for(int i : serie)
        cout << i << " ";
    cout << endl;
    **/

    long int max = 1;
    int argmax = 0;
    long int prod;
    for(int i = 0; i <= (serie.size()-n); i++){
        prod = 1;
        for(int ii = 0; ii < n; ii++)
            prod *= serie[i+ii];
        argmax = argmax + (prod > max)*(i + 1 - argmax);
        max = max + (prod > max)*(prod - max);
    }

    cout << argmax << " : " << max << endl;

    return 0;
}