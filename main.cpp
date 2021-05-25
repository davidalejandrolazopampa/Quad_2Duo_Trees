#include "Quad_tree.h"

int main() {
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

    return 0;
}
