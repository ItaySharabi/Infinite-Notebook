#pragma once
#include <string>
#include "Direction.hpp"
#include <exception>
#include <map>
#include <vector>
#include <iostream>
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
    #define PRINTABLE_MIN 32
    #define PRINTABLE_MAX 126
    
    class Notebook {

        private:
            class Page {
                public:
                    map<int, vector<char>> _page;
                
                    int MAX_ROW = 0;
                    int MAX_COL = 0;
                    int MIN_ROW = INT32_MAX;
                    int MIN_COL = NOTEBOOK_LEN;
                    Page(){}
                    Page(const Page &other) {
                        cout << "copy ctor Page" << endl;
                        _page = map<int, vector<char>>(other._page);
                        MAX_ROW = other.MAX_ROW;
                        MAX_COL = other.MAX_COL;
                        MIN_ROW = other.MIN_ROW;
                        MIN_COL = other.MIN_COL;
                    }
                    ~Page() {
                        // cout << "Page dtor" << endl;
                    }
                    
            };
            // bool valid_input(const int& page, int row, int col, const Direction& dir, const int& len);
            bool page_exists(const int& page);

            void write_vertical(const int& page, int row, int col, const int &len, const string& str);
            void write_horizontal(const int& page, int row, int col, const int &len, const string& str);

            
            map<int, Page*> notebook = map<int, Page*>();
        public:
            Notebook() {
                // notebook = map<int, Page>();
            }

            Notebook(const Notebook& other) {
                cout << "Notebook copy ctor" << endl;
                notebook = map<int, Page*>(notebook);
            }
            ~Notebook();

            void write(const int &page, const int &row, const int &col, const Direction &dir, const string &str);

            string read(const int &page, const int &row, const int &col, const Direction &dir, const int &length);

            void erase(const int &page, const int &row, const int &col, const Direction &dir, const int &length);

            void show(const int &page);
    };


    // class Notebook {
    //     private:
    //         class Page {
    //             public:
    //                 map<int, vector<char>> _page;
                
    //                 int MAX_ROW = 0;
    //                 int MAX_COL = 0;
    //                 int MIN_ROW = INT32_MAX;
    //                 int MIN_COL = NOTEBOOK_LEN;
    //                 Page(){}
    //                 Page(const Page &other) {
    //                     cout << "copy ctor Page" << endl;
    //                     _page = map<int, vector<char>>(other._page);
    //                     MAX_ROW = other.MAX_ROW;
    //                     MAX_COL = other.MAX_COL;
    //                     MIN_ROW = other.MIN_ROW;
    //                     MIN_COL = other.MIN_COL;
    //                 }
    //                 ~Page() {cout << "Page dtor" << endl;}
                    
    //         };
    //         bool valid_input(const int& page, int row, int col, const Direction& dir, const int& len);
    //         Page get_page2(const int& page);
    //         bool page_exists(const int& page);

    //         void write_vertical(const int& page, int row, int col, const int &len, const string& str);
    //         void write_horizontal(const int& page, int row, int col, const int &len, const string& str);

            
    //         map<int, Page*> notebook = map<int, Page*>();
    //     public:
    //         Dog() {
    //             // notebook = map<int, Page>();
    //         }

    //         Dog(const Dog& other) {
    //             cout << "Dog copy ctor" << endl;
    //             notebook = map<int, Page*>(notebook);
    //         }
    //         ~Dog();

    //         void write2(const int &page, const int &row, const int &col, const Direction &dir, const string &str);

    //         string read2(const int &page, const int &row, const int &col, const Direction &dir, const int &length);

    //         void erase2(const int &page, const int &row, const int &col, const Direction &dir, const int &length);

    //         void show2(const int &page);
    // };

}
