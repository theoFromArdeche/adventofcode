#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <regex>

using namespace std;

unordered_set<char> top_value = {'|', '7', 'F'};
unordered_set<char> bottom_value = {'|', 'L', 'J'};
unordered_set<char> left_value = {'F', 'L', '-'};
unordered_set<char> right_value = {'7', 'J', '-'};

unordered_set<char> top_cur_value = {'|', 'L', 'J'};
unordered_set<char> bottom_cur_value = {'|', '7', 'F'};
unordered_set<char> left_cur_value = {'7', '-', 'J'};
unordered_set<char> rigth_cur_value = {'L', '-', 'F'};


void visit_graph(vector<string>& graph, pair<int,int> cur_position, int& count_outside_tiles) {
    count_outside_tiles++; graph[cur_position.first][cur_position.second]='O'; // visited
    if (cur_position.first-1>=0&&graph[cur_position.first-1][cur_position.second]!='&'&&graph[cur_position.first-1][cur_position.second]!='O') {
        visit_graph(graph, make_pair(cur_position.first-1, cur_position.second), count_outside_tiles);
    }
    if (cur_position.first+1<graph.size()&&graph[cur_position.first+1][cur_position.second]!='&'&&graph[cur_position.first+1][cur_position.second]!='O') {
        visit_graph(graph, make_pair(cur_position.first+1, cur_position.second), count_outside_tiles);
    }
    if (cur_position.second-1>=0&&graph[cur_position.first][cur_position.second-1]!='&'&&graph[cur_position.first][cur_position.second-1]!='O') {
        visit_graph(graph, make_pair(cur_position.first, cur_position.second-1), count_outside_tiles);
    }
    if (cur_position.second+1<graph[0].size()&&graph[cur_position.first][cur_position.second+1]!='&'&&graph[cur_position.first][cur_position.second+1]!='O') {
        visit_graph(graph, make_pair(cur_position.first, cur_position.second+1), count_outside_tiles);
    }
}


int main() {
    ifstream input_file("./day10_inputs.txt");
    

    string line;
    vector<string> graph;
    pair<int,int> starting_position;
    while(getline(input_file, line)) {
        graph.push_back(line);
        for (int j=0; j<line.size(); j++) {
            if (line[j]=='S') starting_position = make_pair(1+3*(graph.size()-1)+1, 1+3*j+1);
        }
    }

    vector<string> bigger_graph(graph.size()*3+2, string(graph[0].size()*3+2, '.'));
    for (int i=0; i<graph.size(); i++) {
        for (int j=0; j<graph[0].size(); j++) {
            char cur_value = graph[i][j];
            bigger_graph[1+3*i+1][1+3*j+1]=cur_value;
            if (top_cur_value.find(cur_value)!=top_cur_value.end()){
                bigger_graph[1+3*i][1+3*j+1]='|';
            }
            if (bottom_cur_value.find(cur_value)!=bottom_cur_value.end()) {
                bigger_graph[1+3*i+2][1+3*j+1]='|';
            }

            if (left_cur_value.find(cur_value)!=left_cur_value.end()) {
                bigger_graph[1+3*i+1][1+3*j]='-';
            }

            if (rigth_cur_value.find(cur_value)!=rigth_cur_value.end()) {
                bigger_graph[1+3*i+1][1+3*j+2]='-';
            }
        }
    }


    queue<pair<int,int>> cur_positions; // row, column
    bigger_graph[starting_position.first][starting_position.second]='&'; // visited
    if (bigger_graph[starting_position.first-2][starting_position.second]=='|') {
        cur_positions.push(make_pair(starting_position.first-2, starting_position.second));
        bigger_graph[starting_position.first-1][starting_position.second] = '&';
    }
    if (bigger_graph[starting_position.first+2][starting_position.second]=='|') {
        cur_positions.push(make_pair(starting_position.first+2, starting_position.second));
        bigger_graph[starting_position.first+1][starting_position.second] = '&';
    }
    if (bigger_graph[starting_position.first][starting_position.second-2]=='-') {
        cur_positions.push(make_pair(starting_position.first, starting_position.second-2));
        bigger_graph[starting_position.first][starting_position.second-1] = '&';
    }
    if (bigger_graph[starting_position.first][starting_position.second+2]=='-') {
        cur_positions.push(make_pair(starting_position.first, starting_position.second+2));
        bigger_graph[starting_position.first][starting_position.second+1] = '&';
    }
    
    
    while (!cur_positions.empty()) {
        int cur_positions_size=cur_positions.size();
        for (int i=0; i<cur_positions.size(); i++) {
            pair<int,int> cur_position=cur_positions.front(); cur_positions.pop();
            char cur_value = bigger_graph[cur_position.first][cur_position.second];
            bigger_graph[cur_position.first][cur_position.second]='&'; // visited
            
            if (top_cur_value.find(cur_value)!=top_cur_value.end()&&
                cur_position.first-1>=0&&
                top_value.find(bigger_graph[cur_position.first-1][cur_position.second])!=top_value.end()) {

                cur_positions.push(make_pair(cur_position.first-1, cur_position.second));
            }

            if (bottom_cur_value.find(cur_value)!=bottom_cur_value.end()&&
                cur_position.first+1<bigger_graph.size()&&
                bottom_value.find(bigger_graph[cur_position.first+1][cur_position.second])!=bottom_value.end()) {

                cur_positions.push(make_pair(cur_position.first+1, cur_position.second));
            }

            if (left_cur_value.find(cur_value)!=left_cur_value.end()&&
                cur_position.second-1>=0&&
                left_value.find(bigger_graph[cur_position.first][cur_position.second-1])!=left_value.end()) {

                cur_positions.push(make_pair(cur_position.first, cur_position.second-1));
            }

            if (rigth_cur_value.find(cur_value)!=rigth_cur_value.end()&&
                cur_position.second+1<bigger_graph[0].size()&&
                right_value.find(bigger_graph[cur_position.first][cur_position.second+1])!=right_value.end()) {

                cur_positions.push(make_pair(cur_position.first, cur_position.second+1));
            }
        }       
    }
    
    int count_outside_tiles=0;
    visit_graph(bigger_graph, make_pair(0, 0), count_outside_tiles);

    for (int i=1; i<bigger_graph.size()-1; i++) {
        for (int j=1; j<bigger_graph[0].size()-1; j++) {
            if (bigger_graph[i][j]=='&') {
                for (int r=-1; r<2; r++) {
                    for (int c=-1; c<2; c++) {
                        if (bigger_graph[i+r][j+c]!='&'&&bigger_graph[i+r][j+c]!='O') bigger_graph[i+r][j+c]='#';
                    }
                }
            }
        }
    }

    int count_loop_tiles=0;
    for (auto line:bigger_graph) {
        for (auto letter:line) {
            if (letter=='&'||letter=='#') count_loop_tiles++;
        }
    }

    int inside_tiles = bigger_graph.size()*bigger_graph[0].size() - count_outside_tiles - count_loop_tiles;
    

    cout << "answer : " << inside_tiles/9  << "\n";

    input_file.close();

    return 0;

}