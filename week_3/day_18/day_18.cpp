#include<cstdlib>
#include<deque>
#include<iostream>
#include<set>
#include<string>
#include<vector>
#include"utils.h"

// lambda to return vector of neighbours
auto neighbours = [](auto v) -> std::vector<std::vector<int>>
    { return {{v[0]-1,v[1],v[2]},{v[0],v[1]-1,v[2]},{v[0],v[1],v[2]-1},{v[0],v[1],v[2]+1},{v[0],v[1]+1,v[2]},{v[0]+1,v[1],v[2]}}; };

// lambda to check if cube is in the bounds {-1,-1,-1} -> {25,25,25}
auto inBounds = [](auto v){ return v[0]>=-1 && v[1]>=-1 && v[2]>=-1 && v[0]<=25 && v[1]<=25 && v[2]<=25; };

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {","};
    std::vector<std::vector<int>> input = input_to_int_2D(read_input_2D("input", delimiters));

    // covered borders part1, internal part2
    int part1{0}, part2{0};

    // use hash to allow for quick lookup
    std::set<std::vector<int>> cubes, visited;

    // add all points to set
    for (const auto& cube : input){ cubes.insert(cube); }

    // find all covered borders
    for (const auto& cube : input){
        for (const auto& neighbour : neighbours(cube)){
            if (!cubes.contains(neighbour)){ part1++; }
        }
    }

    // BFS starting in corner
    std::deque<std::vector<int>> queue = {{-1,-1,-1}};
    while (!queue.empty()){

        std::vector<int> current = queue.back();
        queue.pop_back();

        // calculate neighbours and add to search
        for (const auto& neighbour : neighbours(current)){

            // skip neighbour if not empty or already seen.
            if (cubes.contains(neighbour) || visited.contains(neighbour)){ continue; }

            // constrain BFS to 3D area {-1,-1,-1} -> {25,25,25}
            if (inBounds(neighbour)){ queue.push_back(neighbour); }
        }

        // dont repeate step
        visited.insert(current);
    }

    // BFS cannot reach internal voids, hence add up all visited voids
    for (const auto& cube : input){
        for (const auto& neighbour : neighbours(cube)){
            if (visited.contains(neighbour)){ part2++; }
        }
    }
    
    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}
