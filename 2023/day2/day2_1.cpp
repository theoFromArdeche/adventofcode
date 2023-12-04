#include <iostream>
#include <bits/stdc++.h>
#include <fstream>


using namespace std;

int main() {
    ifstream input_file("./day2_inputs.txt");
    int nb_red=12, nb_blue=14, nb_green=13;


    int answer=0;
    string line;
    int id_game=1;
    while(getline(input_file, line)) {
        int count_red=0, count_blue=0, count_green=0;
        string temp="";
        bool flag=false;
        for (int i=7; i<line.size(); i++) {
            if (line[i]==';') {
                if (count_green>nb_green||count_red>nb_red||count_blue>nb_blue) {flag=true; break;}
                count_red=0; count_blue=0; count_green=0;
            }
            if (line[i]<='9'&&line[i]>='0') {
                temp.push_back(line[i]);
            }
            if (line[i]=='g'&&line[i-1]==' ') {count_green+=stoi(temp); temp="";}
            if (line[i]=='b'&&line[i-1]==' ') {count_blue+=stoi(temp); temp="";}
            if (line[i]=='r'&&line[i-1]==' ') {count_red+=stoi(temp); temp="";}
            
        }
        if (!flag&&count_green<=nb_green&&count_red<=nb_red&&count_blue<=nb_blue) answer+=id_game;
        id_game++;
    }
    cout << "answer : " << answer << "\n";

    input_file.close();

    return 0;

}