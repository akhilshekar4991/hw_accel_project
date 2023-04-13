# hw_accel_project
This is for the Hardware Accelerator (CS 6501) project

# To Conduct Benchmarking between Standard C++ Map and Hopscotch Map structure
- We will generate half a million (500,000) key-value pairs of (int, int) type. 
- We will insert it into map structures.
- Then we probe 50,000 (N/10) keys and measure the execution time

Steps - 
1. $ mkdir build
2. $ cmake .. 
3. $ make
4. $ cp -v test.out .. 
5. $ cd .. 
6. $ ./test.out 