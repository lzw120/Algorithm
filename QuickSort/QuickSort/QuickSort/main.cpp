//
//  main.cpp
//  QuickSort
//
//  Created by Zewen Li on 3/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;
#include <math.h>

#define MODE1
//#define MODE2
//#define MODE3

#define length 10000



static int storedArray[length];


static long result = 0;


int Partition (int start, int end)
{

//Option1: choose the first element as the partition line.
//////////////////////////In Place algorithm//////////////////////
#ifdef MODE1
    int divide = start;
    int j = start+1;
    for (int i = start+1; i <= end; i++) {
        if (storedArray[i] > storedArray[divide]) {
            continue;
        }
        else
        {
            // swap storedArray[i] and storedArray[j]
            int tmp = storedArray[i];
            storedArray[i] = storedArray[j];
            storedArray[j] = tmp;
            j++;
        }
    }
    //swap storedarray[divide] and storedarray[j-1]
    int tmp2 = storedArray[divide];
    storedArray[divide] = storedArray[j-1];
    storedArray[j-1] = tmp2;
    divide = j-1;
// still for Option1 but use another algorithm for partition....I don't see the problem clearly 
// enough....
// though it works also, don't use this method for assignment2, u'll get wrong result
//////////////////////// SWAP  Algorithm///////////////////////////
//    while (i < j) {
//        while (storedArray[i] < storedArray[j]) {
//            j--;
//        }
//        if (i < j) {
//            tmp = storedArray[divide];
//            storedArray[divide] = storedArray[j];
//            storedArray[j] = tmp;
//            divide = j;
//            i++;
//        }
//       
//        while (storedArray[j] > storedArray[i]) {
//            i++;
//        }
//        if (i < j) {
//            tmp = storedArray[divide];
//            storedArray[divide] = storedArray[i];
//            storedArray[i] = tmp;
//            divide = i;
//            j--;
//        }
//    }
#endif  //End MODE1
    
    
    //Option2: choose the last element as pivot
//////////////////////////In Place algorithm//////////////////////
#ifdef MODE2
    int divide = end;
    int tmp3 = storedArray[end];
    storedArray[end] = storedArray[start];
    storedArray[start] = tmp3;
    divide = start;
    
    int j = start+1;
    for (int i = start+1; i <= end; i++) {
        if (storedArray[i] > storedArray[divide]) {
            continue;
        }
        else
        {
            // swap storedArray[i] and storedArray[j]
            int tmp = storedArray[i];
            storedArray[i] = storedArray[j];
            storedArray[j] = tmp;
            j++;
        }
    }
    //swap storedarray[divide] and storedarray[j-1]
    int tmp2 = storedArray[divide];
    storedArray[divide] = storedArray[j-1];
    storedArray[j-1] = tmp2;
    divide = j-1;

// still for Option2 but use another algorithm for partition....I don't see the problem clearly 
// enough....
// though it works also, don't use this method for assignment2, u'll get wrong result
//////////////////////////SWAP algorithm//////////////////////
//    int divide = end;
//    int i = start;
//    int j = end;
//    int tmp = 0;
//    while (i < j) {
//       
//        while (storedArray[j] > storedArray[i]) {
//            i++;
//        }
//        if (i < j) {
//            tmp = storedArray[divide];
//            storedArray[divide] = storedArray[i];
//            storedArray[i] = tmp;
//            divide = i;
//            j--;
//        }
//        
//        while (storedArray[i] < storedArray[j]) {
//            j--;
//        }
//        if (i < j) {
//            tmp = storedArray[divide];
//            storedArray[divide] = storedArray[j];
//            storedArray[j] = tmp;
//            divide = j;
//            i++;
//        }
//        
//    }
#endif //end MODE2    
    
    //Option3: choose 1st, middle, and last
//////////////////////////In Place algorithm//////////////////////
#ifdef MODE3
    int first = storedArray[start];
    int tmp2 = (start + end)/2;
    int middle = storedArray[tmp2];
    int last = storedArray[end];
    int means = 0;
    if (first <= last) {
        if ((first <= middle) && (middle <= last)) {
            means = tmp2;
        }
        else if (middle < first)
            means = start;
        else if (last < middle)
            means = end;
    }
    else if (first > last)
    {
        if ((last <= middle) && (middle <= first)) {
            means = tmp2;
        }
        else if (middle < last) {
            means = end;
        }
        else if (first < middle) {
            means = start;
        }
    }
    
    int divide;
    int tmp = storedArray[means];
    storedArray[means] = storedArray[start];
    storedArray[start] = tmp;
    divide = start;
    
    int j = start+1;
    for (int i = start+1; i <= end; i++) {
        if (storedArray[i] > storedArray[divide]) {
            continue;
        }
        else
        {
            // swap storedArray[i] and storedArray[j]
            int tmp = storedArray[i];
            storedArray[i] = storedArray[j];
            storedArray[j] = tmp;
            j++;
        }
    }
    //swap storedarray[divide] and storedarray[j-1]
    int tmp3 = storedArray[divide];
    storedArray[divide] = storedArray[j-1];
    storedArray[j-1] = tmp3;
    divide = j-1;

   
// still for Option3 but use another algorithm for partition....I don't see the problem clearly 
// enough....
// though it works also, don't use this method for assignment2, u'll get wrong result
//////////////////////////SWAP algorithm//////////////////////    
//    
//    int tmp = 0;
//    tmp = storedArray[means];
//    storedArray[means] = storedArray[start];
//    storedArray[start] = tmp;
//    int i = start;
//    int j = end;
//    int divide = start;
//    
//    while (i < j) {
//        
//        while (storedArray[i] < storedArray[j]) {
//            j--;
//        }
//        if (i < j) {
//            tmp = storedArray[divide];
//            storedArray[divide] = storedArray[j];
//            storedArray[j] = tmp;
//            divide = j;
//            i++;
//        }
//        
//        while (storedArray[j] > storedArray[i]) {
//            i++;
//        }
//        if (i < j) {
//            tmp = storedArray[divide];
//            storedArray[divide] = storedArray[i];
//            storedArray[i] = tmp;
//            divide = i;
//            j--;
//        }
//        
//    }
#endif  // end mode3
    
    return divide;
    
    
}

// just for debug test
void printarray( int s, int t)
{
    cout<<"times:"<<t-s<<"array["<<s<<"] to array["<<t<<"]:";
    for (int i = s; i <= t; i++) {
        cout<<storedArray[i]<<" ";
    }
    cout<<endl;
}

void QuickSort (int start, int end)
{
    
    if (start == end) {
        return ;
        // do not count for this
    }

    if (start == end-1) {
        if (storedArray[start] > storedArray[end]) {
            int tmp = storedArray[start];
            storedArray[start] = storedArray[end];
            storedArray[end] = tmp;
        }

        return ;
        //count for 1 but already added outside before this function
    }

    int divide = Partition(start, end);
    

    
    if (divide == start) {
        result += end - divide -1;
        QuickSort(divide+1, end);

    }
    
    else if (divide == end) {
        result += divide - 1 - start;
        QuickSort(start, divide-1);

    }
    else
    {
        result += divide - 1 - start;
        QuickSort(start, divide-1);
        //printarray(start, divide-1);
        

        result += end - divide - 1;
        QuickSort(divide+1, end);
        //printarray(divide+1, end);
        
    }

}

int main (int argc, const char * argv[])
{

    // insert code here...
 
    const char filename[] = "QuickSort.txt";
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
        } 
    }
    else
        cout << "打开文件：" << filename << " 时出错！"; 
    i_file.close();
    
    result += length - 1;
    QuickSort(0, length-1);
    
    cout<<result<<endl;
    //printarray(0, length-1);
    return 0;
}


/*
#include <iostream>
#include <fstream>
#include <ctime>
#define N 10000
using namespace std;
void Swap(int ar[], int a, int b)
{
    int mid;
    mid = ar[a];
    ar[a] = ar[b];
    ar[b] = mid;
}
int Sort(int ar[],int begin, int end)
{
    int k =(begin + end)/2;
    if (ar[begin] > ar[end]){
        if (ar[end] > ar[k]) k = end;
        else if (ar[k]> ar[begin]) k = begin;
    }else {
        if (ar[begin] > ar[k]) k = begin;
        else if (ar[k] > ar[end]) k = end;
    }
    Swap(ar,begin,k);
    int j = begin + 1;
    for(int i = begin + 1; i <= end; i++)
        if(ar[i] < ar[begin]) 
            Swap(ar,j++,i);
    Swap(ar,begin,j-1);
    return j-1;
}
long QuickSort(int ar[],int begin, int end)
{
    if (begin == end) return 0;
    int pivot = Sort(ar,begin,end);
    if (pivot == end)
        return QuickSort(ar,begin,pivot-1) + end - begin;
    else if (pivot == begin)
        return  QuickSort(ar,pivot+1,end) + end - begin;
    return QuickSort(ar,begin,pivot-1) + QuickSort(ar,pivot+1,end) + end - begin;
}
int main()
{
    ifstream in("QuickSort.txt");
    clock_t start, end;
    int ar[N];
    start = clock();
    for (int i = 0; i< N ; i++) in>>ar[i];
    cout<<QuickSort(ar,0,N-1)<<endl;
    end = clock();
    cout<<"Run time: "<<(double)(end - start) / CLOCKS_PER_SEC<<"S"<<endl;
}
*/


