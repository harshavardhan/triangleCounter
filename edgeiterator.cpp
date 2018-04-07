#include <bits/stdc++.h>
using namespace std;
#define ll long long

int vertices,edges;
vector<vector<int> > edge;

ll numTri() {
	ll ret = 0;
	for(int i =0; i< vertices ; i++){
		for(int j = 0;j < edge[i].size();j++) {
			vector<int> v3;
			set_intersection(edge[i].begin(),edge[i].end(),edge[edge[i][j]].begin(),edge[edge[i][j]].end(),back_inserter(v3));
			ret += v3.size();
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
	for (int i = 0 ; i < edges ; i++){
		int node1,node2;
		cin >> node1 >> node2;
		edge[node1].push_back(node2);
		edge[node2].push_back(node1);
	
	}
	for(int i = 0; i < vertices ; i++){
		sort(edge[i].begin(),edge[i].end());
	}
	const clock_t begin_time = clock();
	cout << numTri() << "\n";
	const clock_t end_time = clock();
	cout << "Time taken " << float(end_time - begin_time)/CLOCKS_PER_SEC << "seconds" << endl;
}