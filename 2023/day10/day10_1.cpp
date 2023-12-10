#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <regex>

using namespace std;





int main() {
    ifstream input_file("./day10_inputs.txt");
    

    string line;
    vector<string> graph;
    pair<int,int> starting_position;
    while(getline(input_file, line)) {
        graph.push_back(line);
        for (int i=0; i<line.size(); i++) {
            if (line[i]=='S') starting_position = make_pair(graph.size()-1, i);
        }
    }

    queue<pair<int,int>> cur_positions; // row, column
    cur_positions.push(starting_position);
    int depth=0;
    unordered_set<char> top = {'|', '7', 'F'};
    unordered_set<char> bottom = {'|', 'L', 'J'};
    unordered_set<char> left = {'F', 'L', '-'};
    unordered_set<char> rigth = {'7', 'J', '-'};

    unordered_set<char> top_cur_value = {'|', 'L', 'J', 'S'};
    unordered_set<char> bottom_cur_value = {'|', '7', 'F', 'S'};
    unordered_set<char> left_cur_value = {'7', '-', 'J', 'S'};
    unordered_set<char> rigth_cur_value = {'L', '-', 'F', 'S'};

    while (!cur_positions.empty()) {
        int cur_positions_size=cur_positions.size();
        for (int i=0; i<cur_positions.size(); i++) {
            pair<int,int> cur_position=cur_positions.front(); cur_positions.pop();
            char cur_value = graph[cur_position.first][cur_position.second];
            graph[cur_position.first][cur_position.second] = '.'; // visited
            if (top_cur_value.find(cur_value)!=top_cur_value.end()&&
                cur_position.first-1>=0&&
                top.find(graph[cur_position.first-1][cur_position.second])!=top.end()) {

                cur_positions.push(make_pair(cur_position.first-1, cur_position.second));
            }

            if (bottom_cur_value.find(cur_value)!=bottom_cur_value.end()&&
                cur_position.first+1<graph.size()&&
                bottom.find(graph[cur_position.first+1][cur_position.second])!=bottom.end()) {

                cur_positions.push(make_pair(cur_position.first+1, cur_position.second));
            }

            if (left_cur_value.find(cur_value)!=left_cur_value.end()&&
                cur_position.second-1>=0&&
                left.find(graph[cur_position.first][cur_position.second-1])!=left.end()) {

                cur_positions.push(make_pair(cur_position.first, cur_position.second-1));
            }

            if (rigth_cur_value.find(cur_value)!=rigth_cur_value.end()&&
                cur_position.second+1<graph[0].size()&&
                rigth.find(graph[cur_position.first][cur_position.second+1])!=rigth.end()) {

                cur_positions.push(make_pair(cur_position.first, cur_position.second+1));
            }
        }
        depth++;        
    }


    cout << "answer : " << depth-1 << "\n";

    input_file.close();

    return 0;

}