#include <bits/stdc++.h>
using namespace std;
#define READ_INT(n) {char c; n = getchar_unlocked() - '0'; while((c = getchar_unlocked()) >= '0') n = (n << 3) + (n << 1) + c - '0';}

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
	READ_INT(n); READ_INT(m);
	edg = (int *) malloc(2*m * sizeof(int));
	degree = (int *) malloc(n * sizeof(int));
	startNode = (int *) malloc(n * sizeof(int));
	endNode = (int *) malloc(n * sizeof(int));
	for(int i=0;i<n;i++) {
		degree[i] = -1; startNode[i] = -1; endNode[i] = -1;
	}
	for(int i = 0 ; i < m ; i++) {
		int node1,node2;
		READ_INT(node1); READ_INT(node2);
		stEdges.push_back(make_pair(node1,node2));
		degree[node1]++; degree[node2]++;
	}
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
	const clock_t begin_time = clock();
	cout << numTri() << "\n";
	const clock_t end_time = clock();
	cout << "Time taken " << float(end_time - begin_time)/CLOCKS_PER_SEC << "seconds" << endl;
}