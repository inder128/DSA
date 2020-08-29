// Difference Between Object and Class in C++

// Class is a collection of related data and functions under a single name;
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

// operator overlading 
// default comparetor;
struct className { 
    bool operator()(type t1, type t2) { 
        // return "true" if "t1" is ordered  
        // before "t2", for example: 
        return t1.val < p1.val; 
    } 
}; 


#include <bits/stdc++.h>
using namespace std;

class cube{
	// here a is a private member (by default), and it can't be accessed outside this class;
	// public getter and setter functions are made to access and modify private variable outside the class;
	// except friend class or friend functions.
	// friend concept:- ( https://www.geeksforgeeks.org/friend-class-function-cpp/ )
	int a;

	// just like privet there is another access modifiers (protected);
	// Protected access modifier is similar to that of private access modifiers, 
	// the difference is that the class member declared as Protected are inaccessible 
	// outside the class but they can be accessed by any subclass(derived class) of that class.
	// public members can be accessed anywhere;
	public:

	// constructor functions;
	// this constructor is executed when instance or object is created in a normal way or using 
	// new keyword without any parameters passed.
	// constructors returns nothing;
	// if there is no constructor is defined, c++ by default create a constructor which accepts 
	// no arguents and have nothing in it.
	cube(){}

	// this constructer gets executed if instance or object is created using new keyword
	// All inside class functions are inline functions by default.
	// Macro vs Inline fn :- Macro cannot access private members of class.
	// inline functions :-  ( https://www.geeksforgeeks.org/inline-functions-cpp/ )
	// Inline function is a function that is expanded in line when it is called.
	// usually online small function should be inside because they are inline.
	// and edje is passed as a parameter.
	cube(int edje){
		a = edje;
	}

	// destructors:- ( https://www.geeksforgeeks.org/destructors-c/ )
	// it is called when object goes out of scope (and memory is realesed);
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

// By declaring a function member as static, you make it independent of any particular object of the class. 
// A static member function can be called even if no objects of the class exist;


void diff_allocations(){
	// here d will be a pointer pointing to a object or instance of class cube;
	// new keyword allocates memory execute the right constructor and returns the
	// pointer or addres of first byte of the memory allocated;
	// https://www.geeksforgeeks.org/malloc-vs-new/ - diff b/w new and malloc;
	// new is a operator while malloc is a function;
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

	// NULL is typically defined as (void *) pointer;
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


// Pointers: A pointer is a variable that holds memory address of another variable. 
// A pointer needs to be dereferenced with * operator to access the memory location it points to.

// References : A reference variable is an alias, that is, another name for an already existing variable. 
// A reference, like a pointer, is also implemented by storing the address of an object.


// Python vs C++ :-
//	C++ code needs curly brackets and semicolons to work;
// 	In python code should be properly indentated
//	Instead of using a semicolon, Python treats the end of the line as the end of the statement
//	Variables in C++ need to have a type;
//  Dynamic typing is a feature of Python, meaning that you do not need to indicate the type of the object
//	C++ code must be compiled before running
// 	In Python code is intrepreted line by line (slow)



void DELETEandNEW(){
    // 1 :- normal memory allocation; (stack)
    // no need to free this memory, it is automatically freed when program goes out of scope;
    int n;
    cin>>n;

    // 2 :- dynamic allocation of memory; (heap)
    // programmer must delete the memory manuallt using 'delete' keyword;
    // we can allocate memory of variable size;
    int *ptr1 = new int[n];
    for (int i = 0; i < n; ++i)
        ptr1[i] = i+1;
    cout<<*ptr1<<endl;
    cout<<ptr1<<endl;

    // delete operator doesn't deletes the values at the memory 
    // it just tell the program that this memory is now free to use;
    delete[] ptr1;

    // we can still access value at memory ptr1;
    cout<<ptr1<<endl;

    int *ptr2 = new int[n];
    // ptr2 will be equal to ptr1, because ptr1 memory was free to use (delete[] ptr);
    cout<<ptr2<<endl;
    cout<<*ptr2<<endl;

    int *ptr3 = new int[n];
    // ptr3 will be equal to ptr2+n, because memory from ptr to ptr+n-1 is in use and not free;
    cout<<ptr3<<endl;
    return 0;
}







