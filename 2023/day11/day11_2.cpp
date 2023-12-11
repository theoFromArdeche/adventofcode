#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <regex>

using namespace std;

int main() {
    ifstream input_file("./day11_inputs.txt");
    
    string line;
    vector<string> map;
    while(getline(input_file, line)) {
        map.push_back(line);
    }
    vector<pair<int,int>> coords;
    int delta=0;
    // vertically
    vector<vector<int>> coords_delta(map.size(), vector<int>(map[0].size()));
    for (int i=0; i<map.size(); i++) {
        bool flag=true;
        for (int j=0; j<map[i].size(); j++) {
            if (map[i][j]!='.') {
                flag=false;
                coords_delta[i][j]+=delta;
            }
        }
        if (flag) delta+=1e6-1;
    }

    // horizontally
    delta=0;
    for (int j=0; j<map[0].size(); j++) {
        bool flag=true;
        for (int i=0; i<map.size(); i++) {
            if (map[i][j]!='.') {
                flag=false;
                coords.push_back(make_pair(i+coords_delta[i][j], j+delta));
            }
        }
        if (flag) delta+=1e6-1;
    }

    long long answer=0;
    for (auto c1:coords) {
        for (auto c2:coords) {
            answer+=abs(c1.first-c2.first)+abs(c1.second-c2.second);
        }
    }

    cout << "answer : " << answer/2 << "\n";

    input_file.close();

    return 0;

}