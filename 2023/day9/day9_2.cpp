#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <regex>

using namespace std;

int main() {
    ifstream input_file("./day9_inputs.txt");
    
    int answer=0;
    string line;
    while(getline(input_file, line)) {
        int i=0;
        vector<vector<int>> values(1);
        string temp;
        int index_values=0;
        while (i<line.size()) {
            if (line[i]==' ') {values[index_values].push_back(stoi(temp)); temp="";}
            else temp.push_back(line[i]);
            i++;
        }
        values[index_values].push_back(stoi(temp));
        int flag_not_end=true;
        while (flag_not_end) {
            values.push_back(vector<int>(0));
            flag_not_end=false;
            for (int i=1; i<values[index_values].size(); i++) {
                values[index_values+1].push_back(values[index_values][i]-values[index_values][i-1]);
                if (values[index_values+1].back()!=0) flag_not_end=true;
            }
            index_values++;
        }

        int cur_answer=0;
        for (int i=values.size()-2; i>=0; i--) {
            cur_answer=values[i][0]-cur_answer;
        }
        answer+=cur_answer;

    }
    

    cout << "answer : " << answer << "\n";

    input_file.close();

    return 0;

}