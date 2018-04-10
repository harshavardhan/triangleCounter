# Parallel Triangle Counting in Un-directed Graph

 Number of triangles in a graph is a useful metric in network analysis. It is particularly useful in analysis of social networks. As the size of social networks is increasing day by day, such metrics of the graphs need to be computed quickly and efficiently to analyse them properly.
> This project is done as part of the course Parallel Programming Paradigm offered by [Prof. Sharat Chandran](https://www.cse.iitb.ac.in/~sharat/)

> Find our project proposal [here](https://github.com/joshikosuru/myFiles/blob/master/CS%20421%20Project%20Proposal.pdf)

## What have we done
* We have implemented various sequential algorithms for counting triangles in undirected graph
* We chose the best sequential and parallelizable algorithm and implemented in MPI and Cuda

## Contibutors

* **Harshavardhan ChRS** - [GitHub](https://github.com/Harsha-vardhan30)
* **Mani Shankar** - [GitHub](https://github.com/ManiShankar1154)
* **Joshi Kosuru** - [GitHub](https://github.com/joshikosuru)

## Citations

* Datasets for testing are taken from [SNAP](https://snap.stanford.edu/data/index.html)
* Basic ideas for starting are taken from [Thesis](https://people.csail.mit.edu/jshun/6886-s18/papers/schank-thesis.pdf) of Thomas Schank and [CMU Parallelism Competition](http://www.cs.cmu.edu/afs/cs/user/shuhaoy/www/)
