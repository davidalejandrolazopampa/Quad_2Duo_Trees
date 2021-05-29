//
// Created by Raul.Mosquera on 23/05/2021.
//

#ifndef EDA_TREE_TESTER_H
#define EDA_TREE_TESTER_H

#include "../Components/Quad_tree.h"

class metadata {
public:
    vector<int> data;
    int weight;
    int height;
    int max_property;

    metadata() {

    }

    metadata(const metadata &meta) {
        this->data = meta.data;
    }
};

class tester {
public:
    vector<int> data;
    int weight;
    int height;
    int max_property;

    void static test_8x8() {
        vector<vector<int>> pmg;

        pmg.resize(8);
        pmg.at(0).push_back(0);
        pmg.at(0).push_back(0);
        pmg.at(0).push_back(0);
        pmg.at(0).push_back(0);
        pmg.at(0).push_back(0);
        pmg.at(0).push_back(0);
        pmg.at(0).push_back(0);
        pmg.at(0).push_back(0);

        pmg.at(1).push_back(0);
        pmg.at(1).push_back(0);
        pmg.at(1).push_back(0);
        pmg.at(1).push_back(0);
        pmg.at(1).push_back(0);
        pmg.at(1).push_back(0);
        pmg.at(1).push_back(0);
        pmg.at(1).push_back(0);

        pmg.at(2).push_back(0);
        pmg.at(2).push_back(0);
        pmg.at(2).push_back(0);
        pmg.at(2).push_back(0);
        pmg.at(2).push_back(1);
        pmg.at(2).push_back(1);
        pmg.at(2).push_back(1);
        pmg.at(2).push_back(0);

        pmg.at(3).push_back(0);
        pmg.at(3).push_back(0);
        pmg.at(3).push_back(0);
        pmg.at(3).push_back(0);
        pmg.at(3).push_back(1);
        pmg.at(3).push_back(1);
        pmg.at(3).push_back(0);
        pmg.at(3).push_back(0);

        pmg.at(4).push_back(1);
        pmg.at(4).push_back(1);
        pmg.at(4).push_back(1);
        pmg.at(4).push_back(1);
        pmg.at(4).push_back(1);
        pmg.at(4).push_back(1);
        pmg.at(4).push_back(0);
        pmg.at(4).push_back(0);

        pmg.at(5).push_back(1);
        pmg.at(5).push_back(1);
        pmg.at(5).push_back(1);
        pmg.at(5).push_back(1);
        pmg.at(5).push_back(1);
        pmg.at(5).push_back(1);
        pmg.at(5).push_back(0);
        pmg.at(5).push_back(0);

        pmg.at(6).push_back(1);
        pmg.at(6).push_back(1);
        pmg.at(6).push_back(1);
        pmg.at(6).push_back(1);
        pmg.at(6).push_back(0);
        pmg.at(6).push_back(0);
        pmg.at(6).push_back(0);
        pmg.at(6).push_back(0);

        pmg.at(7).push_back(1);
        pmg.at(7).push_back(1);
        pmg.at(7).push_back(1);
        pmg.at(7).push_back(1);
        pmg.at(7).push_back(0);
        pmg.at(7).push_back(0);
        pmg.at(7).push_back(0);
        pmg.at(7).push_back(1);

        Quad_tree qTree(pmg, 8, 8);

        qTree.build();
        qTree.print();

        qTree.fileName = "../result/qtree_8_8.txt";

        qTree.save();
    }

    void static test_read_8x8() {
        Quad_tree qTree;
        qTree.fileName = "../result/qtree_8_8.txt";
        auto res = qTree.load();
        cout << "read from file " <<endl;
        if(res == 0)
            qTree.print();

    }

    void test_pgm() {
        readFromFile("../dataset/dragon.pgm");

    }

private:
    void readFromFile(const string& fileNameIn) {
    //vector<int> *readFromFile(const string& fileNameIn) {
        vector<int> tmp;
        int num;
        int weight;
        int height;
        int max_property;
        fstream file;
        string linea;
        file = fstream();

        file.open(fileNameIn, ios::in);

        if (!file.is_open())
            cout << " File error " << endl;

        getline(file, linea);

        getline(file, linea);

        file >> weight >> height;
        file >> max_property;

        //tmp.resize(height);
        this->data.reserve(height*weight);
        for(int i=0; i<height;i++) {
            for(int j=0; j<weight;j++) {
                file >> num;
                this->data.emplace_back(num);
            }
        }

        if (file.is_open())
            file.close();

        auto meta = new metadata();
        meta->data = tmp;
        meta->height = height;
        meta->weight = weight;
        meta->max_property = max_property;

    }
};


#endif //EDA_TREE_TESTER_H
