const double EPS = 1e-9, PI = acos(-1);

struct P{ 
	double x, y;
	P(){ x = y = 0.0; }
	P(double _x, double _y) : x(_x), y(_y) {} 

	bool operator < (P other) const {
		if(fabs(x - other.x) > EPS){
			return x < other.x;
		}
		return y < other.y; 
	} 

	bool operator == (P other) const {
		return fabs(x - other.x) < EPS && abs(y - other.y) < EPS; 
	}

	P rotate(double theta) {
		double rad = theta * PI / 180;
		return P(x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad)); 
	}

	double distSq(P other){
		double dx = x - other.x;
		double dy = y - other.y;
		return dx * dx + dy * dy;
	}
	double dist(P other){
		return hypot(x - other.x, y - other.y);
	}

	friend ostream& operator << (ostream &os, const P &p) {
        return os << pi(p.x, p.y);
    }
    friend istream& operator >> (istream &is, P &p) {
        return is >> p.x >> p.y;
    }
};






// int
struct P{ 
	int x, y;
	P(){ x = y = 0; }
	P(int _x, int _y) : x(_x), y(_y) {} 

	bool operator < (P other) const {
		return pi(x, y) < pi(other.x, other.y);
	} 

	bool operator == (P other) const {
		return x == other.x and y == other.y;
	}

	// rotate 90 degree counter clockwise;
	P rotate(){
		return P(-y, x);
	}

	int distSq(P other){
		int dx = x - other.x;
		int dy = y - other.y;
		return dx * dx + dy * dy;
	}
	double dist(P other){
		return hypot(x - other.x, y - other.y);
	}

	friend ostream& operator << (ostream &os, const P &p) {
        return os << pi(p.x, p.y);
    }
    friend istream& operator >> (istream &is, P &p) {
        return is >> p.x >> p.y;
    }
};