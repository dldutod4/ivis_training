#include <iostream>
#include "Table.h"
#include "Cell.h"
std::ostream& operator<<(std::ostream& o, Table& t) {
    o << t.print_table();
    return o;
}
int main() {
    std::cout << "hello world" << std::endl;

    //Cell* cell = new Cell("temp");
    //Table* table = new Table();

   // StringCell* strCell = new StringCell();
    StringCell strCell("hello");
    NumberCell numCell("1000");
    NumberCell numCell2("2000");
    DateCell dateCell("20241125");
    ExprCell exprCell("9*9-7*8-9");
    ExprCell exprCell2("B1+B2");

    TextTable txtTable(10,10);
    txtTable.reg_cell(&strCell,0,4);
    txtTable.reg_cell(&exprCell,0,0);
    txtTable.reg_cell(&numCell,1,1);//B1
    txtTable.reg_cell(&numCell2,1,2);//B2
    txtTable.reg_cell(&dateCell,0,3);
    txtTable.reg_cell(&exprCell2,2,2);
    std::cout<<exprCell.to_numeric()<<std::endl;
    std::cout<<exprCell2.to_numeric()<<std::endl;
    std::cout << txtTable;
    return 0;
}