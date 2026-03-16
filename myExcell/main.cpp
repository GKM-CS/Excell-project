#include <iostream>
#include <string>

using std::string;

namespace MyExcel {
	class Vector {
		string* data;
		int capacity;
		int length;

	public:
		//	생성자
		Vector(int n = 1);

		// 맨 뒤에 원소를 추가
		void push_back(string s);

		// 임의의 위치의 원소에 접근
		string operator[](int i);

		// x 번째 위치한 원소를 삭제
		void remove(int x);

		// 현재 백터 크기
		int size();

		~Vector();
	};
}
