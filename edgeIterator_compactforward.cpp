#include <bits/stdc++.h>
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
			// vector<int> v3;
			// set_intersection(edge[i].begin(),edge[i].end(),edge[edge[i][j]].begin(),edge[edge[i][j]].end(),back_inserter(v3));
			// ret += v3.size();
		}
	}
	return ret;
}

int main(){
	cin >> vertices >> edges;
	for(int i=0;i<vertices;i++) {
		vector<int> temp;
		edge.push_back(temp);
	}
	degree = (int *) malloc(vertices * sizeof(int));
	memset(degree,0,sizeof(degree));
	for(int i = 0 ; i < edges ; i++){
		int node1,node2;
		cin >> node1 >> node2;
		stEdges.push_back(make_pair(node1,node2));
		degree[node1]++; degree[node2]++;
	}
	for(int i = 0 ;i < stEdges.size(); i++) {
		if(degree[stEdges[i].first] <= degree[stEdges[i].second]) {
			edge[stEdges[i].first].push_back(stEdges[i].second);
		}
		else {
			edge[stEdges[i].second].push_back(stEdges[i].first);	
		}
	}
	const clock_t begin_time = clock();
	for(int i = 0; i < vertices ; i++){
		sort(edge[i].begin(),edge[i].end());
	}
	cout << numTri() << "\n";
	const clock_t end_time = clock();
	cout << "Time taken " << float(end_time - begin_time)/CLOCKS_PER_SEC << "seconds" << endl;
}