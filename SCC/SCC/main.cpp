//
//  main.cpp
//  SCC
//
//  Created by Zewen Li on 4/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//



#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;
#include <string.h>


#define NumOfEdge 5105043 //29
#define NumOfNode 875714 //15

multimap<int, int> G;
multimap<int, int> RevG;
static int leader[NumOfNode+1];
static int explored[NumOfNode+1];
static int finish[NumOfNode+1];
static int finishtime = 0;
static int currentleader = 0;
static int result[NumOfNode+1];



void DFS ( multimap<int,int> &graph, int i);




int main (int argc, const char * argv[])
{

//1. initialize all
    //1.1 clear all 
    for (int i = 0; i <= NumOfNode; i++) {
        leader[i] = 0;
        explored[i] = 0;
        finish[i] = 0;
        result[i] = 0;
    }
    
    //1.2 read in data
    ifstream fin("SCC.txt");
    string str, str2;
    
    //1.2.1 Buld a multimap of G's edges and Rev-G's edges
    while (getline(fin, str)) {
        istringstream istr(str);
        int u, v;
        istr>>u;
        istr>>v;
        G.insert(make_pair(u, v));
        RevG.insert(make_pair(v, u));
         
    }
    
    //2. Loop DFS on Rev-G
    for (int i = NumOfNode; i >=1; i--) {
        if (explored[i] == 0) {
            //currentleader = i;
            DFS(RevG, i);
        }
    }
    
    //3.call loop DFS on G, this time we need to set leader
    //3.1 clear explored state
    for (int i = 0; i <= NumOfNode; i++) {
        explored[i] = 0;
    }
    //3.2 start to loop DFS, but notice we need a special order
    for (int i = NumOfNode; i >= 1; i--) {
        int node = finish[i];
        if (explored[node] == 0) {
            currentleader = node;
            DFS(G, node);
        }
    }


//2. call loop DFS on Rev-G
//3. call loop DFS on G set up leader
    

//4. analysis the result from leader[]
//    map<int, int> result;
//    for (int i = 1; i <= NumOfNode; i++) {
//        map<int, int>::iterator iter = result.find(leader[i]);
//        // if not exist
//        if (iter == result.end()) {
//            result.insert(make_pair(leader[i], 1));
//        }
//        // if exist
//        else
//        {
//            result[leader[i]] = result[leader[i]] + 1;
//        }
//    }
//    cout<<"how many SCC?:";
//    cout<<result.size()<<endl;
     

//4. OMG, it's really slow to use map for result analysis, so I just use an array instead.
    for (int i = 0; i <= NumOfNode; i++) {
        result[i] = 0;
    }
    

    for (int i = 1; i <= NumOfNode; i++) {
        result[leader[i]]++;
        }
    
    int count = 0;
    for (int i = 1; i <= NumOfNode; i++) {
        if (result[i] != 0) {
            count++;
            // I guess this may limits our final answer, after all, try to sort takes time 
            // and it's a little complex to find the 5 largest result.
            if (result[i] > 200)
                cout<<"scc"<<i<<"is:"<<result[i]<<endl;
        }
    }

    cout<<count<<endl;

    
    return 0;
}

void DFS(multimap<int, int> &graph,int i)
{
    //set i explored
    explored[i] = 1;
    //set leader to currentleader, never mind in the first round on Rev-G, no use
    // just for unification.
    leader[i] = currentleader;
    
    // for each edge (i, j)
        // if j not explored
            //DFS(graph, j)
        // finishtime++
        // finish[i] = finishtime
// one way to traverse    
    multimap<int, int>::iterator lb = graph.lower_bound(i);
    multimap<int, int>::iterator ub = graph.upper_bound(i);
    for (multimap<int, int>::iterator t = lb; t !=ub; t++) {
        if (!explored[t->second]) {
            DFS(graph, t->second);
        }
    }
    finishtime++;
    //finish[i] = finishtime;
    finish[finishtime] = i;
// another way is to use equal_range, but Mac OS seems not support it well.

    
}



//1. initialize all 
//2. call loop DFS on Rev-G
//3. call loop DFS on G set up leader

// DFS loop:
// DFS loop (G)
// t = 0
// s = null;
// for node i from n to 1
//      if i not explored
//          s = i
//          DFS(G, i)
//
// DFS (G, i):
//  mark i as explored
//  set leader(i) = s
//  for each (i, j) 
//      if j not explored 
//          DFS(G, j)
//  t++
//  set f(i) = t




