#include<array>
#include<cstdlib>
#include<deque>
#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include"utils.h"
#include"point.h"

static constexpr std::array<point,5> moves = {{{0,0}, {1,0}, {-1,0}, {0,1}, {0,-1}}};

// forward function declaration
std::vector<std::vector<std::string>> nextGrid(const std::vector<std::vector<std::string>>& grid);
int navigate(std::vector<std::vector<std::string>>& grid, point start, point end);

int main(){

    // read input into vector of strings.
    std::vector<std::string> delimiters = {};
    std::vector<std::string> input = read_input("input", delimiters);

    // create new grid with possibility of multiple blizzards on the same square
    std::vector<std::vector<std::string>> grid(input.size(), std::vector<std::string>(input[0].size()));
    for (std::size_t y=0; y<input.size(); y++){
        for (std::size_t x=0; x<input[0].size(); x++){
            grid[y][x].push_back(input[y][x]);
        }
    }

    point start(1,0), end{static_cast<int>(grid[0].size())-2, static_cast<int>(grid.size())-1};

    int part1 = navigate(grid, start, end);
    int part2 = part1 + navigate(grid, end, start) + navigate(grid, start, end);

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}

std::vector<std::vector<std::string>> nextGrid(const std::vector<std::vector<std::string>>& grid){

    std::vector<std::vector<std::string>> next(grid.size(), std::vector<std::string>(grid[0].size(), "."));

    for (int y=0; y<static_cast<int>(grid.size()); y++){
        for (int x=0; x<static_cast<int>(grid[0].size()); x++){
            for (char c : grid[y][x]){
                switch (c){
                    case '#': next[y][x][0] = c; break;
                    case '^': next[mod(y-2, static_cast<int>(grid.size())-2)+1][x].push_back(c); break;
                    case 'v': next[mod(y, static_cast<int>(grid.size())-2)+1][x].push_back(c); break;
                    case '<': next[y][mod(x-2, static_cast<int>(grid[0].size())-2)+1].push_back(c); break;
                    case '>': next[y][mod(x, static_cast<int>(grid[0].size())-2)+1].push_back(c); break;
                }
            }
        }
    }

    return next;
}

int navigate(std::vector<std::vector<std::string>>& grid, point start, point end){
    
    std::deque<std::pair<int, point>> steps = {{1, start}};
    std::unordered_map<int, std::unordered_set<point>> states;

    // keep track of steps && when blizzards must be updated
    int stage{0};

    // BFS
    while (!steps.empty()){

        point current = steps.front().second;

        // update grid if needed
        if (stage != steps.front().first){
            grid = nextGrid(grid);
            stage++;
        }
        steps.pop_front();

        // add next steps
        for (const auto& move : moves){
            point next = current + move;

            // reached exit
            if (next == end){ return stage; }

            // edge cases with starting pos
            if (next.y < 0 || next.y >= static_cast<int>(grid.size())){ continue; }

            // if next step is ".", add to queue if not already added
            if (grid[next.y][next.x] == "." && !states[stage+1].contains(next)){
                steps.push_back({stage+1, next});
                states[stage+1].insert(next);
            }
        }
    }

    return -1;
}