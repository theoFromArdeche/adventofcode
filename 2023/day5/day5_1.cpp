#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <regex>

using namespace std;

int main() {
    ifstream input_file("./day5_inputs.txt");
    

    unsigned long long answer=0;
    string line;
    vector<pair<unsigned long long,unsigned long long>> seeds;
    int i=7;
    string temp="";
    getline(input_file, line);
    while (i<line.size()) {
        if (line[i]==' '&&temp!="") {
            seeds.push_back(make_pair(stoull(temp), stoull(temp)));
            temp="";
        } else temp.push_back(line[i]);
        i++;
    }

    if (temp!="") seeds.push_back(make_pair(stoull(temp), stoull(temp)));
    vector<bool> selected = vector<bool>(seeds.size(), false);
    while(getline(input_file, line)) {
        if (line[0]>'9'||line[0]<'0') {
            selected = vector<bool>(seeds.size(), false);
            continue;
        }
        vector<unsigned long long> values;
        i=0;
        temp="";
        while (i<line.size()) {
            if (line[i]==' '&&temp!="") {
                values.push_back(stoull(temp));
                temp="";
            } else temp.push_back(line[i]);
            i++;
        }
        if (temp!="") values.push_back(stoull(temp));

        for (int j=0; j<seeds.size(); j++) {
            if (seeds[j].second>=values[1]&&seeds[j].second<values[1]+values[2]&&!selected[j]) {
                seeds[j].second+=values[0]-values[1];
                selected[j]=true;
            }
        }
    }
    answer=seeds[0].second;
    for (int i=0; i<seeds.size(); i++) {
        if (seeds[i].second<answer) {
            answer=seeds[i].second;
        }
    }

    cout << "answer : " << answer << "\n";

    input_file.close();

    return 0;

}