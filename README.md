# Z80-Machine-Learning
A z80 processor that genetically generates code to solve a given problem

Takes (in its current version) a given input and output string and randomly adds bytes to a 64kb simulated ROM.
After executing the generated code a score is calculated as to how well this code changes the input to the output string.

The input and output strings are written (and finally checked for changes) in the high RAM.

Size of program memory and RAM can be set up individually.
