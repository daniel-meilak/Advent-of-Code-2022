## Day 16

Unfortunately my original code was quite slow...But after having a look at the AoC reddit, I found a very interesting (and fast!) solution to the problem by [juanplopes](https://github.com/juanplopes/advent-of-code-2022/blob/main/day16.py). It uses the Floyd-Warshall algorithm to calculate the shortest distance from each node to every other node. 

After that it's essentially a DFS to explore all the routes between nodes and take the best answer. 