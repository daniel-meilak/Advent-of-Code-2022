## Day 03

For part 1 I implemented my own version of `std::set_intersection` which stops after a single intersection is found (since we know only 1 exists).

For part 2, as each sack has already been partially sorted, it would be much more efficient to implement my own (merge) sort which takes advantage of this. Due to laziness I simply used `std::sort` again and then a combination of `std::set_intersection` and my own intersection function to find each groups badge.