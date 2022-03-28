#include "Notebook.hpp"
#include <iostream>

using namespace std;

namespace ariel {

    Notebook::Notebook() {
        notebook = map<uint, Page*>();
    }

    Notebook::~Notebook() {
        cout << "Notebook destructor" << endl;
        for (auto i : notebook) {
            delete i.second;
        }
    }
    Notebook::Page::~Page() {cout << "Page destructor" << endl;}

    void Notebook::write(uint page, uint row, uint col, Direction direction, string str){
        
        // If page does not exits - create it
        if (notebook.find(page) == notebook.end()) {
            cout << "Did not find page " << page << endl;
            notebook[page] = new Page();
        }
        Page *PAGE = notebook[page];
        uint MAX_ROW = PAGE->MAX_ROW;
        uint MIN_ROW = PAGE->MIN_ROW;
        uint MAX_COL = PAGE->MAX_COL;
        uint MIN_COL = PAGE->MIN_COL;
        PAGE->MAX_ROW = max(row, MAX_ROW);
        PAGE->MAX_COL = max(col, MAX_COL);
        PAGE->MIN_COL = min(col, MIN_COL);
        PAGE->MIN_ROW = min(row, MIN_ROW);

        int erased = 0;
        if (erased) {
            throw invalid_argument("This spot is erased! You cannot write over it!\n");
        }

        if (Direction::Horizontal == direction) {
            // Direction::Horizontal
            if (col + str.size() > NOTEBOOK_LEN) {throw out_of_range("Index out of bounds!");}
            cout << "Horizontal write()" << endl;
            
            if (col + str.size() > MAX_COL) {
                PAGE->MAX_COL = col + str.size();
            }

            if (PAGE->_page[row].empty()) {
                PAGE->_page[row] = vector<char>(NOTEBOOK_LEN, '_'); // Create the line;
            }

            uint i = col;
            for (char c : str) {
                PAGE->_page[row].at(i++) = c;
            }
        }
        else {
            // Direction::Vertical:
            cout << "Vertical write()" << endl;
            if (row + str.size() >= PAGE->MAX_ROW) {
                PAGE->MAX_ROW = row + str.size() - 1;
            }

            for (uint i = row; i < row + str.size(); ++i) {
                if (PAGE->_page[i].empty()) {
                    cout << "No Existing Line!" << endl;
                    PAGE->_page[i] = vector<char>(NOTEBOOK_LEN, '_'); // Create the line;
                }
            }

            for (char c : str) {
                PAGE->_page[row++].at(col) = c;
            }
        }

        notebook[page] = PAGE;
    }

    string Notebook::read(uint page, uint row, uint col, Direction direction, uint lenght){

        return "";
    }

    void Notebook::erase(uint page, uint row, uint col, Direction direction, uint lenght){

    }

    void Notebook::show(uint page){
        

        cout << RED << "------------------ Page #" << page << " ------------------" << RESET << endl;
        Page* PAGE = notebook[page];

        if (PAGE->MIN_COL == PAGE->MAX_COL) {PAGE->MAX_COL++;}
        if (PAGE->MIN_ROW == PAGE->MAX_ROW) {PAGE->MAX_ROW++;}
        uint MAX_ROW = PAGE->MAX_ROW;
        uint MIN_ROW = PAGE->MIN_ROW;
        uint MAX_COL = PAGE->MAX_COL;
        uint MIN_COL = PAGE->MIN_COL;
        int count = 0;

        for (uint i = MIN_ROW; i <= MAX_ROW; ++i) {
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
            for (uint j = MIN_COL; j <= MAX_COL && j < NOTEBOOK_LEN; ++j) {
                if (PAGE->_page.find(i) != PAGE->_page.end()) {
                    cout << PAGE->_page.at(i).at(j);
                }
            }
            cout << endl;
        }
        cout << endl << "------------ end-show() ------------" << endl;
    }
}