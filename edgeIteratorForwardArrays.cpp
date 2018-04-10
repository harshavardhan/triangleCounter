#include <bits/stdc++.h>
#include "timer.h"
using namespace std;

int n,m,*edg,*degree,*startNode,*endNode;
vector<pair<int,int> > stEdges;

long long numTri() {
	long long ret = 0;
	for(int i=0;i<m;i++) {
		int u = edg[i],v = edg[m+i];
		int su = startNode[u],eu = endNode[u]; int sv = startNode[v],ev = endNode[v];
		if(su != -1 and sv != -1) {
			while(su <= eu and sv <= ev) {
				if(edg[su+m] == edg[sv+m]) {
					su++; sv++; ret++;
				}
				else if(edg[su+m] > edg[sv+m]) sv++;
				else su++;
			}
		}
	}
	return ret;
}

int main() {
	double start, end;

	scanf("%d %d",&n, &m );
	edg = (int *) malloc(2*m * sizeof(int));
	degree = (int *) malloc(n * sizeof(int));
	startNode = (int *) malloc(n * sizeof(int));
	endNode = (int *) malloc(n * sizeof(int));
	for(int i=0;i<n;i++) {
		degree[i] = -1; startNode[i] = -1; endNode[i] = -1;
	}

	printf("\nReading Input File\n\n");
	GET_TIME(start);
	for(int i = 0 ; i < m ; i++) {
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
		if(degree[stEdges[i].first] > degree[stEdges[i].second]) {
			swap(stEdges[i].first,stEdges[i].second);
		}
	}
	sort(stEdges.begin(),stEdges.end());
	for(int i = 0 ;i < stEdges.size(); i++) {
		edg[i] = stEdges[i].first; edg[i+m] = stEdges[i].second;
		if(startNode[stEdges[i].first] == -1) startNode[stEdges[i].first] = i;
		endNode[stEdges[i].first] = i;
	}
	GET_TIME(end);
    printf("Sorting and Organising Data took %e seconds\n\n", end - start);

	printf("Computing Triangles\n" );
	GET_TIME(start);
	cout << numTri() << "\n";
	GET_TIME(end);
	cout << "Time taken for computation  = "<< end - start <<" seconds" << endl;
}
