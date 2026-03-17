#include "table.h"
#include "cell.h"
#include <cstdlib>
#include <algorithm>
#include <string>

namespace MyExcel {
	Table::Table(int max_row_size, int max_col_size)
		: max_row_size(max_row_size), max_col_size(max_col_size) {
		data_table = new Cell * *[max_row_size];
		for (int i = 0; i < max_row_size; i++) {
			data_table[i] = new Cell * [max_col_size];
			for (int j = 0; j < max_col_size; j++) {
				data_table[i][j] = NULL;
			}
		}
	}
	Table::~Table() {
		for (int i = 0; i < max_row_size; i++) {
			for (int j = 0; j < max_col_size; j++) {
				if (data_table[i][j]) delete data_table[i][j];
			}
		}
		for (int i = 0; i < max_row_size; i++) {
			delete[] data_table[i];
		}
		delete[] data_table;
	}
	void Table::reg_cell(Cell* c, int row, int col) {
		if (!(row < max_row_size && col < max_col_size)) return;

		if (data_table[row][col]) {
			delete data_table[row][col];
		}
		data_table[row][col] = c;
	}
	int Table::to_numeric(const string& s) {
		// Cell  이름으로 받는다.
		int row = s[0] - 'A';
		int col = atoi(s.c_str() + 1) - 1;

		if (row < max_row_size && col < max_col_size) {
			if (data_table[row][col]) {
				return data_table[row][col]->to_numeric();
			}
		}
		return 0;
	}
	int Table::to_numeric(int row, int col) {
		if (row < max_row_size && col < max_col_size && data_table[row][col]) {
			return data_table[row][col]->to_numeric();
		}
		return 0;
	}
	string Table::stringify(const string& s) {
		// Cell 이름으로 받음
		int row = s[0] - 'A';
		int col = atoi(s.c_str() + 1) - 1;

		if (row < max_row_size && col < max_col_size) {
			if (data_table[row][col]) {
				return data_table[row][col]->stringify();
			}
		}
		return "";
	}
	string Table::stringify(int row, int col) {
		if (row < max_row_size && col < max_col_size && data_table[row][col]) {
			return data_table[row][col]->stringify();
		}
		return "";
	}

	std::ostream& operator<<(std::ostream& o, Table& table) {
		o << table.print_table();
		return o;
	}

	TxtTable::TxtTable(int row, int col) : Table(row, col) {}
	// 텍스트로 표를 깨끗하게 출력
	string TxtTable::print_table() {
		string total_table;

		int* col_max_wide = new int[max_col_size];
		for (int i = 0; i < max_col_size; i++) {
			unsigned int max_wide = 2;
			for (int j = 0; j < max_row_size; j++) {
				if (data_table[j][i] && data_table[j][i]->stringify().length() > max_wide) {
					max_wide = data_table[j][i]->stringify().length();
				}
			}
			col_max_wide[i] = max_wide;
		}

		// 맨 상단에 열 정보 표시
		total_table += "   ";
		int total_wide = 4;
		for (int i = 0; i < max_col_size; i++) {
			if (col_max_wide[i]) {
				int max_len = std::max(2, col_max_wide[i]);
				total_table += " | " + col_num_to_str(i);
				total_table += repeat_char(max_len - col_num_to_str(i).length(), ' ');

				total_wide += (max_len + 3);
			}
		}

		total_table += "\n";
		// 일단 기본적으로 최대 9999번째 행까지 지원
		for (int i = 0; i < max_row_size; i++) {
			total_table += repeat_char(total_wide, '-');
			total_table += "\n" + std::to_string(i + 1);
			total_table += repeat_char(4 - std::to_string(i + 1).length(), ' ');

			for (int j = 0; j < max_col_size; j++) {
				if (col_max_wide[j]) {
					int max_len = std::max(2, col_max_wide[j]);

					string s = " ";
					if (data_table[i][j]) {
						s += data_table[i][j]->stringify();
					}
					total_table += " | " + s;
					total_table += repeat_char(max_len - s.length() + 1, ' ');
				}
			}
			total_table += "\n";
		}

		delete[] col_max_wide;
		return total_table;
	}
	string TxtTable::repeat_char(int n, char c) {
		string s = "";
		for (int i = 0; i < n; i++) s.push_back(c);

		return s;
	}
	// 숫자로 된 열 번호를 A, B , ... Z, AA, AB, ... 로 변환
	string TxtTable::col_num_to_str(int n) {
		string s = "";
		if (n < 26) {
			s.push_back('A' + n);
		}
		else {
			char first = 'A' + n / 26 - 1;
			char second = 'A' + n % 26;

			s.push_back(first);
			s.push_back(second);
		}

		return s;
	}

	HtmlTable::HtmlTable(int row, int col) : Table(row, col) {}
	string HtmlTable::print_table() {
		string s = "<table border='1' cellpadding='10'>";
		for (int i = 0; i < max_row_size; i++) {
			s += "<tr>";
			for (int j = 0; j < max_col_size; j++) {
				s += "<td>";
				if (data_table[i][j]) s += data_table[i][j]->stringify();
				s += "</td>";
			}
			s += "</tr>";
		}
		s += "</table>";
		return s;
	}

	CSVTable::CSVTable(int row, int col) : Table(row, col) {}
	string CSVTable::print_table() {
		string s = "";
		for (int i = 0; i < max_row_size; i++) {
			for (int j = 0; j < max_col_size; j++) {
				if (j >= 1) s += ",";
				// CSV 파일 규칙에 따라 문자열에 큰따옴표가 포함되어 있다면 "" 로 치환
				string temp;
				if (data_table[i][j]) temp = data_table[i][j]->stringify();

				for (int k = 0; k < temp.length(); k++) {
					if (temp[k] == '"') {
						// k 의 위치에 " 를 한 개 더 넣음
						temp.insert(k, 1, '"');

						// 이미 추가된 " 를 다시 확인하는 일이 없게 하기 위해
						// k 를 한 칸 더 이동시킨다.
						k++;
					}
				}
				temp = '"' + temp + '"';
				s += temp;
			}
			s += '\n';
		}
		return s;
	}
}