#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<unordered_map>
#include<deque>
#include"utils.h"
#include"point.h"

static std::vector<point> neighbours = {{0,1},{0,-1},{-1,0},{1,0}};

// forward function declaration
int BFS(const std::vector<std::string>& input, const point start, point& end, const bool reverse = false);

int main(){

    // read input into vector of strings.
    std::vector<std::string> delimiters = {};
    std::vector<std::string> input = read_input("input", delimiters);

    // find start and end positions
    point start, end;

    // replace 'S' with 'a' and 'E' with 'z'
    for (std::size_t y=0; y<input.size(); y++){
        for (std::size_t x=0; x<input[0].size(); x++){

            if (input[y][x] == 'S'){
                start = {static_cast<int>(x), static_cast<int>(y)};
                input[y][x] = 'a';
            }
            else if (input[y][x] == 'E'){
                end = {static_cast<int>(x), static_cast<int>(y)};
                input[y][x] = 'z';
            }
        }
    }

    int part1 = BFS(input, start, end);
    int part2 = BFS(input, end, start, true);

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}


// Breadth first search algorithm
int BFS(const std::vector<std::string>& input, const point start, point& end, const bool reverse){
    
    int distance{0};

    // queue of positions to visit
    std::deque<point> queue;
    queue.push_back(start);

    // visited positions and next step
    std::unordered_map<point,point> came_from;

    // neighbour comparison
    bool (*comparison)(int, int);
    if (reverse){ comparison = [](int a, int b){ return a < b-1; }; }
    else { comparison = [](int a, int b){ return a > b+1; }; }

    // Breadth First Search for 'E'
    while (!queue.empty()){

        point current = queue.front();
        queue.pop_front();

        // stop if you reach end (or in reverse, any 'a')
        if ( reverse && input[current.y][current.x] == 'a'){
            end = current;
            break;
        }
        else if ( current == end){
            break;
        }

        // find all next steps
        for (const auto& neighbour : neighbours){

            point next = current + neighbour;

            // check if out of bounds
            if (next.x < 0 || next.y < 0 || next.x >= static_cast<int>(input[0].size()) || next.y >= static_cast<int>(input.size())){ continue; }

            // check if next is one step higher or less (opposite if doing reverse)
            //if ( comparison(input[next.y][next.x], input[current.y][current.x]) ){ continue; }
            if (comparison(input[next.y][next.x], input[current.y][current.x])){ continue; }

            // has position already been visited?
            if (!came_from.contains(next)){

                // if not, add to queue and map
                queue.push_back(next);
                came_from[next] = current;
            }
        }
    }

    // retrace and count steps
    point p = end;
    while (p != start){
        p = came_from[p];
        distance++;
    }

    return distance;
}