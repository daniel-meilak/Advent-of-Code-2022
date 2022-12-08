#include<iostream>
#include<vector>
#include<string>
#include<string_view>
#include<algorithm>
#include<cstdlib>
#include<unordered_map>
#include<stack>
#include<climits>
#include"utils.h"

// data structure for a directory
struct Dir {
    
    // contained folders
    std::vector<Dir> folders;

    // map of folder name to index in folders vector
    std::unordered_map<std::string_view, std::size_t> index;

    // size of directory
    int size{0};

    // name
    std::string_view name;

    Dir* parent;

    Dir(){};
    Dir(std::string_view name, Dir* parent): name(name), parent(parent){};
};

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" ", "$"};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    // create root dir
    Dir root("root", nullptr);

    // current working directory
    Dir* working_directory = &root;

    // work through input to create directory tree
    for (const auto& line : input){

        // change directory
        if (line[0] == "cd"){

            if      (line[1] == ".."){ working_directory = working_directory->parent; }
            else if (line[1] == "/" ){ working_directory = &root;                     }
            else { working_directory = &working_directory->folders[working_directory->index[line[1]]]; }
        }
        // ls - simply move to next line
        else if (line[0] == "ls"){ continue; }
        // add sub-directory
        else if (line[0] == "dir"){

            // add directory as child of current working directory
            working_directory->folders.push_back(Dir(line[1], working_directory));

            // keep track of index of added subdirectory
            working_directory->index[line[1]] = working_directory->folders.size() - 1;
        }
        // add file size to current directory and all parents
        else {
            Dir* directory = working_directory;

            while (directory != nullptr){
                directory->size += std::stoi(line[0]);
                directory = directory->parent;
            }
        }
    }

    // work out space needed
    int space_needed = 30'000'000 - (70'000'000 - root.size);

    // find all directories of size less than or equal to 100'000
    // and best directory to delete
    std::stack<Dir*> dirs;
    dirs.push(&root);

    int part1{0}, part2{INT_MAX};

    while (!dirs.empty()){

        Dir* current = dirs.top();
        int size = current->size;
        dirs.pop();

        for (auto& dir : current->folders){ dirs.push(&dir); }

        // part 1
        if (size <= 100'000){ part1 += size; }

        // part 2
        if ((size >= space_needed) && size < part2){ part2 = size; }
    }


    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}
