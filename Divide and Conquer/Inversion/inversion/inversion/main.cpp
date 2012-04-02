//
//  main.cpp
//  inversion
//
//  Created by Zewen Li on 3/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;
#include <stdlib.h>
#include <math.h>

long mergeSort (int start, int end);
long merge(int start, int start2, int end);
#define length 100000
static int storedArray[length];
static int sortedArray[length];
static long result = 0;



int main (int argc, const char * argv[])
{

    // insert code here...
    const char filename[] = "IntegerArray.txt";
    ifstream i_file;
    string out_text;
    int count =0;


    
    i_file.open(filename);
    
    // create array first
    if (i_file.is_open())
    {
        while ( (getline(i_file, out_text)) && (count < length))
        {
                storedArray[count] = atoi(out_text.c_str());
                count++;
//            i_file >> out_text; //将读取的内容存储到变量out_text中 
//            cout << out_text << endl; //在控制台输出读取的内容。为什么最后一行的内容会出现两次 
        } 
    }
    else
        cout << "打开文件：" << filename << " 时出错！"; 
    i_file.close();
    
    for (int i = 0; i < length; i++) {
        sortedArray[i] = storedArray[i];
    }
    
    result = mergeSort(0, length-1);
    
    cout<<"the result is:"<<result<<endl;
    
    return 0;
}


long mergeSort ( int start, int end) {

    
    if (start == end) {
        return 0;
    }
    
    if (start == end - 1) {
        
        if (sortedArray[start] <= sortedArray[end]) {
            return 0;
        }
        else //sortedArray[start] > sortedArray[end]
        {
            int tmp =sortedArray[start];
            sortedArray[start] = sortedArray[end];
            sortedArray[end] = tmp;
            return 1;
        }
    }
    
    long result1 = mergeSort(start, (floor ((start+end)/2)));
    
    long result2 = mergeSort((floor ((start+end)/2)+1), end);
    
    long result3 = merge(start, (floor ((start+end)/2)+1), end);

    
    return result1+result2+result3;;
}

long merge (int start1, int start2, int end) {
    
    int *sorted = new int[end-start1+1];
    int j = start1;
    int k = start2;
    long tmpresult = 0;
    
    for (int i = 0; i <= end-start1; i++) {
        
        if (j >= start2) {
            sorted[i] = sortedArray[k];
            k++;
            continue;
        }
        
        if (k > end) {
            sorted[i] = sortedArray[j];
            j++;
            continue;
        }
        
        if (sortedArray[j] <= sortedArray[k])  {
            sorted[i] = sortedArray[j];
            j++;
            continue;
        }
        
         // sortedArray[j] > sortedArray[k]
        if (sortedArray[j] > sortedArray[k]) 
        {
            sorted[i] = sortedArray[k];
            k++;
            // from sortedArray[j] to [start2-1] are all larger than k
            // this number is start2-1-j+1 == start2-j
            tmpresult += start2 - j;
            continue;
            
        }
    }
    
    for (int i = 0; i <= end-start1; i++) {
        sortedArray[start1+i] = sorted[i];
    }
    
    return tmpresult;
}
