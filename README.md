This is the repository for my Advent of Code 2019 solutions, written in C++17.
Catch is used as the unit testing framework for the solutions and it is included as a git submodule, thus you need to clone the repository using the `--recursive` switch. Once you have cloned the repository along with it's submodules you can do a full build and testing the following way:
```
mkdir Build
cd Build
cmake ..
cmake --build .
ctest
```
Every project will be built in it's own directory, meaning that the first solution's first part will be under the `Day1` folder as `Day1_Part1.exe` on Windows or as `Day1_Part1` on Linux. It is important that every executable expects an `input.txt` put directly next to it, so if you move the executable file you should also move the input file along with it. I will try and add a short explanation under every directory that describes how I solve each problem.