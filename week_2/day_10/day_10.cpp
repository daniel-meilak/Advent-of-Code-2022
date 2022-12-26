#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include"utils.h"

// forward function declaration
void DrawToScreen(std::string& screen, int X, int& CRT);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" "};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    int width{40}, height{6};

    std::vector<int> history;
    std::string screen(width*height, ' ');
    int X{1}, CRT{0};

    // work through input
    for (const auto& line : input){

        // noop
        if (line[0] == "noop"){
            history.push_back(X);
            DrawToScreen(screen, X, CRT);
        }
        // addx
        else {
            history.push_back(X);
            DrawToScreen(screen, X, CRT);
            history.push_back(X);
            DrawToScreen(screen, X, CRT);
            X += std::stoi(line[1]);
        }
    }
    history.push_back(X);
    DrawToScreen(screen, X, CRT);

    // get signal strengths
    long long part1 = 20*history[19] + 60*history[59] + 100*history[99] + 140*history[139] + 180*history[179] + 220*history[219];

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << std::endl;
    display1D(screen, width, height);

    return 0;
}

void DrawToScreen(std::string& screen, int X, int& CRT){
    if ((CRT%40 >= X-1) && (CRT%40 <= X+1)){ screen[CRT] = '#'; }
    else { screen[CRT] = '.'; }
    CRT++;
}