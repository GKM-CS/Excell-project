#pragma once

#include <ostream>
#include "utils.h"
#include "cell.h"

namespace MyExcel {
	
	class Cell;
	
	class Table {
	protected:
		// 행 및 열의 최대 크기
		int max_row_size, max_col_size;

		// 데이터를 보관하는 테이블
		// Cell* 을 보관하는 2차원 배열
		Cell*** data_table;

	public:
		Table(int max_row_size, int max_col_size);

		~Table();

		// 새로운 셀을 row행 col열에 등록
		void reg_cell(Cell* c, int row, int col);

		// 해당 셀의 정수 값을 반환
		// s : 셀 이름(Ex. A3, B6과 같이)
		int to_numeric(const string& s);

		// 행 및 열 번호로 셀을 호출
		int to_numeric(int row, int col);

		// 해당 셀의 문자열 반환
		string stringify(const string& s);
		string stringify(int row, int col);

		virtual string print_table() = 0;

		friend std::ostream& operator<<(std::ostream& o, Table& table);
	};

	class TxtTable : public Table {
		string repeat_char(int n, char c);

		// 숫자로 된 열 번호를 A, B , ... Z, AA, AB, ... 로 변환
		string col_num_to_str(int n);

	public:
		TxtTable(int row, int col);

		// 텍스트로 표를 꺠끗하게 출력
		string print_table();
	};
}