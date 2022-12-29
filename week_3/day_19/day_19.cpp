#include<algorithm>
#include<array>
#include<cstdlib>
#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include"utils.h"

struct State {
    int minute{1};
    std::array<int, 4> robots  = {1,0,0,0};
    std::array<bool,4> allowed = {1,1,1,1};
    std::array<bool,4> waiting = {0,0,0,0};
    std::array<int, 4> money   = {0,0,0,0};

    int maxPossible(int minutes) const { return money[3] + (minutes-minute+1)*(robots[3] + (minutes-minute)/2); }

    bool canBuy (const std::array<int,3>& cost) const { return money[0]>=cost[0] && money[1]>=cost[1] && money[2]>=cost[2]; }

    void buy(const std::array<int,3>& cost){ for (std::size_t i=0; i<cost.size(); i++){ money[i] -= cost[i]; } }

    void mine(){ for (std::size_t i=0; i<money.size(); i++){ money[i] += robots[i]; } }

    void checkAllowed(const std::array<std::array<int,3>,4>& costs){
        if (robots[0] >= std::max({costs[0][0],costs[1][0],costs[2][0],costs[3][0]})){ allowed[0] = false; }
        if (robots[1] >= costs[2][1]){ allowed[1] = false; }
        if (robots[2] >= costs[3][2]){ allowed[2] = false; }
    }

    State newState() const { return State(minute+1, robots, allowed, {{0,0,0,0}}, money); }
};

// forward function declaration
int getGeodes(const std::vector<std::vector<std::string>>& input, int minutes);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" ", ":"};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);
    
    std::cout << "Answer (part 1): " << getGeodes(input, 24) << std::endl;
    std::cout << "Answer (part 2): " << getGeodes(input, 32) << std::endl;

    return 0;
}

int getGeodes(const std::vector<std::vector<std::string>>& input, int maxMinutes){
    
    int score1{0}, score2{1};

    // try each blueprint
    for (std::size_t j=0; j<(maxMinutes==24 ? input.size() : 3); j++){

        const auto& line = input[j];

        int max_geodes{0};

        // read costs
        std::array<std::array<int,3>,4> costs = {{{std::stoi(line[6 ]), 0                  , 0                  },
                                                  {std::stoi(line[12]), 0                  , 0                  },
                                                  {std::stoi(line[18]), std::stoi(line[21]), 0                  },
                                                  {std::stoi(line[27]), 0                  , std::stoi(line[30])}}};

        // depth first search
        std::stack<State> stack;
        stack.push(State());
        while (!stack.empty()){

            State current = stack.top();
            stack.pop();

            // check if final minute reached
            if (current.minute > maxMinutes){
                max_geodes = std::max(max_geodes, current.money[3]);
                continue;
            }

            // if resorce production is higher than build cost, turn off build permanently
            current.checkAllowed(costs);

            for (std::size_t i=0; i<costs.size(); i++){

                if (!current.waiting[i] && current.allowed[i] && current.canBuy(costs[i])){

                    current.waiting[i] = true;

                    State s = current.newState();

                    s.mine();
                    
                    s.buy(costs[i]);

                    s.robots[i]++;

                    stack.emplace(std::move(s));
                }
            }

            // current does not buy any robots and gets added back to queue
            current.mine();
            current.minute++;

            // if optimal production less than current max, move on
            if (current.maxPossible(maxMinutes) <= max_geodes){ continue; }

            stack.push(current);
        }

        score1 += std::stoi(line[1]) * max_geodes;
        score2 *= max_geodes;
    }

    return maxMinutes==24 ? score1 : score2;
}