#include "quadtree.h"

QuadTreeNode :: QuadTreeNode(const Rectangle& boundary) : boundary(boundary) {
        for (int i = 0; i < 4; ++i) {
            children[i] = nullptr;
        }
    }

QuadTreeNode ::   ~QuadTreeNode() {
        for (int i = 0; i < 4; ++i) {
            delete children[i];
        }
    }

    bool QuadTreeNode:: isLeafNode() const {
        return children[0] == nullptr;
    }

    bool QuadTreeNode:: insert(const Points& vertices) {
        if (!isInsideBoundary(vertices)) {
            return false;
        }

        if (points.size() < MAX_OBJECTS_PER_NODE) {
            points.push_back(vertices);
            return true;
        }

        if (isLeafNode()) {
            split();
        }

        for (int i = 0; i < 4; ++i) {
            if (children[i]->insert(vertices)) {
                return true;
            }
        }

        return false;
    }

    void QuadTreeNode::split() {
        double subWidth = (boundary.maxX - boundary.minX) / 2;
        double subHeight = (boundary.maxY - boundary.minY) / 2;

        children[0] = new QuadTreeNode({ boundary.minX, boundary.minY, boundary.minX + subWidth, boundary.minY + subHeight });
        children[1] = new QuadTreeNode({ boundary.minX + subWidth, boundary.minY, boundary.maxX, boundary.minY + subHeight });
        children[2] = new QuadTreeNode({ boundary.minX, boundary.minY + subHeight, boundary.minX + subWidth, boundary.maxY });
        children[3] = new QuadTreeNode({ boundary.minX + subWidth, boundary.minY + subHeight, boundary.maxX, boundary.maxY });
    }

    bool QuadTreeNode::isInsideBoundary(const Points& point) const {
        return point.x >= boundary.minX && point.x <= boundary.maxX && point.y >= boundary.minY && point.y <= boundary.maxY;
    }

    Rectangle createBoundingBox(const vector<Shape*>& shapes, double& minX, double& minY, double& maxX, double& maxY, vector<Points>& vertices) {
        Rectangle boundingBox = { DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX };

        for (const Shape* shape : shapes) {
            if (const Circle* circle = dynamic_cast<const Circle*>(shape)) {
                double circleMinX = circle->x - circle->radius;
                double circleMinY = circle->y - circle->radius;
                double circleMaxX = circle->x + circle->radius;
                double circleMaxY = circle->y + circle->radius;

                minX = min(minX, circleMinX);
                minY = min(minY, circleMinY);
                maxX = max(maxX, circleMaxX);
                maxY = max(maxY, circleMaxY);
            }
            else if (const Polygon* polygon = dynamic_cast<const Polygon*>(shape)) {
                for (const Points& vertex : polygon->vertices) {
                    minX = min(minX, vertex.x);
                    minY = min(minY, vertex.y);
                    maxX = max(maxX, vertex.x);
                    maxY = max(maxY, vertex.y);
                }
            }
        }

        boundingBox.minX = min(minX, boundingBox.minX);
        boundingBox.minY = min(minY, boundingBox.minY);
        boundingBox.maxX = max(maxX, boundingBox.maxX);
        boundingBox.maxY = max(maxY, boundingBox.maxY);

        Rectangle boundary = { boundingBox.minX, boundingBox.minY, boundingBox.maxX, boundingBox.maxY };
        QuadTreeNode* root = new QuadTreeNode(boundary);
        for (const Points& vertex : vertices) {
            if (!root->insert(vertex)) {
                std::cout << "Failed to insert point (" << vertex.x << ", " << vertex.y << ")\n";
            }
        }

        delete root;
        return boundingBox;
    }

