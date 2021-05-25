//
// Created by Raul.Mosquera on 24/05/2021.
//

#ifndef QUAD_2DUO_TREES_QUAD_TREE_H
#define QUAD_2DUO_TREES_QUAD_TREE_H

#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> coordinate;

class QNode {
public:
    int property;
    QNode *nwNode= nullptr;
    QNode *neNode= nullptr;
    QNode *seNode= nullptr;
    QNode *swNode= nullptr;
    int width=0;
    int height=0;
    int level=0;
    coordinate x_y;

    QNode(vector<vector<int>> data, coordinate x_y, int width, int height) {
        //auto *node = new QNode();

        this->x_y = x_y;
        this->width = width;
        this->height = height;

        if (width == 1 || height == 1) {

            this->property = data.at(x_y.first).at(x_y.second);
            this->level = 1; // new node is initially

        } else {

            this->nwNode = new QNode(data, x_y, width/2, height/2);
            this->neNode = new QNode(data, {x_y.first + width/2, x_y.second},width - width/2, height/2);
            //this->seNode = new QNode(data, {x_y.first, x_y.second + height/2}, width/2, height - height/2);
            //this->swNode = new QNode(data, {x_y.first + width/2, x_y.second + height / 2} ,
            //                         width - width/2, height - height/2);

            this->seNode = new QNode(data, {x_y.first + width/2, x_y.second + height / 2},
                                     width - width/2, height - height/2);
            this->swNode = new QNode(data, {x_y.first, x_y.second + height/2}, width/2, height - height/2);

        }
    }
};

class Quad_tree {
public:
    QNode *root;
    int width;
    int height;
    vector<vector<int>> data;

    Quad_tree(vector<vector<int>> data, int width, int height) {
        this->root = nullptr;
        this->width = width;
        this->height = height;
        this->data = data;
    }

    void build() {
        this->root = new QNode(this->data, {0,0}, this->width, this->height);
    }
    /*void insert(coordinate x_y, int property) {
        this->root = this->_insert(this->root, x_y, property, this->width, this->height);
    }*/

private:
    /*QNode *_insert(QNode *node, coordinate x_y, int property, int _width, int _height) {

        if (_width == 1 && _height == 1) {
            return QNode::newNode(property, x_y);

        } else {
            auto tmp_x = x_y.first % 2;
            auto tmp_y = x_y.second % 2;

            switch (tmp_x) {
                case 0: {
                    switch (tmp_y) {
                        case 0: {
                            node->nwNode = _insert(node->nwNode, x_y, property, _width / 2, _height / 2);
                        }
                            break;
                        case 1: {
                            node->neNode = _insert(node->neNode, x_y, property, _width / 2, _height / 2);
                        }
                            break;
                        default:;
                    };

                }
                    break;
                case 1: {
                    switch (tmp_y) {
                        case 0: {
                            node->seNode = _insert(node->seNode, x_y, property, _width / 2, _height / 2);
                        }
                            break;
                        case 1: {
                            node->swNode = _insert(node->swNode, x_y, property, _width / 2, _height / 2);
                        }
                            break;
                        default:;
                    };
                }
                    break;
                default:;
            }
        }

        return node;
    }*/
};


#endif //QUAD_2DUO_TREES_QUAD_TREE_H
