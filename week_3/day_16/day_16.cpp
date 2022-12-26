#include<climits>
#include<cstdlib>
#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
#include"utils.h"

struct Room {
    int index;

    int flow_rate;

    std::vector<std::string> connections;

    std::unordered_map<std::string, int> path;
};

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {"Valve ", " has flow rate=", "; tunnels lead to valves ", ", "};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    // create map of rooms for quick lookup
    std::unordered_map<std::string,  Room> rooms;
    for (int i=0; i<static_cast<int>(input.size()); i++){    
        
        // don't add 0 flow rooms
        int flow = std::stoi(input[i][1]);
        if (flow == 0){ continue; }

        Room r;

        r.index = 1 << i;

        r.flow_rate = std::stoi(input[i][1]);

        r.connections = std::vector<std::string>{input[i].begin()+2, input[i].end()};
        
        rooms.emplace(input[i][0], std::move(r));
    }

    // create map of paths from all nodes to all other nodes
    std::unordered_map<std::string, std::unordered_map<std::string, int>> path;
    for (const auto& line : input){
        
        // set connections to 1
        for (std::size_t i=2; i<line.size(); i++){ path[line[0]][line[i]] = 1; }
    
        // all other nodes to INT_MAX
        for (const auto& lineB : input){
            if (!path[line[0]].contains(lineB[0])){ path[line[0]][lineB[0]] = 100'000; };
        }
    }

    // find shortest paths using Floyd-Warshall
    for (auto& [k,_] : path){
        for (auto& [i,_] : path){
            for (auto& [j,_] : path){
                path[i][j] = std::min(path[i][j], path[i][k] + path[k][j]);
            }
        }
    }

    std::cout << "Answer (part 1): " << std::endl;
    std::cout << "Answer (part 2): " << std::endl;

    return 0;
}
