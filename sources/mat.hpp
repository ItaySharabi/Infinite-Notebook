#pragma once
#include <string>

using namespace std;

namespace ariel{

    string mat (int col , int row , char sym1 , char sym2);
    string prefix(int size, char s1, char s2);
    string suffix(int size, char s1, char s2);
    string middle(int line, char s1, char s2);
    bool is_valid(int cols, int rows, char s1, char s2);
}
