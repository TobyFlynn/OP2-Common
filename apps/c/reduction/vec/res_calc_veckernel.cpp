//
// auto-generated by op2.py
//

//user function
inline void res_calc(double *data, int *count) {
  data[0] = 0.0;
  (*count)++;
}
#ifdef VECTORIZE
//user function -- modified for vectorisation
#if defined __clang__ || defined __GNUC__
__attribute__((always_inline))
#endif
inline void
res_calc_vec(double data[][SIMD_VEC], int *count, int idx) {
  data[0][idx] = 0.0;
  (*count)++;
}
#endif

// host stub function
void op_par_loop_res_calc(char const *name, op_set set,
  op_arg arg0,
  op_arg arg1){

  int nargs = 2;
  op_arg args[2];

  args[0] = arg0;
  args[1] = arg1;
  //create aligned pointers for dats
  ALIGNED_double       double * __restrict__ ptr0 = (double *) arg0.data;
  DECLARE_PTR_ALIGNED(ptr0, double_ALIGN);

  // initialise timers
  double cpu_t1, cpu_t2, wall_t1, wall_t2;
  op_timing_realloc(0);
  op_timers_core(&cpu_t1, &wall_t1);

  if (OP_diags>2) {
    printf(" kernel routine with indirection: res_calc\n");
  }

  int exec_size = op_mpi_halo_exchanges(set, nargs, args);

  if (exec_size >0) {

    #ifdef VECTORIZE
    #pragma novector
    for ( int n=0; n<(exec_size/SIMD_VEC)*SIMD_VEC; n+=SIMD_VEC ){
      int dat1[SIMD_VEC];
      for ( int i=0; i<SIMD_VEC; i++ ){
        dat1[i] = 0.0;
      }
      if (n < set->core_size && n > 0 && n % OP_mpi_test_frequency == 0)
        op_mpi_test_all(nargs, args);
      if ((n + SIMD_VEC >= set->core_size) &&
          (n + SIMD_VEC - set->core_size < SIMD_VEC)) {
        op_mpi_wait_all(nargs, args);
      }
      ALIGNED_double double dat0[4][SIMD_VEC];
      #pragma omp simd simdlen(SIMD_VEC)
      for ( int i=0; i<SIMD_VEC; i++ ){

        dat0[0][i] = 0.0;
        dat0[1][i] = 0.0;
        dat0[2][i] = 0.0;
        dat0[3][i] = 0.0;

      }
      #pragma omp simd simdlen(SIMD_VEC)
      for ( int i=0; i<SIMD_VEC; i++ ){
        res_calc_vec(
          dat0,
          &dat1[i],
          i);
      }
      for ( int i=0; i<SIMD_VEC; i++ ){
        int idx0_4 = 4 * arg0.map_data[(n+i) * arg0.map->dim + 0];

        (ptr0)[idx0_4 + 0] += dat0[0][i];
        (ptr0)[idx0_4 + 1] += dat0[1][i];
        (ptr0)[idx0_4 + 2] += dat0[2][i];
        (ptr0)[idx0_4 + 3] += dat0[3][i];

      }
      for ( int i=0; i<SIMD_VEC; i++ ){
        *(int*)arg1.data += dat1[i];
      }
    }

    //remainder
    for ( int n=(exec_size/SIMD_VEC)*SIMD_VEC; n<exec_size; n++ ){
    #else
    for ( int n=0; n<exec_size; n++ ){
    #endif
      if (n==set->core_size) {
        op_mpi_wait_all(nargs, args);
      }
      int map0idx;
      map0idx = arg0.map_data[n * arg0.map->dim + 0];

      res_calc(
        &(ptr0)[4 * map0idx],
        (int*)arg1.data);
    }
  }

  if (exec_size == 0 || exec_size == set->core_size) {
    op_mpi_wait_all(nargs, args);
  }
  // combine reduction data
  op_mpi_reduce(&arg1,(int*)arg1.data);
  op_mpi_set_dirtybit(nargs, args);

  // update kernel record
  op_timers_core(&cpu_t2, &wall_t2);
  OP_kernels[0].name      = name;
  OP_kernels[0].count    += 1;
  OP_kernels[0].time     += wall_t2 - wall_t1;
  OP_kernels[0].transfer += (float)set->size * arg0.size * 2.0f;
  OP_kernels[0].transfer += (float)set->size * arg1.size * 2.0f;
  OP_kernels[0].transfer += (float)set->size * arg0.map->dim * 4.0f;
}
