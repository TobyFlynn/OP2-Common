//
// auto-generated by op2.py on 2014-07-29 15:47
//

//header
#include "op_lib_cpp.h"
#include "op_cuda_rt_support.h"
#include "op_cuda_reduction.h"

//global constants
#ifndef MAX_CONST_SIZE
#define MAX_CONST_SIZE 128
#endif

#define STRIDE(x,y) x*y
__constant__ int nodes_stride;
__constant__ int edges_stride;
__constant__ int bedges_stride;
__constant__ int cells_stride;
__constant__ double gam;
__constant__ double gm1;
__constant__ double cfl;
__constant__ double eps;
__constant__ double mach;
__constant__ double alpha;
__constant__ double qinf[4];

void op_register_strides() {
  int size;
  size = op_size_of_set("nodes");
  cutilSafeCall(cudaMemcpyToSymbol(nodes_stride, &size, sizeof(int)));
  size = op_size_of_set("edges");
  cutilSafeCall(cudaMemcpyToSymbol(edges_stride, &size, sizeof(int)));
  size = op_size_of_set("bedges");
  cutilSafeCall(cudaMemcpyToSymbol(bedges_stride, &size, sizeof(int)));
  size = op_size_of_set("cells");
  cutilSafeCall(cudaMemcpyToSymbol(cells_stride, &size, sizeof(int)));
}

void op_decl_const_char(int dim, char const *type,
int size, char *dat, char const *name){
  if (!strcmp(name,"gam")) {
    cutilSafeCall(cudaMemcpyToSymbol(gam, dat, dim*size));
  }
  else
  if (!strcmp(name,"gm1")) {
    cutilSafeCall(cudaMemcpyToSymbol(gm1, dat, dim*size));
  }
  else
  if (!strcmp(name,"cfl")) {
    cutilSafeCall(cudaMemcpyToSymbol(cfl, dat, dim*size));
  }
  else
  if (!strcmp(name,"eps")) {
    cutilSafeCall(cudaMemcpyToSymbol(eps, dat, dim*size));
  }
  else
  if (!strcmp(name,"mach")) {
    cutilSafeCall(cudaMemcpyToSymbol(mach, dat, dim*size));
  }
  else
  if (!strcmp(name,"alpha")) {
    cutilSafeCall(cudaMemcpyToSymbol(alpha, dat, dim*size));
  }
  else
  if (!strcmp(name,"qinf")) {
    cutilSafeCall(cudaMemcpyToSymbol(qinf, dat, dim*size));
  }
  else
  {
    printf("error: unknown const name\n"); exit(1);
  }
}

//user kernel files
#include "save_soln_kernel.cu"
#include "adt_calc_kernel.cu"
#include "res_calc_kernel.cu"
#include "bres_calc_kernel.cu"
#include "update_kernel.cu"
