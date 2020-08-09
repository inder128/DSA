#include<iostream>
#include "linked_list.h"
using namespace std;

// time complexity -> O(n);
// space complexity -> O(1);
// function detects the cycle in a linked list and returns starting node
// if cycle present otherwise returns NULL;
Node *floyd(Node *head){
    // checking edge cases;
    if(!head) return NULL;
    if(head->next==head) return head;

    // implementating fast runner algo.
    Node *slow = head;
    Node *fast = head->next;
    // break loop if anything becomes null i.e. cycle doesnot exists;
    while(slow and fast and slow!=fast){
        slow = slow->next;
        fast = fast->next;
        if(!fast) break;
        fast = fast->next;
    }

    // checking how did loop broke;
    if(fast!=slow)
        return NULL;

    // now loop exists;
    // head and fast->next will be same difference from start;
    Node *ptr1 = head;
    Node *ptr2 = fast->next;
    while(ptr1!=ptr2){
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    return ptr1;
}

int main(){
    struct Node *head = NULL,  *tail = NULL;

    // n is the total no of nodes in linked list.
    // linked list will be like this :- 
    // (1)->(2)->----->(k-1)->(k)->(k+1)->---->(n-1)->(n)->(k)--->(k+1)--->
    // k is the first node in loop cycle.
    int n, k;
    cin>>n;
    for (int i=1; i<=n; i++)
        append(&head, &tail, i);

    // creating loop
    // give k=0 to test for no loop linked list;
    cin>>k;
    if(k){
        k--;
        Node *tmp = head;
        while(k--)
            tmp = tmp->next;
        tail->next = tmp;
    }

    // getting the node if cycle exists otherwise null.
    Node *start = floyd(head);

    // printing result.
    if(start)
        cout<<start->data<<"\n";
    else
        cout<<"No LOOP Detected\n";

    return 0;
}