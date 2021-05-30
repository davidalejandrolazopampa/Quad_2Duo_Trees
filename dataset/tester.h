//
// Created by Raul.Mosquera on 23/05/2021.
//

#ifndef EDA_TREE_TESTER_H
#define EDA_TREE_TESTER_H

#include "../Components/Quad_tree.h"

class tester {
public:
    vector<vector<int>> data;
    int width;
    int height;
    int maxProperty;

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

        Quad_tree qTree(pmg, 8, 8, 1);

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

    void test_pgm_to_txt() {
        readFromPGM("../dataset/dragon.pgm");

        Quad_tree qTree(this->data, this->width, this->height, this->maxProperty);

        qTree.build();
        //qTree.print();
        qTree.fileName = "../result/dragon.txt";
        int res = qTree.save();
        if(res == 0)
            cout << "file saved"<<endl;
        else
            cout << "file not saved"<<endl;
    }

    void test_export_fefp() {
        Quad_tree qTree;
        qTree.fileName = "../result/fefp.txt";
        auto res = qTree.load();
        if(res == 0) {
            cout << "read from file " <<endl;
            qTree.print();
        }

        string fname = "../result/feepv2.pgm";
        res = qTree.export_2_pgm(fname);
        if(res == 0)
            cout << fname << " exported to PGM correctly" << endl;
        else
            cout << fname << " error "<<endl;
    }

private:
    void readFromPGM(const string& fileNameIn) {
    //vector<int> *readFromPGM(const string& fileNameIn) {
        vector<int> tmp;
        int num;
        //int weight;
        //int height;
        //int maxProperty;
        fstream file;
        string linea;
        file = fstream();

        file.open(fileNameIn, ios::in);

        if (!file.is_open())
            cout << " File error " << endl;

        getline(file, linea);
        getline(file, linea);

        file >> this->width >> this->height;
        file >> this->maxProperty;

        //tmp.resize(height);
        this->data.resize(this->height);
        for(int i=0; i<this->height;i++) {
            tmp.clear();
            for(int j=0; j<this->width; j++) {
                file >> num;
                tmp.emplace_back(num);
            }
            this->data.at(i) = tmp;
        }

        if (file.is_open())
            file.close();

        /*auto meta = new metadata();
        meta->data = tmp;
        meta->height = height;
        meta->weight = weight;
        meta->maxProperty = maxProperty;*/
    }
};


#endif //EDA_TREE_TESTER_H
