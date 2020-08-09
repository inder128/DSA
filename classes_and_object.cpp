// Difference Between Object and Class in C++

// Class is a template or blueprint with which objects are created is known as Class.
// It is a user-defined data type, which holds its own data members and member functions,
// which can be accessed and used by creating an instance (or object) of that class.
// Data members are the data variables and member functions are the functions used to
// manipulate these variables and together these data members and member functions define
// the properties and behaviour of the objects (or instance) of that Class.

// The class is a technique used to bind data and its associated functions together, 
// in contrast, Object is the created instance of a class.

// Object (or instances of a class) is invoked by new keyword. It consumes memory, 
// but when a class is defined it consumes no memory;

#include <bits/stdc++.h>
using namespace std;

class cube{
	// here a is a private member (by default), and it can't be accessed outside this class
	// except friend class or friend functions.
	// frien concept:- ( https://www.geeksforgeeks.org/friend-class-function-cpp/ )
	int a;

	// just like prive there is another access modimiers (protected);
	// Protected access modifier is similar to that of private access modifiers, 
	// the difference is that the class member declared as Protected are inaccessible 
	// outside the class but they can be accessed by any subclass(derived class) of that class.

	// public members can be accessed anywhere;
	public:

	// constructo functions;
	// this constructor is executed when instance or object is created in a normal way or using 
	// new keyword without any parameters passed.
	// constructors returns nothing;
	// if there is no constructor is defined, c++ by default create a constructor which accepts 
	// no arguents and have nothing in it.
	cube(){}

	// this constructer gets executed if instance or object is created using new keyword
	// All inside class functions are inline functions by default.
	// inline functions :-  ( https://www.geeksforgeeks.org/inline-functions-cpp/ )
	// usually online small function should be inside because they are inline.
	// and edje is passed as a parameter.
	cube(int edje){
		a = edje;
	}

	// destructors:- ( https://www.geeksforgeeks.org/destructors-c/ )
	~cube(){
		cout<<"this object ends here\n";
	}

	// setEdje is defined inside class definition. 
	void setEdje(int edje){
		a = edje;
	}

	// volume is defined outside class definition. 
	int volume();
};

// outside class definition. 
int cube::volume(){
	return (a*a*a);
}

void diff_allocations(){
	// here d will be a pointer pointing to a object or instance of class cube;
	// new keyword allocates memory execute the right constructor and returns the
	// pointer or addres of first byte of the memory allocated;
	// https://www.geeksforgeeks.org/malloc-vs-new/ - diff b/w new and malloc;
	// https://www.geeksforgeeks.org/stack-vs-heap-memory-allocation/ 
	cube * d = new cube(4);

	// for the object succesfully create, either the class should have no constructer or
	// a constructor which accepts no arguments;
	cube c;
	c.setEdje(5);

	// here constructor with 
	cube e(4);

	// here is another way to initialise a object;
	cube f = cube(6);

	// you can't do c.a=10 because 'a' is a private attribute of class cube or object c;
	c.setEdje(10);
	cout<<"The volume of the cube c is "<<c.volume()<<"\n";
	cout<<"The volume of the cube d is "<<d->volume()<<"\n";
	cout<<"The volume of the cube e is "<<e.volume()<<"\n";
	cout<<"The volume of the cube f is "<<f.volume()<<"\n";
}

// Encapsulation:-
// it is wraping up the data and the fumctions that manipulates them.
// it also leads to data abstraction or hiding, which will be discussed later.
// The process of implementing encapsulation can be sub-divided into two steps:
//   1)- The data members should be labeled as private using the private access specifiers
//   2)- The member function which manipulates the data members should be labeled 
// 	     as public using the public access specifier.


int main(){
	diff_allocations();
	return 0;
}