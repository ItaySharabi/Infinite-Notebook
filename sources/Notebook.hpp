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
                map<uint, vector<char>> _page;
            
                uint MAX_ROW = 0;
                uint MAX_COL = 0;
                uint MIN_ROW = INT8_MAX;
                uint MIN_COL = NOTEBOOK_LEN;
                ~Page();
        };
        
        map<uint, Page*> notebook;


    public:

        Notebook();
        ~Notebook();

        void write(uint page, uint row, uint col, Direction dir, string str);

        std::string read(uint page, uint row, uint col, Direction dir, uint length);

        void erase(uint page, uint row, uint col, Direction dir, uint length);

        void show(uint page);
    };

}
