#include <iostream>
#include <fstream>
#include "table.h"
#include "cell.h"

int main() {
    /*
    MyExcel::TxtTable table(5, 5);
    std::ofstream out("test.txt");

    table.reg_cell(new MyExcel::StringCell("Hello~", 0, 0, &table), 0, 0);
    table.reg_cell(new MyExcel::StringCell("C++", 0, 1, &table), 0, 1);
    table.reg_cell(new MyExcel::StringCell("Programming", 1, 1, &table), 1, 1);
    std::cout << std::endl << table;
    out << table;

    MyExcel::CSVTable csvTable(5, 5);
    std::ofstream out2("test.csv");

    csvTable.reg_cell(new MyExcel::StringCell("Hello~", 0, 0, &csvTable), 0, 0);
    csvTable.reg_cell(new MyExcel::StringCell("C++", 0, 1, &csvTable), 0, 1);
    csvTable.reg_cell(new MyExcel::StringCell("Programming", 1, 1, &csvTable), 1, 1);
    out2 << csvTable;

    MyExcel::HtmlTable htmlTable(5, 5);
    std::ofstream out3("test.html");

    htmlTable.reg_cell(new MyExcel::StringCell("Hello~", 0, 0, &htmlTable), 0, 0);
    htmlTable.reg_cell(new MyExcel::StringCell("C++", 0, 1, &htmlTable), 0, 1);
    htmlTable.reg_cell(new MyExcel::StringCell("Programming", 1, 1, &htmlTable), 1, 1);
    out3 << htmlTable;
    */
    MyExcel::TxtTable table(5, 5);
    table.reg_cell(new MyExcel::NumberCell(2, 1, 1, &table), 1, 1);
    table.reg_cell(new MyExcel::NumberCell(3, 1, 2, &table), 1, 2);

    table.reg_cell(new MyExcel::NumberCell(4, 2, 1, &table), 2, 1);
    table.reg_cell(new MyExcel::NumberCell(5, 2, 2, &table), 2, 2);
    table.reg_cell(new MyExcel::ExprCell("B2+B3*(C2+C3-2)", 3, 3, &table), 3, 2);
    table.reg_cell(new MyExcel::StringCell("B2 + B3 * ( C2 + C3 - 2 ) = ", 3, 2, &table),
        3, 1);
    std::cout << table;

}