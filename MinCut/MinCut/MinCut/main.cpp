//
//  main.cpp
//  MinCut
//
//  Created by Zewen Li on 3/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#define NUM 40

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


// for nodes store which nodes belong to which group
static int NodeGroup[NUM+1];
int MaxGroupNo = 0;
// for edges
static int E[NUM+1][NUM+1];
long result = 0;





// contract u and v, which could be set of nodes.
void Contract (int u, int v)
{
    //1. find u's group NO and v's group NO
    int groupU = NodeGroup[u];
    int groupV = NodeGroup[v];
    
    //2. switch case
    
    // if groupU and groupV both == 0
    // MaxGroupNo++
    // NoU and NoV both = MaxGroupNo
    // remove edge (u, v) : E[u][v] = E[v][u] = 0
    if ((groupU == 0) && (groupV == 0)) {
        MaxGroupNo++;
        //groupU = groupV = MaxGroupNo;
        //E[u][v] = E[v][u] = 0;
        NodeGroup[u] = MaxGroupNo;
        NodeGroup[v] = MaxGroupNo;
        E[u][v] = 0;
        E[v][u] = 0;
    }
    

    
    // if groupU == 0 and groupV != 0
    // 
    else if ((groupU == 0) && (groupV != 0))
    {
        NodeGroup[u] = groupV;
        // remove edges from all groupV's nodes with u
        for (int i = 1; i <= NUM; i++) {
            if (NodeGroup[i] == groupV) {
                E[u][i] = 0;
                E[i][u] = 0;
            }
        }
    }
    
    // if groupV == 0 and groupU != 0
    // ... similiar to the prior
    else if ((groupV == 0) && (groupU != 0))
    {
        NodeGroup[v] = groupU;
        // remove edges from all groupU's nodes with v
        for (int i = 1; i <= NUM; i++) {
            if (NodeGroup[i] == groupU) {
                E[v][i] = 0;
                E[i][v] = 0;
            }
        }
    }
    
    // if both != 0
    // remove all edges between them, and set them one same groupno
    // here we just choose u's #
    else
    {
        for (int i = 1; i <= NUM; i++) {
            // find all members of groupU 
            if (NodeGroup[i] == groupU) {
                for (int j = 1; j <= NUM; j++) {
                    // find all members of groupV
                    if (NodeGroup[j] == groupV) {
                        
                        // remove edge(i,j)
                        E[i][j] = 0;
                        E[j][i] = 0;

                    }
                    else
                        continue;
                }
            }
            else
                continue;
            
           
        }
        
        // can not set this in the above loop!!
        //set all groupV's members to groupNo U
        for (int i = 1; i <= NUM; i++) {
            if (NodeGroup[i] == groupV) {
                NodeGroup[i] = groupU;
            }

        }
    }
    
    
    return;
}

int MinimalCut ()
{
    int vNum = NUM;
    int u = 0;
    int v = 0;
    
    static int test = 0;
    //2.1 while current nodes # vNum > 2
    while (vNum > 2) {
        
        //2.1.1 randomly pick an edge (u,v)
        //
        // first count how many edges left
        int EdgeNum = 0;
        for (int i = 1; i <= NUM; i++) {
            for (int j = 1; j <= NUM; j++) {
                if (E[i][j] == 1) {
                    EdgeNum++;
                }
            }
        }
        // each edge we count 2 times......suck
        EdgeNum = EdgeNum/2;
        
        if (test < EdgeNum) {
            cout<<""<<endl;
        }
        
        // second randomize a count to choose an edge
        int count = rand()%EdgeNum + 1;
        int tmp = 0;
        for (int i = 1; i <= NUM; i++) {
            for (int j = 1; j <= NUM; j++) {
                if (E[i][j] == 1) {
                    tmp++;
                }
                if (tmp == count) {
                    u = i;
                    v = j;
                    break; //catch edge
                }
            }
            if (tmp == count) {
                break;
            }
        }
        
        
        
        //2.1.2 contract u and v
        // call Contract (u,v)
        Contract(u, v);
        
        test = EdgeNum;
        //2.1.3 vNum -- ;
        vNum--;
        
        
        
    }
    
    //2.2 count how many edges still == 1
    // ...
    
    int EdgeNum = 0;
    for (int i = 1; i <= NUM; i++) {
        for (int j = 1; j <= NUM; j++) {
            if (E[i][j] == 1) {
                EdgeNum++;
            }
        }
    }
    
    EdgeNum = EdgeNum/2;
    
    //cout<<"final result is:"<<EdgeNum<<endl;
    
    
    return EdgeNum;
}

int main (int argc, const char * argv[])
{
    
    srand(time(0)); 


//    while (1)
//    {
        //initialize
        //time_t t; 
        //srand( (unsigned)time( &t ) );
 
        
        for (int i = 0; i <= NUM; i++) {
            NodeGroup[i] = 0;
        }
        
        for (int i = 0; i <= NUM; i++) {
            for (int j = 0; j <= NUM; j++) {
                E[i][j] = 0;
            }
        }
        
        
        
        // 1. we need to read from file to initlize E
        // 
        string str;
        string str2;
        int Node = 0;
        int j = 0;
        ifstream fin("kargerAdj.txt");
        while(getline(fin, str))
        {
            istringstream istr(str);
            istr>>Node;
            
            while( !istr.eof() )
            {
                istr >> j ; //get a word
                E[Node][j] = 1;
                E[j][Node] = 1;
            }
            
        }
        
        
        int result = 0;
        // 2. call function MinimalCut () 
        result = MinimalCut();
        cout<<"final result is:"<<result<<endl;
        
        // reset all condition!!
    
//    }
    
    return 0;
}


// while more than 2 vertexes: (while num of v > 2)
// pick a remain edge (u,v) randomly (random choose edge E with E[u][v] == 1 )

// contract u, v into single vertex 
// 1. (find E's vertex : u, v) 
// 2. (set E[u][v] = 0 && E[v][u] = 0)
//for every node y connected to v (not include v)
//  for every node x connected to u (not include u),
//      if E[x][u] == 0  (so u x are contracted before)
//          set E[x][y] = 0 E[y][x] = 0
//          and add x into y's connected node
//          and add y into x's connected node
// cotinue do this for u and all nodes connectd with v
// as well as for v and all nodes connected with u
// remove self-loops (already done)
// num of v - 1

// return cut by final 2 vertices


//FYI
// traverse a multi map
//search_item = "B";
//for(iter = example.lower_bound(search_item);iter != example.upper_bound(search_item);++iter)
//{
//    std::cout<<iter->first<<":"<<iter->second<<endl;
//}



/*
#include <iostream>
#include <cstdio>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#define TURNS 2000
using namespace std;
int ne, nv, p[50];
pair<int, int> e[1000];
int root(int u) { return p[u] == u ? u : (p[u] = root(p[u])); }
int mincut()
{
    int m = ne - 1, ret = 0;
    for(int i = 1; i < nv; i++) p[i] = i;
    for(int i = 1; i < nv - 2; i++) {
        int now, u, v;
        while(true) {
            now = rand() % (m + 1);
            u = e[now].first, v = e[now].second;
            if(root(u) != root(v)) break;
            swap(e[now], e[m--]);
        }
        p[root(u)] = root(v);
    }
    for(int i = 0; i < ne; i++)
        if(root(e[i].first) != root(e[i].second)) ret++;
    return ret;
}
int main()
{
    srand(time(NULL));
    string line;
    freopen("kargerAdj.txt", "r", stdin);
    for(ne = 0, nv = 1; getline(cin, line); nv++) {
        int u, v;
        stringstream ss(line);
        ss >> u;
        while(ss >> v) if(u < v) e[ne++] = make_pair(u, v);
    }
    int ans = ne;
    for(int i = 0; i < TURNS; i++)
        ans = min(ans, mincut());
    cout << ans << endl;
    return 0;
}
*/