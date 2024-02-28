#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

#define n_digits 10

int max_of_rest(int * digits,int index){
    int min = n_digits;
    int argmin = index;
    for(int ii = index+1;ii<n_digits;ii++){
        if((digits[ii] > digits[index]) && (digits[ii] < min)){
            min = digits[ii];
            argmin = ii;
        }
    }
    return argmin;
}



bool permutate_with_greater(int (&digits)[n_digits],int index){
    if(index<0 || index>n_digits - 2) EXIT_FAILURE;
    
    int argnext = max_of_rest(digits,index);
    if(argnext == index){
        return 1;
    }else{
        int tmp = digits[index];
        digits[index] = digits[argnext];
        digits[argnext] = tmp;
        return 0;
    }
}

void next_permutation(int (&digits)[n_digits]){
    int i = n_digits - 2;
    bool perm;
    do{
        perm = permutate_with_greater(digits,i);
        i--;
    }while((i>=0) && (perm));
    i++;
    // Ordenar de menor a mayor todo lo que hay luego de i.
    if(i+1<n_digits-1){ // No está funcionando
        std::sort(digits+i+1,digits+n_digits);
    }
}


int main(int argc, char * argv[]){
    // Project Euler problem 24:
    // Find the millionth permutation of 0,1,2,...,9 in the lexicographic order.

    int index;
    if(argc == 1){
        index = 1000000;
    }else{
        index = std::stoi(std::string(argv[1]));
    }

    int digits[n_digits] = {0,1,2,3,4,5,6,7,8,9};

    for(int i = 1;i<index;i++){
        next_permutation(digits);
    }

    for(int i = 0;i<n_digits;i++) std::cout << digits[i] << std::flush;;
    std::cout << std::endl;


}