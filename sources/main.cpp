#include <iostream>
#include "Notebook.hpp"
#include "mat.hpp"

using namespace std;
using namespace ariel;

#define max 999
#define MAIN_INPUT_MSG "Choose an action to perform in the notebook:\n\t1. Choose page\n\t2. Quit\nYour input: "
#define ACTION_INPUT_MSG "Which action would you like to perform?"
#define WRITE_ACTION_MSG "Write(row, col, direction, content)"
#define CARPET_ACTION_MSG "Write_Carpet(row, col, n<100, m<100)"
#define ERASE_ACTION_MSG "Erase(row, col, direction, length)"
#define SHOW_ACTION_MSG "Show(page)"


vector<string> split (const string &str, char seperator)
{
    // cout << str << endl;
    uint currIndex = 0;
    uint i = 0;  
    uint startIndex = 0;
    uint endIndex = 0;
    vector<string> ans = vector<string>(0);
    string subStr;
    uint word = 0;

    while (i <= str.size()) {
        if (str[i] == seperator || i == str.size()) {
            // cout << "found new_line" << endl;
            subStr = "";
            ans.push_back(subStr);
            endIndex = i;  
            subStr.append(str, startIndex, endIndex - startIndex);  
            // strings[currIndex] = subStr;            
            currIndex += 1;
            startIndex = endIndex + 1;  
            ans[word++] = subStr;
        }
        i++;
    }
    return ans;
}

Notebook notebook;
void start_page_menu(const int& page_num) {
    int usr_in;
    int row, col, len, dir;
    string usr_string_in = string("");
    Direction d;
    string dummy;
    while (true) {
        cout << ACTION_INPUT_MSG << endl;
        cout << "1. " << WRITE_ACTION_MSG << endl;
        cout << "2. " << CARPET_ACTION_MSG << endl;
        cout << "3. " << ERASE_ACTION_MSG << endl;
        cout << "4. " << SHOW_ACTION_MSG << endl;
        cout << "5. Quit" << endl << "Your input: ";
        cin >> usr_in;
        cout << endl;
        try {
            if (usr_in == 1) { // Write
                cout << "Horizontal = 1  |  Vertical = 2" << endl;
                cout << "Write(row="; cin >> row; 
                cout << ", col="; cin >> col; 
                cout << ", direction="; cin >> dir;
                cout << ", content="; cin >> dummy;
                getline(cin, usr_string_in);
                cout << ")" << endl;
                usr_string_in = dummy + usr_string_in;
                d = (dir == 1) ? Direction::Horizontal : Direction::Vertical;
                notebook.write(page_num, row, col, d, usr_string_in);
                cout << "Succesfully written `" << usr_string_in;
                cout << "` " << ((dir == 1) ? "(Horizontally)" : "(Vertically)") << endl << endl;
            }
            else if (usr_in == 2) { // Write Carpets
                int n, m;
                cout << "Write_Carpet(row="; cin >> row; 
                cout << ", col="; cin >> col; 
                cout << ", n="; cin >> n;
                cout << ", m="; cin >> m;
                cout << ")" << endl;
                vector<string> carpet = split(mat(n, m, '#', '*'), '\n');
                for (uint i = 0; i < n; ++i) {
                    notebook.write(page_num, row + (int)i, col, Direction::Horizontal, carpet[i]);
                }
                cout << "Succesfully drawn a " << n << "x" << m << " carpet!" << endl;
            }
            else if (usr_in == 3) { // Erase
                cout << "Horizontal = 1  |  Vertical = 2" << endl;
                cout << "Erase(row="; cin >> row; 
                cout << ", col="; cin >> col; 
                cout << ", direction="; cin >> dir;
                cout << ", length="; cin >> len;
                cout << ")" << endl;
                d = (dir == 1) ? Direction::Horizontal : Direction::Vertical;
                notebook.erase(page_num, row, col, d, len);
                cout << "Succesfully erased content";
                cout << " " << ((dir == 1) ? "(Horizontally)" : "(Vertically)") << endl << endl;
            }
            else if (usr_in == 4) { // Show
                notebook.show(page_num);
            }
            else if (usr_in == 5) {
                break;
            }
            else {
                cout << "Invalid input" << endl;
                cin >> usr_in;
            }

        } catch (const exception& e) {
            cout << "usr_in: " << usr_in << endl;
            cout << e.what() << endl;
            break;
        }
    }
}


int main(){
	// Notebook notebook;

    notebook.write(/*page=*/1, /*row=*/12, /*column=*/40, Direction::Horizontal , "Advanced CPP Notebook: ");
    string s = "";

    for (int i = 0; i < 50; ++i) {

        s += "@#";
    }

    notebook.write(1, 11, 0, Direction::Horizontal, s);
    // // notebook.show(1);
    notebook.write(1, 13, 0, Direction::Horizontal, s);
    notebook.write(1, 12, 99, Direction::Vertical, "@");
    notebook.write(1, 12, 0, Direction::Vertical, "#");

    notebook.show(1);

    int usr_in;
    char usr_in_c;
    int page, row, col, length;
    string user_string_in = string("");

    while (true) {
        cout << MAIN_INPUT_MSG;
        cin >> usr_in;
        cout << endl;

        if (usr_in == 1) {
            cout << "Page #";
            cin >> page;
            cout << endl;
            if (page < 0) {continue;}
            cout << "------------- Opened Page #" << page << " -------------" << endl;
            start_page_menu(page);
        }

        // cout << "User entered: " << usr_in << endl;
        if (usr_in == 2) {
            break;
        }
    }
    return 0;
}

