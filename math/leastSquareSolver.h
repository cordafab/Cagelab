#ifndef LEASTSQUARESOLVER_H
#define LEASTSQUARESOLVER_H

//#include "cinolib/cinolib.h"
//#include "cinolib/common.h"
#include "cinolib/linear_solvers.h"

class LeastSquareSolver
{
public:
   LeastSquareSolver();
   LeastSquareSolver(const Eigen::SparseMatrix<double> & A);
   void init (const Eigen::SparseMatrix<double> & A);
   void solve(const Eigen::VectorXd & b,
                    Eigen::VectorXd & x);

private:
   Eigen::SparseMatrix<double> At;
   Eigen::SparseMatrix<double> AtA;
   Eigen::SimplicialLLT< Eigen::SparseMatrix<double> > solver;

};

#endif // LEASTSQUARESOLVER_H
