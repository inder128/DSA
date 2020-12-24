#include <iostream>
using namespace std;

void rotate_90(int *mat, int n){
    int index = 0, len = n-1, tmp;
    while(len>0){
        for (int i = 0; i <= len-1; ++i){
            tmp = *(mat + (index)*n + (index+i));
            *(mat + (index)*n + (index+i)) = *(mat + (index+len-i)*n + (index));
            *(mat + (index+len-i)*n + (index)) = *(mat + (index+len)*n + (index+len-i));
            *(mat + (index+len)*n + (index+len-i)) = *(mat + (index+i)*n + (index+len));
            *(mat + (index+i)*n + (index+len)) = tmp;
        }
        index++; len -= 2;
    }
}

void transpose(int *mat, int n){
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            swap(*(mat + i*n + j), *(mat + j*n + i));
}

void print_matrix(int *mat, int n){
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j)
            cout<<*(mat + i*n + j)<<" ";
        cout<<"\n";
    }
}

int main(){
    int n;
    cin>>n;
    int mat[n][n];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            mat[i][j] = i*n+j+1;
    print_matrix(mat[0], n);
    cout<<"\n";
    rotate_90(mat[0], n);
    print_matrix(mat[0], n);
    cout<<"\n";
    transpose(mat[0], n);
    print_matrix(mat[0], n);
    return 0;
}