# Goal
This code was made for Exercise sheet one of the course "Debugging and Fuzzing".

# Setup
I am working on Windows 10 (shame on my), that's why the make-file is a bit weird.
I am using tcc, dunno why, started it years ago.

# Challenges
It was hard for me to write code that works and then figuring out ways to manipulate it, to get an creative error.
Errors that have been added:

* isSorted accepts descending as well as ascending sorting.
* SortArray might try to flip the last element with one outside the array
* BinarySearch possibly gets stuck and does not find the element it is looking for.

I had to modify the functions given in the exercise sheet, since giving an array to a function in C makes it a pointer, and so it's not possible to get the size of an array.
