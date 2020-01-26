# Project Name : "Client_Server_Communication"

# Description  
this is a programm that solves a problem of finding the best path (min cost 
 path) in a grid wich is represented by a matrix. 
 there is a problem of a grid with costs (matrix) every cell is a state 
  (point) and we need to activate an algorithm of searching problem solver (A
  -STAR is the best according to an experiment we did). the algorithm will 
   solve the problem and return a string that specify the exact path you 
    should do in order to obtain the perfect path. 
    of course part of the problem is the initial state (begin entry) and the 
     goal state (end position). 

Programming - Topics we Used:
-----------------------------
* Using Pattern Designs and Architecture
* Communication and Client-Server Architecture
* Using Data Structures and DataBase
* injecting files and data to server and receive as well
* Multythread Programming
* Use of design and architecture templates.
* Comparison, selection and assimilation of algorithms within the system we
 create.
* Parallel programming.


The Classes (include 2 interfaces):
-----------------------------------
**Arye's Classes:**   
- empiric_test.cpp
- <<Searcher.h>> Interface
- <<Searchable.h>> Interface
- Matrix
- SearchableMatrix
- BFS
- DFS
- BestFS
- AStar
- State
- <<CacheManager.h>> Interface
- MyMatrixCacheManager

**Miri's Classes:**
- Server.h
- Solver.h
- StringReverser
- ClientHandler.h
- MyClientHandler
- MySerialServer
- MyParallelServer
- MyTestClientHandler
- ParalelServer
- ObjectAdapter

# Installation  
1. open terminal in a linux system and in the directory of the programm:
2. type:
 g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor
 -pedantic -o a.out -pthread
3. run script of clients and get the solutions!

# Support  
arye.amsalem@gmail.com  
miriyungreis@gmail.com

# Roadmap  
none.

# Contributing  
none.

# Authors and acknowledgment  
in this opportunity i would like to praise and thank Miri Jungreis - my partner
, that was very strong and dominant in managing the team of this project.

# License  
All rights reserved for Arye & Miri - no open source in this point.

# Project status  
Mile Stone #2 - delivered.

# Git Hub Link ~ ~ for instructors 89210
https://github.com/Arye182/Client_Server_Communication