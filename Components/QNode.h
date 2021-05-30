//
// Created by Raul.Mosquera on 29/05/2021.
//

#ifndef QUAD_2DUO_TREES_QNODE_H
#define QUAD_2DUO_TREES_QNODE_H

#include<bits/stdc++.h>
#include<iostream>
#include<fstream>

using namespace std;

typedef pair<int, int> coordinate;

const int property_null = -1;

class QNode {
public:
    int property = property_null;
    QNode *nwNode = nullptr;
    QNode *neNode = nullptr;
    QNode *seNode = nullptr;
    QNode *swNode = nullptr;
    int width = 0;
    int height = 0;
    int level = 0;
    coordinate x_y;

    QNode(vector<vector<int>> data, coordinate x_y, int width, int height, int maxProperty) {
        //auto *node = new QNode();

        this->x_y = x_y;
        this->width = width;
        this->height = height;

        if (width == 1 || height == 1) {
            int sum = 0, cells;
            auto col = x_y.first;
            auto row = x_y.second;

            for (int i = row; i < row + height; i++)
                for (int j = col; j < col + width; j++)
                    sum += data.at(i).at(j);

            if (width == height)
                cells = 1;
            else if (width > height)
                cells = width;
            else
                cells = height;

            this->property = sum / cells;
            //this->property = data.at(x_y.second).at(x_y.first);
            this->level = 1; // new node is initially
            cout << col <<"x" << row << " " << "w="<< width << " h="<<height<< " "<<this->property <<endl;
        } else {

            this->nwNode = new QNode(data, x_y, width / 2, height / 2, maxProperty);
            this->neNode = new QNode(data, {x_y.first + width / 2, x_y.second}, width - width / 2, height / 2,
                                     maxProperty);
            this->seNode = new QNode(data, {x_y.first + width / 2, x_y.second + height / 2}, width - width / 2,
                                     height - height / 2, maxProperty);
            this->swNode = new QNode(data, {x_y.first, x_y.second + height / 2}, width / 2, height - height / 2,
                                     maxProperty);

            //this->seNode = new QNode(data, {x_y.first, x_y.second + height/2}, width/2, height - height/2);
            //this->swNode = new QNode(data, {x_y.first + width/2, x_y.second + height / 2} ,width - width/2, height - height/2);

            check_and_merge();
        }
    }

    QNode(fstream &file, int property, coordinate x_y, int width, int height, int maxProperty) {
        string linea;

        this->x_y = x_y;
        this->width = width;
        this->height = height;
        this->property = property;

        if (property >= 0 && property <= maxProperty) {
            //this->property = property_null;
            //this->level
        } else {

            getline(file, linea);
            if (linea != "") {
                QNode tmp(linea);
                this->nwNode = new QNode(file, tmp.property, tmp.x_y, tmp.width, tmp.height, maxProperty);
            }

            getline(file, linea);
            if (linea != "") {
                QNode tmp(linea);
                this->neNode = new QNode(file, tmp.property, tmp.x_y, tmp.width, tmp.height, maxProperty);
            }

            getline(file, linea);
            if (linea != "") {
                QNode tmp(linea);
                this->seNode = new QNode(file, tmp.property, tmp.x_y, tmp.width, tmp.height, maxProperty);
            }

            getline(file, linea);
            if (linea != "") {
                QNode tmp(linea);
                this->swNode = new QNode(file, tmp.property, tmp.x_y, tmp.width, tmp.height, maxProperty);
            }
        }
    }

    QNode(string line) {
        coordinate x_y;
        char str[line.length() + 1];
        strcpy(str, line.c_str());

        char *pch;
        pch = strtok(str, ":");

        int index = 0;
        while (pch != NULL) {
            switch (index) {
                case 0: {
                    string tmp(pch);
                    auto pos = tmp.find('x');
                    this->width = stoi(tmp.substr(0, pos));
                    this->height = stoi(tmp.substr(pos + 1, tmp.length()));
                }
                    break;
                case 1: {
                    string tmp(pch);
                    auto pos = tmp.find(',');
                    this->x_y.first = stoi(tmp.substr(0, pos));
                    this->x_y.second = stoi(tmp.substr(pos + 1, tmp.length()));
                }
                    break;
                case 2:
                    this->property = atoi(pch);
                    break;
            }
            pch = strtok(NULL, ":");
            index++;
        }
    }

    void check_and_merge() {
        set<int> tmp;

        tmp.insert(this->nwNode->property);
        tmp.insert(this->neNode->property);
        tmp.insert(this->seNode->property);
        tmp.insert(this->swNode->property);

        auto size = tmp.size();
        if (size != 1)
            return;
        else if (size == 1 && tmp.find(property_null) == tmp.end()) {
            auto proper = this->nwNode->property;

            this->property = proper;

            delete this->nwNode;
            delete this->neNode;
            delete this->seNode;
            delete this->swNode;
            this->nwNode = nullptr;
            this->neNode = nullptr;
            this->seNode = nullptr;
            this->swNode = nullptr;
        }

    }
};


#endif //QUAD_2DUO_TREES_QNODE_H
