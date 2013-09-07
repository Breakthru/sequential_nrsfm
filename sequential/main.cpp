#include <iostream>
#include <sba.h>

void my_cost_function(double *p, struct sba_crsm *idxij,
		      int *rcidxs, int *rcsubs,
		      double *hx, void *adata)
{
  /* functional relation describing measurements. Given a parameter vector p,
  * computes a prediction of the measurements \hat{x}. p is (m*cnp + n*pnp)x1,
  * \hat{x} is (n*m*mnp)x1, maximum
  * rcidxs, rcsubs are max(m, n) x 1, allocated by the caller and can be used
  * as working memory
  */
  int cnp = 2; // parameters per camera
  int pnp = 3; // parameters per point
  int mnp = 2; // measurements per point  
  // idxij description copied from sba_levmar.c:
  /* sparse matrix containing the location of x_ij in x. This is also the location of A_ij 
  * in jac, e_ij in e, etc.
  * This matrix can be thought as a map from a sparse set of pairs (i, j) to a continuous
  * index k and it is used to efficiently lookup the memory locations where the non-zero
  * blocks of a sparse matrix/vector are stored
  */
  int  n_frames=idxij->nc;
  double *pa=p; // camera parameters
  double *pb=p+n_frames*cnp; // point parameters

  // pointer arithmetics everywhere
  double *pcam; // parameter vector for one camera
  double *ppt; // parameter vector for one point
  double *pmeasurements; // measurements for one point
  
  // loop to compute hatx: measurements given parameters p
  for(int j=0; j<n_frames; ++j){
    /* j-th camera parameters */
    pcam=pa+j*cnp;
    
    int nnz=sba_crsm_col_elmidxs(idxij, j, rcidxs, rcsubs); /* find nonzero hx_ij, i=0...n-1 */

    for(int i=0; i<nnz; ++i){
      // now compute projection of point i in frame j
      ppt=pb + rcsubs[i]*pnp;
      pmeasurements=hx + idxij->val[rcidxs[i]]*mnp; // set pmeas to point to hx_ij
      pmeasurements[0] = i + pcam[0]+pcam[1]; // mock use of camera parameters
      pmeasurements[1] = j + ppt[0] + ppt[1] + ppt[2]; // mock use of points parameters
    }
  }

}

void my_cost_jacobian(double *p, struct sba_crsm *idxij,
		      int *rcidxs, int *rcsubs,
		      double *jac, void *adata)
{
  /* function to evaluate the sparse jacobian dX/dp.
    * The Jacobian is returned in jac as
    * (dx_11/da_1, ..., dx_1m/da_m, ..., dx_n1/da_1, ..., dx_nm/da_m,
    *  dx_11/db_1, ..., dx_1m/db_1, ..., dx_n1/db_n, ..., dx_nm/db_n), or (using HZ's notation),
    * jac=(A_11, B_11, ..., A_1m, B_1m, ..., A_n1, B_n1, ..., A_nm, B_nm)
    * Notice that depending on idxij, some of the A_ij and B_ij might be missing.
    * Note also that A_ij and B_ij are mnp x cnp and mnp x pnp matrices resp. and they
    * should be stored in jac in row-major order.
    * rcidxs, rcsubs are max(m, n) x 1, allocated by the caller and can be used
    * as working memory
    *
    * If NULL, the jacobian is approximated by repetitive func calls and finite
    * differences. This is computationally inefficient and thus NOT recommended.
    */
}

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
    int iterations;
    int n_points = 3;
    int n_frames = 7;
    // missing data matrix
    char vmask[n_points*n_frames];
    // set all points visible in all frames
    for (int i=0; i<n_frames*n_points; i++)
      vmask[i] = 1;

    int cnp = 2; // say two parameters per camera
    int pnp = 3; // say three parameters per point
    double parameters[n_frames*cnp+n_points*pnp]; // some pIarameters
    // let's set all camera parameters to zero
    for (int i=0; i < n_frames*cnp; i++)
    {
      parameters[i] = 0.0;          
    }    
    // let's set all points parameters to some values
    for (int i=n_frames*cnp; i < n_frames*cnp+n_points*pnp; i++)
    {
      parameters[i] = 3.0;
    }
    std::cout << "parameters vector: " << std::endl;
    for (int i=0; i< n_frames*cnp+n_points*pnp; i++)
    {
      std::cout << parameters[i] << " , ";
    }
    std::cout << std::endl << "end parameters vector!" << std::endl;
    
    
    double *covariance = NULL;
    int mnp = 2; // number of measurements for each point (usually 2: x and y positions)
    double measurements[n_frames*n_points*mnp];
    double *m = measurements;
    // set some measurements that we try to fit our parameters to
    for (int i=0 ;i<n_points; i++)
      for (int j=0; j<n_frames; j++)
      {
	// i-th point at the j-th image
	*m = i; // x of point ij is i
	m++; // next
	*m = j; // y of point ij is j
	m++;
      }
    void *adata = NULL;
    int max_iterations = 100;
    int verbose = 5;
    double opts[SBA_OPTSSZ];
    
    opts[0]=SBA_INIT_MU; opts[1]=SBA_STOP_THRESH; opts[2]=SBA_STOP_THRESH;
    opts[3]=SBA_STOP_THRESH; opts[4]=0.0;
    double info[SBA_INFOSZ];
    
    iterations = sba_motstr_levmar_x(n_points,
				     0,
				     n_frames,
				     0,
				     vmask,
				     parameters,
				     cnp,
				     pnp,
				     measurements,
				     covariance,
				     mnp,
				     my_cost_function,
				     NULL,
				     adata,
				     max_iterations,
				     verbose,
				     opts,
				     info
		 );
    
    std::cout << "parameters after optimization: " << std::endl;
    for (int i=0; i< n_frames*cnp+n_points*pnp; i++)
    {
      std::cout << parameters[i] << " , ";
    }
    std::cout << std::endl << "end parameters vector!" << std::endl;
    return 0;
}
