#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include "find_graph.h"

using namespace std;

        GraphFinder::GraphFinder(int _numberOfPoints, int _pointLimit, bool manualSetDistance){
            points = new int[3*_numberOfPoints];
            numberOfPoints = _numberOfPoints;
            pointLimit = _pointLimit;
            distance = new double*[numberOfPoints];
            for (int i = 0 ; i < numberOfPoints ; i++){
                distance[i] = new double[numberOfPoints];
            }
            for (int i = 0; i < numberOfPoints; i++){
                distance[i][i] = 0.0;
            }
            for(int i = 0; i < 3*numberOfPoints; i++){
                points[i] = 0;
            }

            if(manualSetDistance){
                for(int i = 0; i < numberOfPoints-1; i++){
                    for(int j = i+1; j < numberOfPoints; j++){
                        cout<<"Please enter the distance between point #"<<i<<" and point #"<<j<<endl;
                        cin>>distance[i][j];
                    }
                }
            }

            else{
                ifstream input;
                input.open("graph.txt");
                if(input.is_open()){
                    string line;
                    string value;                    
                    size_t pos;

                    for(int i = 0; i < numberOfPoints-1; i++){
                        for(int j = i+1; j < numberOfPoints; j++){
                            getline(input,line);
                            pos = line.find("=");
                            pos++;
                            value = line.substr(pos);
                            value.erase(remove_if(value.begin(), value.end(), (int(*)(int))isspace), value.end());
                            distance[i][j] = atoi(value.c_str());                            
                        }
                    }
                }

                input.close();

            }
        }

        double GraphFinder::calcDistance(int A, int B){
            A++;
            B++;
            A = 3*A-3;
            B = 3*B-3;
            return sqrt(pow(points[A] - points[B],2) + pow(points[A+1] - points[B+1],2) + pow(points[A+2] - points[B+2],2));
        }

        void GraphFinder::setDistanceWith(int fromPoint, int toPoint, int dist){
            distance[fromPoint][toPoint] = dist;
            distance[toPoint][fromPoint] = dist;
        }

        int GraphFinder::getDistanceWith(int fromPoint, int toPoint){
           return distance[fromPoint][toPoint];
        }

        bool GraphFinder::graphValidation(){
            bool output = true;
            for(int i = 0; i < numberOfPoints-1; i++){
                for(int j = i+1; j < numberOfPoints; j++){
                    if(distance[i][j] != -1){
                        if(calcDistance(i,j) != distance[i][j]){
                            output = false;
                            break;
                        }
                    }
                }

                if(!output){
                    break;
                }
            }

            return output;
        }

        void GraphFinder::iteratePoints(int i){
            if(points[i] == pointLimit){
                points[i] = 0;
                iteratePoints(i+1);
            }
            else{
                points[i]++;
            }
        }

        bool GraphFinder::isFinished(){
            for(int i = 0; i < numberOfPoints*3 ; i++){
                if(points[i] != pointLimit){
                    return false;
                }
            }

            return true;
        }

        int GraphFinder::getNumberOfPoints(){
            return numberOfPoints;
        }

        void GraphFinder::FindGraph(){
            cout<<"Looking for possible graph(s), please wait. This may take several minutes."<<endl;
            output.open("output.txt");
            int counter = 0;
            int graphsFound = 0;

            output<<"Possible complete graph(s) with "<<numberOfPoints<<" points."<<endl;
            output<<endl;

            int n = numberOfPoints;

            for(int i = 0; i < n-1 ; i++){
                for(int j = i+1; j<n; j++){
                    output<<"Distance value between point "<<i<<" and point "<<j<<" has been set to "<<distance[i][j]<<endl;
                }
            }
            output<<endl;
            output<<"----------------------------------------------------------------------------------------"<<endl;

            while(!isFinished()){
                 if(graphValidation()){
                    output<<"Graph #"<<graphsFound<<endl;
                    for(int i = 0; i < 3*numberOfPoints; i+=3){
                        output<<"X = "<<points[i]<<" Y = "<<points[i+1]<<" Z = "<<points[i+2]<<endl;
                    }
                    output<<"----------------------------------------------------------------------------------------"<<endl;
                    graphsFound++;
                    cout<<graphsFound<<" graph(s) found. Looking for more..."<<endl;
                }

                iteratePoints();
            }

            cout<<"Finished! "<<graphsFound<<" graph(s) found!"<<endl;
            output.close();

        }

