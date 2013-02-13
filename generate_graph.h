#ifndef GENERATE_GRAPH_H
#define GENERATE_GRAPH_H



class Point{
    private:
        int x, y, z;        

    public:
        void setPoint(int _x, int _y, int _z){
            x = _x;
            y = _y;
            z = _z;
        }

        int getX(){return x;}
        int getY(){return y;}
        int getZ(){return z;}
};



class GraphGenerator{
    private:
        int numberOfVertices, maximumDistance;
        double verticeRange;
        int*** grid;
        Point** points;
        std::ofstream graph_output;

    public:
        GraphGenerator(int _numberOfVertices, int _maximumDistance, double _verticeRange);

        void PlotRandomPoint(int index);

        double calcDistance(int i, int j);

        void GenerateGraph();

};

#endif // GENERATE_GRAPH_H
