#include <bits/stdc++.h>
using namespace std;

vector<set<int>> V;
long int n, m, numOfTriangles;

void readFile(){
    int n1, n2;
    for (size_t i = 0; i < m; i++) {
        cin >> n1 >> n2;
        V[n1].insert(n2);
        V[n2].insert(n1);
    }
}

void countTriangles(){
    set<int>::iterator j, k;
    for (size_t i = 0; i < n; i++) {
        for (j = V[i].begin(); j != V[i].end(); j++) {
            for (k = j; k != V[i].end(); k++) {
                if(k != j)
                    if(V[*j].find(*k) != V[*j].end())
                        numOfTriangles ++;
            }
        }
    }
}

int main(){
    cin >>n >>m;
    for (size_t i = 0; i < n; i++) {
        set<int> X;
        V.push_back(X);
    }
    readFile();
    const clock_t begin_time = clock();
    countTriangles();
    const clock_t end_time = clock();

    cout << "Number of triangles = " << numOfTriangles/3 <<endl;
    cout << "Time taken is  = " << float(end_time - begin_time)/CLOCKS_PER_SEC << "seconds" << endl;
}
