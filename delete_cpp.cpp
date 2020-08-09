#include <iostream>
using namespace std;

int main(){
    int n;
    cin>>n;

    // we can allocate memory of variable size;
    int *ptr1 = new int[n];
    for (int i = 0; i < n; ++i)
        ptr1[i] = i+1;
    cout<<*ptr1<<endl;
    cout<<ptr1<<endl;

    // delete operator doesn't deletes the values at the memory 
    // it just tell the program that this memory is now free to use;
    delete[] ptr1;

    // we can still access value at memory ptr1;
    cout<<ptr1<<endl;

    int *ptr2 = new int[n];
    // ptr2 will be equal to ptr1, because ptr1 memory was free to use (delete[] ptr);
    cout<<ptr2<<endl;
    cout<<*ptr2<<endl;

    int *ptr3 = new int[n];
    // ptr3 will be equal to ptr2+n, because memory from ptr to ptr+n-1 is in use and not free;
    cout<<ptr3<<endl;
    return 0;
}