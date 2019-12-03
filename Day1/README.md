## Day #1

This is the first problem, and as one would expect it is very easy. We receive a .txt input file with ~100 lines, each line storing a single positive integer which is the mass of a module. We need to run the `for every x sum(floor(x / 3) - 2) ` equation and output the result. I use unsigned long longs (64-bit unsigned integer) in the solution to prevent overflows.