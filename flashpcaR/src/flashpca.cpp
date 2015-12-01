// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppEigen.h>
#include <Rcpp.h>

using namespace Rcpp;

#include "randompca.hpp"

// [[Rcpp::export]]
List flashpca_internal(Eigen::Map<Eigen::MatrixXd> X, int method, int stand,
   bool transpose, unsigned int ndim, unsigned int nextra,
   unsigned int maxiter, double tol, long seed, int kernel,
   double sigma, bool rbf_center, unsigned int rbf_sample,
   bool save_kernel, bool do_orth, bool verbose, bool do_loadings,
   int mem, bool return_scale, unsigned int num_threads)
{

#ifdef _OPENMP
   omp_set_num_threads(num_threads);
#endif

   Eigen::MatrixXd Xm = X;

   RandomPCA rp;
   rp.stand_method = stand;
   rp.verbose = verbose;
   rp.pca(Xm, method, transpose, ndim, nextra,
      maxiter, tol, seed, kernel,
      sigma, rbf_center, rbf_sample,
      save_kernel, do_orth, do_loadings, mem);

   NumericMatrix U(wrap(rp.U));
   NumericMatrix P(wrap(rp.Px));
   NumericVector d(wrap(rp.d));

   NumericVector X_mean(0);
   NumericVector X_sd(0);

   // STANDARDIZE_NONE: 0
   if(return_scale && stand != 0)
   {
      NumericMatrix X_meansd(wrap(rp.X_meansd));
      X_mean = X_meansd(_, 0);
      X_sd = X_meansd(_, 1);
   }
   
   Rcpp::List res;

   if(do_loadings)
   {
      NumericMatrix V(wrap(rp.V));
      res = Rcpp::List::create(
         Rcpp::Named("values")=d,
         Rcpp::Named("vectors")=U,
         Rcpp::Named("projection")=P,
	 Rcpp::Named("loadings")=V,
	 Rcpp::Named("center")=X_mean,
	 Rcpp::Named("scale")=X_sd
      );
   }
   else
   {
      res = Rcpp::List::create(
         Rcpp::Named("values")=d,
         Rcpp::Named("vectors")=U,
         Rcpp::Named("projection")=P,
	 Rcpp::Named("center")=X_mean,
	 Rcpp::Named("scale")=X_sd
      );
   }

   return res;
}

// [[Rcpp::export]]
List scca_internal(Eigen::Map<Eigen::MatrixXd> X, Eigen::Map<Eigen::MatrixXd> Y,
   double lambda1, double lambda2, unsigned int ndim, int stand,
   int mem, long seed, int maxiter,  double tol,
   bool verbose, unsigned int num_threads)
{
#ifdef _OPENMP
   omp_set_num_threads(num_threads);
#endif

   Eigen::MatrixXd Xm = X;
   Eigen::MatrixXd Ym = Y;

   RandomPCA rp;
   rp.stand_method = stand;
   rp.verbose = verbose;
   rp.scca(Xm, Ym, lambda1, lambda2, seed, ndim, mem, maxiter, tol);

   NumericMatrix U(wrap(rp.U));
   NumericMatrix V(wrap(rp.V));
   NumericMatrix Px(wrap(rp.Px));
   NumericMatrix Py(wrap(rp.Py));
   NumericVector d(wrap(rp.d));

   Rcpp::List res;

   res = Rcpp::List::create(
	 Rcpp::Named("U")=U,
         Rcpp::Named("V")=V,
         Rcpp::Named("d")=d,
         Rcpp::Named("Px")=Px,
         Rcpp::Named("Py")=Py
   );

   return res;
}
