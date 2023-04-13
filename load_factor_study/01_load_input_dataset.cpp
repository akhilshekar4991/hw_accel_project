#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <tsl/hopscotch_map.h>
#include <tsl/hopscotch_set.h>
#include <iostream>
#include <chrono>
#include <map>
#include <unordered_map>
#include "../00_map_helper.hpp"

using json = nlohmann::json;
using namespace std;
using namespace chrono;

#define     NUM_OF_KV_PAIRS         (99999999+1)
#define     INPUT_DATA_FILENAME     "input_data_1.json"

int main(){
    unordered_map<int, int>   plainStdMap;

    loadDatasetAndReturnMap<unordered_map<int,int>>(plainStdMap, INPUT_DATA_FILENAME);

    cout << "Size of Hashmap = " << plainStdMap.size();
    cout << "\nLoad Factor = " << plainStdMap.load_factor();

    // Wait on user prompt to exit()
    char user_input[5];
    cin.getline(user_input, 5);
}