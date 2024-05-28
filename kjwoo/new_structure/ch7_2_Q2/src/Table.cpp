#include "Table.h"
#include <iostream>

Table::Table(int max_row, int max_col) :max_row(max_row),max_col(max_col){
    data_base = new Cell **[max_row];
    for (int i = 0; i < max_row; i++)
    {
        data_base[i] = new Cell *[max_col];
    }
    for (int i = 0; i < max_row; i++)
    {
        for (int j = 0; j < max_col; j++)
        {
            data_base[i][j] = nullptr;
        }
    }  
}

Table::~Table() {
    for (int i = 0; i < max_row; i++)
    {
        for (int j = 0; j < max_col; j++)
        {
            if (data_base[i][j])
                delete data_base[i][j];
        }
    }
    for (int i = 0; i < max_row; i++)
    {
        delete[] data_base[i];
    }
    delete[] data_base;
}

std::string Table::print_table() {
    
    return {};
}

void Table::reg_cell(Cell* c, int row, int col) {
    c->table = this;
    c->x = col;
    c->y = row;
    // db에 등록
    data_base[row][col] = c;
    return;
}

std::string Table::get_cell_std(int row, int col) {
    if (data_base[row][col] != nullptr)
    {
        return data_base[row][col]->data;
    }
    else
    {
        return "empty";
    }
}


std::string TextTable::print_table()
{
    std::string s;
    
    //std::cout <<"print:"<<max_row<<","<<max_col<<std::endl;
    for (int i = 0; i < max_row; i++)
    {
        for (int j = 0; j < max_col; j++)
        {
            s = s + get_cell_std(i, j);
            s += ' ';
        }
        s += '\n';
    }
    return s;
}

std::string CsvTable::print_table()
{
    std::string s;

    for (int i = 0; i < max_row; i++)
    {
        for (int j = 0; j < max_col; j++)
        {
            s = s + get_cell_std(i, j);
            if (j != max_col - 1)
                s += ',';
        }
        s += '\n';
    }
    return s;
}

std::string HTMLTable::print_table()
{
    std::string s;
    s += "<table>\n";
    for (int i = 0; i < max_row; i++)
    {
        s += "    <tr>\n";
        for (int j = 0; j < max_col; j++)
        {
            s += "        <th>";
            s += get_cell_std(i, j);
            s += "</th>\n";
        }
        s += "    </tr>\n";
    }
    s += "</table>";
    return s;
}