#include <iostream>
#include <fstream>

class Table;

class Cell
{
protected:
    friend Table;

    //자신이 붙어 있는 테이블
    Table* table;

    //셀이 붙어있는 위치 좌표
    int x,y;

public:
    //실제 문자열 정보
    std::string data;
    Cell(Table* T, int x, int y, const std::string str): table(T), x(x), y(y), data(str) {};
};



class Table
{
protected:
    //Cell들은 해당 base_table로 부터 뻗어져 나간다.
    Cell*** base_table;
    
    //table 행과 열의 크기를 저장
    int row_size;
    int col_size;

public:
    Table(int row, int col);
    virtual std::string print_table() = 0;
    void reg_cell(Cell* c, int row, int col);

    Table(){}

    ~Table();
};

Table::Table(int row, int col) : row_size(row), col_size(col)
{
    //Cell의 row 크기만큼 미리 할당
    base_table = new Cell**[row_size];
    
    for (size_t i = 0; i < row; i++)
    {
        //Cell의 col 크기만큼 미리 할당
        base_table[i] = new Cell*[col_size];
        for (size_t j = 0; j < col; j++)
        {
            //실제 셀들을 붙이는 말단을 미리 할당
            base_table[i][j] = NULL;
            //std::cout << base_table[i][j] << std::endl;
        }
    }
}

Table::~Table()
{
    //붙어 있는 셀들을 삭제한다
    for (size_t i = 0; i < row_size; i++)
    {
        for (size_t j = 0; j < col_size; j++)
        {
            if(base_table[i][j])delete base_table[i][j];
        }
    }

    //col 크기만큼 할당 되어있는 cell을 삭제한다.
    for (size_t i = 0; i < row_size; i++)
    {
        delete[] base_table[i];
    }

    //row크기만큼 할당되어 있는 cell을 삭제한다
    delete[] base_table;
}

void Table::reg_cell(Cell* c, int row, int col)
{
    //기존에 셀이 있다면 삭제한고 새로운 셀을 붙인다
    if(base_table[row][col])delete base_table[row][col];
    base_table[row][col] = c;
}



class TextTable : public Table
{
public:
    TextTable(int row, int col) : Table(row, col){}
    std::string print_table();
};

std::string TextTable::print_table()
{
    //각 열의 최대 문자열 길이를 찾는다.
    int* col_str_size = new int[row_size]; 
    for (size_t i = 0; i < col_size; i++)
    {
        for (size_t j = 0; j < row_size; j++)
        {
            if(base_table[j][i] == 0)continue;
            std::string str = base_table[j][i]->data;
            if(col_str_size[i]<str.length())col_str_size[i]=str.length();
        }
        //각 열의 가독성을 위해 4칸을 양옆으로 준다
        col_str_size[i] += 4;
    }

    
    std::string str, temp, out;
    // 철 취선 표시를 위한 변수
    int str_max_len = 0;

    // 첫 번째 행을 출력
    str += "    |";
    for (size_t i = 0; i < col_size; i++)
    {
        str_max_len += col_str_size[i]+2;
        temp =('A'+i);
        str += temp;
        for (size_t j = 0; j < col_str_size[i]-1; j++)
        {
            str += " ";
        }
        str += "|";
    }
    str += "\n";
    out += str;

    
    //각 행에 해당하는 정보를 순서대로 출력
    for (size_t i = 0; i < row_size; i++)
    {
        str = "";
        for (size_t i = 0; i < str_max_len; i++)
        {
            str+="-";
        }
        str += "\n";
        out += str;

        str = "    |";
        temp = std::to_string(i+1);
        str.replace(0, temp.length(), temp);

        for (size_t j = 0; j < col_size; j++)
        {
            str += "  ";
            if(col_str_size[j] != 4)
            {
                //빈 셀일 경우  공백으로 채운다
                if(base_table[i][j] == 0)
                    for (size_t k = 0; k < col_str_size[j]-4; k++)
                        str+= " ";
                
                //빈 셀이 아닐 경우 앞 공백 2개 이후부터 채운다
                else
                {
                    str+=base_table[i][j]->data;
                    for (size_t k = 0; k < col_str_size[j]-4 - base_table[i][j]->data.length(); k++)
                        str += " ";
                }
            }
            str += "  |";
        }
        str += "\n";
        out += str;
    }
    
    std::cout << out << std::endl;

    //사용이 끝난 행렬 크기 반환
    delete[] col_str_size;
    return out;
}


int main()
{
    TextTable table(5,5);
    std::ofstream textout("text.txt");

    table.reg_cell(new Cell(&table, 0, 0, "Hello"), 0, 0);
    table.reg_cell(new Cell(&table, 1, 0, "c++"), 1, 0);
    table.reg_cell(new Cell(&table, 1, 0, "Programming"), 2, 2);
    textout << table.print_table();

    return 0;
}