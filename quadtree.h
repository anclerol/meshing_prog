#pragma once
#ifndef QUADTREE_H

#define QUADTREE_H

#include "struct.h"
#include "ReadFile.h"

const int MAX_OBJECTS_PER_NODE = 4; // Максимальное количество объектов в узле


class QuadTreeNode {
public:
    Rectangle boundary;
    std::vector<Points> points;
    QuadTreeNode* children[4];

    QuadTreeNode(const Rectangle& boundary);

    ~QuadTreeNode();

    bool isLeafNode() const;

    bool insert(const Points& vertecis);

    void split();

    bool isInsideBoundary(const Points& vertecis) const;
};
Rectangle createBoundingBox(const vector<Shape*>& shapes, double& minX, double& minY, double& maxX, double& maxY, vector<Points>& vertices);
#endif // !QUASDTREE_H
