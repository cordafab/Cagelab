#include "greenCoordinates.h"

#define EPS 0.00000000001
#define EPS1 0.0000001
#define EPS2 0.00001
#define SCALE 100000
#define sign2(i) ((i >= EPS) ? (1) : (-1))

GreenCoordinates::GreenCoordinates()
{

}

GreenCoordinates::GreenCoordinates(Character * _character,
                                   Cage      * _cage)
   :CageSkinning(_character, _cage)
{

}

GreenCoordinates::~GreenCoordinates()
{

}

void GreenCoordinates::deform()
{
   //Calculation of scaling factors between cage and deformed cage
   calcScalingFactors();
   std::vector<double> cageCoords = cage->getVerticesVector();
   for(unsigned int l=0; l<cageCoords.size(); l++)
      cageCoords[l]*=SCALE;

   //Deformed mesh deformed
   std::vector<double> newCoords;
   //newCoords.resize(3*character->getNumVertices());
   newCoords = character->getVerticesVector();

   cg3::Vec3d vi, normalFj;
   int x,y,z, idV, idC=0;

   //For each η, vertex of the mesh to deform
   for(unsigned int k=0; k<gcV.size(); k++)
   {
      //Init vectors for compute sum
      cg3::Vec3d sumV, sumF, eta;

      double translInvariance = 0.0;

      //For each cage vertex
      for(unsigned int i=0; i<gcV[k].size(); i++)
      {
         //Index for the current vi, is at i*3
         idV = i*3;

         //Retrieve coordinates for vi
         x = cageCoords[idV+0];
         y = cageCoords[idV+1];
         z = cageCoords[idV+2];
         vi.set(x,y,z);

         //Sum φi(η)*vi
         sumV = sumV + (gcV[k][i]*vi);

         translInvariance += gcV[k][i];
      }

      //For each face of the deformed cage
      for(unsigned int j=0; j<gcF[k].size(); j++)
      {
         //Retrieve normal to the face tj
         normalFj =  cage->getTriangleNormal(j);//.triangle_normal(j);
         assert(fabs(1.0-normalFj.length())<1e-4); //Error in normal value

         //Sum ψj(η)*sj*n(t'j)
         sumF = sumF + (gcF[k][j]*gcS[j]*normalFj);
      }

      //New coordinates for each point of the object
      eta = sumV + sumF;

      //Pointer to the current vertex
      idC = k*3;

      //Save coordinates in the array of coordinates (x,y,z) for the current vertex
      newCoords[idC+0] = eta.x();
      newCoords[idC+1] = eta.y();
      newCoords[idC+2] = eta.z();
   }
   for( unsigned int l=0; l<newCoords.size(); l++)
      newCoords[l]/=SCALE;
   character->setVerticesVector(newCoords);
}

bool GreenCoordinates::generateCoords()
{
   //Resize and init gcV, gcF vectors
   gcV.resize(character->getNumVertices());
   gcF.resize(character->getNumVertices());
   //Resize vector of scaling factors
   gcS.resize(cage->getNumTriangles());

   for(int i=0; i<character->getNumVertices(); i++)
   {
      gcV[i].resize(cage->getNumVertices(), 0.0);
      gcF[i].resize(cage->getNumTriangles(), 0.0);
   }

   /**
     *   j = 0 .. cageFaces.size() for each face 3 vertices  j=j+3
     *   i = 0 .. mesh->num_vertices()
     */

   std::vector<double>  cageCoords = cage->getVerticesVector();//.vector_coords();
   std::vector<int>     cageFaces  = cage->getTrianglesVector();//vector_triangles();
   std::vector<double>  objCoords  = character->getVerticesVector();//mesh->vector_coords();
   std::vector<int>     objFaces   = character->getTrianglesVector();//mesh->vector_triangles();

   std::vector<int>     outerPoints;
   std::set<int>        outerFaces;
   std::map<int,int>    triC2triM;

   for(unsigned int l=0; l<objCoords.size(); l++)
   {
      objCoords[l] *= SCALE;
   }
   for(unsigned int l=0; l<cageCoords.size(); l++)
   {
      cageCoords[l] *= SCALE;
   }


   //Vertices of the current cage face, point of the mesh and normal to the current face
   cg3::Vec3d v1, v2, v3, eta, normalF;
   cg3::Vec3d t1, t2, t3;
   double x, y, z;
   int v1_id, v2_id, v3_id;

   //For each point η of the original mesh
   for(int i=0; i<character->getNumVertices(); i++)
   {
      int vid = i*3;

      x = objCoords[vid+0];
      y = objCoords[vid+1];
      z = objCoords[vid+2];

      eta.set(x,y,z);
      cg3::Vec3d zeroeta;

      int idF = 0; //Id of the current face

      //Foreach cage face j with vertices v1 v2 v3
      for(unsigned int j=0; j<cageFaces.size(); j=j+3) //The index for the next face is j = j+3
      {
         //Set vertex coordinates for vertices v1, v2, v3

         //Index for vertices v1,v2,v3 that lies in the face idF
         int j1 = cageFaces[j+0];
         int j2 = cageFaces[j+1];
         int j3 = cageFaces[j+2];


         //Get id for vertices v1,v2,v3
         v1_id = 3*j1;
         v2_id = 3*j2;
         v3_id = 3*j3;


         //Coords of v1
         x = cageCoords[v1_id];
         y = cageCoords[v1_id+1];
         z = cageCoords[v1_id+2];
         t1.set(x,y,z);

         //Coords of v2
         x = cageCoords[v2_id];
         y = cageCoords[v2_id+1];
         z = cageCoords[v2_id+2];
         t2.set(x,y,z);

         //Coords of v3
         x = cageCoords[v3_id];
         y = cageCoords[v3_id+1];
         z = cageCoords[v3_id+2];
         t3.set(x,y,z);

         //Compute normal to the face
         normalF = cage->getTriangleNormal(idF); //cage.triangle_normal(idF);
         assert(fabs(1.0-normalF.length())<1e-4); //Error in normal value



         //Compute vj = vj - η for j=1,2,3
         v1 = t1 - eta;
         v2 = t2 - eta;
         v3 = t3 - eta;

         //Compute p = scalarproduct((v1-0),normalF)*normalF
         cg3::Vec3d p = ((v1-zeroeta).dot(normalF))*normalF;

         // l=1
         double myInt1=0;
         //Compute scalarproduct((v1-p)x(v2-p))*normalF
         double mysign1 = ((v1-p).cross(v2-p)).dot(normalF);
         //Compute sign of mysign1
         mysign1 = sign2(mysign1);

         myInt1 = gcTriInt(p, v1, v2, zeroeta);


         double myInt2=0;
         //Compute scalarproduct((v2-p)x(v3-p))*normalF
         double mysign2 = ((v2-p).cross(v3-p)).dot(normalF);
         //Compute sign of mysign2
         mysign2 = sign2(mysign2);

         myInt2 = gcTriInt(p, v2, v3, zeroeta);


         double myInt3=0;
         //Compute scalarproduct((v3-p)x(v1-p))*normalF
         double mysign3 = ((v3-p).cross(v1-p)).dot(normalF);
         //Compute sign of mysign3
         mysign3 =  sign2(mysign3);

         myInt3 = gcTriInt(p, v3, v1, zeroeta);


         //I = |s1 I1 + s2 I2 + s3 I3 |
         double I_t = -abs(mysign1*myInt1 + mysign2*myInt2 + mysign3*myInt3);


         //ψj(η)
         double II = -I_t;

         //Robustness check
         if(II != II)
         {
            std::cout <<"NAN";
         }


         //II_l for l=1,2,3 for triangle t' in N(t)
         double I_tp1 = gcTriInt(zeroeta, v2, v1, zeroeta );
         double I_tp2 = gcTriInt(zeroeta, v3, v2, zeroeta );
         double I_tp3 = gcTriInt(zeroeta, v1, v3, zeroeta );


         /*************************************************
            * Compute ql for l=1,2,3 and Nl = ql / ||ql||
            * ***********************************************/

         //l=1
         cg3::Vec3d n1 = (v2-zeroeta).cross(v1-zeroeta);
         double sn1 = n1.length();
         if(sn1 < EPS1)
         {
            I_tp1 = 0.0;
         }
         else
         {
            n1.normalize();
         }


         //l=2
         cg3::Vec3d n2 = (v3-zeroeta).cross(v2-zeroeta);
         double sn2 = n2.length();
         if(sn2 < EPS1)
         {
            I_tp2 = 0.0;
         }
         else
         {
            n2.normalize();
         }


         //l=3
         cg3::Vec3d n3 = (v1-zeroeta).cross(v3-zeroeta);
         double sn3 = n3.length();
         if(sn3 < EPS1)
         {
            I_tp3 = 0.0;
         }
         else
         {
            n3.normalize();
         }


         cg3::Vec3d w = zeroeta + normalF*I_t + (n1*I_tp1 + n2*I_tp2 + n3*I_tp3);
         //Check if v1, v2, v3 are on the same plane - If so don't contribute to psi
         double wl = w.length();

         if(wl<EPS2)
         {
            if(mysign1>0 && mysign2>0 && mysign3>0)
            {
               //The point is inside de face remember factor 2
               gcS[i] = 1.0+idF; //add face index for later to recognize the face
            }
         }
         else
         {
            double I1 = (n2.dot(w)) / (n2.dot(v1));
            double I2 = (n3.dot(w)) / (n3.dot(v2));
            double I3 = (n1.dot(w)) / (n1.dot(v3));

            //Update φj(η)
            /*
                * For each vertex its φj(η) value is saved at index cageFaces[j]
                * pointer to x value into cageCoords is vj_id (3*cageFaces[j])
                *
                **/
            gcV[i][j1] = gcV[i][j1] + I1;
            gcV[i][j2] = gcV[i][j2] + I2;
            gcV[i][j3] = gcV[i][j3] + I3;

         }
         //Not using any normalization here only at deformation time
         //ψidF(η)
         gcF[i][idF] = II;

         //Go to next face
         idF++;
      }

      /************************************************************
        *  Determines which points need the update of the coordinates
        ************************************************************/
      double sumV=0.0;
      for(unsigned int j=0; j<gcV[i].size(); j++)
      {
         sumV += gcV[i][j];
      }
      //eta is outside the cage
      if(sumV<0.5)
      {
         //Insert id of point that lies outside cage (need to update coordinates)
         outerPoints.push_back(i);
      }
   }

   /** **********************************************************ù
    *
    *    EXTENSION COORDINATES OUTSIDE CAGE
    *
    * **********************************************************/

   /********************************************************
    * FIND INTERSECTION BETWEEN CAGE AND MESH:
    * -Determines which faces of the cage intersect mesh
    * ******************************************************/
   for(unsigned int it=0; it<outerPoints.size(); it++)
   {
      //Searches for faces that contains the vertex
      for(unsigned int fi=0; fi<objFaces.size(); fi++)
      {
         if(objFaces[fi]==outerPoints[it])
         {
            //Insert id of the face
            outerFaces.insert(fi/3);
         }
      }
   }

   int idf = 0;
   //Foreach cage face l with vertices v1 v2 v3
   for(unsigned int j=0; j<cageFaces.size(); j=j+3)
   {
      cg3::Vec3d centerCage = cage->getTriangleBarycenter(idf);//cage.faceCenter(idf);

      //Set vertex coordinates for vertices v1, v2, v3
      cg3::Vec3d v1, v2, v3;

      //Index for vertices v1,v2,v3 that lies in the face idF
      int j1 = cageFaces[j+0];
      int j2 = cageFaces[j+1];
      int j3 = cageFaces[j+2];


      //Get id for vertices v1,v2,v3
      v1_id = 3*j1;
      v2_id = 3*j2;
      v3_id = 3*j3;


      //Coords of v1
      x = cageCoords[v1_id];
      y = cageCoords[v1_id+1];
      z = cageCoords[v1_id+2];
      v1.set(x,y,z);

      //Coords of v2
      x = cageCoords[v2_id];
      y = cageCoords[v2_id+1];
      z = cageCoords[v2_id+2];
      v2.set(x,y,z);

      //Coords of v3
      x = cageCoords[v3_id];
      y = cageCoords[v3_id+1];
      z = cageCoords[v3_id+2];
      v3.set(x,y,z);

      cg3::Vec3d n = cage->getTriangleNormal(idf);//cage.triangle_normal(idf);
      double d =  -(x*n.x()+y*n.y()+z*n.z());

      std::set<int>::iterator fit;
      fit = outerFaces.begin();
      bool intFounded = false;
      double minDist=DBL_MAX;

      while(fit != outerFaces.end() && (!intFounded))
      {

         int id_f = *fit;
         cg3::Vec3d centerObj = character->getTriangleBarycenter(id_f);//mesh->faceCenter(id_f);
         double currDist=(centerCage-centerObj).length();

         if(currDist<minDist)
         {

            id_f *=3;

            int e1_id, e2_id, e3_id, xe, ye, ze;
            cg3::Vec3d e1, e2, e3;

            e1_id = objFaces[id_f+0];
            e2_id = objFaces[id_f+1];
            e3_id = objFaces[id_f+2];


            //Set coords for v1
            xe = objCoords[3*e1_id+0];
            ye = objCoords[3*e1_id+1];
            ze = objCoords[3*e1_id+2];
            e1.set(xe,ye,ze);

            //Set coords for v2
            xe = objCoords[3*e2_id+0];
            ye = objCoords[3*e2_id+1];
            ze = objCoords[3*e2_id+2];
            e2.set(xe,ye,ze);

            //Set coords for v3
            xe = objCoords[3*e3_id+0];
            ye = objCoords[3*e3_id+1];
            ze = objCoords[3*e3_id+2];
            e3.set(xe,ye,ze);


            Eigen::Matrix4d S1, S2, S3;
            Eigen::Vector4d f1;
            Eigen::Vector4d f2;
            Eigen::Vector4d f3;
            Eigen::Vector4d f4;
            Eigen::Vector4d b;

            //Detect intersection between edge e2-e1 and the plain in which triangle lies
            f1 << -1.0,  0.0,  0.0, n.x();
            f2 <<  0.0, -1.0,  0.0, n.y();
            f3 <<  0.0,  0.0, -1.0, n.z();
            f4 <<  (e2.x()-e1.x()), (e2.y()-e1.y()), (e2.z()-e1.z()), 0;
            S1.col(0) = f1;
            S1.col(1) = f2;
            S1.col(2) = f3;
            S1.col(3) = f4;

            b << -e1.x(), -e1.y(), -e1.z(), -d;

            Eigen::Vector4d sol1 = S1.fullPivLu().solve(b);

            //Lambda e mi, used to test if the intersection is inside the triangle
            double lambda=0.0, mi=0.0;

            //Check if line (edge 1) intersect the plane, defined by cage triangle
            if(sol1[3]>=0 && sol1[3]<=1)
            {
               //Check if point P, founded from line/plane intersection is inside triangle cage
               lambda = (((sol1[0]-v1.x())*(v2.y()-v1.y())) - ((sol1[1]-v1.y())*(v2.x()-v1.x()))) /
                     ( ((v3.x()-v1.x())*(v2.y()-v1.y())) - ((v3.y()-v1.y())*(v2.x()-v1.x())) );

               mi = -( ((sol1[0]-v1.x())*(v3.y()-v1.y()))-((sol1[1]-v1.y())*(v3.x()-v1.x())) ) /
                     ( ((v3.x()-v1.x())*(v2.y()-v1.y())) - ((v3.y()-v1.y())*(v2.x()-v1.x())) );

               //Cage triangle intersect mesh triangle (this face is a feasible exitFace)
               if(lambda>=0 && mi>=0 && ((lambda+mi)<=1)) //Is inside, intersection founded
               {
                  //Insert id of the face into exitFaces vector
                  exitFaces.push_back(idf);
                  //Go to next cage face
                  intFounded = true;
               }
               else //No real intersection, Test the next edge
               {
                  //Detect intersection between edge e3-e2 and the plain in which triangle lies
                  f1 << -1.0,  0.0,  0.0, n.x();
                  f2 <<  0.0, -1.0,  0.0, n.y();
                  f3 <<  0.0,  0.0, -1.0, n.z();
                  f4 <<  (e3.x()-e2.x()), (e3.y()-e2.y()), (e3.z()-e2.z()), 0;
                  S2.col(0) = f1;
                  S2.col(1) = f2;
                  S2.col(2) = f3;
                  S2.col(3) = f4;

                  b << -e2.x(), -e2.y(), -e2.z(), -d;

                  Eigen::Vector4d sol2 = S2.fullPivLu().solve(b);

                  //Check if line (edge 2) intersect the plane, defined by cage triangle
                  if(sol2[3]>=0 && sol2[3]<=1)
                  {
                     //Check if point P, founded from line/plane intersection is inside triangle cage
                     lambda = (((sol2[0]-v1.x())*(v2.y()-v1.y())) - ((sol2[1]-v1.y())*(v2.x()-v1.x()))) /
                           ( ((v3.x()-v1.x())*(v2.y()-v1.y())) - ((v3.y()-v1.y())*(v2.x()-v1.x())) );

                     mi = -( ((sol2[0]-v1.x())*(v3.y()-v1.y()))-((sol2[1]-v1.y())*(v3.x()-v1.x())) ) /
                           ( ((v3.x()-v1.x())*(v2.y()-v1.y())) - ((v3.y()-v1.y())*(v2.x()-v1.x())) );

                     //Cage triangle intersect mesh triangle (this face is a feasible exitFace)
                     if(lambda>=0 && mi>=0 && ((lambda+mi)<=1)) //Is inside, intersection founded
                     {
                        //Insert id of the face into exitFaces vector
                        exitFaces.push_back(idf);
                        intFounded = true;
                     }
                  }
                  else //No intersection, test the last edge
                  {
                     //Detect intersection between edge e1-e3 and the plain in which triangle lies
                     f1 << -1.0,  0.0,  0.0, n.x();
                     f2 <<  0.0, -1.0,  0.0, n.y();
                     f3 <<  0.0,  0.0, -1.0, n.z();
                     f4 <<  (e1.x()-e3.x()), (e1.y()-e3.y()), (e1.z()-e3.z()), 0;
                     S3.col(0) = f1;
                     S3.col(1) = f2;
                     S3.col(2) = f3;
                     S3.col(3) = f4;

                     b << -e3.x(), -e3.y(), -e3.z(), -d;

                     Eigen::Vector4d sol3 = S3.fullPivLu().solve(b);

                     //Check if line (edge 2) intersect the plane, defined by cage triangle
                     if(sol3[3]>=0 && sol3[3]<=1)
                     {

                        lambda = (((sol3[0]-v1.x())*(v2.y()-v1.y())) - ((sol3[1]-v1.y())*(v2.x()-v1.x()))) /
                              ( ((v3.x()-v1.x())*(v2.y()-v1.y())) - ((v3.y()-v1.y())*(v2.x()-v1.x())) );

                        mi = -( ((sol3[0]-v1.x())*(v3.y()-v1.y()))-((sol3[1]-v1.y())*(v3.x()-v1.x())) ) /
                              ( ((v3.x()-v1.x())*(v2.y()-v1.y())) - ((v3.y()-v1.y())*(v2.x()-v1.x())) );

                        //Cage triangle intersect mesh triangle (this face is a feasible exitFace)
                        if(lambda>=0 && mi>=0 && ((lambda+mi)<=1)) //Is inside, intersection founded
                        {
                           //Insert id of the face into exitFaces vector
                           exitFaces.push_back(idf);
                           intFounded = true;
                        }
                        else
                        {
                           if(currDist<minDist)
                              minDist = currDist;
                        }
                     }
                  }

               }
            }
         }
         ++fit;
      }
      idf++;
   }

   //Update Coordinates for points outside cage
   for(unsigned int j=0; j<outerPoints.size(); j++)
   {
      int vid = 3*outerPoints[j];
      int i = outerPoints[j];
      cg3::Vec3d eta;

      x = objCoords[vid+0];
      y = objCoords[vid+1];
      z = objCoords[vid+2];

      eta.set(x,y,z);


      int closestF = -1;
      //Determine the correct exit face
      for(unsigned int h=0; h<exitFaces.size(); h++)
      {
         int v0_id = cageFaces[3*exitFaces[h]];
         cg3::Vec3d v0;
         int x0,y0,z0;

         //Coords of v0
         x0 = cageCoords[v0_id];
         y0 = cageCoords[v0_id+1];
         z0 = cageCoords[v0_id+2];
         v0.set(x0,y0,z0);

         double side=0.0;

         side = (cage->getTriangleNormal(exitFaces[h])).dot(eta-v0);

         //If side > 0, then the point is on the side of the plane the normal is pointing towards
         if(side>=0)
         {
            closestF = exitFaces[h];
         }
      }
      if(closestF==-1) //No Face founded, Bind point with closest face
      {
         //If there is only one exit face, unclassified points are mapped to this face
         if(exitFaces.size()==1)
         {
            closestF = exitFaces[0];
         }
         else
         {
            //Search the closest exit face for unclassified points
            double minDist = DBL_MAX;

            //Looking for face nearest to the point eta (exit face)
            for(unsigned int j=0; j<exitFaces.size(); j++)
            {
               cg3::Vec3d centerF = cage->getTriangleBarycenter(exitFaces[j]);
               double dist = (eta-centerF).length();
               if(dist<minDist)
               {
                  minDist = dist;
                  //Id of the closest face
                  closestF = exitFaces[j];
               }
            }
         }
      }

      if(closestF==-1)
         std::cout<<"ALERT";

      //Get the ids of the vertices that lie on the face
      double  x,y,z;
      std::vector<cg3::Vec3d> vFace(3);
      int j1,j2,j3;

      j1 = cageFaces[3*closestF+0];
      j2 = cageFaces[3*closestF+1];
      j3 = cageFaces[3*closestF+2];

      //Get id for vertices v1,v2,v3
      v1_id = 3*j1;
      v2_id = 3*j2;
      v3_id = 3*j3;

      //Coords of v1
      x = cageCoords[v1_id];
      y = cageCoords[v1_id+1];
      z = cageCoords[v1_id+2];
      vFace[0].set(x,y,z);

      //Coords of v2
      x = cageCoords[v2_id];
      y = cageCoords[v2_id+1];
      z = cageCoords[v2_id+2];
      vFace[1].set(x,y,z);

      //Coords of v3
      x = cageCoords[v3_id];
      y = cageCoords[v3_id+1];
      z = cageCoords[v3_id+2];
      vFace[2].set(x,y,z);

      // compute alpha[3] and beta
      Eigen::Matrix4d A;
      for (int l = 0; l < 3; l++)
      {
         Eigen::Vector4d fp; fp << vFace[l].x(), vFace[l].y(), vFace[l].z(), 1.0;
         A.col(l) = fp;
      }

      Eigen::Vector4d fn; fn << cage->getTriangleNormal(closestF).x(),
            cage->getTriangleNormal(closestF).y(),
            cage->getTriangleNormal(closestF).z(),
            0.0;
      A.col(3) = fn;

      Eigen::Vector4d pnt; pnt << eta.x(), eta.y(), eta.z(), 1.0;

      Eigen::Vector4d xsol = A.fullPivLu().solve(pnt);

      //Update φj(η) for point η, that lies outside cage

      gcV[i][j1] = gcV[i][j1] + xsol[0];
      gcV[i][j2] = gcV[i][j2] + xsol[1];
      gcV[i][j3] = gcV[i][j3] + xsol[2];

      //Update ψclosestF(η) for point η for the exit face (closestF)
      gcF[i][closestF] = gcF[i][closestF] + xsol[3];
   }

   return true;

}

Weights *GreenCoordinates::getWeightsV()
{
   return weightsV;
}

Weights *GreenCoordinates::getWeightsF()
{
   return weightsF;
}

double GreenCoordinates::gcTriInt(const cg3::Vec3d & p,
                                  const cg3::Vec3d & t1,
                                  const cg3::Vec3d & t2,
                                  const cg3::Vec3d & eta)
{

   //t2-t1
   cg3::Vec3d t2mt1 = t2-t1;
   //p-t1
   cg3::Vec3d pmt1 = p-t1;
   //p-t2
   cg3::Vec3d pmt2 = p-t2;

   //norma di p-t1 e p-t2
   double lpmt1 = pmt1.length();
   double lpmt2 = pmt2.length();
   //norma di t1-t2
   double lt2mt1 = t2mt1.length();


   //Compute ((t2-t1)(p-t1)) / (||t2-t1||*||p-t1||)
   double den = (lt2mt1*lpmt1);
   double tmpval = (t2mt1.dot(pmt1)) / den;

   //Exit condition
   if(abs(tmpval)>(1.0-EPS))
   {
      return 0.0;
   }

   double alpha = acos(tmpval);

   //Exit condition


   if(abs(alpha-M_PI) < EPS || abs(alpha) < EPS)
   {
      return 0.0;
   }

   //Compute ((p-t1)(p-t2)) / (||p-t1||*||p-t2||)
   den = (lpmt1*lpmt2);
   tmpval = (pmt1.dot(pmt2)) / (den);

   //Exit condition
   if(abs(tmpval)>(1.0-EPS))
   {
      return 0.0;
   }

   double beta = acos(tmpval);

   double lambda = pmt1.lengthSquared()*sin(alpha)*sin(alpha);

   //First value of delta
   double delta = M_PI-alpha;

   cg3::Vec3d pmeta = p-eta;

   // c=||p-eta||^2
   double c = pmeta.lengthSquared();

   double sqrt_c = sqrt(c);

   //Direct calculation
   double sqrt_l = sqrt(lambda);
   double S = sin(delta);
   double C = cos(delta);

   //Compute sign of S
   double sign_S = sign2(S);

   //Compute I and II values
   double I=0.0, II=0.0;

   //Idelta
   double den1=0.0, den2=0.0, den3=0.0;
   den1 = (sqrt(lambda+c*S*S) );
   den2 = (c*(1+C)+lambda+sqrt_l*sqrt(lambda+c*S*S));
   den3 = pow((1-C),2);


   I = -0.5*sign_S*( 2*sqrt_c*atan((sqrt_c*C) / (den1) )+sqrt_l*log(((sqrt_l*(1-2*c*C/(den2))))*(2*S*S/(den3))));


   //Update value for delta, S, C and sign od S
   delta = delta-beta;
   S = sin(delta);
   C = cos(delta);
   sign_S = sign2(S);

   den1 = (sqrt(lambda+c*S*S) );
   den2 = (c*(1+C)+lambda+sqrt_l*sqrt(lambda+c*S*S));
   den3 = pow((1-C),2);

   //IIdelta
   II = -0.5*sign_S*( 2*sqrt_c*atan((sqrt_c*C) / den1 )+sqrt_l*(log((sqrt_l*(1-2*c*C/den2))*(2*S*S/den3))));


   //Compute myInt and return value
   double myInt = (-1.0/(4*M_PI))*abs(I-II-sqrt_c*beta);
   return myInt;

}

void GreenCoordinates::calcScalingFactors() //È necessaria la deformed cage?
{
   std::vector<int>    oldFaces  = cage->getTrianglesVector();
   std::vector<double> oldCoords = cage->getRestPoseVerticesVector(); //.vector_coords();

   std::vector<int>    newFaces  = cage->getTrianglesVector(); //deformedCage.vector_triangles();
   std::vector<double> newCoords = cage->getVerticesVector(); //deformedCage.vector_coords();

   //Id of the current face
   int idF = 0;

   for(unsigned int j=0; j<oldFaces.size(); j=j+3)
   {
      /*
            * Get vertex coordinates for face of the old cage
            */

      //Pointer to vertices of the current face
      int v1_id, v2_id, v3_id;

      v1_id =  3*oldFaces[j+0];
      v2_id =  3*oldFaces[j+1];
      v3_id =  3*oldFaces[j+2];

      //Vertices of the current face
      //vec3d v1 = new vec3d(), v2 = new vec3d(), v3 = new vec3d();
      cg3::Vec3d v1, v2,v3;
      double x,y,z;

      //Get coordinate for vertex v1
      x = oldCoords[v1_id+0];
      y = oldCoords[v1_id+1];
      z = oldCoords[v1_id+2];
      v1.set(x, y, z);


      //Get coordinate for vertex v2
      x = oldCoords[v2_id+0];
      y = oldCoords[v2_id+1];
      z = oldCoords[v2_id+2];
      v2.set(x, y, z);


      //Get coordinate for vertex v3
      x = oldCoords[v3_id+0];
      y = oldCoords[v3_id+1];
      z = oldCoords[v3_id+2];
      v3.set(x, y, z);

      //T with edge defined by the vectors u and v
      cg3::Vec3d u = (v1-v2);
      cg3::Vec3d v = (v1-v3);

      //Area of triangle T  - Area of triangle: 0.5 * | u x v |
      double areaT = 0.5*(u.cross(v)).length();

      /*
            * Get vertex coordinates for face of the deformed cage
            */

      //Pointer to vertices of the current face

      v1_id =  3*newFaces[j+0];
      v2_id =  3*newFaces[j+1];
      v3_id =  3*newFaces[j+2];

      //Vertices of the current face

      //Get coordinate for vertex v1
      x = newCoords[v1_id+0];
      y = newCoords[v1_id+1];
      z = newCoords[v1_id+2];
      v1.set(x, y, z);


      //Get coordinate for vertex v2
      x = newCoords[v2_id+0];
      y = newCoords[v2_id+1];
      z = newCoords[v2_id+2];
      v2.set(x, y, z);


      //Get coordinate for vertex v3
      x = newCoords[v3_id+0];
      y = newCoords[v3_id+1];
      z = newCoords[v3_id+2];
      v3.set(x, y, z);

      //T1 with edge defined by the vectors u1 and w1
      cg3::Vec3d u_p = (v1-v2);
      cg3::Vec3d v_p = (v1-v3);


      //Compute scaling factor
      gcS[idF] = (sqrt( u_p.lengthSquared()*v.lengthSquared() - 2*((u_p.dot(v_p))*(u.dot(v)))
                        + v_p.lengthSquared()*u.lengthSquared()) ) / (sqrt(8)*areaT);

      //Next face
      idF++;
   }
}
