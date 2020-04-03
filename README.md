# Description

This code provides a simple algorithm for searching an exact optimal trajectory for a spherical body in the 2D domain with polygonal obstacles.

### How to use this code

This code has very few external dependencies. In fact, they all are limited by C++ STL library items, so we hope one can build it on any machine without any technical difficulties. Authors have already tested it in Unix and Windows environment. The other way to use the code is to download an executable file from master branch and use it directly.

To execute the code, one should specify two locations: wthe path to the input file and where to store the output file in the filesystem. The first argument to provide is a simple input text file, yet it should have a special formatting described below. The second file is an output file. It is always generated automatically. It can be empty as its content will be anyway replaced during the program execution.

To run the program, simply type

```sh
$ CMakeTrajectory my_directory_1/my_input_file.txt my_directory_2/my_output.txt
```

If the arguments to executable are not provided, the program will try to replace them by default values: strings "input.txt" and "output.txt". Thus, in order to use the program without any parameters, just add the file "input.txt" in the same folder with your executable.

### Input file format

Input file sample is provided in master branch. Briefly, its format is
```sh
[$Start]
x y r   # x,y-coordinates of start point, radius of the body
[$Finish]
x y     # x,y-coordinates of finish point
[$NumObstacles]
n       # number of obstacles
[$PtsObstacles]
n1      # number of vertices of the first obstacle
x1 y1   # coordinates of the boundary vertices in counter-clockwise order
...
n2      # number of vertices of the second obstacle
x2 y2
...
```
We are sorry, but in this version of the code inline comments are not supported. They were added for the sake of detailed explanation.

### Output file format

Output file is generated automatically. The first part of the output is simply a copy of input file. After the input data, the fifth section is added to represent the optimal path:
```sh
[$Start]
...
[$OptPath]
x1 y1   # coordinates of trajectory nodes
...
xn yn
# EOF
```
### Visualization
To make Octave visualization of the result, run the script **graphics.m** in visualization folder. If you use not default output file, enter its name as the *fopen* argument in the script.