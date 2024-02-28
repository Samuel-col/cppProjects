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

    for(int k = 1; k<101; k++){
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

int main(){
    // Project Euler problem 67

    vector<vector<int>> triangle = read_triangle("p067_triangle.txt");


    for(int k = 98; k >= 0; k--){
        for(int i = 0; i <= k;i++){
            triangle[k][i] = triangle[k][i] + max(triangle[k+1][i],triangle[k+1][i+1]);
        }
    }


    int ans = triangle[0][0];

    cout << ans << endl;

    return 0;
}