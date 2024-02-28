#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

vector<vector<int>> read_triangle(string file_name){
    vector<vector<int>> triangle;
    ifstream file(file_name);
    string line;
    vector<int> tmp_line;
    int tmp_int;

    for(int k = 1; k<16; k++){
        for(int i = 0; i<k;i++){
            file >> tmp_int;
            tmp_line.push_back(tmp_int);
        }
        triangle.push_back(tmp_line);
        tmp_line.clear();
    }

    file.close();

    return triangle;
}

void print_vector(vector<int> vec){
    for(int i : vec){
        cout << setw(4) << i << "  ";
    }
    cout << endl;
}

void print_triangle(vector<vector<int>> triangle){
    for(int k = 0; k < 15;k++){
        cout << string(4*(15-k-1),' ');
        print_vector(triangle[k]);
    }
}


int main(){
    // Project Euler problem 18

    vector<vector<int>> triangle = read_triangle("pr18_data.txt");

    print_triangle(triangle);

    for(int k = 13; k >= 0; k--){
        for(int i = 0; i <= k;i++){
            triangle[k][i] = triangle[k][i] + max(triangle[k+1][i],triangle[k+1][i+1]);
        }
    }

    print_triangle(triangle);

    int ans = triangle[0][0];

    cout << ans << endl;

    return 0;
}