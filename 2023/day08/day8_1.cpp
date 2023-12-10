#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <regex>

using namespace std;



int main() {
    ifstream input_file("./day8_inputs.txt");
    
    string instructions;
    getline(input_file, instructions);

    int answer=0;
    string line;
    getline(input_file, line);
    unordered_map<string, pair<string,string>> map;
    while(getline(input_file, line)) {
        map[line.substr(0,3)]=make_pair(line.substr(7,3), line.substr(12,3));
    }
   
    string cur_node="AAA";
    int index=0;
    while (cur_node!="ZZZ") {
        if (instructions[index]=='L') cur_node=map[cur_node].first;
        else cur_node=map[cur_node].second;   
        index++; answer++;
        if (index==instructions.size()) index=0;
    }
    
    cout << "answer : " << answer << "\n";

    input_file.close();

    return 0;

}