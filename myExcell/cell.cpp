#include "cell.h"
#include "table.h"

namespace MyExcel {
	Cell::Cell(int x, int y, Table* table)
	: x(x), y(y), table(table) {}

	// StringCell
	StringCell::StringCell(string data, int x, int y, Table* t)
		: data(data), Cell(x, y, t) {}
	
	string StringCell::stringify() { return data; }
	int StringCell::to_numeric() { return 0; }

	// NumberCell
	NumberCell::NumberCell(int data, int x, int y, Table* t)
		: data(data), Cell(x, y, t) {}
	
	string NumberCell::stringify() { return std::to_string(data); }
	int NumberCell::to_numeric() { return data; }
	
	// DataCell
	DataCell::DataCell(string s, int x, int y, Table* t) : Cell(x, y, t) {
		// 입력받는 Data형식은 항상 yyyy-mm-dd
		int year = std::stoi(s);
		int month = std::stoi(s.substr(5, 2));
		int day = std::stoi(s.substr(8, 2));
		
		tm timeinfo = {};
		
		timeinfo.tm_year = year - 1900;
		timeinfo.tm_mon = month - 1;
		timeinfo.tm_mday = day;
		timeinfo.tm_hour = 0;
		timeinfo.tm_min = 0;
		timeinfo.tm_sec = 0;
		
		data = mktime(&timeinfo);
	}
	string DataCell::stringify() {
		char buf[50];
		tm temp;
		localtime_s(&temp, &data);
		
		strftime(buf, 50, "%F", &temp);
		
		return string(buf);
	}
	int DataCell::to_numeric() { return static_cast<int>(data); }	
	
	ExprCell::ExprCell(string s, int x, int y, Table* t)
		: data(s), Cell(x, y, t) {
		parse_expression();
	}
	string ExprCell::stringify() {
		return std::to_string(to_numeric());
	}
	int ExprCell::to_numeric() {
		double result = 0;
		NumStack stack;
		
		for (int i = 0; i < exp_vec.size(); i++) {
			string s = exp_vec[i];
			
			// 셀 일 경우
			if (isalpha(s[0])) {
				stack.push(table->to_numeric(s));
			}
			// 숫자 일 경우(한 자리)
			else if (isdigit(s[0])) {
				stack.push(std::stol(s));
				// stack.push(atoi(s.c_str()));
			} else {
				double y = stack.pop();
				double x = stack.pop();
				switch (s[0]) {
					case '+':
						stack.push(x+y);
						break;
					case '-':
						stack.push(x-y);
						break;
					case '*':
						stack.push(x*y);
						break;
					case '/':
						stack.push(x/y);
						break;
				}
			}
		}
		return stack.pop();
	}
	int ExprCell::precedence(char c) {
		switch (c) {
			case '(':
			case '{':
			case '[':
				return 0;
			case '+':
			case '-':
				return 1;
			case '*':
			case '/':
				return 2;
		}
		return 0;
	}
	void ExprCell::parse_expression() {
		Stack stack;
		
		// 수식 전체를 ()로 둘러사서 exp_vec에 남아 있는 연산자들이 push되게함
		data.insert(0, "(");
		data.push_back(')');
		/*			< 중위 표기법을 후위 표기법으로 변환하는 방식 >
			1. 피연산자 (셀 이름이나 숫자) 일 경우 그냥 exp_vec 에 넣습니다.
			2. 여는 괄호( (, [, { 와 같은 것들 ) 을 만날 경우 스택에 push 합니다.
			3. 닫는 괄호( ), ], } 와 같은 것들 ) 을 만날 경우 여는 괄호가 pop 될 때 까지 pop 되는
				연산자들을 exp_vec 에 넣습니다.
			4. 연산자일 경우 자기 보다 우선순위가 낮은 연산자가 스택 최상단에 올 때 까지 (혹은 스택이
				빌 때 까지) 스택을 pop 하고 (낮은 것은 pop 하지 않습니다), pop 된 연산자들을 exp_vec
				에 넣습니다. 그리고 마지막에 자신을 스택에 push 합니다.
		 */
		for (int i = 0; i < data.length(); i++) {
			if (isalpha(data[i])) {	// 셀 이름의 경우 첫 번째 글자가 알파벳
				exp_vec.push_back(data.substr(i, 2));
				i++;
			} else if (isdigit(data[i])) {	// 첫번째 글자가 숫자라면 정수 데이터
				exp_vec.push_back(data.substr(i,1));
			} else if (data[i] == '(' || data[i] == '[' || data[i] == '{') {
				stack.push(data.substr(i,1));
			} else if (data[i] == ')' || data[i] == ']' || data[i] == '}') {
				string t = stack.pop();
				while (t != "(" && t != "[" && t != "{") {
					exp_vec.push_back(t);
					t = stack.pop();
				}
			} else if (data[i] == '+' || data[i] == '-' || data[i] == '*' || data[i] == '/') {
				while (!stack.is_empty() && precedence(stack.peek()[0]) >= precedence(data[i])) {
					 	exp_vec.push_back(stack.pop());
					} 
				stack.push(data.substr(i,1));
			}
		}
	}
}
