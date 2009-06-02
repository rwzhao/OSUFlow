
#ifndef _LATTICE4D_H_
#define _LATTICE4D_H_ 
    
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#include "header.h"
#include "calc_subvolume.h"
#include "VectorMatrix.h" 
#include "OSUFlow.h"
#include "Partition.h"

class  Lattice4D {

 public: 
  
  Lattice4D(int xlen, int ylen, int zlen, int tlen, int ghost, int nsp, 
	    int ntp, int d = 4, int myproc = -1, int nproc = -1); 
  ~Lattice4D(); 
  int GetRank(int i, int j, int k, int l);
  int GetRank(float x, float y, float z, float t);
  int GetIndices(int rank, int &i, int &j, int&k, int&t);
  int GetIndices(float x, float y, float z, float t, int& iidx, int &jidx, 
		 int&kidx, int& lidx);
  int GetBounds(int i, int j, int k, int t, volume_bounds_type& vb);
  int GetBounds(int rank, volume_bounds_type& vb);
  volume_bounds_type* GetBoundsList(){ return vb_list;}
  void GetLatticeDims(int& i, int&j, int &k, int &l) 
  {i = idim; j=jdim; k=kdim; l = tdim; }
  bool isIn(float, float, float, float, int, int, int, int); 

  int GetNeighbor(int myrank, float x, float y, float z, float t, 
		  int &ei, int &ej, int &ek, int &et); 

  int GetNeighbor(int myrank, float x, float y, float z, float t);
  int CheckNeighbor(int myrank, float x, float y, float z, float t); 
  int GetProc(int, int, int, int); 
  int GetProc(int); 
  void InitSeedLists(); 
  void ResetSeedLists(); 
  void ResetSeedLists(int i); 
  bool InsertSeed(int, int, int, int, VECTOR4); 
  bool InsertSeed(int from_i, int from_j, int from_k, int from_t, 
		  int to_i, int to_j, int to_k, int to_t, VECTOR4); 
  bool InsertSeed(int to_rank, VECTOR4); 
  bool InsertSeed(int from_rank, int to_rank, VECTOR4); 
  void RoundRobin_proc(int n); 
  void GetPartitions(int, int**, int&); 
  void ResetFlowMatrix();
  int GetFlowMatrix(int i, int j) {return flowMatrix[i*npart+j];}
  int GetNumPartitions(int proc);
  void GetPartitions(int proc, int*p_list);
  void GetNeighborRanks(int myrank, int *neighbor_ranks);
  void NeighborIndices(int n, int i, int j, int k, int l, int &in,
		       int &jn, int &kn, int &ln);
  void GetVB(int block, VECTOR3 &min_s, VECTOR3 &max_s, 
	     int &min_t, int &max_t);
  void GetGlobalVB(int part, VECTOR3 &min_s, VECTOR3 &max_s, 
		   int &min_t, int &max_t);

 private: 

  int idim, jdim, kdim, tdim; //the lattice range
  int xdim, ydim, zdim, ldim; //the whole data range
  int nbhd; // neighborhood size
  int npart; // total number of partitions in the domain
  int nblocks; // number of blocks belonging to my process
  int *block_ranks; // rank (global partition number) of each of my blocks
  int myproc; // my process or thread number (-1 if serial code)
  int nproc; // number of processes or threads (-1 if serial code)
  volume_bounds_type *vb_list; 
  class Partition *part;
  int* flowMatrix; 

 public:

  // wrappers around partition methods
  void SetReq(int myrank);
  void ClearReq(int myrank);
  int GetReq(int myrank);
  void SetLoad(int myrank);
  void ClearLoad(int myrank);
  int GetLoad(int myrank);
  void SetComp(int myrank, int iter_num);
  void ClearComp(int myrank);
  int GetComp(int myrank, int iter_num);
  void PostPoint(int myrank, VECTOR4 p);
  void PrintPost(int myrank);
  void PrintRecv(int myrank);
  void GetRecvPts(int myrank, VECTOR4 *ls);
  void SendNeighbors(int myrank);
  int ReceiveNeighbors(int myrank);

  list<VECTOR4> *seedlists; 

}; 

#endif 
 
