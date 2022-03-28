#include <iostream>
#include "sources/Notebook.hpp"
#include "sources/mat.hpp"

using namespace std;
using namespace ariel;

#define max 999
string strings[max];
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
            strings[currIndex] = subStr;            
            currIndex += 1;
            startIndex = endIndex + 1;  
            ans[word++] = subStr;
        }
        i++;
    }
    return ans;
}  


int main(){
	Notebook notebook;

    notebook.write(/*page=*/21, /*row=*/12, /*column=*/40, Direction::Horizontal , "Advanced CPP Notebook: ");
    string s = "";

    for (int i = 0; i < 50; ++i) {

        s += "@~";
    }

    notebook.write(21, 11, 0, Direction::Horizontal, s);
    notebook.write(21, 13, 0, Direction::Horizontal, s);
    notebook.write(21, 11, 99, Direction::Vertical, "|||");
    notebook.write(21, 11, 0, Direction::Vertical, "|||");

    notebook.show(21);
    int n = 7;

    vector<string> carpet = split(mat(n, n, '$', '@'), '\n');

    for (uint i = 0; i < n; ++i) {
        notebook.write(21, 100 + 20 + i, 0, Direction::Horizontal, carpet[i]);
    }

    n = 13;
    carpet = split(mat(n, n-4, '~', '*'), '\n');
    for (uint i = 0; i < n; ++i) {
        notebook.write(21, 100 + 20 + i, 50, Direction::Horizontal, carpet[i]);
    }


    n = 11;
    carpet = split(mat(n, n, '~', '*'), '\n');
    for (uint i = 0; i < n; ++i) {
        notebook.write(21, 100 + 16 + i, 24, Direction::Horizontal, carpet[i]);
    }

    n = 25;
    carpet = split(mat(n, n, '~', '*'), '\n');
    for (uint i = 0; i < n; ++i) {
        notebook.write(21, 100 + 180 + i, 12, Direction::Horizontal, carpet[i]);
    }
    notebook.write(21, 100 + 178, 14, Direction::Horizontal, "Here's a big one, far enough...");


    notebook.show(21);
    return 0;
}

