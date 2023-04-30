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
#include "../HashMap/Hashmap_vec_dq/HashMap.h"

using json = nlohmann::json;
using namespace std;
using namespace chrono;

#define     NUM_OF_KV_PAIRS         (99999999+1)
#define     INPUT_DATA_FILENAME     "/bigtemp/rgq5aw/input_data_100M.json"
// #define     INPUT_DATA_FILENAME     "input_data1.json"

#define     OUTPUT_DATA_FILENAME     "out.txt"
#define     NUM_OF_BUCKETS 50000

auto hash_func = [](const int& key) {
    return std::hash<int>{}(key);
};

int main(){
    unordered_map<int, int>   plainStdMap;
    HashMap<int, int> hmap(NUM_OF_BUCKETS, hash_func);
    loadDatasetAndReturnMap<unordered_map<int,int>>(plainStdMap, INPUT_DATA_FILENAME);
    cout << "loading the unordered map finished and size is:  " << plainStdMap.size() << endl;
    ofstream out(OUTPUT_DATA_FILENAME);
    cout << "Size of Hashmap = " << plainStdMap.size() << endl;
    cout << "\nLoad Factor = " << plainStdMap.load_factor() << endl;
    int count = 0;
    for (auto i : plainStdMap)
    {
        hmap.put(i.first, i.second);
        count++;
        //cout << "first: " << i.first << endl;
        // if(count % 100000 == 0)
        //     cout << "count : " << count << endl;
    }
    cout << "loading the hmap finished " << endl;
    int value = 0;size_t pos = 0;size_t bucket = 0;
    for (auto i : plainStdMap)
    {
        bool result = hmap.get(i.first, value, pos, bucket);
        //cout << "first: " << i.first << endl;
        assert(result);
        assert(value == i.second);
        out << "key : " << i.first << ", value : " << value << ", pos : " << pos << ", bucket : " << bucket << endl;
    }
    cout << "key probing finished " << endl;
    // Wait on user prompt to exit()
    // char user_input[5];
    // cin.getline(user_input, 5);
    out.close();
}

// int main()
// {
//     HashMap<int, string> hmap(NUM_OF_BUCKETS, hash_func);
//     hmap.put(1, "1");
//     hmap.put(2, "2");
//     hmap.put(3, "3");
//     hmap.put(12, "12");
//     hmap.put(22, "22");
//     hmap.put(11, "11");
//     hmap.put(33, "33");

//     string value = "";size_t pos = 0;size_t bucket = 0;
//     bool result = hmap.get(2, value, pos, bucket);
//     assert(result);
//     assert(value == "2");
//     cout << "value : " << value << ", valuePos : " << pos << ", bucket : " << bucket << endl;
//     value = "";pos = 0;bucket = 0;
//     result = hmap.get(3, value, pos, bucket);
//     assert(result);
//     assert(value == "3");
//     cout << "value : " << value << ", valuePos : " << pos << ", bucket : " << bucket << endl;
//     value = "";pos = 0;bucket = 0;
//     result = hmap.get(12, value, pos, bucket);
//     assert(result);
//     assert(value == "12");
//     cout << "value : " << value << ", valuePos : " << pos << ", bucket : " << bucket << endl;
//     value = "";pos = 0;bucket = 0;
//     result = hmap.get(22, value, pos, bucket);
//     assert(result);
//     assert(value == "22");
//     cout << "value : " << value << ", valuePos : " << pos << ", bucket : " << bucket << endl;
//     value = "";pos = 0;bucket = 0;
//     result = hmap.get(33, value, pos, bucket);
//     assert(result);
//     assert(value == "33");
//     cout << "value : " << value << ", valuePos : " << pos << ", bucket : " << bucket << endl;
//     value = "";pos = 0;bucket = 0;
//     // hmap.remove(3);
//     // result = hmap.get(3, value, pos, bucket);
//     // assert(!result);
//     // cout << "value : " << value << ", valuePos : " << pos << ", bucket : " << bucket << endl;
// }