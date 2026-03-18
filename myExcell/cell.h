#pragma once

#include "utils.h"

namespace MyExcel {
	class Table;

	class Cell {
	protected:
		int x, y;
		Table* table;

	public:
		virtual string stringify()=0;
		virtual int to_numeric() = 0;

		Cell(int x, int y, Table* table);
	};

	class StringCell : public Cell {
		string data;
	public:
		string stringify();
		int to_numeric();

		StringCell(string data, int  x, int y, Table* t);
	};

	class NumberCell : public Cell {
		int data;

	public:
		string stringify();
		int to_numeric();

		NumberCell(int dta, int x, int y, Table* t);
	};

	class DataCell : public Cell {
		time_t data;

	public:
		string stringify();
		int to_numeric();

		DataCell(string s, int x, int y, Table* t);
	};
	
	class ExprCell : public Cell {
		string data;
		string* parsed_expr;
		// 후위 표긱법 스택에 들어갈 연산자와 피연산자 배열 
		// 3, 4, 5, *, +, 4, 7, 2, -, *, + 등	
		Vector exp_vec;	
		
		// 연산자 우선 순위를 반환
		int precedence(char c);
		
		// 수식을 분석(중위표기법 -> 후이 표기법으로 변환
		void parse_expression();
		
	public:;
		ExprCell(string s, int x, int y, Table* t);
		
		string stringify();
		int to_numeric();
	};
}