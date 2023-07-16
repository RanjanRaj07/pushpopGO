#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;
constexpr auto MAX = 5;

//the stack class 
class Stack {

public:
	int stack[MAX] , top = -1;

public:
	int isStackFill() {
		if (top == MAX-1 )
			return 1;
		else
			return 0;
	} 
	int stackCount() {
		return top+1;
	}

public:
	int isUnderflow() {
		if (top == -1) 
			return 1;
		else
			return 0;
	}

	void display() {
		int i;
		if (top == -1)
			cout << "\n--!!--the stack is empty--!!--\n";
		else {
			cout << "\nelements of the stack are\n";
			for (i = top; i >= 0; i--)
				cout << stack[i] << endl;
		}
	}

public:
	void push() {
		if (top == (MAX - 1))
			cout << "\nstack over flow : \n";
		else {
			top++;
			cout << "++++++++++++++PUSH OPERATION++++++++++++++" << endl;
			cout << "item pushed - " << top << endl;
			stack[top] = top;
		}
		display();
	}

public:
	void pop() {
		int item;
		if (top == -1)
			cout << "\nstack underflow:!!\n";
		else {
			item = stack[top];
			top--;
			cout << "--------------POP OPERATION--------------" << endl;
			cout << "\n the element poped is : " << item;
		}
		display();
	}
};

#endif STACK_H