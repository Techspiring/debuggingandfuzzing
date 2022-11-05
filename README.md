# Goal
This code was made for Exercise sheet one of the course "Debugging and Fuzzing".

# Setup
I am working on Windows 10 (shame on my), that's why the make-file is a bit weird.
I am using tcc, dunno why, started it years ago.

# Challenges
It was hard for me to write code that works and then figuring out ways to manipulate it, to get an creative error.
So I used one of the errors I did when writing the code in the BinarySearch-Function as an example error.
In my unit-Tests (using semi-random values <- big trap for young players because they are not random as one might want them to) you can not see the problem.
Can you? ;)

I had to modify the functions given in the exercise sheet, since giving an array to a function in C makes it a pointer, and so it's not possible to get the size of an array.
