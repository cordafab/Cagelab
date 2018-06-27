#include "meanValueCoordinates.h"

#define EPS 0.00000000001
#define sign(i) ((i >= EPS) ? (1) : (-1))

MeanValueCoordinates::MeanValueCoordinates()
{

}

MeanValueCoordinates::MeanValueCoordinates(Weights           * _w,
                                           Character * _character,
                                           Cage      * _cage)
   :CageSkinning(_w, _character, _cage)
{

}

void MeanValueCoordinates::deform()
{
   int vertexNumber = character->getNumVertices();

   double totalW = 0;

   //Add deformation for rest pose
   for(int i=0; i<vertexNumber; ++i)
   {
      const std::vector<double> & weights = w->getWeights(i);
      cg3::Point3d v1;

      for(unsigned long j=0; j<weights.size(); ++j)
      {
         double w = weights[j];
         v1 += w * cage->getVertex(j);
         totalW += w;
      }

      if(totalW > 0)
      {
         character->setVertex(i, v1);
      }
      totalW = 0;
   }

}

bool MeanValueCoordinates::generateCoords(Weights   * & weights,
                                          Character *   character,
                                          Cage      *   cage)
{
   std::vector<std::vector <double>> mvcW;

   mvcW.resize(character->getNumVertices());
   for(int i=0; i<character->getNumVertices(); i++)
      mvcW[i].resize(cage->getNumVertices(), 0.0);

   /**
     *   j = 0 .. cageFaces.size() for each face 3 vertices  j=j+3
     *   i = 0 .. objMesh.num_vertices()
     */

   //Cage vertices and coordinates
   const std::vector<double> & cageVertices = cage->getVerticesVector();
   const std::vector<int> & cageFaces = cage->getTrianglesVector();

   //Coordinates of the vertices of the mesh
   const std::vector<double> & characterVertices = character->getVerticesVector();

   //Current vertex of the object mesh
   cg3::Vec3d v;

   //Vertices of the current face of the cage
   cg3::Vec3d p1, p2, p3;
   cg3::Vec3d u1, u2, u3;

   double x, y, z;
   int v1Id, v2Id, v3Id;

   //Foreach point v of the original mesh
   for(int i=0; i<character->getNumVertices(); i++)
   {
      int vId = i*3;

      x = characterVertices[vId+0];
      y = characterVertices[vId+1];
      z = characterVertices[vId+2];

      v.set(x,y,z);

      //Foreach cage face j with vertices v1 v2 v3
      for(unsigned int j=0; j<cageFaces.size(); j=j+3)
      {

         //Set vertex coordinates for vertices p1, p2, p3

         //Get id for vertices p1,p2,p3
         v1Id = 3*cageFaces[j];
         v2Id = 3*cageFaces[j+1];
         v3Id = 3*cageFaces[j+2];

         //Coords of p1
         x = cageVertices[v1Id];
         y = cageVertices[v1Id+1];
         z = cageVertices[v1Id+2];
         p1.set(x,y,z);

         //Coords of p2
         x = cageVertices[v2Id];
         y = cageVertices[v2Id+1];
         z = cageVertices[v2Id+2];
         p2.set(x,y,z);

         //Coords of p3
         x = cageVertices[v3Id];
         y = cageVertices[v3Id+1];
         z = cageVertices[v3Id+2];
         p3.set(x,y,z);

         /*
         * Index for vertices p1,p2,p3 that lies in the current face,
         * in which mvc weight function(mvcW) is saved
         */
         int j1 = cageFaces[j+0];
         int j2 = cageFaces[j+1];
         int j3 = cageFaces[j+2];


         double d1,d2,d3;

         d1 = (p1-v).length();
         d2 = (p2-v).length();
         d3 = (p3-v).length();

         if(d1<EPS)
         {
         return false; ///booooooooooooooooooooooooooooooooo  return fi?
         }
         if(d2<EPS)
         {
         return false; ///booooooooooooooooooooooooooooooooo  return fi?
         }
         if(d3<EPS)
         {
         return false; ///booooooooooooooooooooooooooooooooo  return fi?
         }

         u1 = (p1-v)/d1;
         u2 = (p2-v)/d2;
         u3 = (p3-v)/d3;


         double l1, l2, l3, theta1, theta2, theta3, h, c1, c2, c3, s1, s2, s3;
         l1 = (u2-u3).length();
         l2 = (u3-u1).length();
         l3 = (u1-u2).length();

         //Compute thetai = 2*arcsin(li/2)
         theta1 = 2.0*asin(l1/2.0);
         theta2 = 2.0*asin(l2/2.0);
         theta3 = 2.0*asin(l3/2.0);

         //Compute h=sum(thetai)/2
         h = (theta1+theta2+theta3)/2.0;
         if(M_PI-h < EPS)
         {
            //Point v lies on t, use 2D barycentric coordinates

            mvcW[i][j1] = sin(theta1)*d3*d2;
            mvcW[i][j2] = sin(theta2)*d1*d3;
            mvcW[i][j3] = sin(theta3)*d2*d1;

         }

         c1 = (2*sin(h)*sin(h-theta1))/(sin(theta2)*sin(theta3))-1;
         c2 = (2*sin(h)*sin(h-theta2))/(sin(theta3)*sin(theta1))-1;
         c3 = (2*sin(h)*sin(h-theta3))/(sin(theta1)*sin(theta2))-1;

         double det=0.0;
         det =  u1.x()*(u2.y()*u3.z()-u2.z()*u3.y())
               -u1.y()*(u2.x()*u3.z()-u2.z()*u3.x())
               +u1.z()*(u2.x()*u3.y()-u2.y()*u3.x());
         s1 = sign(det)*sqrt(1-c1*c1);
         s2 = sign(det)*sqrt(1-c2*c2);
         s3 = sign(det)*sqrt(1-c3*c3);

         if(s1<=EPS || s2<=EPS || s3<=EPS)
         {
            continue;
         }

         //Update weights
         mvcW[i][j1] =
               mvcW[i][j1] + (theta1 -c2*theta3-c3*theta2)/(d1*sin(theta2)*s3);

         mvcW[i][j2] =
               mvcW[i][j2] + (theta2 -c3*theta1-c1*theta3)/(d2*sin(theta3)*s1);

         mvcW[i][j3] =
               mvcW[i][j3] + (theta3 -c1*theta2-c2*theta1)/(d3*sin(theta1)*s2);
      }

   }

   //Transfering weights from mvcW to Weights

   weights = new Weights(character->getNumVertices(),cage->getNumVertices());
   for(unsigned long i=0; i<mvcW.size(); ++i)
   {
      double totalW = 0.0;

      for(unsigned long j=0; j<mvcW[i].size(); ++j)
      {
         totalW += mvcW[i][j];
      }

      for(unsigned long j=0; j<mvcW[i].size(); ++j)
      {
         weights->setWeight(j,i,mvcW[i][j]/totalW);
      }
   }

   return true;
}
