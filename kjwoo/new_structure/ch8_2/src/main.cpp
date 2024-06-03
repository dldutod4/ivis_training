#include<fstream>
#include "Cell.h"
#include "Table.h"

std::ostream &operator<<(std::ostream &o, Table &table)
{
  o << table.print_table();
  return o;
}
int main()
{
    std::cout <<"?"<<std::endl;
    CsvTable tbl(5, 5);
   
}