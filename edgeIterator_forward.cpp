#include <bits/stdc++.h>
#include "timer.h"
using namespace std;
#define ll long long

int vertices,edges;
vector<vector<int> > edge;

ll numTri() {
	ll common = 0;

	for(int i =0; i< vertices ; i++){
		// #pragma omp parallel for reduction(+:common)
		for(int j = 0;j < edge[i].size();j++) {
			int p = 0,q = 0,r = edge[i].size(),s = edge[edge[i][j]].size();
			while(p < r and q < s) {
				if(edge[i][p] == edge[edge[i][j]][q]) {
					p++; q++; common++;
				}
				else if(edge[i][p] < edge[edge[i][j]][q]) p++;
				else q++;
			}
		}
	}
	return common;
}

int main(){
	double start, end;
	scanf("%d %d", &vertices, &edges);
	for(int i=0;i<vertices;i++) {
		vector<int> temp;
		edge.push_back(temp);
	}

	printf("\nReading Input File\n\n");
	GET_TIME(start);
	for (int i = 0 ; i < edges ; i++){
		int node1,node2;
		scanf("%d %d", &node1, &node2 );
		if(node1 < node2){
			edge[node1].push_back(node2);
		}
		else{
			edge[node2].push_back(node1);
		}
	}
	GET_TIME(end);
    printf("Reading Input and adding it to data structure took %e seconds\n\n", end - start);

	printf("Sorting\n");
	GET_TIME(start);
	for(int i = 0; i < vertices ; i++){
		sort(edge[i].begin(),edge[i].end());
	}
	GET_TIME(end);
    printf("Sorting took %e seconds\n\n", end - start);

	printf("Computing Triangles\n" );
	GET_TIME(start);
	cout << numTri() << "\n";
	GET_TIME(end);

	cout << "Time taken for computation  = "<< end - start <<" seconds" << endl;
}
