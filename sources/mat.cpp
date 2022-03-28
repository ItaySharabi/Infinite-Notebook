#include <string>
#include <iostream>
using namespace std;


namespace ariel{
    string create_pref(int size, char s1, char s2){ 

        if (size==1){
            string p = string(""); 
            p += s1;
            return p;
        }

        string ans = string(""); 
        int i = 0;
        char symbol = s1;

        while(i < size){

            ans += symbol;
            symbol = (symbol == s1)? s2 : s1;
            i++;

        }
        return ans;
    }

    string create_post(int size, char s1, char s2){ 
        if(size % 2 == 1) {
            return create_pref(size , s1 , s2);
        }
        return create_pref(size , s2 , s1);
    }

    string create_mid(int row, int column, int size, char s1, char s2) {
        if (column == 1) {
            return string("");
        }

        string sym = string(""); 
        string ans = string(""); 
        sym += (row % 2 == 0) ? s1 : s2;
        
        for (int j = 0; j < column - (2 * size); j++) {
            ans.append(sym);
        }

        return ans;
    }


    string mat (int column , int row , char s1 , char s2){

        /*
9 7  cols > rows
@@@@@@@@@ 0
@-------@ 1
@-@@@@@-@ 2
@-@---@-@ 3  i == "rows/2
@-@@@@@-@ 4  # reverese
@-------@ 5
@@@@@@@@@ 6
7 7
@@@@@@@
@-----@
@-@@@-@
@-@--@-@
@-@@@-@
@-----@
@@@@@@@
7 9 cols <= rows
@@@@@@@ 0
@-----@ 1
@-@@@-@ 2
@-@-@-@ 3 prefix = 4 == rows/2 && rows gt cols
@-@-@-@ 4 ???  from i = 0 to cols/2 + 1:
@-@-@-@ 5 ???       append(pref(k) + pref(n-k))
@-@@@-@ 6 # reverse
@-----@ 7 
@@@@@@@ 8
        */

    //    cout << "column: " << column << "\nrow: " << row << endl;

        if(column %2 == 0 || column < 0 || row %2 == 0 || row < 0 ){
            throw invalid_argument("Ilegal input");
        }

        string MAT = string(""); 
       

        int pref_size = 1;
        int i = 0;
        string sym;
        bool flag = false;

        while(i < row){

            MAT.append(create_pref(pref_size,s1,s2));
            if (column == 1) {
                MAT.append("\n");
                i++;
                continue;
            }
            string mid = create_mid(i, column, pref_size, s1, s2);
            MAT.append(mid);

            if(pref_size == (column/2) && row >= column){

                MAT.append(create_post(pref_size,s1,s2));
                MAT.append("\n");
                i++;
                int t = 0;

                while (t < row - 2*i) {

                    MAT.append(create_pref(pref_size, s1, s2));
                    MAT.append(create_post(pref_size+1, s1, s2));
                    MAT.append("\n");
                    t++;
                }
                i += t;
                flag = true;
                pref_size--;
                continue;
            }
            
            if (i >= row/2) {

                flag = true;
            }

            
            MAT.append(create_post(pref_size, s1, s2));
            MAT.append("\n");
            i++;
            pref_size += (flag) ? -1 : 1;
        }
        

        return MAT;
    }

    
}