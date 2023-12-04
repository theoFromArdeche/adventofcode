#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <regex>

using namespace std;

int main() {
    ifstream input_file("./day1_inputs.txt");

    unordered_map<int,string> mp = {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}, {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}};


    int answer=0;
    string line;
    while(getline(input_file, line)) {
        for (int i=1; i<=9; i++) line=regex_replace(line, regex(mp[i]), mp[i]+to_string(i)+mp[i]);

        int first_int=-1, last_int;
        for (auto letter:line) {
            if (letter<'a') {
                if (first_int==-1) {first_int=letter-'0'; last_int=first_int;}
                else last_int=letter-'0';
            }
        }
        answer+=first_int*10+last_int;
    }
    cout << "answer : " << answer << "\n";

    input_file.close();

    return 0;

}