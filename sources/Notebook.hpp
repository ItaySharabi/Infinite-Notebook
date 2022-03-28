#pragma once
#include <string>
#include "Direction.hpp"
#include <exception>
#include <map>
#include <vector>

using namespace std;

const std::string RESET       = "\033[0m";       /* Default White*/
const std::string BLACK       = "\033[30m";      /* Black */
const std::string RED         = "\033[31m";      /* Red */
const std::string YELLOW      = "\033[33m";      /* Yellow */
const std::string BLUE        = "\033[34m";      /* Blue */
const std::string GREEN       = "\033[32m";      /* Green */
const std::string MAGENTA     = "\033[35m";      /* Magenta */
const std::string BOLDMAGENTA = "\033[1m\033[35m";      /* Bold Magenta */
const std::string BOLDCYAN    = "\033[1m\033[36m";      /* Bold Cyan */

namespace ariel {
    #define NOTEBOOK_LEN 100
    class Notebook {

    private:

        class Page {
            public:
                map<int, vector<char>> _page;
            
                int MAX_ROW = 0;
                int MAX_COL = 0;
                int MIN_ROW = INT8_MAX;
                int MIN_COL = NOTEBOOK_LEN;
                ~Page();
        };
        
        map<int, Page*> notebook;

        // Help methods:
        Page *write_horizontal(Page* page, const int &row, uint col, const int &len, const string& str);
        Page *write_vertical(Page* page, const int &row, uint col, const int &len, const string& str);

    public:
    
        Notebook();
        ~Notebook();

        void write(const int &page, const int &row, const int &col, const Direction &dir, const string &str);

        string read(const int &page, const int &row, const int &col, const Direction &dir, const int &length);

        void erase(const int &page, const int &row, const int &col, const Direction &dir, const int &length);

        void show(const int &page);

        // Help methods:
        Page *getPage(const int &page_num);
    };

}
