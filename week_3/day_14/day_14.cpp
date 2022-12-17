#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<unordered_set>
#include<climits>
#include"utils.h"
#include"point.h"

// forward function declaration
bool drop_sand(std::unordered_set<point>& walls, point& sand, int fall, int& part);

// source of sand
const point source(500,0);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {"->", " ", ","};
    std::vector<std::vector<int>> input = input_to_int_2D(read_input_2D("input", delimiters));

    // wall positions
    std::unordered_set<point> walls, copy;

    // work through input to find all walls
    for (const auto& line : input){
        for (std::size_t i=3; i<line.size(); i+=2){

            // horizontal or vertical line
            if (line[i] == line[i-2]){

                int x = line[i-3];

                int n = (x - line[i-1])/std::abs((x - line[i-1]));
                while (x != line[i-1]){
                    walls.insert({x,line[i]});
                    x -= n;
                }

                walls.insert({line[i-1], line[i]});
            }
            else {

                int y = line[i-2];

                int n = (y - line[i])/std::abs((y - line[i]));
                while (y != line[i]){
                    walls.insert({line[i-1],y});
                    y -= n;
                }

                walls.insert({line[i-1],line[i]});
            }
        }
    }

    // save original walls
    copy = walls;

    // drop sand
    point sand = source;
    bool inf_drop{false};
    int part1{0};

    while (!inf_drop){
        inf_drop = drop_sand(walls, sand, 0, part1);
        sand = source;
    }  

    // reset walls
    walls = copy;

    // find floor pos
    int floor = INT_MIN;
    for (const auto& p : walls){
        if (p.y > floor){ floor = p.y; }
    }
    floor += 2;

    // add floor to walls
    for (int i=0; i<1000; i++){ walls.insert({i,floor}); }

    // drop sand
    bool reached_source{false};
    int part2{0};
    while (!reached_source){
        reached_source = drop_sand(walls, sand, 0, part2);
        sand = source;
    } 

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}

bool drop_sand(std::unordered_set<point>& walls, point& sand, int fall, int& part){

    if (fall == 1000 || walls.contains(source)){ return true; }

    bool inf_drop{false};

    // empty under
    if (!walls.contains({sand.x, sand.y+1})){
        sand += {0,1};
        inf_drop = drop_sand(walls, sand, ++fall, part);
    }
    // empty under and to the left
    else if (!walls.contains({sand.x-1, sand.y+1})){
        sand += {-1,1};
        inf_drop = drop_sand(walls, sand, ++fall, part);
    }
    // empty under and to the right
    else if (!walls.contains({sand.x+1, sand.y+1})){
        sand += {1,1};
        inf_drop = drop_sand(walls, sand, ++fall, part);
    }
    // rest position
    else {
        walls.insert(sand);
        part++;
    }

    return inf_drop;
}