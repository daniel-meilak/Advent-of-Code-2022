#include<algorithm>
#include<climits>
#include<cstdlib>
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include"utils.h"

std::map<std::string, int> indexMap;
std::map<std::string, int> flowMap;
std::map<std::string, std::map<std::string, int>> shortestPath;

// function that performs a dfs
void visit(const std::string& room, int budget, int state, int flow, std::map<int,int>& pressure){
    pressure[state] = std::max(pressure[state], flow);

    for (const auto& [next_room, index] : indexMap){
        int newBudget = budget - shortestPath.at(room).at(next_room) - 1;

        if ( (index & state) || (newBudget <= 0) ){ continue; }

        visit(next_room, newBudget, state | index, flow + newBudget * flowMap.at(next_room), pressure);
    }
}

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {"=", ";", " ", ","};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    // create map of rooms for quick lookup
    for (int i=0; i<static_cast<int>(input.size()); i++){    

        // don't add 0 flow rooms
        int flow = std::stoi(input[i][5]);
        if (flow == 0){ continue; }

        const auto& room = input[i][1];

        indexMap[room] = 1 << indexMap.size();
        flowMap[room] = flow;
    }

    // create map of paths from all nodes to all other nodes
    for (const auto& line : input){
        
        // set connections to 1
        for (std::size_t i=10; i<line.size(); i++){ shortestPath[line[1]][line[i]] = 1; }
    
        // all other nodes to large number (not INT_MAX due to overflow)
        for (const auto& lineB : input){
            if (!shortestPath[line[1]].contains(lineB[1])){ shortestPath[line[1]][lineB[1]] = 10'000; };
        }
    }

    // find shortest paths using Floyd-Warshall
    for (auto& [k,_] : shortestPath){
        for (auto& [i,_] : shortestPath){
            for (auto& [j,_] : shortestPath){
                    shortestPath[i][j] = std::min(shortestPath[i][j], shortestPath[i][k]+shortestPath[k][j]);
            }
        }
    }

    // get max points in paths
    int part1{INT_MIN}, part2{INT_MIN};
    std::map<int, int> part1_map, part2_map;
    
    visit("AA", 30, 0, 0, part1_map);
    visit("AA", 26, 0, 0, part2_map);

    // part 1
    for (const auto& [_,value] : part1_map){ part1 = std::max(part1, value); }
    
    // part 2 
    for (const auto& [key1, value1] : part2_map){
        for (const auto& [key2, value2] : part2_map){
            if (!(key1 & key2)){ part2 = std::max(part2, value1 + value2); }
        }
    }

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}