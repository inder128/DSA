// Two lines different for different Hulls;
class Line{
public:
    // m -> slope;
    // c -> constant;
    // line -> y = m * x + c;
    // p -> x coordinate of intersection with next line (whose slope(o->m) >= m);
    mutable int m, c, p;
    bool operator<(const Line& o) const { 
        // return m < o.m; // for upper Hull
        return m > o.m; // for lower Hull
    }
    bool operator<(int op) const { 
        return p < op; 
    }
};

class LineContainer : multiset<Line, less<>> {
    // in multiset lines are soreted with increasing / decreasing slope(m);
public:
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    static const int inf = LLONG_MAX;

    int div(int a, int b){ // floored division
        return a / b - ((a ^ b) < 0 && a % b); 
    }

    // return true if line y becomes useless and must be deleted;
    bool isect(iterator x, iterator y){
        if(y == end()){ 
            x->p = inf;
            return false;
        }

        if(x->m == y->m){
            // x->p = x->c > y->c ? inf : -inf; // for upper Hull
            x->p = x->c < y->c ? inf : -inf; // for lower Hull
        }
        else{
            // assert(y->m > x->m);
            x->p = div(y->c - x->c, x->m - y->m);
        }
        return x->p >= y->p;
    }

    void add(int m, int c){
        auto z = insert({m, c, 0}), y = z++, x = y;

        // z.m > y.m;
        while(isect(y, z)){
            z = erase(z);
        }

        if(x != begin() and isect(--x, y)){ // handle x.m == y.m;
            isect(x, y = erase(y));
        }

        while((y = x) != begin() and (--x)->p >= y->p){ // x.m < y.m;
            isect(x, erase(y));
        }

        // now every itr->m is unique in multiset;
    }

    int query(int x){
        assert(!empty());
        auto l = *lower_bound(x);
        return l.m * x + l.c;
    }

    void print(){
        for(auto itr = begin(); itr != end(); itr++){
            cout<<(itr->m)<<" "<<(itr->c)<<" "<<(itr->p)<<el;
        }
    }
};