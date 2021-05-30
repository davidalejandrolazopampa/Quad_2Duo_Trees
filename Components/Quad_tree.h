//
// Created by Raul.Mosquera on 24/05/2021.
//

#ifndef QUAD_2DUO_TREES_QUAD_TREE_H
#define QUAD_2DUO_TREES_QUAD_TREE_H

#include "QNode.h"

class Quad_tree {
public:
    QNode *root;
    int width;
    int height;
    int maxProperty;
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

    Quad_tree(vector<vector<int>> data, int width, int height, int maxProperty) {
        this->root = nullptr;
        this->width = width;
        this->height = height;
        this->data = data;
        this->fileName = "";
        this->maxProperty = maxProperty;
    }

    void build() {
        this->root = new QNode(this->data, {0, 0}, this->width, this->height, this->maxProperty);
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

        this->archivo << this->maxProperty << endl;
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

        this->file >> this->maxProperty;
        getline(this->file, linea);
        getline(this->file, linea);
        QNode tmp(linea);
        this->width = tmp.width;
        this->height = tmp.height;

        this->root = new QNode(this->file, tmp.property, tmp.x_y, this->width, this->height,
                               this->maxProperty);

        this->file.clear();
        this->file.seekg(0);
        getline(this->file, linea);

        this->data.resize(this->height);

        for(int i=0; i<this->height;i++) {
            this->data.at(i).resize(this->width);
        }

        while(getline(this->file, linea)) {
            QNode tmp2(linea);

            if(tmp2.property >= 0 && tmp2.property <= this->maxProperty) {
                auto col = tmp2.x_y.first;
                auto row = tmp2.x_y.second;

                for (int i = row; i < row + tmp2.height; i++) {
                    for (int j = col; j < col + tmp2.width; j++) {
                        this->data.at(i).at(j) = tmp2.property;
                    }
                }
            }
        }

        if (this->file.is_open())
            this->file.close();


        return 0;
    }

    int export_2_pgm(string fname_pgm) {

        try {
            if (fname_pgm == "")
                throw "Saving Not possible, no filename";
        } catch (...) {
            std::cerr << "No filename" << '\n';
        }

        //file = fstream();

        ofstream file(fname_pgm, std::ios_base::binary | std::ios_base::out);

        file << "P2\n";
        file << "# feepv2.pgm\n";
        file << this->width << " " << this->height << "\n" << this->maxProperty << "\n";

        for(int i=0;i<this->height;i++) {
            for(int j=0;j<this->width;j++) {
                if(j == 0)
                    file << to_string(this->data.at(i).at(j));
                else
                    file << setw(3) << to_string(this->data.at(i).at(j));
            }

            if(i != this->height-1)
                file << "\n";
        }

        if (!file.is_open()) {
            cout << " File error " << endl;
            return -1;
        }

        file << std::flush;

        if (file.is_open())
            file.close();

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
