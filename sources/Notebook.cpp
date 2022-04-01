#include "Notebook.hpp"
#include <iostream>

using namespace std;

namespace ariel {

    /**
     * @brief A method that checks if a given page
     * already exists in our notebook.
     * Throws an error if page is negative!
     * 
     * @param page - page number
     * @return true - if page already exists.
     * @return false - otherwise.
     */
    bool Notebook::page_exists(const int& page) {
        if (page < 0) {throw invalid_argument("Page number must be non-negative!");}
        return notebook.find(page) != notebook.end();
    }

    /**
     * @brief A method which checks for negative input,
     * or any input exceeding the notebooks limits:
     * For example:
     * If writing horizontally: then it must hold that col + len <= NOTEBOOK_LEN
     * 
     * @param page 
     * @param row 
     * @param col 
     * @param dir 
     * @param len 
     * @return true - if page, row, ... are all valid
     * @return false - otherwise.
     */
    bool valid_input(const int& page, int row, int col, const Direction& dir, const int& len) {
        if (page < 0 || row < 0 || col < 0 || len < 0 || col >= NOTEBOOK_LEN) {
            return false;
        }

        if (Direction::Horizontal == dir){
            if (col + len > NOTEBOOK_LEN) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief A method which is called to perform the actual
     * Vertical writing. This method does not check given arguments
     * since it is a private method that is only called from within our class.
     * 
     * @param page 
     * @param row 
     * @param col 
     * @param len 
     * @param str - string to write in a vertical orientation
     */
    void Notebook::write_vertical(const int& page, int row, int col, const int &len, const string& str) {
        if (col > notebook[page]->MAX_COL) {
            notebook[page]->MAX_COL = col;
        }

        if (row + (int)str.size() >= notebook[page]->MAX_ROW) {
            notebook[page]->MAX_ROW = row + (int)str.size();
        }

        string dummy;
        int i = row;
        uint j = 0;
        while (i < len + row) {
            dummy = string("");
            write_horizontal(page, i++, col, 1, (dummy + str[j]));
            if (j < str.size()-1) {
                j++;
            }
        }
    }

    /**
     * @brief A method which is called to perform the actual
     * Horizontal writing. This method does not check given arguments
     * since it is a private method that is only called from within our class.
     * 
     * @param page 
     * @param row 
     * @param col 
     * @param len 
     * @param str - string to write in a horizontal orientation
     */
    void Notebook::write_horizontal(const int& page, int row, int col, const int &len, const string& str) {

        if (!page_exists(page)) {
            notebook[page] = new Page(); // Create the page if it does not exist.
        }

        Page *p = notebook[page];
        if (col + len > p->MAX_COL) {
            p->MAX_COL = col + len - 1; // update MAX_COL
        }

        if (row >= p->MAX_ROW) {
            p->MAX_ROW = row; // update MAX_ROW
        }

        int j = col; // column index
        int i = 0; // string index
        while (j < col + len) {
            if (p->_page[row].empty()) {
                // If the row was not created - create it!
                p->_page[row] = vector<char>(NOTEBOOK_LEN, '_');
            }
            p->_page[row].at((uint)j++) = str.at((uint)i); // Write to page

            if (i < str.size() - 1) {
                i++;
            }
        }
        *notebook[page] = *p; // Make notebook[page] point to this page now.
    }
    
    void Notebook::write(const int &page, const int &row, const int &col, const Direction &dir, const string &str) {
        
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
                
                if (str.at(0) == '~' && str.size() <= 1) {
                    throw out_of_range("This place is erased and cannot be over written!");
                }
                throw out_of_range("There are writings over here: `" + read(page, row, col, dir, str.size()) + "`");
            }
        }
            write_horizontal(page, row, col, (int)str.size(), str);
        }
        else {
            // Direction::Vertical
            for (int i = row; i < row + (int)str.size(); ++i) { 
                // if line did not exist:
                if (notebook[page]->_page.find(i) == notebook[page]->_page.end()) {
                    notebook[page]->_page[i] = vector<char>(NOTEBOOK_LEN, '_'); // Create the line
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
        if (!valid_input(page, row, col, dir, length)) {
            throw invalid_argument("Arguments for erase() must be non-negative!!");
        }
        if (!page_exists(page)) {
            notebook[page] = new Page();
        }

        Page *p = notebook[page];
        if (Direction::Horizontal == dir) {
            // Direction::Horizontal
            if (p->_page.find(row) == p->_page.end()) {

                p->_page[row] = vector<char>(NOTEBOOK_LEN, '_');
            }
            write_horizontal(page, row, col, length, "~");
        }
        else {
            // Direction::Vertical:
            for (int i = row; i < row + length; ++i) {
                if (p->_page[i].empty()) {
                    p->_page[i] = vector<char>(NOTEBOOK_LEN, '_');
                }
            }
            write_vertical(page, row, col, length, "~");
        }
    }


    void Notebook::show(const int& page) {
        Page p;
        if (!page_exists(page)) {
            notebook[page] = new Page();
        }
        cout << RED << "---------------------------------------------- Page #" << page 
                    << " ----------------------------------------------" << RESET << endl;
        p = *notebook[page];
        int MAX_ROW = p.MAX_ROW;
        int MIN_ROW = p.MIN_ROW;
        int MAX_COL = p.MAX_COL;
        int MIN_COL = p.MIN_COL;
        int count = 0;
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
        // cout << endl << RED << "------------ end-show() ------------" << RESET << endl;
        cout << endl << RED << "------------------------------------------- end-show(" << page 
            << ") --------------------------------------------" << RESET << endl;
    }
    
    Notebook::~Notebook() {
        // cout << "Notebook dtor" << endl;
    }
}