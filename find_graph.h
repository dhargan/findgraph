#ifndef FIND_GRAPH_H
#define FIND_GRAPH_H

class GraphFinder{
    private:
        std::ofstream output;
        int* points;
        double** distance;
        int numberOfPoints;
        int pointLimit;

    public:
        GraphFinder(int _numberOfPoints, int _pointLimit, bool manualSetDistance = true);

        double calcDistance(int A, int B);

        void setDistanceWith(int fromPoint, int toPoint, int dist);

        int getDistanceWith(int fromPoint, int toPoint);

        bool graphValidation();

        void iteratePoints(int i = 0);

        bool isFinished();

        int getNumberOfPoints();

        void FindGraph();

};

#endif
