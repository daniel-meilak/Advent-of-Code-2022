#include<cstdlib>
#include<functional>
#include<iostream>
#include<string>
#include<unordered_set>
#include<unordered_map>
#include<utility>
#include<vector>
#include"point.h"
#include"utils.h"

// defined rocks
const std::vector<std::vector<point>> rocks = {
    {{3,0}, {4,0}, {5,0}, {6,0}},
    {{4,0}, {3,1}, {4,1}, {5,1}, {4,2}},
    {{3,0}, {4,0}, {5,0}, {5,1}, {5,2}},
    {{3,0}, {3,1}, {3,2}, {3,3}},
    {{3,0}, {4,0}, {3,1}, {4,1}}
};

static constexpr long long part1Aim = 2022;
static constexpr long long part2Aim = 1'000'000'000'000; 

bool allowedMove(const std::vector<point>& rock, int LR, int down, const std::unordered_set<point>& positions){
    bool allowed{true};
    for (const auto& part : rock ){ 
        allowed &= (part.x + LR > 0) && (part.x + LR < 8) && (!positions.contains({LR+part.x,down+part.y})); }

    return allowed;
}

long long getHeight(long long aim, int current_step, int current_height, point step_and_height){
    long long remainder = (aim - current_step) % (current_step - step_and_height.x);

    if (remainder != 0){ return 0; }
    else {
        long long quotient  = (aim - current_step) / (current_step - step_and_height.x);
        return current_height + (current_height - step_and_height.y)*quotient;
    }
}

int main(){

    // read input into string.
    std::vector<std::string> delimiters = {};
    const std::string input = read_line("input", delimiters);

    // positions of all rocks (and pieces), starting with floor
    std::unordered_set<point> positions = {{1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0}};

    // next rock & movement & max height
    int ID{0}, move{0}, current_height{0};

    // state map {ID, move} -> {step, height}
    std::unordered_map<point, point> state;

    long long part1{0}, part2{0};

    // drop rocks
    for (int i=0; i<1'000'000; i++){

        // check for same state
        if (auto it = state.find({ID,move}); it != state.end()){

            if (!part1){ part1 = getHeight(part1Aim, i, current_height, it->second); }
            if (!part2){ part2 = getHeight(part2Aim, i, current_height, it->second); }

            if (part1 && part2){ break; }
        }
        else { state[{ID, move}] = {i, current_height}; }

        // select next rock
        std::vector<point> rock{rocks[ID]};

        // move rock to correct height
        for (auto& part : rock){ part.y += current_height + 4; }

        bool landed{false};

        // move rock untill it lands
        while(!landed){
            
            int LeftRight = input[move]=='<' ? -1 : 1;
            if (allowedMove(rock, LeftRight, 0, positions)){ for (auto& part : rock){ part.x += LeftRight; } };

            // move down
            if (allowedMove(rock, 0, -1, positions)){ for (auto& part : rock){ part.y += -1; } }
            else {
                for (const auto& part : rock){ positions.insert(part); }
                landed = true;
            }

            // next move
            move = (move + 1) % static_cast<int>(input.size());
        }

        // next rock
        ID   = (ID + 1) % static_cast<int>(rocks.size());

        // get current height
        current_height = std::max(current_height, rock.back().y);
    }

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}