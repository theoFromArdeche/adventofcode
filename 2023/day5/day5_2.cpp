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
    bool flag=false;
    unsigned long long a;
    while (i<line.size()) {
        if (line[i]==' '&&temp!="") {
            if (flag) {
                seeds.push_back(make_pair(a, a+stoull(temp)-1));
                flag=false;
            } else {
                a=stoull(temp);
                flag=true;
            }
            temp="";
        } else temp.push_back(line[i]);
        i++;
    }

    if (temp!="") seeds.push_back(make_pair(a, a+stoull(temp)-1));
    vector<pair<unsigned long long,unsigned long long>> new_seeds;
    getline(input_file, line); getline(input_file, line);
    while(getline(input_file, line)) {
        if (line[0]>'9'||line[0]<'0') {
            if (line[0]>='a'&&line[0]<='z') {
                for (auto x:new_seeds) seeds.push_back(x);
                new_seeds=vector<pair<unsigned long long,unsigned long long>>(0);
            }
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
            if (seeds[j].first>seeds[j].second) continue;
            if (seeds[j].first<=values[1]&&seeds[j].second<=values[1]+values[2]-1&&seeds[j].second>=values[1]) {
                new_seeds.push_back(make_pair(values[0], seeds[j].second+values[0]-values[1]));
                seeds[j].second=values[1]-1;
            } else if (seeds[j].first>=values[1]&&seeds[j].first<=values[1]+values[2]-1&&seeds[j].second>=values[1]+values[2]-1) {
                new_seeds.push_back(make_pair(seeds[j].first+values[0]-values[1], values[0]+values[2]-1));
                seeds[j].first=values[1]+values[2];
            } else if (seeds[j].first<values[1]&&seeds[j].second>values[1]+values[2]-1) {
                new_seeds.push_back(make_pair(values[0], values[0]+values[2]-1));
                seeds.push_back(make_pair(values[1]+values[2], seeds[j].second));
                seeds[j].second=values[1]-1;
            } else if (seeds[j].first>values[1]&&seeds[j].second<values[1]+values[2]-1) {
                new_seeds.push_back(make_pair(seeds[j].first+values[0]-values[1], seeds[j].second+values[0]-values[1]));
                seeds[j].first=seeds[j].second+1;
            }
        }
    }
    for (auto x:new_seeds) seeds.push_back(x);
    answer=INT_MAX;
    for (int i=0; i<seeds.size(); i++) {
        if (seeds[i].first>seeds[i].second) continue;
        //if (seeds[i].first == 0) cout << seeds[i].second << "\n";
        if (seeds[i].first<answer&&seeds[i].first!=0) {
            answer=seeds[i].first;
        }
    }

    cout << "answer : " << answer << "\n";

    input_file.close();

    return 0;

}