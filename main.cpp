#include<bits/stdc++.h>

#define FOR(i, a, b) for(int i=(a);i<=(b);i++)

using namespace std;

typedef pair<int, int> pb;

vector<int> array_a;

int main() {
    int n, x, num;

    cin >> n >> x;
    FOR(i, 0, n - 1) {
        cin >> num;
        array_a.push_back(num);
    }

    int i = 0;
    int j = 0;
    int sum = 0;
    int tmp = 0;
    int cant=0;

    tmp = array_a.at(0);
    sum = tmp;
    while (i < n) {
        while (sum < x && j < n - 1) {
            j++;
            sum += array_a.at(j);
        }
        if (sum == x) {
            i++;
            sum = array_a.at(i);
            cant++;
            j = i+1;
        } else {
            i++;
            sum -= abs(tmp);
        }
        if (i < n)
            tmp = array_a.at(i);
    }
    cout << cant << endl;
}
