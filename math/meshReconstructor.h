#ifndef MESHRECONSTRUCTOR_H
#define MESHRECONSTRUCTOR_H

#include "geom/trimesh.h"

#include "cinolib/linear_solvers.h"

class MeshReconstructor
{  
public:
   MeshReconstructor();
   MeshReconstructor(const Trimesh & t);

   void init(const Trimesh & t);

   void computeTopologicalLaplacianTriplets(const Trimesh & t,
                                                  std::vector<Eigen::Triplet<double>> & entries
                                            );

   void computeUniformDifferentialCoordinates
         (const Trimesh & t,
          Eigen::VectorXd & differentialCoordinatesX,
          Eigen::VectorXd & differentialCoordinatesY,
          Eigen::VectorXd & differentialCoordinatesZ);

   void computeCotagentDifferentialCoordinates
         (const Trimesh & t,
          Eigen::VectorXd & differentialCoordinatesX,
          Eigen::VectorXd & differentialCoordinatesY,
          Eigen::VectorXd & differentialCoordinatesZ);

   Trimesh reconstruct();

private:

   typedef Eigen::Triplet<double> Entry;

   Trimesh _t;

   Eigen::VectorXd _differentialCoordinatesX;
   Eigen::VectorXd _differentialCoordinatesY;
   Eigen::VectorXd _differentialCoordinatesZ;

   std::vector<Entry> _entriesOfL;

   Eigen::SparseMatrix<double> _L;

   void computeTrisAreas(const Trimesh & t,
                         std::vector<double> & trisAreas);


};

#endif // MESHRECONSTRUCTOR_H
