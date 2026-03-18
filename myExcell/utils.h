#pragma once

#include <string>
#include <ctime>
using std::string;

namespace MyExcel {
class Vector {
	string* data;
	int capacity;
	int length;
public:
	// 생성자 
	Vector(int n = 1);

	// 멘 뒤에 새 원소 추가
	void push_back(string s);

	// 임의의 위치의 원소에 접근
	string operator[](int i);

	// x 번째 원소 삭제
	void remove(int x);

	// 현재 벡터의 크기
	int size();

	// 소멸자
	~Vector();
};

class Stack {
	struct Node {
		Node* prev;
		string s;

		Node(Node* prev, string s) : prev(prev), s(s) {}
	};

	Node* current;
	Node start;
public:
	Stack();

	// 최상단에 새로운 원소 추가
	void push(string s);

	// 최상단에 원소를 제거하고 반환
	string pop();

	// 최상단 원소 반환
	string peek();
	
	// 스택 empty 여부 반환
	bool is_empty();

	// 소멸자
	~Stack();
};

class NumStack {
	struct Node {
		Node* prev;
		double s;

		Node(Node* prev, double s) : prev(prev), s(s) {}
	};

	Node* current;
	Node start;
public:
	NumStack();
	void push(double s);
	double pop();
	double peek();
	bool is_empty();

	~NumStack();
};
}
