#include <iostream> 
using namespace std; 

bool comp1ss(pair<int, int> p1, pair<int, int> p2){
    if(p1.first==p2.first)
        return (p1.second<p2.second);
    return (p1.first<p2.first); 
}

bool comp1sg(pair<int, int> p1, pair<int, int> p2){
    if(p1.first==p2.first)
        return (p1.second>p2.second);
    return (p1.first<p2.first); 
}

bool comp1gg(pair<int, int> p1, pair<int, int> p2){
    if(p1.first==p2.first)
        return (p1.second>p2.second);
    return (p1.first>p2.first); 
}

bool comp1gs(pair<int, int> p1, pair<int, int> p2){
    if(p1.first==p2.first)
        return (p1.second<p2.second);
    return (p1.first>p2.first); 
}

bool comp2ss(pair<int, int> p2, pair<int, int> p1){
    if(p1.second==p2.second)
        return (p1.first>p2.first);
    return (p1.second>p2.second); 
}

bool comp2sg(pair<int, int> p2, pair<int, int> p1){
    if(p1.second==p2.second)
        return (p1.first>p2.first);
    return (p1.second<p2.second); 
}

bool comp2gg(pair<int, int> p2, pair<int, int> p1){
    if(p1.second==p2.second)
        return (p1.first<p2.first);
    return (p1.second<p2.second); 
}

bool comp2gs(pair<int, int> p2, pair<int, int> p1){
    if(p1.second==p2.second)
        return (p1.first<p2.first);
    return (p1.second>p2.second); 
}

int main() { 
    
    pair <int, int> p[6];
    p[0] = make_pair(1, 1);
    p[1] = make_pair(2, 3);
    p[2] = make_pair(2, 2);
    p[3] = make_pair(1, 2);
    p[4] = make_pair(1, 5);
    p[5] = make_pair(1, 6);
    // sort(p, p+6, comp1ss);
    // sort(p, p+6, comp1sg);
    // sort(p, p+6, comp1gg);
    // sort(p, p+6, comp1gs);
    // sort(p, p+6, comp2ss); 
    // sort(p, p+6, comp2sg); 
    // sort(p, p+6, comp2gg); 
    // sort(p, p+6, comp2gs);
    for (int i = 0; i < 6; ++i)
        cout<<p[i].first<<" "<<p[i].second<<"   ";
    cout<<endl;
    return 0; 
}