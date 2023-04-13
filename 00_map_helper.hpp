#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <tsl/hopscotch_map.h>
#include <tsl/hopscotch_set.h>
#include <iostream>
#include <chrono>
#include <map>
#include <unordered_map>

using json = nlohmann::json;
using namespace std;
using namespace chrono;

#define     QUERY_DATA_FILENAME     "query_data.json"
#define     NUM_OF_QUERIES          50000

// function to perform a search of a map
template <typename mapType, class keyType> bool findit(const mapType& inputMap, keyType val) {
    //cout << "Trying find() on value " << val << endl;
    auto result = inputMap.find(val);
    if (result != inputMap.end()) {
        //cout << "Element found: "; cout << endl;
        return false;
    } else {
        //cout << "Element not found." << endl;
        return true;
    }
}

// Function to print contents of a map
template<typename mapType>
void printMap(mapType &hashMap)
{
    for(const auto& key_value : hashMap) {
        std::cout << "{" << key_value.first << ", " << key_value.second << "}" << std::endl;
    }
}

// Program to output number of microseconds it takes to query the map structure.
// An array of an queries is passed. 
template<typename mapType, class queryArrayType, class keyType>
microseconds    checkMapExecutionTime(mapType  &hashMap, queryArrayType &queryArray){
    
    // Check the time execution for performing all queries
    auto start = high_resolution_clock::now();
    
    for(int i=1; i<queryArray.max_size(); i++) {
        findit<mapType, keyType>(hashMap, queryArray[i]);
    }
    auto stop = high_resolution_clock::now();
    microseconds timeTakenInUs= duration_cast<microseconds>(stop - start);

    return timeTakenInUs;
}

// Query the map structure. 
// This function will parse the query_data.json and construct an array of queries to perform. 
// This array of queries is used to probe the map structure, and return the execution time in microseconds (us)

template<typename mapType, class keyType>
microseconds queryMap(mapType &hashMap)
{
    ifstream    queryDataFile(QUERY_DATA_FILENAME);
    json    queryData; 

    queryDataFile >> queryData;
    queryDataFile.close();

    array<keyType, NUM_OF_QUERIES> queryArray;
    //printMap<tsl::hopscotch_map<int, int>>(hashMap);

    for(int i=1; i<NUM_OF_QUERIES; i++){
        string str = to_string(i);
        queryArray[i] = queryData[str];
    }

    microseconds    ExecutionTimeInUs = 
        checkMapExecutionTime<mapType, array<keyType, NUM_OF_QUERIES>, int>(hashMap, queryArray);
    
    return ExecutionTimeInUs;
}

/**
 * @brief Function to read the JSON file for key and value pairs
 * 
 * @tparam mapType 
 * @param hashMap   pointer to the hashmap to load the data into
 * @param inputFilename    Name of the JSON file containing the key-value pairs
 */

template<typename mapType>
void loadDatasetAndReturnMap(mapType &hashMap, string inputFilename){

    // Check the time execution for performing all queries
    auto start = high_resolution_clock::now();
    ifstream    inputDatasetFile(inputFilename);
    json    inputJson; 

    srand(time(0));
    inputDatasetFile >> inputJson;
    inputDatasetFile.close();
    auto stop = high_resolution_clock::now();

    seconds timeTaken= duration_cast<seconds>(stop - start);
    cout << "Time taken to read JSON file = " << timeTaken.count() << " seconds \n";

    map<int, int>   plainStdMap;
    int value;
    for(int key=1; key < inputJson.size(); key++){
        //string key = to_string(i * (rand() % 10000));
        //cout << "key=" << str << " Value=" << inputJson[str] << endl;

        // Read from JSON structure
        string str = to_string(key); 
        value = inputJson[str];

        // Insert into the plain map
        hashMap[key] = value;
    }
    cout << "Finished loading the JSON file into hashmap structure\n";
}