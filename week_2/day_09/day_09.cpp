#include<cstdlib>
#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include"point.h"
#include"utils.h"


// map of movements for each direction
std::unordered_map<char, point> dir = {{'U',{0,1}},{'D',{0,-1}},{'L',{-1,0}},{'R',{1,0}}};

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" "};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    // starting position of head and tails
    std::vector<point> knots(10);

    // visited positions
    std::unordered_set<point> visited1, visited2;
    visited1.insert({0,0});
    visited2.insert({0,0});

    // work through input
    for (const auto& line : input){

        int steps = std::stoi(line[1]);

        for (int i=0; i<steps; i++){
            
            // move head
            knots[0] += dir[line[0][0]];

            // work through each successive knot
            for (std::size_t i=1; i<10; i++){

                point& head = knots[i-1];
                point& tail = knots[i];

                // check distance
                int distance = chebyshev(head, tail);
                
                // move knot if needed
                if (distance == 2){
                    if      (head.x > tail.x){ tail.x++; }
                    else if (head.x < tail.x){ tail.x--; }
                    if      (head.y > tail.y){ tail.y++; }
                    else if (head.y < tail.y){ tail.y--; }
                    
                    if (i==1){ visited1.insert(tail); }
                    if (i==9){ visited2.insert(tail); }
                }
            }
        }
    }

    std::cout << "Answer (part 1): " << visited1.size() << std::endl;
    std::cout << "Answer (part 2): " << visited2.size() << std::endl;

    return 0;
}
