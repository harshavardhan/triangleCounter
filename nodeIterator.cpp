#include <bits/stdc++.h>
#include "timer.h"
using namespace std;

vector<set<int>> V;
long long int numOfTriangles;
int n, m;
void readFile(){
    int n1, n2;
    for (size_t i = 0; i < m; i++) {
        scanf("%d %d", &n1, &n2);
        V[n1].insert(n2);
        // V[n2].insert(n1);
    }
}

void countTriangles(){
    set<int>::iterator j, k;
    for (size_t i = 0; i < n; i++) {
        for (j = V[i].begin(); j != V[i].end(); j++) {
            for (k = j; k != V[i].end(); k++) {
                if(k != j){
                    if(*j < *k)
                        if(V[*j].find(*k) != V[*j].end()){
                            numOfTriangles ++;
                        }
                    else
                        if(V[*k].find(*j) != V[*k].end()){
                            numOfTriangles ++;
                        }
                }
            }
        }
    }
}

int main(){
    double start, end;
    scanf("%d %d", &n, &m);
    for (size_t i = 0; i < n; i++) {
        set<int> X;
        V.push_back(X);
    }

    printf("\nReading Input File\n\n");
    GET_TIME(start);
    readFile();
    GET_TIME(end);
    printf("Reading Input and adding it to data took %e seconds\n\n", end - start);

    printf("Starting Computation for counting Triangles\n\n");
    GET_TIME(start);
    countTriangles();
    GET_TIME(end);

    cout << "Number of triangles = " << numOfTriangles <<endl<<endl;
    cout << "Time taken for computation  = "<< end - start <<" seconds" << endl;
}
