#include "Notebook.hpp"
#include <iostream>

using namespace std;

namespace ariel {

    Notebook::Notebook() {
        notebook = map<int, Page*>();
    }

    Notebook::~Notebook() {
        // cout << "Notebook destructor" << endl;
        for (auto i : notebook) {
            delete i.second;
        }
    }
    Notebook::Page::~Page() {
        // cout << "Page destructor" << endl;
    }

    Notebook::Page *Notebook::write_horizontal(Page* p, const int &row, uint col, const int &len, const string& str) {
        if(p->_page[row].empty()) {
            p->_page[row] = vector<char>(NOTEBOOK_LEN, '_'); // Create the line;
        }
        uint j = col;
        for (char c : str) {
            p->_page[row].at(j++) = c;
        }
        return p;
    }

    Notebook::Page *Notebook::write_vertical(Page* p, const int &row, uint col, const int &len, const string& str) {
        int i = row;
        for (char c : str) {
            if(p->_page[i++].empty()) {
                p->_page[row] = vector<char>(NOTEBOOK_LEN, '_'); // Create the line;
            }
            p->_page[i++].at((uint)col) = c;
        }
        return p;
    }

    void Notebook::write(const int &page, const int &row, const int &col, const Direction &dir, const string &str) {
        for (char c : str) { if(c == '~'){throw out_of_range("You are not allowed to write `~`!  (?)");}}
        
        // If page does not exits - create it
        if (notebook.find(page) == notebook.end()) {
            // cout << "Did not find page " << page << endl;
            notebook[page] = new Page();
        }
        Page *PAGE = notebook[page];
        int MAX_ROW = PAGE->MAX_ROW;
        int MIN_ROW = PAGE->MIN_ROW;
        int MAX_COL = PAGE->MAX_COL;
        int MIN_COL = PAGE->MIN_COL;
        PAGE->MAX_ROW = max(row, MAX_ROW);
        PAGE->MAX_COL = max(col, MAX_COL);
        PAGE->MIN_COL = min(col, MIN_COL);
        PAGE->MIN_ROW = min(row, MIN_ROW);

        if (Direction::Horizontal == dir) {
            // Direction::Horizontal
            if ((int)str.size() + col > NOTEBOOK_LEN) {throw out_of_range("Index out of bounds!");}
            
            
            if (PAGE->_page[row].empty()) {
                PAGE->_page[row] = vector<char>(NOTEBOOK_LEN, '_'); // Create the line;
            }

            for (uint j = (uint)col; j < PAGE->MAX_COL; ++j) { 
                if(PAGE->_page.at(row).at(j) == '~'){
                    throw out_of_range("This place is erased and cannot be over written!");
                }
            }
            // Cast to int becuase implicitly converting (int + uint) = (uint) int
            if (col + (int)str.size() > MAX_COL) {
                PAGE->MAX_COL = col + (int)str.size();
            }

            PAGE = write_horizontal(PAGE, row, (uint)col, str.size(), str);
            // uint j = (uint)col;
            // for (char c : str) {
                // PAGE->_page[row].at(j++) = c;
            // }
        }
        else {
            // Direction::Vertical:
            if (row + (int)str.size() >= PAGE->MAX_ROW) {
                PAGE->MAX_ROW = row + (int)str.size() - 1;
            }

            for (int i = row; i < row + (int)str.size(); ++i) {
                if (PAGE->_page[i].empty()) {
                    PAGE->_page[i] = vector<char>(NOTEBOOK_LEN, '_'); // Create the line;
                }
            }
            int i = row;
            for (char c : str) {
                PAGE->_page[i++].at((uint)col) = c;
            }
        }
        notebook[page] = PAGE;
    }

    Notebook::Page* Notebook::getPage(const int &page_num) {
        if (notebook.find(page_num) == notebook.end()) {return NULL;}
        return notebook.at(page_num);
    }

    string Notebook::read(const int &page, const int &row, const int &col, const Direction &dir, const int &length){
        if (page < 0 || row < 0 || col < 0 || length < 1) {
            throw invalid_argument("Input parameters must be non-negative!");
        }
        Page *p = getPage(page);
        if (p == NULL) {
            // No such page exists
            p = new Page(); // Create a new Page
        }

        if (Direction::Horizontal == dir) {
            // Direction::Horizontal:
            if (col + length > NOTEBOOK_LEN) {
                throw out_of_range("Reading out of range...");
            }
            if (p->_page.find(row) == p->_page.end() /*p->_page[row].empty()*/) {
                // No such row exists
                p->_page[row] = vector<char>(NOTEBOOK_LEN, '_'); // Create the line
            }

            string ans = "";
            for (int j = col; j < col + length; ++j) {
                ans += p->_page[row].at((uint)j);
            }
            return ans;
        }
        else {
            // Direction::Vertical:
            
            if (p->_page.find(row) == p->_page.end() /*p->_page[row].empty()*/) {
                // No such row exists
                p->_page[row] = vector<char>(NOTEBOOK_LEN, '_'); // Create the line
            }

            string ans = "";
            for (int i = col; i < row + length; ++i) {
                ans += p->_page[i].at((uint)col);
            }
            return ans;
        }


        
        return "";
    }

    void Notebook::erase(const int &page, const int &row, const int &col, const Direction &dir, const int &length){

        Page *p = getPage(page);
        if (p == NULL) {
            p = new Page();
        }

        if (Direction::Horizontal == dir) {
            // Direction::Horizontal 

            p = write_horizontal(p, row, (uint)col, length, "~");
        }
        else {
            // Direction::Vertical:
            p = write_vertical(p, row, (uint)col, length, "~");
        }
        notebook[page] = p;
    }

    void Notebook::show(const int &page){

        // if (getPage())
        

        cout << RED << "------------------ Page #" << page << " ------------------" << RESET << endl;
        Page* PAGE = getPage(page);
        if (!PAGE) {
            PAGE = new Page();
        }

        if (PAGE->MIN_COL == PAGE->MAX_COL) {PAGE->MAX_COL++;}
        if (PAGE->MIN_ROW == PAGE->MAX_ROW) {PAGE->MAX_ROW++;}
        int MAX_ROW = PAGE->MAX_ROW;
        int MIN_ROW = PAGE->MIN_ROW;
        int MAX_COL = PAGE->MAX_COL;
        int MIN_COL = PAGE->MIN_COL;
        int count = 0;

        for (int i = MIN_ROW; i <= MAX_ROW; ++i) {
            if (PAGE->_page.find(i) == PAGE->_page.end() && count < 3) {
                // First 3 unused lines - print:
                cout << i << ": ." << endl;
                count++;
                continue;
            } else if (PAGE->_page.find(i) == PAGE->_page.end() && count >= 3){
                continue; // Skip Unused lines
            }
            else if (PAGE->_page.find(i) != PAGE->_page.end()) {
                // Found a line with content
                cout << i << ": ";
                count = 0;
            }
            for (int j = MIN_COL; j <= MAX_COL && j < NOTEBOOK_LEN; ++j) {
                if (PAGE->_page.find(i) != PAGE->_page.end()) {
                    cout << PAGE->_page.at(i).at((uint)j);
                }
            }
            cout << endl;
        }
        cout << endl << RED << "------------ end-show() ------------" << RESET << endl;
    }
}