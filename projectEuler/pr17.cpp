#include <iostream>
#include <vector>

using namespace std;

string number_to_string(int n,
    vector<string> from_1_to_19,
    vector<string> tens,
    string hundred){
    if(n<20){
        return from_1_to_19[n-1];
    }else if(n<100){
        int my_tens = n/10;
        int my_units = n - 10*my_tens;
        string result;
        if(my_units == 0){
            return tens[my_tens-2];
        }else{
            return tens[my_tens-2] + from_1_to_19[my_units-1];
        }
        
    }else if(n<1000){
        string and_ = "and";
        int my_cent = n/100;
        int my_rest = n - 100*my_cent;
        if(my_rest == 0){
            return from_1_to_19[my_cent-1] + hundred;
        }else{
            return from_1_to_19[my_cent-1] + hundred + and_ + number_to_string(my_rest,from_1_to_19,tens,hundred);
        }
    }else{
        return "onethousand";
    }
}

int main(){
    // Project Euler problem 17
    
    cout << "Enter the last number: ";
    int N;
    cin >> N;

    const vector<string> from_1_to_19 = {
        "one","two","three","four","five","six",
        "seven","eight","nine","ten","eleven",
        "twelve","thirteen","fourteen","fifteen",
        "sixteen","seventeen","eighteen","nineteen"
    };

    const vector<string> tens = {
        "twenty","thirty","forty","fifty","sixty",
        "seventy","eighty","ninety"
    };

    const string hundred = "hundred";

    int s = 0;
    string name;
    for(int k = 1; k <= N; k++){
        name = number_to_string(k,from_1_to_19,tens,hundred);
        s += name.size();
        cout << k << " | " << name << " | " << name.size() << endl;
    }

    cout << s << endl;


    return 0;
}