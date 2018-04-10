#include <bits/stdc++.h>
#include "timer.h"
using namespace std;

int vertices,edges;
vector<vector<int> > edge;
vector<pair<int,int> > stEdges;
int * degree;

long long numTri() {
	long long ret = 0;
	for(int i=0; i< vertices ; i++){
		for(int j = 0;j < edge[i].size();j++) {
			int common  = 0;
			int p = 0,q = 0,r = edge[i].size(),s = edge[edge[i][j]].size();
			while(p < r and q < s) {
				if(edge[i][p] == edge[edge[i][j]][q]) {
					p++; q++; common++;
				}
				else if(edge[i][p] < edge[edge[i][j]][q]) p++;
				else q++;
			}
			ret += common;
		}
	}
	return ret;
}

int main(){
	double start, end;
	scanf("%d %d", &vertices, &edges);
	for(int i=0;i<vertices;i++) {
		vector<int> temp;
		edge.push_back(temp);
	}
	degree = (int *) malloc(vertices * sizeof(int));
	memset(degree,0,sizeof(degree));

	printf("\nReading Input File\n\n");
	GET_TIME(start);
	for(int i = 0 ; i < edges ; i++){
		int node1,node2;
		scanf("%d %d", &node1, &node2 );
		stEdges.push_back(make_pair(node1,node2));
		degree[node1]++; degree[node2]++;
	}
	GET_TIME(end);
    printf("Reading Input and adding it to data structure took %e seconds\n\n", end - start);

	printf("Sorting and Organising data\n");
	GET_TIME(start);
	for(int i = 0 ;i < stEdges.size(); i++) {
		if(degree[stEdges[i].first] <= degree[stEdges[i].second]) {
			edge[stEdges[i].first].push_back(stEdges[i].second);
		}
		else {
			edge[stEdges[i].second].push_back(stEdges[i].first);
		}
	}
	for(int i = 0; i < vertices ; i++){
		sort(edge[i].begin(),edge[i].end());
	}
	GET_TIME(end);
    printf("Sorting and Organising Data took %e seconds\n\n", end - start);

	printf("Computing Triangles\n" );
	GET_TIME(start);
	cout << numTri() << "\n";
	GET_TIME(end);
	cout << "Time taken for computation  = "<< end - start <<" seconds" << endl;
}
