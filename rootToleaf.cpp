#include <iostream>
#include <vector>
#include "buildTree.h"
using namespace std;

void called(Node * root);

int main() {
    int t;
    scanf("%d ",&t);
    while(t--){
        string s;
        getline(cin,s);
        Node* root = buildTree(s);
        called(root);
        cout<<endl;
    }
    return 0;
}

void printvec(vector <Node *> &v){
    vector<Node *>::iterator ptr;
    for (ptr = v.begin(); ptr < v.end(); ptr++) 
        cout<<(*ptr)->data<<" ";  
    cout<<endl;  
}

void rTol(Node *root, vector<Node *> &v){
    v.push_back(root);
    if(root->left==NULL and root->right==NULL)
        printvec(v);
    if(root->left) rTol(root->left, v);
    if(root->right) rTol(root->right, v);
    v.pop_back();
}

void rootToleaf(Node *root){
    vector<Node *> v;
    rTol(root, v);
}

void called(Node *root){
    rootToleaf(root);
}