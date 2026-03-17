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

	MyExcel::CSVTable csvTable(5, 5);
	std::ofstream out2("test.csv");

	csvTable.reg_cell(new MyExcel::Cell("Hello~", 0, 0, &csvTable), 0, 0);
	csvTable.reg_cell(new MyExcel::Cell("C++", 0, 1, &csvTable), 0, 1);
	csvTable.reg_cell(new MyExcel::Cell("Programming", 1, 1, &csvTable), 1, 1);
	out2 << csvTable;

	MyExcel::HtmlTable htmlTable(5, 5);
	std::ofstream out3("test.html");

	htmlTable.reg_cell(new MyExcel::Cell("Hello~", 0, 0, &htmlTable), 0, 0);
	htmlTable.reg_cell(new MyExcel::Cell("C++", 0, 1, &htmlTable), 0, 1);
	htmlTable.reg_cell(new MyExcel::Cell("Programming", 1, 1, &htmlTable), 1, 1);
	out3 << htmlTable;
}