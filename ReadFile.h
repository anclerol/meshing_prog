
#ifndef ReadFile_H

#define ReadFile_H
#include "struct.h"
#include "include.h"

class Shape {
public:
    virtual void Draw() = 0;
};

class Circle : public Shape {
public:
    double radius;
    double x, y;
    void Draw () override;
};

class Polygon : public Shape {
public:
    vector<Points> vertices;

    void Draw() override;
        
};

void ReadCircle(ifstream& file, Circle& circle);

void ReadPolygon(ifstream& file, Polygon& polygon);

class DataEntry {
public:
    DataEntry(const string& filename);
    void ReadData(vector<Shape*>& shapes);
private:
    string filename_;
};
Rectangle createBoundingBox(const vector<Shape*>& shapes, double& minX, double& minY, double& maxX, double& maxY, vector<Points>& vertices);
#endif // !ReadFile_H