#include <iostream>
#include <math.h>
#include <vector>

int sum_of_divisors(int n){

    int s = 0;
    for(int k = 1; k < std::sqrt(n); k++)
        s += k*(n%k == 0) + (n/k)*(n%k == 0)*(k!=1);
    if(std::floor(std::sqrt(n)) == std::sqrt(n)) s += std::sqrt(n);

    return s;
}

std::vector<int> list_abundant_numbers(int upper){

    std::vector<int> result;
    for(int k = 1; k < upper;k++)
        if(k < sum_of_divisors(k))
            result.push_back(k);

    return result;
}



int main(){
    // Project Euler problem 23
    
    // Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.

    int upper = 28123;
    std::vector<int> abundants = list_abundant_numbers(upper);

    // Imprimir números abudantes hasta upper
    /**
    for(int k : abundants)
        std::cout << k << " ";
    std::cout << std::endl;
    */
    

    // Crear array indicador de ser suma de abundantes
    bool * is_sum_of_abundants;
    is_sum_of_abundants = new bool [upper];
    for(int i = 0;i < upper;i++)
        is_sum_of_abundants[i] = 0;

    // Llenar array indicador
    for(int a : abundants)
        for(int b : abundants)
            if(a+b <= upper)
                is_sum_of_abundants[a+b-1] = 1;

    // Sumar números que no son suma de abundantes
    int s = 0;
    for(int i = 0; i<upper; i++)
        if(!is_sum_of_abundants[i])
            s += i+1;

    std::cout << s << std::endl;
}