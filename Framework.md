# Overview 
## TODO 
1. write python script 
2. to add demand scale factor

## python script 
1. Step 1: read and set input/ouput folder 
2. Step 2: set the test parameters 
    * network 
    * set of links to be removed
    * copy and back up the folders
3. Step 3: run c++ code to get the results 
    * output the flow and proper warnings 
    * write the output into folder
4. Step 3: process the results files 
    * copy and back up the results folders 


## C++ codes 
1. Step 1: read test parameters 
    * network 
    * remove links (three cases)
        -  all links one by one 
        -  a list of links
> remarks: for a large network, it may be better the seperated the list of link into different files and run them seperatedly considering the memory issue
