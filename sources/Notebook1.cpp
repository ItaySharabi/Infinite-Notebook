// #include "Notebook.hpp"
// #include <iostream>

// using namespace std;

// namespace ariel {

//     // Notebook::Notebook() {
//     //     // notebook = map<int, Page*>();
//     // }

//     Notebook::~Notebook() {
//         cout << "Notebook destructor" << endl;
//         // for (auto i : notebook) {
//         //     delete i.second;
//         // }
//     }
//     // Notebook::Page::~Page() {
//     //     cout << "Page destructor" << endl;
//     // }

//     bool Notebook::valid_page_args(ariel::Notebook::Page* p, int row, int col, Direction dir, int len) {
//         // cout << row << ", " << col << ", " << len << endl;
//         cout << "valid_page_args()" << endl;
//         if (p == nullptr || row < 0 || col < 0 || len < 0 || col >= NOTEBOOK_LEN) {
//             return false;
//         }

//         if (Direction::Horizontal == dir) {
//             if (len > NOTEBOOK_LEN) {return false;}
//             if (len + col > NOTEBOOK_LEN) {return false;}
//             if (p->_page[row].empty()) {
//                 // cout << "Horiz" << endl;
//                 p->_page[row] = vector<char>(NOTEBOOK_LEN, '_'); // Create the line;
//             }


//         }
//         else {
//             // Direction::Vertical
            
//             for (int i = row; i <= row + len; ++i) {
//                 if (p->_page.find(i) == p->_page.end()) {
//                     // cout << "No row exists: vertical" << endl;
//                     p->_page[i] = vector<char>(NOTEBOOK_LEN, '_'); // Create the line;
//                 }
//             }
//         }
        
//         return true;
//     }

//     Notebook::Page *Notebook::write_horizontal(Page* p, const int &row, int col, const int &len, const string& str) {
//         cout << "write_horizontal()" << endl;

//         if (valid_page_args(p, row, col, Direction::Horizontal, str.size())) {
        
//             // if line did not exist - 
//             if (p->_page.find(row) == p->_page.end()) {
//                 p->_page[row] = vector<char>(NOTEBOOK_LEN, '_'); // Create the line;
//             }

//             for (int j = col; j < col + len; ++j) { 
//                 // Check for erased spots
//                 if(p->_page.at(row).at((uint)j) != '_') {
//                     if (str.at(0) != '~' || str.size() > 1) {
//                         throw out_of_range("This place is erased and cannot be over written!");
//                     }
//                 }
//             }

//             int j = col;
//             uint i = 0;
//             while (j < col + len) {
//                 p->_page[row].at((uint)j++) = str[i];
//                 if (i < str.size() - 1) {
//                     i++;
//                 }
//             }
//         }
//         else {
//             throw invalid_argument("What to throw?");
//         }
//         return p;
//     }

//     Notebook::Page *Notebook::write_vertical(Page* p, const int &row, int col, const int &len, const string& str) {
//         // if (row < 0 || col < 0 || len < 0 || str.size() == 0) {
//         //     throw invalid_argument("Poisitive numbers only!");
//         // }
//         cout << "write_vertical()" << endl;
        
//         if (p == NULL) {
//             return NULL;
//         }
//         if (valid_page_args(p, row, col, Direction::Vertical, str.size())) {

//             for (int i = row; i < row + len; ++i) { 
//                 // if line did not exist - 
//                 if (p->_page.find(i) == p->_page.end()) {
//                     p->_page[i] = vector<char>(NOTEBOOK_LEN, '_'); // Create the line;
//                 }

//                 // Check for erased spots
//                 else if(p->_page.at(i).at((uint)col) != '_') {
//                     if (str.at(0) != '~' || str.size() > 1) {
//                         throw out_of_range("This place is erased and cannot be over written!");
//                     }
//                 }
//             }

//             int i = row;
//             uint j = 0;
//             while (i < row + len) {
//                 p->_page[i++].at((uint)col) = str[j];
//                 if (j < str.size() - 1) {
//                     j++;
//                 }
//             }
//             return p;
//         }
//         throw invalid_argument("Line 71: IDK If i should throw");
//     }

//     void Notebook::write(const int &page, const int &row, const int &col, const Direction &dir, const string &str) {
//         cout << "write()" << endl;
//         for (char c : str) { if(c == '~'){throw out_of_range("You are not allowed to write `~`!  (?)");}}
        
//         Page *PAGE = getPage(page);
//         int MAX_ROW = PAGE->MAX_ROW;
//         int MIN_ROW = PAGE->MIN_ROW;
//         int MAX_COL = PAGE->MAX_COL;
//         int MIN_COL = PAGE->MIN_COL;
//         PAGE->MAX_ROW = max(row, MAX_ROW);
//         PAGE->MAX_COL = max(col, MAX_COL);
//         PAGE->MIN_COL = min(col, MIN_COL);
//         PAGE->MIN_ROW = min(row, MIN_ROW);

//         for (char c : str) {
//             if (c == '~') {
//                 if (str.size() > 1) {
//                     throw invalid_argument("String input must not contain `~`!");
//                 }
//             } else if (c < PRINTABLE_MIN || c > PRINTABLE_MAX) {
//                 throw invalid_argument("String input must not contain `~`!");
//             }
//         }

//         if (Direction::Horizontal == dir) {
//             // Direction::Horizontal
            
//             PAGE = write_horizontal(PAGE, row, col, str.size(), str);
//         }
//         else {
//             // Direction::Vertical:
            
//             PAGE = write_vertical(PAGE, row, col, str.size(), str);
//         }
//         if (col + (int)str.size() > PAGE->MAX_COL) {
//             PAGE->MAX_COL = col + (int)str.size();
//         }
//         if (row + (int)str.size() >= PAGE->MAX_ROW) {
//             PAGE->MAX_ROW = row + (int)str.size() - 1;
//         }
//         notebook[page] = PAGE;
//     }

//     Notebook::Page* Notebook::getPage(const int &page_num) {
//         if (page_num < 0) {
//             throw invalid_argument("Page number must be non-negative!");
//         }
//         if (notebook.find(page_num) == notebook.end()) {return new Page();}
//         return notebook.at(page_num);
//     }

//     string Notebook::read(const int &page, const int &row, const int &col, const Direction &dir, const int &length){
//         cout << "read()" << endl;

//         Page *p = getPage(page);
//         // cout << "(" << row << ", " << col << "), " << "(" << length << ")" << endl;
//         if (!valid_page_args(p, row, col, dir, length)) {
//             throw invalid_argument("Arguments must be non-negative!");
//         }
//         if (Direction::Horizontal == dir) {
//                 string ans = string("");
//                 for (int j = col; j < col + length; ++j) {
//                     ans += p->_page[row].at((uint)j);
//                 }
//                 return ans;
//             }
            
//             // Direction::Vertical
//             string ans = string("");
//             for (int i = row; i < row + length; ++i) {
//                 if (p->_page[i].empty()) {
//                     ans += "_";
//                 }
//                 else {
//                     ans += p->_page[i].at((uint)col);
//                 }
//             }
//             return ans;
//     }

//     void Notebook::erase(const int &page, const int &row, const int &col, const Direction &dir, const int &length){
//         cout << "erase()" << endl;
//         Page *p = getPage(page);
        
//         if (valid_page_args(p, row, col, dir, length)) {

//             if (Direction::Horizontal == dir) {
//                 // Direction::Horizontal

//                 p = write_horizontal(p, row, col, length, "~");
//             }
//             else {
//                 // Direction::Vertical:
//                 p = write_vertical(p, row, col, length, "~");
//             }
//             notebook[page] = p;
//         }
//         else {
//             throw invalid_argument("Arguments for erase() must be non-negative!!");
//         }
        
//     }

    // void Notebook::show(const int &page){

    //     // if (getPage())
    //     Page* PAGE = getPage(page);
    //     cout << RED << "------------------ Page #" << page << " ------------------" << RESET << endl;

    //     int MAX_ROW = PAGE->MAX_ROW;
    //     int MIN_ROW = PAGE->MIN_ROW;
    //     int MAX_COL = PAGE->MAX_COL;
    //     int MIN_COL = PAGE->MIN_COL;
    //     int count = 0;
    //     // cout << "(" << MIN_ROW << ", " << MIN_COL << "), " << "(" << MAX_ROW << ", " << MAX_COL << ")" << endl;
    //     for (int i = MIN_ROW; i <= MAX_ROW; ++i) {
    //         if (PAGE->_page.find(i) == PAGE->_page.end() && count < 3) {
    //             // First 3 unused lines - print:
    //             cout << i << ": ." << endl;
    //             count++;
    //             continue;
    //         }
    //         if (PAGE->_page.find(i) == PAGE->_page.end() && count >= 3){
    //             continue; // Skip Unused lines
    //         }
    //         if (PAGE->_page.find(i) != PAGE->_page.end()) {
    //             // Found a line with content
    //             cout << i << ": ";
    //             count = 0;
    //         }
    //         for (int j = MIN_COL; j <= MAX_COL && j < NOTEBOOK_LEN; ++j) {
    //             if (PAGE->_page.find(i) != PAGE->_page.end()) {
    //                 cout << PAGE->_page.at(i).at((uint)j);
    //             }
    //         }
    //         cout << endl;
    //     }
    //     cout << endl << RED << "------------ end-show() ------------" << RESET << endl;
    // }
// }