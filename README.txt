CSC 173 Project 4
Name: Minh Tuan Nguyen
NetID: mnguy32
Email: mnguy32@u.rochester.edu

Build and Run command:
gcc -o main Database.c ReadWriteDB.c RelationalAlgebra.c main.c -Wall -Werror -std=c99
gdb main
run

*Note: Please run it as "gdb main" instead of "main" because for some reasons, my 3rd part fails to run on the normal terminal.
Also, please run it on your command line for best performance XD. Thank you very much!

I got this for part 3 when running gdb:
Part 3

1) Selection
Course          StudentId               Grade
MATH150         67890           C+
CSC171          67890           B

2) Projection
Course
MATH150
CSC171

3) Join
Course          Room            Day             Hour
DSCC201         Bausch & Lomb 109               M               900
DSCC201         Bausch & Lomb 109               W               900
DSCC202         Dewey 2162              M               1650
DSCC202         Dewey 2162              W               1650
DSCC265         Wegmans 1400            M               1400
DSCC265         Wegmans 1400            W               1400
CSC171          Hutchison Hall 141              T               1400
CSC171          Hutchison Hall 141              R               1400
CSC252          Wegmans 1400            T               1230
CSC252          Wegmans 1400            R               1230
CSC172          Hutchison Hall 141              T               1525
CSC172          Hutchison Hall 141              R               1640
CSC173          Wegmans 1400            T               1400
CSC173          Wegmans 1400            R               1400

4) All of the above
Day             Hour
M               1400
R               1230
R               1400
T               1230
T               1400
W               1400

There are some formatting issues but I hope they don't cause you any inconveniences. 

In case you can't run on gdb, the build and run command is:
gcc -o main Database.c ReadWriteDB.c RelationalAlgebra.c main.c -Wall -Werror -std=c99
main
(You may have to repeat "main" a couple of times before it works properly so please be patient)

I also did both parts of the extra credit:
Part 1: 
Reading and Writing format:
[key] [number of attributes in a tuple] [number of tuples]
[attribute1]
[attribute2]
...

[tuple1 data1]
[tuple1 data2]
...

[tuple2 data1]
[tuple2 data2]
...

Part 2: I implemented a generic database in Databse.c 

Thank you very much for grading my project!