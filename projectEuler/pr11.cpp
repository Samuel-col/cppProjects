#include <iostream>
#include <fstream>

using namespace std;

int ** read_matrix(string file_name,int ncol,int nrow){
    
    int ** A;
    A = new int *[ncol];
    for(int i = 0; i < ncol; i++){
        *(A+i) = new int [nrow];
    }

    ifstream file(file_name);
    int k;
    for(int i = 0; i < nrow; i++)
        for(int j = 0; j < ncol; j++){
            file >> k;
            *(*(A+j)+i) = k;
        }

    file.close();
    
    return A;
}

void print_matrix(int ** A,int ncol,int nrow){
    
    for(int i = 0; i < nrow;i++){
        for(int j = 0; j < ncol; j++){
            cout << A[j][i] << " ";
        }
        cout << endl;
    }

}

int greatest_row_product(int **A,int ncol, int nrow,int line_size){
    
    long int max = 1;
    long int prod;
    for(int j = 0; j<ncol-line_size;j++){
        for(int i = 0; i<nrow;i++){
            prod = 1;
            for(int jj = 0; jj<line_size;jj++)
                prod *= *(*(A+j+jj)+i);
            max = max + (prod > max)*(prod - max);
        }
    }

    return max;
}

int greatest_col_product(int **A,int ncol, int nrow,int line_size){

    long int max = 1;
    long int prod;
    for(int j = 0; j<ncol;j++){
        for(int i = 0; i<nrow-line_size;i++){
            prod = 1;
            for(int ii = 0; ii<line_size;ii++)
                prod *= *(*(A+j)+i+ii);
            max = max + (prod > max)*(prod - max);
        }
    }

    return max;

}

int greatest_did_product(int **A, int ncol, int nrow,int line_size){

    long int max = 1;
    long int prod;
    for(int j = 0; j<ncol-line_size;j++){
        for(int i = 0; i<nrow-line_size;i++){
            prod = 1;
            for(int ij = 0; ij<line_size;ij++)
                prod *= *(*(A+j+ij)+i+ij);
            max = max + (prod > max)*(prod - max);
        }
    }

    return max;

}

int greatest_dia_product(int **A, int ncol, int nrow,int line_size){

    long int max = 1;
    long int prod;
    for(int j = 0; j<ncol-line_size;j++){
        for(int i = 3; i<nrow;i++){
            prod = 1;
            for(int ij = 0; ij<line_size;ij++)
                prod *= *(*(A+j+ij)+i-ij);
            max = max + (prod > max)*(prod - max);
        }
    }

    return max;

}

int main(){
    // Project Euler problem 11

    int ncol = 20;
    int nrow = 20;
    int ** A = read_matrix("pr11_data.txt",ncol,nrow);

    cout << "Matriz leida:" << endl;
    print_matrix(A,ncol,nrow);

    long int max_h, max_v, max_dd, max_da;
    max_h  = greatest_row_product(A,ncol,nrow,4);
    max_v  = greatest_col_product(A,ncol,nrow,4);
    max_dd = greatest_did_product(A,ncol,nrow,4);
    max_da = greatest_dia_product(A,ncol,nrow,4);

    cout << "El máximo producto es " << max(max(max_dd,max_da),max(max_h,max_v)) << endl;





    return 0;
}