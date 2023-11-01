#include "ReadFile.h"



    void  Circle :: Draw()  {
        cout << "Drawing circle with r: " << radius << " x: " << x << " y: " << y << endl;
    }


    void  Polygon :: Draw() {
        cout << "Drawing polygon with: " << vertices.size() << " vertices " << endl;
        for (const auto& vertex : vertices) {
            cout << "x: " << vertex.x << " y: " << vertex.y << endl;
        }
    }


void ReadCircle(ifstream& file, Circle& circle) {
    file >> circle.radius;
    file >> circle.x >> circle.y;
}
void ReadPolygon(ifstream& file, Polygon& polygon) {
    int num_vertices;
    file >> num_vertices;
    if (num_vertices < 3) {
        cerr << "A polygon must have at least 3 vertices " << endl;
    }
    polygon.vertices.resize(num_vertices);
    for (int i = 0; i < num_vertices; ++i) {
        file >> polygon.vertices[i].x >> polygon.vertices[i].y;
    }
}


DataEntry :: DataEntry(const string& filename) : filename_(filename) {};
    void DataEntry :: ReadData(vector<Shape*>& shapes) {
        ifstream input_file(filename_);
        if (!input_file.is_open()) {
            cerr << "Unable to read file " << filename_ << endl;
            return;
        }
        string figure_type;
        while (input_file >> figure_type) {
            if (figure_type == "circle") {
                Circle* circle = new Circle;
                ReadCircle(input_file, *circle);
                shapes.push_back(circle);
            }
            else if (figure_type == "polygon") {
                Polygon* polygon = new Polygon;
                ReadPolygon(input_file, *polygon);
                shapes.push_back(polygon);
            }
        }
        cout << "File readed: " << filename_ << endl;
        input_file.close();
    }
