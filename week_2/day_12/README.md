## Day 12

Slightly too hacky a BFS algorithm but it does the trick. Really the most annoying part of todays puzzle is dealing with the starting positions being marked by upper case letters, while I'm doing `>` or `<` comparisons of each tile. 

In addition, the fact that part 1 required looking for a particular position, while part 2 required looking for a particular elevation, futher muddied the BFS exit statement.

A decent reminder of why I haven't templated a BFS or DFS algorithm into my `Utils` header. Too often I find myself creating slightly customised versions of those algorithms.