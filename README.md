#CS-201-Hw4--Finding-Paths

This is a homework assignment given by Bilkent University in the CS 201 course.


This assignment involves assisting students in navigating a complex university building to reach their TA's office hour. The building consists of a grid of cubicles, some separated by walls, with movement allowed only horizontally or vertically, not diagonally. The task is to find all paths from an origin cubicle to a target cubicle, ensuring each cubicle is visited only once.

Objective:

Implement a system to find paths using a non-recursive exhaustive depth-first search algorithm with a stack. The stack is not implemented using standard library. Also depth-first search algortihm is not recursive, it is iterative.

Building Map Encoding:
Each cubicle is represented by a number indicating the presence of walls:
0: No walls
1: Left wall
2: Bottom wall
3: Both left and bottom walls


File Structure:

The building map file starts with the number of rows and columns, followed by lines representing each row of cubicles.
