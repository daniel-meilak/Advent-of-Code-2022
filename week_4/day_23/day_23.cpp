#include<algorithm>
#include<array>
#include<climits>
#include<cstdlib>
#include<iostream>
#include<string>
#include<tuple>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<point.h>
#include"utils.h"

static constexpr point NW(-1,-1), N(0,-1), NE(1,-1), E(1,0), SE(1,1), S(0,1), SW(-1,1), W(-1,0);

static constexpr std::array<std::array<int,3>,4> M = {{{0,1,2},
                                                       {4,5,6},
                                                       {0,7,6},
                                                       {2,3,4}}};

static constexpr std::array<point,4> dir = {N,S,W,E};

int main(){

    // read input into vector of strings.
    std::vector<std::string> delimiters = {};
    std::vector<std::string> input = read_input("input", delimiters);

    // map of new position to elves who want to move there
    std::unordered_map<point, std::vector<point>> next;
    std::unordered_set<point> elves, copy, save;

    // read elf positions into map
    for (int y=0; y<static_cast<int>(input.size()); y++){
        for (int x=0; x<static_cast<int>(input[0].size()); x++){
            if (input[y][x] == '#'){ elves.insert({x,y}); }
        }
    }

    // perform iterations untill state stops changing
    int i{0};
    while (copy != elves){
        // save state for comparison
        copy = elves;
        
        // propose movements
        std::vector<bool> neighbours(8);
        for (const auto& elf : elves){
            
            neighbours = {elves.contains(elf+NW), elves.contains(elf+N), elves.contains(elf+NE), elves.contains(elf+E),
                          elves.contains(elf+SE), elves.contains(elf+S), elves.contains(elf+SW), elves.contains(elf+W)};

            // all true
            if ( std::ranges::all_of(neighbours, [](bool b){ return !b; }) ){ next[elf].push_back(elf); }
            // NW, N, NE
            else if (!neighbours[M[(i+0)%4][0]] && !neighbours[M[(i+0)%4][1]] && !neighbours[M[(i+0)%4][2]]){ next[elf + dir[(i+0)%4]].push_back(elf); }
            // SW, S, SE
            else if (!neighbours[M[(i+1)%4][0]] && !neighbours[M[(i+1)%4][1]] && !neighbours[M[(i+1)%4][2]]){ next[elf + dir[(i+1)%4]].push_back(elf); }
            // NW, W, SW
            else if (!neighbours[M[(i+2)%4][0]] && !neighbours[M[(i+2)%4][1]] && !neighbours[M[(i+2)%4][2]]){ next[elf + dir[(i+2)%4]].push_back(elf); }
            // NE, E, SE
            else if (!neighbours[M[(i+3)%4][0]] && !neighbours[M[(i+3)%4][1]] && !neighbours[M[(i+3)%4][2]]){ next[elf + dir[(i+3)%4]].push_back(elf); }
            // no possible moves, stay in same position
            else { next[elf].push_back(elf); }
        }
        elves.clear();

        // perform movements and deal with collisions
        for (const auto& [pos, movers] : next){
            if (movers.size() == 1){ elves.insert(pos); }
            else { for (const auto& elf : movers){ elves.insert(elf); } }
        }
        next.clear();

        // save positions on turn 10
        if (++i==10){ save = elves;}
    }

    // get size of area
    int x0{INT_MAX}, x1{INT_MIN}, y0{INT_MAX}, y1{INT_MIN};
    for (const auto& elf : save){
        x0 = std::min(x0, elf.x);
        x1 = std::max(x1, elf.x);
        y0 = std::min(y0, elf.y);
        y1 = std::max(y1, elf.y);
    }

    // area - elves
    int part1 = (1+x1-x0)*(1+y1-y0) - static_cast<int>(save.size());

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << i     << std::endl;

    return 0;
}