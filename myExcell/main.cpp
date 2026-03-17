#include <iostream>
#include <fstream>
#include "table.h"
#include "cell.h"


int main() {
	MyExcel::TxtTable table(5, 5);
	std::ofstream out("test.txt");
	table.reg_cell(new MyExcel::Cell("Hello~", 0, 0, &table), 0, 0);
	table.reg_cell(new MyExcel::Cell("C++", 0, 1, &table), 0, 1);
	table.reg_cell(new MyExcel::Cell("Programming", 1, 1, &table), 1, 1);
	std::cout << std::endl << table;
	out << table;
}