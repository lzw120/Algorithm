//
//  main.cpp
//  Hash
//
//  Created by Zewen Li on 4/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <hash_map.h>

using namespace std;
#include <string.h>

#define length 9
//Here are 9 "target sums", in increasing order: 231552,234756,596873,648219,726312,981237,988331,1277361,1283379. Your task is to implement, for each of the 9 target sums x, whether or not x can be formed as the sum of two entries in the given array.
static int target[length] = {231552,234756,596873,648219,726312,981237,988331,1277361,1283379};
// save the result 0 stands for no with target[i], 1 stands for yes
static int result[length] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
__gnu_cxx::hash_map<int, int> storeHash;


int main (int argc, const char * argv[])
{


    //1. read in the numbers
    ifstream in("HashInt.txt");
    string buffer = "";
    int num = 0;
    //2. at the same time build the hash map
    while (getline(in, buffer)) {
        num = atoi(buffer.c_str());
        storeHash[num] = 1;
    }
    
    //3. for all target, start to find 
    for (int i = 0; i < length; i++) {
        __gnu_cxx::hash_map<int, int>::iterator iter;
        
        //3.1 for target[i] try to find  any pair adds up to it.
        for (iter = storeHash.begin(); iter != storeHash.end(); iter++) {
            int diff = target[i] - iter->first;
            // if diff exists, then find it.
            if (storeHash.find(diff) != storeHash.end()) {
                result[i] = 1;
                // and break this loop, no need to find more pairs.
                break;
            }
            // if iterate all hashmap , find no pairs
            else
                result[i] = 0;
            
        }
    }
    
    // ok game over.
    for (int i = 0; i <length; i++) {
        cout<<result[i];
    }
    cout<<endl;
    
    return 0;
}

