#ifndef GREENCOORDINATES_H
#define GREENCOORDINATES_H

#include "skinning/weights.h"
#include "geom/character.h"
#include "geom/cage.h"
#include "geom/vec3.h"
#include "skinning/cageSkinning.h"
#include <vector>

class GreenCoordinates:
      public CageSkinning
{
public:
   GreenCoordinates();
   GreenCoordinates(Weights     * _w,
                    Character   * _character,
                    Cage        * _cage);

      void deform();
      void deformPartial();

      bool generateCoords(Weights     * & weights,
                          Character   *   character,
                          Cage        *   cage); //cerca di impostarlo come statico
private:

   //Utilities methods for the calculation of coords and mesh deformation
   double gcTriInt(const cg3::Vec3d & p,
                   const cg3::Vec3d & t1,
                   const cg3::Vec3d & t2,
                   const cg3::Vec3d & eta);
   void calcScalingFactors(Cage * deformedCage);

   //Green cooordinate functions and scaling factors
   std::vector<std::vector<double> > gcV; //φi(η)  i∈ V
   std::vector<std::vector<double> > gcF; //ψj(η)  j∈ F
   std::vector<double>               gcS;  //Scaling factors
   std::vector<int>                  exitFaces;
};

#endif // GREENCOORDINATES_H
