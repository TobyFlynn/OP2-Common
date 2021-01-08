//
// auto-generated by op2.py
//

//user function
int opDat0_res_calc_stride_OP2CONSTANT;
int opDat0_res_calc_stride_OP2HOST = -1;
int opDat2_res_calc_stride_OP2CONSTANT;
int opDat2_res_calc_stride_OP2HOST = -1;
//user function
//#pragma acc routine
inline void res_calc_openacc( const float *x1, const float *x2, const float *q1,
                     const float *q2, const float *adt1, const float *adt2,
                     float *res1, float *res2) {
  float dx, dy, mu, ri, p1, vol1, p2, vol2, f;

  dx = x1[(0) * opDat0_res_calc_stride_OP2CONSTANT] -
       x2[(0) * opDat0_res_calc_stride_OP2CONSTANT];
  dy = x1[(1) * opDat0_res_calc_stride_OP2CONSTANT] -
       x2[(1) * opDat0_res_calc_stride_OP2CONSTANT];

  ri = 1.0f / q1[(0) * opDat2_res_calc_stride_OP2CONSTANT];
  p1 = gm1 * (q1[(3) * opDat2_res_calc_stride_OP2CONSTANT] -
              0.5f * ri *
                  (q1[(1) * opDat2_res_calc_stride_OP2CONSTANT] *
                       q1[(1) * opDat2_res_calc_stride_OP2CONSTANT] +
                   q1[(2) * opDat2_res_calc_stride_OP2CONSTANT] *
                       q1[(2) * opDat2_res_calc_stride_OP2CONSTANT]));
  vol1 = ri * (q1[(1) * opDat2_res_calc_stride_OP2CONSTANT] * dy -
               q1[(2) * opDat2_res_calc_stride_OP2CONSTANT] * dx);

  ri = 1.0f / q2[(0) * opDat2_res_calc_stride_OP2CONSTANT];
  p2 = gm1 * (q2[(3) * opDat2_res_calc_stride_OP2CONSTANT] -
              0.5f * ri *
                  (q2[(1) * opDat2_res_calc_stride_OP2CONSTANT] *
                       q2[(1) * opDat2_res_calc_stride_OP2CONSTANT] +
                   q2[(2) * opDat2_res_calc_stride_OP2CONSTANT] *
                       q2[(2) * opDat2_res_calc_stride_OP2CONSTANT]));
  vol2 = ri * (q2[(1) * opDat2_res_calc_stride_OP2CONSTANT] * dy -
               q2[(2) * opDat2_res_calc_stride_OP2CONSTANT] * dx);

  mu = 0.5f * ((*adt1) + (*adt2)) * eps;

  f = 0.5f * (vol1 * q1[(0) * opDat2_res_calc_stride_OP2CONSTANT] +
              vol2 * q2[(0) * opDat2_res_calc_stride_OP2CONSTANT]) +
      mu * (q1[(0) * opDat2_res_calc_stride_OP2CONSTANT] -
            q2[(0) * opDat2_res_calc_stride_OP2CONSTANT]);
  res1[(0) * opDat2_res_calc_stride_OP2CONSTANT] += f;
  res2[(0) * opDat2_res_calc_stride_OP2CONSTANT] -= f;
  f = 0.5f * (vol1 * q1[(1) * opDat2_res_calc_stride_OP2CONSTANT] + p1 * dy +
              vol2 * q2[(1) * opDat2_res_calc_stride_OP2CONSTANT] + p2 * dy) +
      mu * (q1[(1) * opDat2_res_calc_stride_OP2CONSTANT] -
            q2[(1) * opDat2_res_calc_stride_OP2CONSTANT]);
  res1[(1) * opDat2_res_calc_stride_OP2CONSTANT] += f;
  res2[(1) * opDat2_res_calc_stride_OP2CONSTANT] -= f;
  f = 0.5f * (vol1 * q1[(2) * opDat2_res_calc_stride_OP2CONSTANT] - p1 * dx +
              vol2 * q2[(2) * opDat2_res_calc_stride_OP2CONSTANT] - p2 * dx) +
      mu * (q1[(2) * opDat2_res_calc_stride_OP2CONSTANT] -
            q2[(2) * opDat2_res_calc_stride_OP2CONSTANT]);
  res1[(2) * opDat2_res_calc_stride_OP2CONSTANT] += f;
  res2[(2) * opDat2_res_calc_stride_OP2CONSTANT] -= f;
  f = 0.5f * (vol1 * (q1[(3) * opDat2_res_calc_stride_OP2CONSTANT] + p1) +
              vol2 * (q2[(3) * opDat2_res_calc_stride_OP2CONSTANT] + p2)) +
      mu * (q1[(3) * opDat2_res_calc_stride_OP2CONSTANT] -
            q2[(3) * opDat2_res_calc_stride_OP2CONSTANT]);
  res1[(3) * opDat2_res_calc_stride_OP2CONSTANT] += f;
  res2[(3) * opDat2_res_calc_stride_OP2CONSTANT] -= f;
}

// host stub function
void op_par_loop_res_calc(char const *name, op_set set,
  op_arg arg0,
  op_arg arg1,
  op_arg arg2,
  op_arg arg3,
  op_arg arg4,
  op_arg arg5,
  op_arg arg6,
  op_arg arg7){

  int nargs = 8;
  op_arg args[8];

  args[0] = arg0;
  args[1] = arg1;
  args[2] = arg2;
  args[3] = arg3;
  args[4] = arg4;
  args[5] = arg5;
  args[6] = arg6;
  args[7] = arg7;

  // initialise timers
  double cpu_t1, cpu_t2, wall_t1, wall_t2;
  op_timing_realloc(2);
  op_timers_core(&cpu_t1, &wall_t1);
  OP_kernels[2].name      = name;
  OP_kernels[2].count    += 1;

  int  ninds   = 4;
  int  inds[8] = {0,0,1,1,2,2,3,3};

  if (OP_diags>2) {
    printf(" kernel routine with indirection: res_calc\n");
  }

  // get plan
  #ifdef OP_PART_SIZE_2
    int part_size = OP_PART_SIZE_2;
  #else
    int part_size = OP_part_size;
  #endif

  int set_size = op_mpi_halo_exchanges_cuda(set, nargs, args);


  int ncolors = 0;

  if (set_size > 0) {

    if ((OP_kernels[2].count == 1) ||
        (opDat0_res_calc_stride_OP2HOST != getSetSizeFromOpArg(&arg0))) {
      opDat0_res_calc_stride_OP2HOST = getSetSizeFromOpArg(&arg0);
      opDat0_res_calc_stride_OP2CONSTANT = opDat0_res_calc_stride_OP2HOST;
    }
    if ((OP_kernels[2].count == 1) ||
        (opDat2_res_calc_stride_OP2HOST != getSetSizeFromOpArg(&arg2))) {
      opDat2_res_calc_stride_OP2HOST = getSetSizeFromOpArg(&arg2);
      opDat2_res_calc_stride_OP2CONSTANT = opDat2_res_calc_stride_OP2HOST;
    }

    //Set up typed device pointers for OpenACC
    int *map0 = arg0.map_data_d;
    int *map2 = arg2.map_data_d;

    float *data0 = (float *)arg0.data_d;
    float *data2 = (float *)arg2.data_d;
    float *data4 = (float *)arg4.data_d;
    float *data6 = (float *)arg6.data_d;

    op_plan *Plan = op_plan_get_stage(name,set,part_size,nargs,args,ninds,inds,OP_COLOR2);
    ncolors = Plan->ncolors;
    int *col_reord = Plan->col_reord;
    int set_size1 = set->size + set->exec_size;

    // execute plan
    for ( int col=0; col<Plan->ncolors; col++ ){
      if (col==1) {
        op_mpi_wait_all_cuda(nargs, args);
      }
      int start = Plan->col_offsets[0][col];
      int end = Plan->col_offsets[0][col+1];

      #pragma acc parallel loop independent deviceptr(col_reord,map0,map2,data0,data2,data4,data6)
      for ( int e=start; e<end; e++ ){
        int n = col_reord[e];
        int map0idx;
        int map1idx;
        int map2idx;
        int map3idx;
        map0idx = map0[n + set_size1 * 0];
        map1idx = map0[n + set_size1 * 1];
        map2idx = map2[n + set_size1 * 0];
        map3idx = map2[n + set_size1 * 1];

        res_calc_openacc(&data0[map0idx], &data0[map1idx], &data2[map2idx],
                         &data2[map3idx], &data4[1 * map2idx],
                         &data4[1 * map3idx], &data6[map2idx], &data6[map3idx]);
      }

    }
    OP_kernels[2].transfer  += Plan->transfer;
    OP_kernels[2].transfer2 += Plan->transfer2;
  }

  if (set_size == 0 || set_size == set->core_size || ncolors == 1) {
    op_mpi_wait_all_cuda(nargs, args);
  }
  // combine reduction data
  op_mpi_set_dirtybit_cuda(nargs, args);

  // update kernel record
  op_timers_core(&cpu_t2, &wall_t2);
  OP_kernels[2].time     += wall_t2 - wall_t1;
}
