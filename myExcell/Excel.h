#pragma once

#include "utils.h"


namespace MyExcel {
	class Table;

	class Excel {
		Table* current_table;

	public:
		Excel(int max_row, int max_col, int choice);

		int parse_user_input(string s);
		void command_line();
	};
}