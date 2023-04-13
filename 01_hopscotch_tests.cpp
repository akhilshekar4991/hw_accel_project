#include "00_map_helper.hpp"

using json = nlohmann::json;
using namespace std;
using namespace chrono;

#define     NUM_OF_KV_PAIRS         500000
#define     INPUT_DATA_FILENAME     "input_data.json"

int main(void)
{
    json    inputDataset;
    string inputDatasetFilename = INPUT_DATA_FILENAME;
    ifstream inputDataJsonFile(inputDatasetFilename);

    inputDataJsonFile >> inputDataset;
    inputDataJsonFile.close();

    tsl::hopscotch_map<int, int> myHopscotchMap;
    map<int, int>   plainStdMap;
    unordered_map<int, int>     plainUnorderedMap;
    int key, value;
    for(int i=1; i < NUM_OF_KV_PAIRS; i++)
    {
        // Insert into the hopscotch map
        string str = to_string(i);
        key = i; 
        value = inputDataset[str];
        myHopscotchMap[key] = value;

        // Insert into the plain map
        plainStdMap[key] = value;
        
        // Inset into plain unordered_map
        plainUnorderedMap[key] = value;
    }

    microseconds executionTimeInUsForHopScotch = queryMap<tsl::hopscotch_map<int, int>, int>(myHopscotchMap);
    microseconds executionTimeInUsForStdMap = queryMap<map<int, int>, int>(plainStdMap);
    microseconds executionTimeInUsForStdUnorderedMap = queryMap<unordered_map<int, int>, int>(plainUnorderedMap);

    cout << "Time taken to execute all queries by hopscotch = " << executionTimeInUsForHopScotch.count() << " us.\n";
    cout << "Time taken to execute all queries by Plain Map = " << executionTimeInUsForStdMap.count() << " us.\n";
    cout << "Time taken to execute all queries by Plain Unordered Map = " << executionTimeInUsForStdUnorderedMap.count() << " us.\n";
}
