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
#include "../HashMap/hashmap/HashMap.h"

using json = nlohmann::json;
using namespace std;
using namespace chrono;

#define     NUM_OF_KV_PAIRS         (99999999+1)
#define     INPUT_DATA_FILENAME     "/bigtemp/rgq5aw/input_data_100M.json"
#define     OUTPUT_DATA_FILENAME     "out.txt"
#define     NUM_OF_BUCKETS 50

struct MyKeyHash {
    unsigned long operator()(const int& k) const
    {
        unsigned long prime = 40567019;
        return (k * prime) % NUM_OF_BUCKETS;
    }
};

int main(){
    unordered_map<int, int>   plainStdMap;
    HashMap<int, int, NUM_OF_BUCKETS, MyKeyHash> hmap;
    loadDatasetAndReturnMap<unordered_map<int,int>>(plainStdMap, INPUT_DATA_FILENAME);
    ofstream out(OUTPUT_DATA_FILENAME);
    cout << "Size of Hashmap = " << plainStdMap.size();
    cout << "\nLoad Factor = " << plainStdMap.load_factor();
    for (auto i : plainStdMap)
    {
        hmap.put(i.first, i.second);
        //cout << "first: " << i.first << endl;
    }
    int value = 0;long pos = 0;unsigned long bucket = 0;
    for (auto i : plainStdMap)
    {
        bool result = hmap.get(i.first, value, pos, bucket);
        //cout << "first: " << i.first << endl;
        assert(result);
        assert(value == i.second);
        out << "key : " << i.first << ", value : " << value << ", pos : " << pos << ", bucket : " << bucket << endl;
    }
    // Wait on user prompt to exit()
    // char user_input[5];
    // cin.getline(user_input, 5);
    out.close();
}

// int main()
// {
//     HashMap<int, string, NUM_OF_BUCKETS, MyKeyHash> hmap;
//     hmap.put(1, "1");
//     hmap.put(2, "2");
//     hmap.put(3, "3");
//     hmap.put(12, "12");
//     hmap.put(22, "22");
//     hmap.put(11, "11");
//     hmap.put(33, "33");

//     string value = "";long pos = 0;unsigned long bucket = 0;
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
//     hmap.remove(3);
//     result = hmap.get(3, value, pos, bucket);
//     assert(!result);
//     cout << "value : " << value << ", valuePos : " << pos << ", bucket : " << bucket << endl;
// }