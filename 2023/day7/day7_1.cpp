#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <regex>

using namespace std;



int main() {
    ifstream input_file("./day7_inputs.txt");


    struct comparator {
        unordered_map<char, int> mp = {{'A',13}, {'K',12}, {'Q',11}, {'J',0}, {'T',9}, {'9',8}, {'8',7}, {'7',6}, {'6',5}, {'5',4}, {'4',3}, {'3',2}, {'2',1}};
        inline bool operator() (const string& s1, const string& s2) {
            for (int i=0; i<s1.size(); i++) {
                if (s1[i]!=s2[i]) return (mp[s1[i]] > mp[s2[i]]);
            }
            return true;
        }
    };

    long answer=0;
    string line;
    vector<vector<string>> types(7);
    unordered_map<string,int> bid_map;
    int nb_hand=0;
    while(getline(input_file, line)) {
        nb_hand++;
        int i=0;
        string temp="", hand="";
        while (i<line.size()) {
            if (line[i]==' ') {hand=temp; temp="";}
            else temp.push_back(line[i]);
            i++;
        }
        bid_map[hand]=stoi(temp);
        unordered_map<char,int> count;
        int j_count=0;
        for (auto letter:hand) {
            if (letter=='J') j_count++;
            else count[letter]++;
        }
       
        vector<int> freq;
        for (auto x:count) freq.push_back(x.second);
        sort(freq.begin(), freq.end(), greater<int>());
        if (j_count==5||freq[0]+j_count==5) types[0].push_back(hand);
        else if (freq[0]+j_count==4) types[1].push_back(hand);
        else if (freq[0]+j_count==3&&freq[1]==2) types[2].push_back(hand);
        else if (freq[0]+j_count==3&&freq[1]==1) types[3].push_back(hand);
        else if (freq[0]+j_count==2&&freq[1]==2) types[4].push_back(hand);
        else if (freq[0]+j_count==2&&freq[1]==1) types[5].push_back(hand);
        else types[6].push_back(hand);
    }
    int rank=0;
    for (int i=0; i<types.size(); i++) {
        //cout << "taille : " << types[i].size() << "\n";
        sort(types[i].begin(), types[i].end(), comparator());
        for (auto hand:types[i]) {
            answer+=(nb_hand-rank)*bid_map[hand];
            //cout << hand << " " << bid_map[hand] << " " << nb_hand-rank << "\n";
            rank++;
        }
    }


    cout << "answer : " << answer << "\n";

    input_file.close();

    return 0;

}