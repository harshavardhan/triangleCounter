#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;

int proc_id, num_procs;
int num_blocks;

void mpi_init(){
    // Initialize the MPI environment. The two arguments to MPI Init are not
    // currently used by MPI implementations, but are there in case future
    // implementations might need the arguments.
    MPI_Init(NULL, NULL);
    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    // Get the remap of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
}

void mpi_end(){
    // Finalize the MPI environment. No more MPI calls can be made after this
    MPI_Finalize();
}

int num_V, num_E;
int* edges;
int* degrees;
vector<vector<int> > low_nbr;
int* block;
#define READ_INT(n) {char c; n = getchar_unlocked() - '0'; while((c = getchar_unlocked()) >= '0') n = (n << 3) + (n << 1) + c - '0';}

void input(char* filename){
    int block1 = proc_id / num_blocks, block2 = proc_id % num_blocks;
    // ***** INPUT *****
    FILE* file;
    int* input_edges;
    int num_input_edges;
    if(proc_id == 0){ // only root reads from file
        freopen(filename, "r", stdin);
        READ_INT(num_V);
        READ_INT(num_input_edges);
    }
    MPI_Bcast(&num_V, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&num_input_edges, 1, MPI_INT, 0, MPI_COMM_WORLD);
    input_edges = new int[2 * num_input_edges];
    if(proc_id == 0){
        for(int i = 0; i < num_input_edges * 2; i++)
            READ_INT(input_edges[i]);
    }
    MPI_Bcast(input_edges, 2 * num_input_edges, MPI_INT, 0, MPI_COMM_WORLD);
    block = new int[num_V];
    for(int i = 0; i < num_V; i++)
        block[i] = i % num_blocks;
    degrees = new int[num_V];
    memset(degrees, 0, num_V * sizeof(int));
    num_E = 0;
    for(int i = 0; i < num_input_edges; i++){
        int u = input_edges[2 * i];
        int v = input_edges[2 * i + 1];
        degrees[u]++;
        degrees[v]++;
        if(block[u] == block1 || block[u] == block2)
            num_E++;
        if(block[v] == block1 || block[v] == block2)
            num_E++;
    }
    edges = new int[num_E * 2];
    int next_E = 0;
    for(int i = 0; i < num_input_edges; i++){
        int u = input_edges[2 * i];
        int v = input_edges[2 * i + 1];
        if(block[u] == block1 || block[u] == block2){
            edges[next_E++] = u;
            edges[next_E++] = v;
        }
    }
    for(int i = 0; i < num_input_edges; i++){
        int u = input_edges[2 * i];
        int v = input_edges[2 * i + 1];
        if(block[v] == block1 || block[v] == block2){
            edges[next_E++] = v;
            edges[next_E++] = u;
        }
    }
    delete[] input_edges;
}
void radix_sort(){
    int block1 = proc_id / num_blocks, block2 = proc_id % num_blocks;
    // ***** RADIX SORT *****
    int* remap = new int[num_V];
    int next_id = 0;
    int* radix_sizes = new int[num_V];
    int* radix_next = new int[num_V];
    int** radix = new int*[num_V];
    memset(radix_sizes, 0, num_V * sizeof(int));
    for(int v = 0; v < num_V; v++)
        radix_sizes[degrees[v]]++;
    for(int d = 0; d < num_V; d++)
        if(radix_sizes[d] > 0)
            radix[d] = new int[radix_sizes[d]];
    memset(radix_next, 0, num_V * sizeof(int));
    for(int v = 0; v < num_V; v++)
        radix[degrees[v]][radix_next[degrees[v]]++] = v;
    for(int d = 0; d < num_V; d++)
        for(int i = 0; i < radix_sizes[d]; i++){
            int v = radix[d][i];
            remap[v] = next_id++;
    }
    assert(next_id == num_V);
    int* new_block = new int[num_V];
    for(int v = 0; v < num_V; v++)
        new_block[remap[v]] = block[v];
    delete[] block;
    block = new_block;
    // reuse radix for another radix sort
    for(int d = 0; d < num_V; d++)
        if(radix_sizes[d] > 0)
            delete[] radix[d];
    memset(radix_sizes, 0, num_V * sizeof(int));
    for(int i = 0; i < num_E; i++){
        int& v = edges[2 * i];
        int& w = edges[2 * i + 1];
        v = remap[v];
        w = remap[w];
    }
    for(int i = 0; i < num_E; i++){
        int w = edges[2 * i], v = edges[2 * i + 1];
        if(v < w)
        radix_sizes[v]++;
    }
    for(int v = 0; v < num_V; v++)
        if(radix_sizes[v] > 0)
            radix[v] = new int[radix_sizes[v]];
    memset(radix_next, 0, num_V * sizeof(int));
    for(int i = 0; i < num_E; i++){
        int w = edges[2 * i], v = edges[2 * i + 1];
        if(v < w)
            radix[v][radix_next[v]++] = w;
    }
    // using vectors for low_nbr seems to work better for num_triangles()
    low_nbr = vector<vector<int> >(num_V);
    for(int v = 0; v < num_V; v++)
        for(int i = 0; i < radix_sizes[v]; i++){
            int w = radix[v][i];
            low_nbr[w].push_back(v);
        }
    delete[] remap;
    for(int v = 0; v < num_V; v++)
        if(radix_sizes[v])
            delete[] radix[v];
    delete[] radix_next;
    delete[] radix_sizes;
}
long long num_triangles(){
    int block1 = proc_id / num_blocks, block2 = proc_id % num_blocks;
    // ***** COUNTS NUMBER OF TRIANGLES *****
    double start_time = MPI_Wtime();
    long long counter = 0;
    for(int i = 0; i < num_E; i++){
        int w = edges[2 * i], v = edges[2 * i + 1];
        if(!(v < w && block[v] == block1 && block[w] == block2)) continue;
        int v_ptr = 0;
        int w_ptr = 0;
        while(v_ptr < low_nbr[v].size() && low_nbr[w][w_ptr] < v){
            if(low_nbr[v][v_ptr] < low_nbr[w][w_ptr])
                v_ptr++;
            else if(low_nbr[v][v_ptr] > low_nbr[w][w_ptr])
                w_ptr++;
            else{
            counter++;
            v_ptr++;
            w_ptr++;
            }
        }
    }
    return counter;
}
int main(int argc, char** argv){
    assert(argc == 2);
    char* filename = argv[1];
    mpi_init();
    double start_time = MPI_Wtime();
    num_blocks = -1;
    for(int i = 1; i <= num_procs; i++)
        if(i * i == num_procs)
            num_blocks = i;
    assert(num_blocks != -1);
    input(filename);
    radix_sort();
    long long num_tri = num_triangles();
    if(proc_id == 0){
        long long total = num_tri;
        for(int proc = 1; proc < num_procs; proc++){
            long long add = 0;
            MPI_Recv(&add, 1, MPI_LONG_LONG, proc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total += add;
        }
        printf("***** found %lld triangles in %lf seconds (ignoring input time) *****\n", total,
        MPI_Wtime() - start_time);
    }
    else
        MPI_Send(&num_tri, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
    mpi_end();
}
