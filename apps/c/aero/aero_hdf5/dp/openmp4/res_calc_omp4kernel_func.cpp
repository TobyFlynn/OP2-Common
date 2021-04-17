//
// auto-generated by op2.py
//

void res_calc_omp4_kernel(int *map0, int map0size, double *data8, int dat8size,
                          double *data0, int dat0size, double *data4,
                          int dat4size, double *data9, int dat9size,
                          double *data13, int dat13size, int *col_reord,
                          int set_size1, int start, int end, int num_teams,
                          int nthread, int opDat0_res_calc_stride_OP2CONSTANT,
                          int direct_res_calc_stride_OP2CONSTANT,
                          int optflags) {

#pragma omp target teams num_teams(num_teams) thread_limit(nthread)            \
    map(to : data8[0 : dat8size])                                              \
        map(to : gm1_ompkernel, gm1i_ompkernel, m2_ompkernel,                  \
            wtg2_ompkernel[ : 4], Ng2_xi_ompkernel[ : 32]) map(                \
                to : col_reord[0 : set_size1],                                 \
                               map0[0 : map0size],                             \
                                    data0[0 : dat0size],                       \
                                          data4[0 : dat4size],                 \
                                                data9[0 : dat9size],           \
                                                      data13[0 : dat13size])
#pragma omp distribute parallel for schedule(static, 1)
  for ( int e=start; e<end; e++ ){
    int n_op = col_reord[e];
    int map0idx;
    int map1idx;
    int map2idx;
    int map3idx;
    map0idx = map0[n_op + set_size1 * 0];
    map1idx = map0[n_op + set_size1 * 1];
    map2idx = map0[n_op + set_size1 * 2];
    map3idx = map0[n_op + set_size1 * 3];

    const double *arg0_vec[] = {&data0[map0idx], &data0[map1idx],
                                &data0[map2idx], &data0[map3idx]};
    const double* arg4_vec[] = {
       &data4[1 * map0idx],
       &data4[1 * map1idx],
       &data4[1 * map2idx],
       &data4[1 * map3idx]};
    double* arg9_vec[] = {
       &data9[1 * map0idx],
       &data9[1 * map1idx],
       &data9[1 * map2idx],
       &data9[1 * map3idx]};
    double *arg13_vec[] = {&data13[map0idx], &data13[map1idx], &data13[map2idx],
                           &data13[map3idx]};
    //variable mapping
    const double **x = arg0_vec;
    const double **phim = arg4_vec;
    double *K = &data8[n_op];
    double **res = arg9_vec;
    double **none = arg13_vec;

    //inline function
    
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        K[(j * 4 + k) * direct_res_calc_stride_OP2CONSTANT] = 0;
      }
    }
    for (int i = 0; i < 4; i++) {
      double det_x_xi = 0;
      double N_x[8];

      double a = 0;
      for (int m = 0; m < 4; m++)
        det_x_xi += Ng2_xi_ompkernel[4 * i + 16 + m] *
                    x[m][(1) * opDat0_res_calc_stride_OP2CONSTANT];
      for (int m = 0; m < 4; m++)
        N_x[m] = det_x_xi * Ng2_xi_ompkernel[4 * i + m];

      a = 0;
      for (int m = 0; m < 4; m++)
        a += Ng2_xi_ompkernel[4 * i + m] *
             x[m][(0) * opDat0_res_calc_stride_OP2CONSTANT];
      for (int m = 0; m < 4; m++)
        N_x[4 + m] = a * Ng2_xi_ompkernel[4 * i + 16 + m];

      det_x_xi *= a;

      a = 0;
      for (int m = 0; m < 4; m++)
        a += Ng2_xi_ompkernel[4 * i + m] *
             x[m][(1) * opDat0_res_calc_stride_OP2CONSTANT];
      for (int m = 0; m < 4; m++)
        N_x[m] -= a * Ng2_xi_ompkernel[4 * i + 16 + m];

      double b = 0;
      for (int m = 0; m < 4; m++)
        b += Ng2_xi_ompkernel[4 * i + 16 + m] *
             x[m][(0) * opDat0_res_calc_stride_OP2CONSTANT];
      for (int m = 0; m < 4; m++)
        N_x[4 + m] -= b * Ng2_xi_ompkernel[4 * i + m];

      det_x_xi -= a * b;

      for (int j = 0; j < 8; j++)
        N_x[j] /= det_x_xi;

      double wt1 = wtg2_ompkernel[i] * det_x_xi;


      double u[2] = {0.0, 0.0};
      for (int j = 0; j < 4; j++) {
        u[0] += N_x[j] * phim[j][0];
        u[1] += N_x[4 + j] * phim[j][0];
      }

      double Dk = 1.0 + 0.5 * gm1_ompkernel * (m2_ompkernel - (u[0] * u[0] + u[1] * u[1]));
      double rho = pow(Dk, gm1i_ompkernel);
      double rc2 = rho / Dk;

      for (int j = 0; j < 4; j++) {
        res[j][0] += wt1 * rho * (u[0] * N_x[j] + u[1] * N_x[4 + j]);
      }
      for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 4; k++) {
          K[(j * 4 + k) * direct_res_calc_stride_OP2CONSTANT] +=
              wt1 * rho * (N_x[j] * N_x[k] + N_x[4 + j] * N_x[4 + k]) -
              wt1 * rc2 * (u[0] * N_x[j] + u[1] * N_x[4 + j]) *
                  (u[0] * N_x[k] + u[1] * N_x[4 + k]);
        }
      }
    }
    //end inline func
  }
}
