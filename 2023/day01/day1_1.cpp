#include <iostream>
#include <bits/stdc++.h>
#include <fstream>


using namespace std;

int main() {
    ifstream input_file("./day1_inputs.txt");


    int answer=0;
    string line;
    while(getline(input_file, line)) {
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