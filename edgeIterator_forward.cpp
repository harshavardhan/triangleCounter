#include <bits/stdc++.h>
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
			
			// vector<int> v3;
			// set_intersection(edge[i].begin(),edge[i].end(),edge[edge[i][j]].begin(),edge[edge[i][j]].end(),back_inserter(v3));
			// ret += v3.size();
		}
	}
	return common;
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
		if(node1 < node2){
			edge[node1].push_back(node2);
		}
		else{
			edge[node2].push_back(node1);
		}
		
	
	}
	for(int i = 0; i < vertices ; i++){
		sort(edge[i].begin(),edge[i].end());
	}
	const clock_t begin_time = clock();
	cout << numTri() << "\n";
	const clock_t end_time = clock();
	cout << "Time taken " << float(end_time - begin_time)/CLOCKS_PER_SEC << "seconds" << endl;
}