#include "cell.h"
#include "table.h"

namespace MyExcel {
	Cell::Cell(string data, int x, int y, Table* table)
		: data(data), x(x), y(y), table(table) {
	}
	string Cell::stringify() { return data; }
	int Cell::to_numeric() { return 0; }
}