#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include"utils.h"

struct Monkey {
    int id;
    std::vector<long long> items;
    long long (*f)(long long, long long);
    bool old{false};
    int if_true, if_false, inspected{0};
    long long divisor, n;
};

// forward function declaration
long long monkeyBuisness(std::vector<Monkey> monkeys, int rounds, bool decrease_worry, long long lcm);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" ", ":", "Starting items", ","};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    // create monkey vector
    std::vector<Monkey> monkeys;

    std::size_t line{0};
    while (line < input.size()){

        Monkey monkey;

        // get monkey id
        monkey.id = std::stoi(input[line++][1]);
        
        // create list of monkeys items
        for (const auto& item : input[line++]){ monkey.items.push_back(std::stoll(item)); }

        // get number to muliply/add. If it is 'old' use -1;
        if (input[line][5] == "old"){ monkey.old = true; }
        else { monkey.n = std::stoll(input[line][5]); }

        // get operation to perform
        if (input[line++][4] == "+"){ monkey.f = [](long long a, long long b){ return a+b; }; }
        else { monkey.f = [](long long a, long long b){ return a*b; }; }

        // get the test and monkeys to pass on pass/fail
        monkey.divisor  = std::stoi(input[line++][3]);
        monkey.if_true  = std::stoi(input[line++][5]);
        monkey.if_false = std::stoi(input[line++][5]);

        // save to list of monkeys
        monkeys.push_back(std::move(monkey));

        line++;
    }

    // lcm of tests to deal with part 2
    long long lcm{1ll};
    for (const auto& monkey : monkeys){ lcm *= monkey.divisor; }

    // play keep away for x rounds
    long long part1 = monkeyBuisness(monkeys, 20, true, lcm);
    long long part2 = monkeyBuisness(monkeys, 10'000, false, lcm);

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}

long long monkeyBuisness(std::vector<Monkey> monkeys, int rounds, bool decrease_worry, long long lcm){
    
    for (int round=0; round<rounds; round++){

        // give each monkey a go
        for (auto& monkey : monkeys){

            // monkey checks each item they have
            for (auto& item : monkey.items){

                // first calculate new worry level
                if (monkey.old){ monkey.n = item; }
                item = monkey.f(item, monkey.n);

                // decrease worry level
                if (decrease_worry){ item /= 3; }
                else { item %= lcm; }

                // perform test and pass to monkey
                if ( item % monkey.divisor == 0){ monkeys[monkey.if_true].items.push_back(item); }
                else { monkeys[monkey.if_false].items.push_back(item); }

                // keep track of how many items this monkey inspected
                monkey.inspected++;
            }

            // remove all items that have been passed to other monkeys
            monkey.items.clear();
        }
    }

    // sort monkeys to find which 2 inspected the most items
    std::sort(monkeys.begin(), monkeys.end(), [](Monkey a, Monkey b){ return a.inspected > b.inspected; });

    return static_cast<long long>(monkeys[0].inspected) * static_cast<long long>(monkeys[1].inspected);
}