//
// Created by Raul.Mosquera on 24/05/2021.
//

#ifndef QUAD_2DUO_TREES_QUAD_TREE_H
#define QUAD_2DUO_TREES_QUAD_TREE_H

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

    QNode(vector<vector<int>> data, coordinate x_y, int width, int height) {
        //auto *node = new QNode();

        this->x_y = x_y;
        this->width = width;
        this->height = height;

        if (width == 1 || height == 1) {

            this->property = data.at(x_y.second).at(x_y.first);
            this->level = 1; // new node is initially

        } else {

            this->nwNode = new QNode(data, x_y, width / 2, height / 2);
            this->neNode = new QNode(data, {x_y.first + width / 2, x_y.second}, width - width / 2, height / 2);
            this->seNode = new QNode(data, {x_y.first + width / 2, x_y.second + height / 2}, width - width / 2,
                                     height - height / 2);
            this->swNode = new QNode(data, {x_y.first, x_y.second + height / 2}, width / 2, height - height / 2);

            //this->seNode = new QNode(data, {x_y.first, x_y.second + height/2}, width/2, height - height/2);
            //this->swNode = new QNode(data, {x_y.first + width/2, x_y.second + height / 2} ,width - width/2, height - height/2);

            check_and_merge();
        }
    }

    QNode(fstream &file, int property, coordinate x_y, int width, int height) {
        string linea;

        this->x_y = x_y;
        this->width = width;
        this->height = height;
        this->property = property;

        if(property == 0 || property == 1) {
            //this->property = property_null;
            //this->level
        } else {

            getline(file, linea);
            if(linea != "") {
                QNode tmp(linea);
                this->nwNode = new QNode(file, tmp.property, tmp.x_y, tmp.width, tmp.height);
            }

            getline(file, linea);
            if(linea != "") {
                QNode tmp(linea);
                this->neNode = new QNode(file, tmp.property, tmp.x_y, tmp.width, tmp.height);
            }

            getline(file, linea);
            if(linea != "") {
                QNode tmp(linea);
                this->seNode = new QNode(file, tmp.property, tmp.x_y, tmp.width, tmp.height);
            }

            getline(file, linea);
            if(linea != "") {
                QNode tmp(linea);
                this->swNode = new QNode(file, tmp.property, tmp.x_y, tmp.width, tmp.height);
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
                    this->height = stoi(tmp.substr(pos+1, tmp.length()));
                } break;
                case 1: {
                    string tmp(pch);
                    auto pos = tmp.find(',');
                    this->x_y.first = stoi(tmp.substr(0, pos));
                    this->x_y.second = stoi(tmp.substr(pos+1, tmp.length()));
                } break;
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
        else {
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

class Quad_tree {
public:
    QNode *root;
    int width;
    int height;
    vector<vector<int>> data;
    string fileName;
    ofstream archivo;
    fstream file;
    char mode;

public:
    Quad_tree() {
        this->root = nullptr;
        this->width = 0;
        this->height = 0;
        this->fileName = "";
    }

    Quad_tree(vector<vector<int>> data, int width, int height) {
        this->root = nullptr;
        this->width = width;
        this->height = height;
        this->data = data;
        this->fileName = "";
    }

    void build() {
        this->root = new QNode(this->data, {0, 0}, this->width, this->height);
    }

    void print() {
        bool new_line = true;
        if (!this->root)
            return;

        /*if (new_line)
            cout << "(" << this->root->width << "x" << this->root->height << ") " << this->root->property << endl;
        else
            cout << "(" << this->root->width << "x" << this->root->height << ") " << this->root->property << " ";
        */
        this->_print(this->root, new_line);
    }

    int save() {
        bool new_line = true;
        try {
            if (this->fileName == "")
                throw "Saving Not possible, no filename";
        } catch (...) {
            std::cerr << "No filename" << '\n';
        }
        this->mode = 'S';

        if (this->mode == 'S')
            archivo.open(this->fileName, ios::out);

        this->_print(this->root, new_line);

        if (this->mode == 'S')
            archivo.close();
    }

    int load() {
        string linea;

        try {
            if (this->fileName == "")
                throw;
        } catch (...) {
            std::cerr << "No filename" << '\n';
        }

        this->file = fstream();

        this->file.open(this->fileName, ios::in);

        if (!this->file.is_open()) {
            cout << " File error " << endl;
            return -1;
        }

        getline(this->file, linea);
        QNode tmp(linea);

        this->root = new QNode(this->file, tmp.property, tmp.x_y, tmp.width, tmp.height);

        if (this->file.is_open())
            this->file.close();

        return 0;
    }

private:

    void _print(QNode *node, bool new_line = false) {
        string line="";
        if (node != nullptr) {
            //if(node->property != property_null)
            if (new_line) {
                line = to_string(node->width) + "x" + to_string(node->height) + ":" + to_string(node->x_y.first)
                        + "," + to_string(node->x_y.second) +":"+ to_string(node->property);
                if (this->mode == 'S')
                    this->archivo << line << endl;
                else
                    cout << line << endl;
            } else {
                if (this->mode == 'S')
                    this->archivo << "(" << node->width << "x" << node->height << ") " << node->property << " ";
                else
                    cout << "(" << node->width << "x" << node->height << ") " << node->property << " ";
            }

            _print(node->nwNode, new_line);
            _print(node->neNode, new_line);
            _print(node->seNode, new_line);
            _print(node->swNode, new_line);
        }
    }
};


#endif //QUAD_2DUO_TREES_QUAD_TREE_H
