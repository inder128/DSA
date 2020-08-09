#include <bits/stdc++.h>
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

// always pass a map by & , if you pass it by reference.
pair<int, int> min_max_path(Node *root,  map <Node *, pair<int, int> > &map_path){
    if(root==NULL) return make_pair(0, 0);
    if(map_path.find(root) != map_path.end()) return map_path[root];

    pair <int, int> left_path_pair = min_max_path(root->left, map_path);
    pair <int, int> right_path_pair = min_max_path(root->right, map_path);

    int curr_min = 1, curr_max=1;

    if(root->left!=NULL and root->data == root->left->data-1)
        curr_min = max(curr_min, 1 + left_path_pair.first);
    if(root->right!=NULL and root->data == root->right->data-1)
        curr_min = max(curr_min, 1 + right_path_pair.first);

    if(root->left!=NULL and root->data == root->left->data+1)
        curr_max = max(curr_max, 1 + left_path_pair.second);
    if(root->right!=NULL and root->data == root->right->data+1)
        curr_max = max(curr_max, 1 + right_path_pair.second);

    // cout<<root->data<<endl;
    // cout<<curr_min<<" "<<curr_max<<endl;

    map_path[root] = make_pair(curr_min, curr_max);
    return map_path[root];
}

// it computes the max lenth of path in which all values are consecutive;
void incPath(Node *root){
    int max_path = 0;
    map <Node *, pair<int, int> > map_path;
    min_max_path(root, map_path);

    map <Node *, pair<int, int> >::iterator itr;
    for (itr = map_path.begin(); itr != map_path.end(); itr++){
        pair <int, int> pr = itr->second;
        // cout<<pr.first<<" "<<pr.second<<endl;
        max_path = max(max_path, pr.first + pr.second - 1);
    }
    cout<<max_path<<endl;
}


// this function takes value of a node and returns its path from root to that node in a vector;
bool bfsPathSearch(Node *root, vector <Node *> &dq, int &k){
    if(root->data==k) return true;
    if(root->left!=NULL){
        dq.push_back(root->left);
        if(bfsPathSearch(root->left, dq, k))
            return true;
    }
    if(root->right!=NULL){
        dq.push_back(root->right);
        if(bfsPathSearch(root->right, dq, k))
            return true;
    }
    dq.pop_back();
    return false;
}

void called(Node *root){
    // call your function here;
    return;
}