#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <ctime>
#include "generate_graph.h"

using namespace std;
using namespace boost;

typedef adjacency_list <vecS, vecS, undirectedS> Graph;

GraphGenerator::GraphGenerator(int _numberOfVertices, int _maximumDistance, double _verticeRange){
    numberOfVertices = _numberOfVertices;
    maximumDistance = _maximumDistance;
    points = new Point*[numberOfVertices];

    for(int i = 0; i< numberOfVertices; i++ ){
        points[i] = new Point();
    }

    verticeRange = _verticeRange;

    grid = new int**[maximumDistance];
    for (int i = 0 ; i < maximumDistance ; i++){
        grid[i] = new int*[maximumDistance];
        for (int j = 0 ; j < maximumDistance ; j++){
            grid[i][j] = new int[maximumDistance];
        }
    }

    for(int i = 0; i < maximumDistance; i++){
        for(int j = 0; j < maximumDistance; j++){
            for(int k = 0; k < maximumDistance; k++){
                grid[i][j][k] = 0;
            }
        }
    }
}

void GraphGenerator::PlotRandomPoint(int index){
    srand(time(NULL));
    int x = rand() % maximumDistance;
    int y = rand() % maximumDistance;
    int z = rand() % maximumDistance;    

    while(grid[x][y][z] == 1){
        x = rand() % maximumDistance;
        y = rand() % maximumDistance;
        z = rand() % maximumDistance;
    }

    grid[x][y][z] = 1;
    points[index]->setPoint(x,y,z);    
}

double GraphGenerator::calcDistance(int i, int j){
    return sqrt(pow(points[i]->getX() - points[j]->getX(),2) + pow(points[i]->getY() - points[j]->getY(),2) + pow(points[i]->getZ() - points[j]->getZ(),2));
}

void GraphGenerator::GenerateGraph(){
    Graph G;

    for(int i = 0; i < numberOfVertices; i++){
        PlotRandomPoint(i);        
    }


    for(int i = 0; i < numberOfVertices -1; i++){
        for(int j = i+1; j < numberOfVertices; j++){
            if(calcDistance(i,j) <= verticeRange){
                add_edge(i,j,G);
            }
        }
    }

    bool isConnected = true;

    vector<int> component(num_vertices(G));
    int num = connected_components(G, &component[0]);

    vector<int>::size_type i;

    for(i = 0; i!= component.size(); ++i){
        if(component[i] != component[0]){
            isConnected = false;
        }
    }

    if(component.size() < 1){
        isConnected = false;
    }

    if(isConnected){
        graph_output.open("graph.txt");
        for(int i = 0; i < numberOfVertices -1; i++){
            for(int j = i+1; j < numberOfVertices; j++){
                if(calcDistance(i,j) <= verticeRange){
                    graph_output<<i<<" "<<j<<" = "<<calcDistance(i,j)<<endl;
                }else{
                    graph_output<<i<<" "<<j<<" = "<<"-1"<<endl;
                }
            }
        }

    }else{
        GenerateGraph();
    }

    graph_output.close();
}
