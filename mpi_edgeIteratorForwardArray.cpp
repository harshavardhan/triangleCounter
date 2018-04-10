#include <bits/stdc++.h>
#include <mpi.h>
#include "timer.h"
using namespace std;

int id, size;
int n,m,*edg,*degree,*startNode,*endNode;
int begin_edge, end_edge;
vector<pair<int,int> > stEdges;


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
	for(int i=begin_edge;i<=end_edge;i++) {
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
        scanf("%d %d", &node1, &node2);
        stEdges.push_back(make_pair(node1,node2));
        degree[node1]++; degree[node2]++;
    }
}
void sort_computation(){
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

    double start, end;

    if(id == 0){
        FILE * file;
        freopen(argv[1], "r", stdin);
        scanf("%d %d", &n, &m);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(m < size){
        if(id == 0)
            printf("More number of processors! Number of processors shouls not exceed number of edges\n");
        MPI_Finalize();
    }

    edg = (int *) malloc(2*m * sizeof(int));
    degree = (int *) malloc(n * sizeof(int));
    startNode = (int *) malloc(n * sizeof(int));
    endNode = (int *) malloc(n * sizeof(int));


    if(id == 0){
        printf("\nReading Input File\n\n");
        GET_TIME(start);
        read_edges();
        GET_TIME(end);
        printf("Reading Input and adding it to data took %e seconds\n\n", end - start);
        printf("\nSorting Data\n\n");
        GET_TIME(start);
        sort_computation();
        GET_TIME(end);
        printf("Sorting data took %e seconds\n\n", end - start);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if(id == 0){
        printf("Process 0 is broadcasting data\n" );
        GET_TIME(start);
    }
    MPI_Bcast(edg, 2*m, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(degree, n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(startNode, n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(endNode, n, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    if(id == 0){
        GET_TIME(end);
        printf("All the processes received data\n" );
        printf("Time taken by all the processes to recieve the data = %e\n", end - start);
    }
    begin_end_assign();

    long long totalTriangles = 0;
    printf("Process %d Starting Computation for counting Triangles\n", id);
    GET_TIME(start);
    long long num_triangles = numTri();

    MPI_Reduce(&num_triangles, &totalTriangles, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    GET_TIME(end);
    printf("Process-%d : Time taken for computation  of triangles = %e seconds\n", id, end-start);

    if(id == 0)
        printf("Total number of triangles = %lld\n", totalTriangles );

    // free(edg);
    // free(degree);
    // free(startNode);
    // free(endNode);
    mpi_end();
}
