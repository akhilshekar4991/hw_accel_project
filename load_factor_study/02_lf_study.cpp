#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <vector>
#include "../00_map_helper.hpp"

using json = nlohmann::json;
using namespace std;
using namespace chrono;

#define     NUM_OF_KV_PAIRS         (99999999+1)
#define     INPUT_DATA_FILENAME     "input_data_1.json"

template<typename mapType>
vector<int> checkBucketLengths(const mapType &hashMap){
    int numOfBuckets = hashMap.bucket_count();
    vector<int> bucketLengths;
    for(int bucket_iter = 0; bucket_iter < numOfBuckets; bucket_iter++){
        bucketLengths.push_back(hashMap.bucket_size(bucket_iter));
    }

    return bucketLengths;
}

void dumpBucketLengthsIntoFile(vector<int> bucketLengths, string outputFileName){
    
    ofstream outFile(outputFileName);
    json j; 
    j["vector_lengths"] = bucketLengths;
    outFile << j << endl;
    outFile.close();
}

int main(){
    unordered_map<int, int>   hashMap;
    int numOfBuckets;

    loadDatasetAndReturnMap<unordered_map<int,int>>(hashMap, INPUT_DATA_FILENAME);

    cout << "Vanilla Mapping \n";
    cout << "Size of Hashmap = " << hashMap.size();
    cout << "\nLoad Factor = " << hashMap.load_factor();
    cout << "\nBucket Count = " << hashMap.bucket_count();
    vector<int> vanillaBucketLengths =
        checkBucketLengths<unordered_map<int, int>>(hashMap);
    dumpBucketLengthsIntoFile(vanillaBucketLengths, "vanilla_mapping.json");
    
    numOfBuckets = 4096;
    hashMap.rehash(numOfBuckets);
    cout << "\n4K Mapping \n";
    cout << "Size of Hashmap = " << hashMap.size();
    cout << "\nLoad Factor = " << hashMap.load_factor();
    cout << "\nBucket Count = " << hashMap.bucket_count();
    vanillaBucketLengths = checkBucketLengths<unordered_map<int, int>>(hashMap);
    dumpBucketLengthsIntoFile(vanillaBucketLengths, "4K_mapping.json");

    /*
    numOfBuckets = 16384;
    hashMap.rehash(numOfBuckets);
    cout << "16K Mapping \n";
    cout << "Size of Hashmap = " << hashMap.size();
    cout << "\nLoad Factor = " << hashMap.load_factor();
    cout << "\nBucket Count = " << hashMap.bucket_count();
    vector<int> vanillaBucketLengths =
        checkBucketLengths<unordered_map<int, int>>(hashMap);
    dumpBucketLengthsIntoJsonFile(vanillaBucketLengths, "16K_mapping.json");

    numOfBuckets = 32768;
    hashMap.rehash(numOfBuckets);
    cout << "32K Mapping \n";
    cout << "Size of Hashmap = " << hashMap.size();
    cout << "\nLoad Factor = " << hashMap.load_factor();
    cout << "\nBucket Count = " << hashMap.bucket_count();
    vector<int> vanillaBucketLengths =
        checkBucketLengths<unordered_map<int, int>>(hashMap);
    dumpBucketLengthsIntoJsonFile(vanillaBucketLengths, "32K_mapping.json");

    numOfBuckets = 65536;
    hashMap.rehash(numOfBuckets);
    cout << "64K Mapping \n";
    cout << "Size of Hashmap = " << hashMap.size();
    cout << "\nLoad Factor = " << hashMap.load_factor();
    cout << "\nBucket Count = " << hashMap.bucket_count();
    vector<int> vanillaBucketLengths =
        checkBucketLengths<unordered_map<int, int>>(hashMap);
    dumpBucketLengthsIntoJsonFile(vanillaBucketLengths, "64K_mapping.json");

    numOfBuckets = 131072;
    hashMap.rehash(numOfBuckets);
    cout << "128K Mapping \n";
    cout << "Size of Hashmap = " << hashMap.size();
    cout << "\nLoad Factor = " << hashMap.load_factor();
    cout << "\nBucket Count = " << hashMap.bucket_count();
    vector<int> vanillaBucketLengths =
        checkBucketLengths<unordered_map<int, int>>(hashMap);
    dumpBucketLengthsIntoJsonFile(vanillaBucketLengths, "128K_mapping.json");
    */

   cout << "\n";
}