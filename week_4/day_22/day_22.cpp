#include<cctype>
#include<cstdlib>
#include<iostream>
#include<string>
#include<utility>
#include<vector>
#include"point.h"
#include"utils.h"

#include<fstream>

// forward function declaration
int  walkPath(std::vector<std::string>& input, const std::string& movement, bool part1);
void wrap(std::vector<point>::const_iterator& facing, point& pos);

const std::vector<point> dir = {{1,0}, {0,1}, {-1,0}, {0,-1}};

int main(){

    // read input into vector of strings.
    std::vector<std::string> delimiters = {};
    std::vector<std::string> input = read_input("input", delimiters);

    // get instructions, then remove from input
    const std::string movement = input.back() + 'R';
    input.pop_back();
    input.pop_back();

    // fill in input to create rectangular grid
    std::size_t max_width{0};
    for (auto& line : input){ max_width = std::max(max_width, line.size()); }
    for (auto& line : input){ if (line.size() != max_width){ line.append(input[0].size() - line.size(), ' '); } }

    int part1 = walkPath(input, movement, true);
    int part2 = walkPath(input, movement, false);

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}

int walkPath(std::vector<std::string>& input, const std::string& movement, bool part1){

    std::size_t start{0}, end{0};
    int width  = static_cast<int>(input[0].size());
    int height = static_cast<int>(input.size());

    // starting pos and orientation
    point pos(static_cast<int>(input[0].find(".")), 0);
    auto facing = dir.begin();
    
    // work through instructions
    int distance;
    char turn;
    std::ofstream myfile ("output", std::ios::trunc);

    while (++end != movement.size()){
        
        if (std::isdigit(movement[end])){ continue; }

        // get distance and orientation
        distance = std::stoi(movement.substr(start, end-start));
        turn = movement[end];

        start = end + 1;

        // move
        for (int i=0; i<distance; i++){

            point next;
            if (part1){
                next = {mod(pos.x + facing->x, width), mod(pos.y + facing->y, height)};

                // if out of bounds (' ') keep searching for land
                while (input[next.y][next.x] == ' '){
                    next.x = mod(next.x + facing->x, width);
                    next.y = mod(next.y + facing->y, height);
                }
            }
            else {
                next = {pos.x + facing->x, pos.y + facing->y};
                
                auto it = facing;
                if (next.y<0 || next.x<0 || next.y>=height || next.x>=width || input[next.y][next.x]==' '){
                    wrap(facing, next);
                    if (input[next.y][next.x] == '#'){
                        facing = it;
                        break;
                    }
                }   
            }

            // if wall stop
            if (input[next.y][next.x] == '#'){ break; }

            // step
            pos = next;
        }

        // turn
        facing = next_cyclic(facing, turn=='R'? 1 : -1, dir);
    }

    // undo last turn
    facing = next_cyclic(facing, turn=='R'? -1 : 1, dir);
    
    return 1000*(pos.y+1) + 4*(pos.x+1) + static_cast<int>(std::distance(dir.begin(), facing));
}

// cube wrapping function
void wrap(std::vector<point>::const_iterator& facing, point& pos){
    
    int x{pos.x/50}, y{pos.y/50};
    if      (facing->x== 1 && y==0){ advance_cyclic(facing, 2, dir); pos = {      99 , 149-pos.y}; }
    else if (facing->x== 1 && y==1){ advance_cyclic(facing, 3, dir); pos = {pos.y+50 ,  49      }; }
    else if (facing->x== 1 && y==2){ advance_cyclic(facing, 2, dir); pos = {      149, 149-pos.y}; }
    else if (facing->x== 1 && y==3){ advance_cyclic(facing, 3, dir); pos = {pos.y-100, 149      }; }
    else if (facing->x==-1 && y==0){ advance_cyclic(facing, 2, dir); pos = {      0  , 149-pos.y}; }
    else if (facing->x==-1 && y==1){ advance_cyclic(facing, 3, dir); pos = {pos.y-50 , 100      }; }
    else if (facing->x==-1 && y==2){ advance_cyclic(facing, 2, dir); pos = {      50 , 149-pos.y}; }
    else if (facing->x==-1 && y==3){ advance_cyclic(facing, 3, dir); pos = {pos.y-100,  0       }; }
    else if (facing->y== 1 && x==0){ advance_cyclic(facing, 0, dir); pos = {pos.x+100,  0       }; }
    else if (facing->y== 1 && x==1){ advance_cyclic(facing, 1, dir); pos = {      49 , 100+pos.x}; }
    else if (facing->y== 1 && x==2){ advance_cyclic(facing, 1, dir); pos = {      99 , -50+pos.x}; }
    else if (facing->y==-1 && x==0){ advance_cyclic(facing, 1, dir); pos = {      50 ,  50+pos.x}; }
    else if (facing->y==-1 && x==1){ advance_cyclic(facing, 1, dir); pos = {      0  , 100+pos.x}; }
    else if (facing->y==-1 && x==2){ advance_cyclic(facing, 0, dir); pos = {pos.x-100, 199      }; }
}