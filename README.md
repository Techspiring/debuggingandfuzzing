# Goal
This code was made the course "Debugging and Fuzzing".

# Setup
I am working on Windows 10 (shame on my), that's why the make-file is a bit weird.
I am using tcc, dunno why, started it years ago.

# Challenges Exercise sheet 01
It was hard for me to write code that works and then figuring out ways to manipulate it, to get an creative error.
Errors that have been added:

* isSorted accepts descending as well as ascending sorting.
* SortArray might try to flip the last element with one outside the array
* BinarySearch possibly gets stuck and does not find the element it is looking for. Yet this error can not be found by my "random" unit-tests.

I had to modify the functions given in the exercise sheet, since giving an array to a function in C makes it a pointer, and so it's not possible to get the size of an array.

This exercise sheet took me about 7 hours, since I am not used to program C outside of small Microcontrollers.
I usually do only work with fixed array sizes and I usually only call functions with pointers to custom objects, not arrays.
Quite a different experience to what I am used to when programming C. :)

Reminds me why I love my embedded stuff on tiny controllers: I can do a 100% Coverage-Test of nearly all functions within seconds. :)

# Challenges Exercise sheet 03
I was lacking time quite a bit, so I did not do too much again. :(
What I achieved took about 2 hours after trying to debug sth. else and cbmc not finishing.

It still does not finish (at least not after about 1 hr runtime), so I am somewhat clueless.

# GIT
https://github.com/Techspiring/debuggingandfuzzing