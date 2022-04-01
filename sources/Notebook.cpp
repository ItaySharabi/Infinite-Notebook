#include "Notebook.hpp"
#include <iostream>

using namespace std;

namespace ariel {

    void print_vector(const vector<char>& vec) {

        for (uint i = 0; i < vec.size()/2; ++i) {
            cout << vec[i] << " ";
        }
        cout << "." << endl;
    }


    bool Notebook::page_exists(const int& page) {
        if (page < 0) {throw invalid_argument("Page number must be non-negative!");}
        return notebook.find(page) != notebook.end();
    }

    bool valid_input(const int& page, int row, int col, const Direction& dir, const int& len) {
        if (page < 0 || row < 0 || col < 0 || len < 0 || col >= NOTEBOOK_LEN) {
            return false;
        }

        if (Direction::Horizontal == dir) {
            if (col + len > NOTEBOOK_LEN) {
                return false;
            }
        }
        return true;
    }

    void Notebook::write_vertical(const int& page, int row, int col, const int &len, const string& str) {
        // cout << "vert" << endl;
        // cout << "row: " << row << ", " << "col: " << col << ", ln: " << len << endl;
        if (col > notebook[page]->MAX_COL) {
            notebook[page]->MAX_COL = col;
        }
        // cout << "row: " << row << ", " << "col: " << col << ", ln: " << len << endl;

        if (row + (int)str.size() >= notebook[page]->MAX_ROW) {
            notebook[page]->MAX_ROW = row + (int)str.size() - 1;
        }
        // cout << "row: " << row << ", " << "col: " << col << ", ln: " << len << endl;

        string dummy;
        int i = row;
        uint j = 0;
        while (i < len + row) {
            dummy = string("");
            // cout << "row: " << row << ", " << "col: " << col << ", ln: " << len << endl;
            // cout << "dummy + str[" << j << "] = " << (dummy + str[j]) << endl;
            write_horizontal(page, i++, col, 1, (dummy + str[j]));
            // print_vector(notebook[page]->_page[i-1]);
            if (j < str.size()-1) {
                j++;
            }
        }
    }

    void Notebook::write_horizontal(const int& page, int row, int col, const int &len, const string& str) {
        // cout << "Writing horizontally: " << endl;
        // cout << "row: " << row << ", " << "col: " << col << ", ln: " << len << endl;

        if (!page_exists(page)) {
            notebook[page] = new Page();
        }

        Page *p = notebook[page];
        // cout << "check: col + len" << endl;
        if (col + len > p->MAX_COL) {
            p->MAX_COL = col + len - 1;
        }
        // cout << "check: row" << endl;
        if (row >= p->MAX_ROW) {
            p->MAX_ROW = row;
        }

        int j = col; // column index
        int i = 0; // string index
        while (j < col + len) {
            if (p->_page[row].empty()) {
                p->_page[row] = vector<char>(NOTEBOOK_LEN, '_');
            }
            p->_page[row].at((uint)j) = str.at((uint)i);
            if (i < str.size() - 1) {
                i++;
            }
            j++;
        }
        *notebook[page] = *p;
    }
    
    void Notebook::write(const int &page, const int &row, const int &col, const Direction &dir, const string &str) {

        // for (char c : str) { if(c == '~'){throw out_of_range("You are not allowed to write `~`!  (?)");}}
        // String input check: 
        
        if (!valid_input(page, row, col, dir, str.size())) {
            throw out_of_range("Bad Input!");
        }

        for (char c : str) {
            if (c == '~') {
                throw invalid_argument("String input must not contain `~`!");
            }
            if (c < PRINTABLE_MIN || c > PRINTABLE_MAX) {
                throw invalid_argument("String input must contain printable characters!");
            }
        }
        if (!page_exists(page)) {
            notebook[page] = new Page();
        }
        
        // Direction check:
        if (Direction::Horizontal == dir) {
        for (int j = col; j < col + (int)str.size(); ++j) { 
            if (notebook[page]->_page.find(row) == notebook[page]->_page.end()) {
                notebook[page]->_page[row] = vector<char>(NOTEBOOK_LEN, '_'); // Create the line;
            }
            // Check for erased spots
            if(notebook[page]->_page.at(row).at((uint)j) != '_') {
                
                if (str.at(0) != '~' || str.size() > 1) {
                    throw out_of_range("This place is erased and cannot be over written!");
                }
            }
        }
            write_horizontal(page, row, col, (int)str.size(), str);
        }
        else {
            // Direction::Vertical
            // cout << "Vhere" << endl;
            for (int i = row; i < row + (int)str.size(); ++i) { 
                // if line did not exist - 
                if (notebook[page]->_page.find(i) == notebook[page]->_page.end()) {
                    // cout << "create line" << endl;
                    notebook[page]->_page[i] = vector<char>(NOTEBOOK_LEN, '_'); // Create the line;
                    // cout << "notebook[" << page << "].at( " << i <<  " ) = " << notebook[page]->_page.at(i).at(0) << endl;
                }

                if(notebook[page]->_page.at(i).at((uint)col) != '_') {

                    if (str.at(0) != '~' || str.size() > 1) {
                        throw out_of_range("This place is erased and cannot be over written!");
                    }
                }
            }
            write_vertical(page, row, col, (int)str.size(), str);
        }
        // Update (row, col) minimum
        notebook[page]->MIN_COL = min(col, notebook[page]->MIN_COL);
        notebook[page]->MIN_ROW = min(row, notebook[page]->MIN_ROW);
    }

    string Notebook::read(const int &page, const int &row, const int &col, const Direction &dir, const int &length) {
        // cout << "read()" << endl;
        
        if (!valid_input(page, row, col, dir, length)) {
            throw invalid_argument("Arguments must be non-negative!");
        }

        if (!page_exists(page)) {
            notebook[page] = new Page();
        }

        Page *p = notebook[page];
        if (Direction::Horizontal == dir) {
            if (p->_page.find(row) == p->_page.end()) {
                p->_page[row] = vector<char>(NOTEBOOK_LEN, '_');
            }
            string ans = string("");
            for (int j = col; j < col + length; ++j) {
                // cout << "j: " << j << ", ln: " << length << endl;

                ans += p->_page[row].at((uint)j);
            }
            return ans;
        }
        
        // Direction::Vertical
        string ans = string("");
        for (int i = row; i < row + length; ++i) {
            if (p->_page[i].empty()) {
                ans += "_";
            }
            else {
                ans += p->_page[i].at((uint)col);
            }
        }
        return ans;
    }

    void Notebook::erase(const int &page, const int &row, const int &col, const Direction &dir, const int &length) {
        // cout << "erase()" << endl;
        if (!valid_input(page, row, col, dir, length)) {
            throw invalid_argument("Arguments for erase() must be non-negative!!");
        }
        if (!page_exists(page)) {
            notebook[page] = new Page();
        }
        // cout << "create page pointer *p" << endl;
        Page *p = notebook[page];
        if (Direction::Horizontal == dir) {
            // Direction::Horizontal
            if (p->_page.find(row) == p->_page.end()) {
                // cout << "create new row" << endl;
                p->_page[row] = vector<char>(NOTEBOOK_LEN, '_');
                // cout << "after new row created" << endl;
            }
            write_horizontal(page, row, col, length, "~");
        }
        else {
            // Direction::Vertical:
            // cout << "p: " << page << ", r: " << row << ", c: " << col << "ln: " << length << endl;
            for (int i = row; i < row + length; ++i) {
                if (p->_page[i].empty()) {
                    // cout << "create new row" << endl;
                    p->_page[i] = vector<char>(NOTEBOOK_LEN, '_');
                    // print_vector(p->_page[i]);
                    // cout << "after new row created" << endl;
                }
            }
            write_vertical(page, row, col, length, "~");
        }
    }


    void Notebook::show(const int& page) {
        cout << "show()" << endl;
        Page p;
        if (!page_exists(page)) {
            cout << "Creating new Page()" << endl;
            notebook[page] = new Page();
        }
        cout << RED << "------------------ Page #" << page << " ------------------" << RESET << endl;
        p = *notebook[page];
        int MAX_ROW = p.MAX_ROW;
        int MIN_ROW = p.MIN_ROW;
        int MAX_COL = p.MAX_COL;
        int MIN_COL = p.MIN_COL;
        int count = 0;
        cout << "(" << MIN_ROW << ", " << MIN_COL << "), " << "(" << MAX_ROW << ", " << MAX_COL << ")" << endl;
        for (int i = MIN_ROW; i <= MAX_ROW; ++i) {
            if (p._page.find(i) == p._page.end() && count < 3) {
                // First 3 unused lines - print:
                cout << i << ": ." << endl;
                count++;
                continue;
            }
            if (p._page.find(i) == p._page.end() && count >= 3){
                continue; // Skip Unused lines
            }
            if (p._page.find(i) != p._page.end()) {
                // Found a line with content
                cout << i << ": ";
                count = 0;
            }
            for (int j = MIN_COL; j <= MAX_COL && j < NOTEBOOK_LEN; ++j) {
                if (p._page.find(i) != p._page.end()) {
                    cout << p._page.at(i).at((uint)j); // print cell
                }
            }
            cout << endl;
        }
        cout << endl << RED << "------------ end-show() ------------" << RESET << endl;
    }
    
    Notebook::~Notebook() {
        // cout << "Notebook dtor" << endl;
    }


    // void Notebook::write(const int &page, const int &row, const int &col, const Direction &dir, const string &str) {

    // }
    // string Notebook::read(const int &page, const int &row, const int &col, const Direction &dir, const int &length) {
    //     return "";
    // }
    // void Notebook::erase(const int &page, const int &row, const int &col, const Direction &dir, const int &length) {

    // }
    // void Notebook::show(const int &page){

        // // if (getPage())
        // // Page* PAGE = getPage(page);
        // cout << RED << "------------------ Page #" << page << " ------------------" << RESET << endl;

        // int MAX_ROW = PAGE->MAX_ROW;
        // int MIN_ROW = PAGE->MIN_ROW;
        // int MAX_COL = PAGE->MAX_COL;
        // int MIN_COL = PAGE->MIN_COL;
        // int count = 0;
        // // cout << "(" << MIN_ROW << ", " << MIN_COL << "), " << "(" << MAX_ROW << ", " << MAX_COL << ")" << endl;
        // for (int i = MIN_ROW; i <= MAX_ROW; ++i) {
        //     if (PAGE->_page.find(i) == PAGE->_page.end() && count < 3) {
        //         // First 3 unused lines - print:
        //         cout << i << ": ." << endl;
        //         count++;
        //         continue;
        //     }
        //     if (PAGE->_page.find(i) == PAGE->_page.end() && count >= 3){
        //         continue; // Skip Unused lines
        //     }
        //     if (PAGE->_page.find(i) != PAGE->_page.end()) {
        //         // Found a line with content
        //         cout << i << ": ";
        //         count = 0;
        //     }
        //     for (int j = MIN_COL; j <= MAX_COL && j < NOTEBOOK_LEN; ++j) {
        //         if (PAGE->_page.find(i) != PAGE->_page.end()) {
        //             cout << PAGE->_page.at(i).at((uint)j);
        //         }
        //     }
        //     cout << endl;
        // }
        // cout << endl << RED << "------------ end-show() ------------" << RESET << endl;
    // }
}