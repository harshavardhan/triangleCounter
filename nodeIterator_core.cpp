#include <bits/stdc++.h>
#include "timer.h"
using namespace std;

vector<set<int> > V;
set <pair<int,int> > st;

int * degree;

long long int numOfTriangles;
int n, m;

void readFile() {
    int n1, n2;
    for (size_t i = 0; i < m; i++) {
        scanf("%d %d", &n1, &n2);
        V[n1].insert(n2);
        V[n2].insert(n1);
        degree[n1]++; degree[n2]++;
    }
    for(int i=0;i<n;i++) {
        if(degree[i] != 0) st.insert(make_pair(degree[i],i));
    } 
}

void countTriangles() {
    while(st.size() != 0) {
        pair<int,int> top = *st.begin(); st.erase(top);
        int i = top.second; 
        set<int>::iterator j,k;   
        for (j = V[i].begin(); j != V[i].end(); j++) {
            for (k = j; k != V[i].end(); k++) {
                if(k != j) {
                    if(V[*j].find(*k) != V[*j].end()) {
                        numOfTriangles++;
                    }
                }
            }
        }
        for (j = V[i].begin(); j != V[i].end(); j++) {
            st.erase(make_pair(degree[*j],*j));
            V[*j].erase(i);
            degree[*j]--;
            if(degree[*j] != 0) st.insert(make_pair(degree[*j],*j));
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
    degree = (int *) malloc(n * sizeof(int));
    memset(degree,0,sizeof(degree));
    printf("\nReading Input File\n\n");
    GET_TIME(start);
    readFile();
    GET_TIME(end);
    printf("Reading Input and adding it to data took %e seconds\n\n", end - start);

    printf("Starting Computation for counting Triangles\n\n");
    GET_TIME(start);
    countTriangles();
    GET_TIME(end);

    cout << "Number of triangles = " << numOfTriangles <<endl;
    cout << "Time taken for computation  = "<< end - start <<" seconds" << endl;
}