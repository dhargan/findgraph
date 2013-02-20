#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <time.h>
#include "find_graph.h"
#include "generate_graph.h"

using namespace std;

int main(){
    ifstream input;
    int values[2];
    input.open("input.txt");

    if(input.is_open()){
        string line;
        string value;
        int lineNo = 0;
        size_t pos;
        while(input.good()){
            getline(input,line);
            pos = line.find("=");
            pos++;
            value = line.substr(pos);
            value.erase(remove_if(value.begin(), value.end(), (int(*)(int))isspace), value.end());
            values[lineNo] = atoi(value.c_str());
            lineNo++;
        }
    }

    input.close();

    GraphGenerator* gg = new GraphGenerator(values[0],values[1],6);
    gg->GenerateGraph();
    GraphFinder* g = new GraphFinder(values[0],values[1],false);
    cout<<"Graph has been generated. Looking for possible occurences..."<<endl;
    clock_t start;
    start = clock();
    g->FindGraph();

    cout<<"Elapsed time: "<<((float)(clock()-start)/CLOCKS_PER_SEC)<<" seconds"<<endl;
    return 0;
}

