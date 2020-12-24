#include <iostream>
#include <string>
#include <vector>
using namespace std;

string str, pat;
int n, m;
vector <int> start_indexes;

int pre_suf_matching(int curr, int comp, int lp[]){
    if(comp<0) return 0;
    if(pat[curr]==pat[lp[comp]])
        return lp[comp]+1;
    return pre_suf_matching(curr, lp[comp]-1, lp);
}

void pre_suf_matching_iterative(int lp[]){
    lp[0]=0;
    int curr=1, comp=0;
    while(curr<m){
        if(pat[curr]==pat[comp]){
            lp[curr] = comp+1;
            curr++;
            comp++;
        }
        else{
            if(comp==0){
                lp[curr] = 0;
                curr++;
            }
            else comp = lp[comp-1];
        }
    }
    
}

    

int main(){
    cin>>str>>pat;
    n = str.length();
    m = pat.length();
    int lp[m];

    // iterative method;
    pre_suf_matching_iterative(lp);

    // recurrence method;
    // for (int i = 1; i < m; ++i)
    //     lp[i] = pre_suf_matching(i, i-1, lp);

    for (int i = 0; i < m; ++i)
        cout<<lp[i]<<" ";
    cout<<endl;
    int curr_str = 0, curr_pat = 0;
    while(curr_str<n){
        if(str[curr_str]==pat[curr_pat]){
            curr_str++;
            curr_pat++;
        } 
        else{
            if(curr_pat==0) curr_str++;
            else curr_pat = lp[curr_pat-1];
        }
        
        if(curr_pat==m){
            start_indexes.push_back(curr_str-m);
            curr_pat = lp[m-1];
        }
    }
    for (int i = 0; i < start_indexes.size(); ++i)
        cout<<start_indexes[i]<<" ";
    cout<<endl;
    return 0;
}