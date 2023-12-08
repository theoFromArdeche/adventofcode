#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <regex>

using namespace std;


long long gcd(long long int a, long long int b) { 
    if (b == 0) return a; 
    return gcd(b, a % b); 
} 
 
long long lcm(long long a, long long b) { 
    return (a / gcd(a, b)) * b; 
}


int main() {
    ifstream input_file("./day8_inputs.txt");
    
    string instructions="";
    getline(input_file, instructions);

    long long answer=1;
    string line;
    getline(input_file, line);
    unordered_map<string, pair<string,string>> map;
    vector<string> cur_nodes;
    while(getline(input_file, line)) {
        map[line.substr(0,3)]=make_pair(line.substr(7,3), line.substr(12,3));
        if (line[2]=='A') cur_nodes.push_back(line.substr(0,3));
    }
   
    
    for (auto start_node:cur_nodes) {
        int index=0;
        long long count=0;
        bool flag_z=true;
        string cur_node=start_node;
        while (flag_z) {
            if (instructions[index]=='L') cur_node=map[cur_node].first;
            else cur_node=map[cur_node].second;
            if (cur_node[2]=='Z') flag_z=false;    
            index++;
            count++;
            if (index==instructions.size()) index=0;
        }
        answer=lcm(answer, count);
    }

    cout << "answer : " << answer << "\n";

    input_file.close();

    return 0;

}