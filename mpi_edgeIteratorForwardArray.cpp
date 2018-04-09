#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;

#define READ_INT(n) {char c; n = getchar_unlocked() - '0'; while((c = getchar_unlocked()) >= '0') n = (n << 3) + (n << 1) + c - '0';}

int id, size;
int n,m,*edg,*degree,*startNode,*endNode;
vector<pair<int,int> > stEdges;
int begin_edge, end_edge;

void mpi_init(){
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
}

void mpi_end(){
    MPI_Finalize();
}

long long numTri() {
	long long ret = 0;
	for(int i=begin_edge;i<end_edge;i++) {
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

void begin_end_assign(){
    int rem = m%size;
    int count = m/size;
    if(id < rem){
        begin_edge = id * (count + 1);
        end_edge = begin_edge + count;
    }else{
        begin_edge = id*count + rem;
        end_edge = begin_edge + count -1 ;
    }
}

void read_edges(){
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
}

int main(int argc, char** argv){

    mpi_init();

    if(id == 0){
        printf("x\n");
        READ_INT(n);
        READ_INT(m);
    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    edg = (int *) malloc(2*m * sizeof(int));
    degree = (int *) malloc(n * sizeof(int));
    startNode = (int *) malloc(n * sizeof(int));
    endNode = (int *) malloc(n * sizeof(int));

    if(id == 0){
        read_edges();
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(edg, 2*m, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(degree, n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(startNode, n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(endNode, n, MPI_INT, 0, MPI_COMM_WORLD);


    begin_end_assign();

    double start_time = MPI_Wtime();

    long long num_triangles = numTri();

    long long totalTriangles;

    MPI_Reduce(&num_triangles, &totalTriangles, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(id == 0)
        printf("Total number of triangles = %lld. Time taken = %lf seconds\n", totalTriangles, MPI_Wtime() - start_time );

    mpi_end();
}
