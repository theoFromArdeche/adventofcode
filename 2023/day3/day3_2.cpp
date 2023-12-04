#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <regex>

using namespace std;

int main() {
    ifstream input_file("./day3_inputs.txt");
    

    int answer=0;
    string line;
    vector<vector<char>> mat;
    while(getline(input_file, line)) {
        mat.push_back(vector<char>(0));
        for (int i=0; i<line.size(); i++) {
            mat.back().push_back(line[i]);
        }
    }
    
    for (int row=0; row<mat.size(); row++) {
        for (int column=0; column<mat[0].size(); column++) {
            if (mat[row][column]=='*') {
                int count=0, mul=1;
                for (int i=-1; i<2; i++) {
                    for (int j=-1; j<2; j++) {
                        if (row+i<0||row+i>=mat.size()||column+j<0||column+j>=mat[0].size()) continue;
                        if (mat[row+i][column+j]<='9'&&mat[row+i][column+j]>='0') {
                            int diff=0;
                            while (column+j+diff>0&&mat[row+i][column+j+diff]<='9'&&mat[row+i][column+j+diff]>='0') diff--;
                            if (mat[row+i][column+j+diff]>'9'||mat[row+i][column+j+diff]<'0') diff++;
                            string temp="";
                            while (column+j+diff<mat[0].size()&&mat[row+i][column+j+diff]<='9'&&mat[row+i][column+j+diff]>='0') {
                                temp.push_back(mat[row+i][column+j+diff]);
                                mat[row+i][column+j+diff]='.';
                                diff++;
                            }
                            mul*=stoi(temp); count++;
                        }
                    }
                }
                if (count>1) answer+=mul;
            }
        }
    }

    cout << "answer : " << answer << "\n";

    input_file.close();

    return 0;

}