#ifndef BUILD_TREE_H
#define BUILD_TREE_H

//explanation at the end of this file

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
};

void called(Node * root);

Node* newNode(int val){
    Node* temp = new Node;
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

Node* buildTree(string str){
    if(str.length() == 0 || str[0] == 'N')
        return NULL;
    vector<string> ip;
    istringstream iss(str);
    for(string str; iss >> str; )
        ip.push_back(str);
    Node* root = newNode(stoi(ip[0]));
    queue<Node*> queue;
    queue.push(root);
    int i = 1;
    while(!queue.empty() && i < ip.size()) {
        Node* currNode = queue.front();
        queue.pop();
        string currVal = ip[i];
        if(currVal != "N") {
            currNode->left = newNode(stoi(currVal));
            queue.push(currNode->left);
        }
        i++;
        if(i >= ip.size()) break;
        currVal = ip[i];
        if(currVal != "N") {
            currNode->right = newNode(stoi(currVal));
            queue.push(currNode->right);
        }
        i++;
    }
    return root;
}

// here is a demonstration how to use this function
// build tree takes a string of type ("10 20 30 40 60 N N") 
// and converts it into a tree and returns pointer to head of tree.
// int main() {
//     int t;
//     string s;
//     cin>>t;
//     getline(cin, s); //to break the line
//     while(t--){
//         getline(cin, s);
//         Node* root = buildTree(s);
//         cout<<root->data;
//     }
//     return 0;
// }

#endif