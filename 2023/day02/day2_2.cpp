#include <iostream>
#include <bits/stdc++.h>
#include <fstream>


using namespace std;

int main() {
    ifstream input_file("./day2_inputs.txt");


    int answer=0;
    string line;
    int id_game=1;
    while(getline(input_file, line)) {
        int count_red=0, count_blue=0, count_green=0;
        int max_red=0, max_green=0, max_blue=0;
        string temp="";
        for (int i=7; i<line.size(); i++) {
            if (line[i]==';') {
                max_red=max(max_red, count_red); max_blue=max(max_blue, count_blue); max_green=max(max_green, count_green);
                count_red=0; count_blue=0; count_green=0;
            }
            if (line[i]<='9'&&line[i]>='0') {
                temp.push_back(line[i]);
            }
            if (line[i]=='g'&&line[i-1]==' ') {count_green+=stoi(temp); temp="";}
            if (line[i]=='b'&&line[i-1]==' ') {count_blue+=stoi(temp); temp="";}
            if (line[i]=='r'&&line[i-1]==' ') {count_red+=stoi(temp); temp="";}
            
        }
        
        max_red=max(max_red, count_red); max_blue=max(max_blue, count_blue); max_green=max(max_green, count_green);
        answer+=max_red*max_green*max_blue;
        
        id_game++;
    }
    cout << "answer : " << answer << "\n";

    input_file.close();

    return 0;

}