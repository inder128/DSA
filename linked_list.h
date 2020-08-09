#ifndef LINKED_LIST_H
#define LINKED_LIST_H

//explanation at the end of this file
//geeksforgeeks tempelate of linked list

#include<iostream>
using namespace std;

/* Link list Node */
struct Node {
  int data;
  struct Node *next;
  Node(int x){
    data = x;
    next = NULL;
  }
};

void append(struct Node** head_ref, struct Node **tail_ref,
            int new_data){
    struct Node* new_node = new Node(new_data);
    
    if (*head_ref == NULL)
        *head_ref = new_node;
    else
        (*tail_ref)->next = new_node;
    *tail_ref = new_node;
}

void printList(struct Node *head){
    struct Node *temp = head;
    while (temp != NULL)
    {
       printf("%d ", temp->data);
       temp  = temp->next;
    }
}

/* Driver program to test above function*/
// int main(){
//     struct Node *head = NULL,  *tail = NULL;
//     int n, l;
//     cin>>n;
//     for (int i=1; i<=n; i++){
//         cin>>l;
//         append(&head, &tail, l);
//     }
//     return 0;
// }

#endif