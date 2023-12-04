#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <regex>

using namespace std;

int main() {
    ifstream input_file("./day4_inputs.txt");
    
    vector<int> count_total(1000, 0);
    int answer=0;
    string line;
    int index=0;
    while(getline(input_file, line)) {
        count_total[index]++;
        int i=8;
        string temp="";
        unordered_set<string> winning;
        bool boucle =true;
        while (i<line.size()&&boucle) {
            if (line[i]<='9'&&line[i]>='0') temp.push_back(line[i]);
            if (line[i]==' '&&temp!="") {winning.insert(temp); temp="";}
            if (line[i]=='|') boucle=false;
            i++;
        }
        temp="";
        unordered_set<string> I_have;
        while (i<line.size()) {
            if (line[i]<='9'&&line[i]>='0') temp.push_back(line[i]);
            if (line[i]==' '&&temp!="") {I_have.insert(temp); temp="";}
            i++;
        }
        if (temp!="") I_have.insert(temp);
        int count=-1;
        for (auto x:I_have) {
            if (winning.find(x)!=winning.end()) count++;
        }
        
        if (count!=-1) {
            for (int j=index+1; j<=index+count+1; j++) {
                count_total[j]+=count_total[index];
            }
        }
        index++;
    }

    for (int i=0; i<index; i++) {
        answer+=count_total[i];
    }
    cout << "answer : " << answer << "\n";

    input_file.close();

    return 0;

}