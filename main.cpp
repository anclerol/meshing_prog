#include "ReadFile.h"

#include "struct.h"
//min max coordinates






int main()
{
    DataEntry data("grid.txt");
    vector<Shape*>shapes;
    data.ReadData(shapes);

    double minX = numeric_limits<double>::max();
    double minY = numeric_limits<double>::max();
    double maxX = numeric_limits<double>::min();
    double maxY = numeric_limits<double>::min();

    Rectangle boundingBox = createBoundingBox(shapes, minX, minY, maxX, maxY);
    for (const auto& shape : shapes) {
        shape->Draw();
    }

    cout << boundingBox.minX << " " << boundingBox.minY << endl;
    cout << boundingBox.maxX << " " << boundingBox.maxY << endl;

    for (const auto& shape : shapes) {
        delete shape;
    }

    return 0;
}
