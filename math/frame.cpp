#include "frame.h"

//TEST ROTATION CONVERSION
//#include "cinolib/simplicial_map.h"
//#include "cinolib/matrix.h"

namespace cg3
{

Frame::Frame()
{

}

Frame::Frame(Vec3d u, Vec3d v, Vec3d w, Vec3d o)
{
   setFrame(u,v,w,o);
}

void Frame::setFrame(Vec3d u, Vec3d v, Vec3d w, Vec3d o)
{
   /*frame <<
      u[0], v[0], w[0], o[0],
      u[1], v[1], w[1], o[1],
      u[2], v[2], w[2], o[2],
         0,    0,    0,    1;*/
   _u = u;
   _v = v;
   _w = w;
   _o = o;

   createRotationMatrixes();
}

Vec3d Frame::LocalToGlobal(Vec3d vLocal)
{
   cg3::Vec3d globalFrame = vLocal.x()*_u+
                            vLocal.y()*_v+
                            vLocal.z()*_w
                            ;
   /*std::cout << "Local to global." << std::endl;
   std::cout << "Local x: "  << vLocal.x()
             << ".y: "       << vLocal.y()
             << ".z: "       << vLocal.z()      << std::endl;
   std::cout << "frame u: "  << _u
             << ".v: "       << _v
             << ".w: "       << _w
             << ".o: "       << _o << std::endl;
   std::cout << "Global x: " << globalFrame.x()
             << ".y: "       << globalFrame.y()
             << ".z: "       << globalFrame.z() << std::endl << std::endl;*/

   return globalFrame;
}

Vec3d Frame::GlobalToLocal(Vec3d vGlobal)
{
   //double u = (vGlobal-_o).dot(_u);
   //double v = (vGlobal-_o).dot(_v);
   //double w = (vGlobal-_o).dot(_w);
   double u = (vGlobal).dot(_u);
   double v = (vGlobal).dot(_v);
   double w = (vGlobal).dot(_w);

   /*std::cout << "Global to local." << std::endl;
   std::cout << "Global x: " << vGlobal.x()
             << ".y: "       << vGlobal.y()
             << ".z: "       << vGlobal.z() << std::endl;
   std::cout << "frame u: "  << _u
             << ".v: "       << _v
             << ".w: "       << _w
             << ".o: "       << _o          << std::endl;
   std::cout << "Local x: "  << u
             << ".y: "       << v
             << ".z: "       << w           << std::endl << std::endl;*/

   return Vec3d(u,v,w);
}

//http://www.meshola.com/Articles/converting-between-coordinate-systems

Transform Frame::LocalToGlobal(Transform tLocal)
{
   //return tLocal.cumulateWith(rotationMatrixLocalToGlobal);
}

Transform Frame::GlobalToLocal(Transform tGlobal)
{
   //return tGlobal.cumulateWith(rotationMatrixGlobalToLocal);
}

void Frame::createRotationMatrixes()
{
   //PROVA 1
   /*cg3::Vec3d x1(1,0,0);cg3::Vec3d y1(0,1,0);cg3::Vec3d z1(0,0,1);
   double m[3][3];
   double t[3];
   cinolib::affine_simplicial_map(Vec3d(0,0,0),
                                  x1,
                                  y1,
                                  z1,
                                  Vec3d(0,0,0),
                                  _u,
                                  _v,
                                  _w,
                                  m,
                                  t);

   rotationMatrixGlobalToLocal = cg3::Transform(cg3::Vec3d(m[0][0], m[1][0], m[2][0]),
                                                cg3::Vec3d(m[0][1], m[1][1], m[2][1]),
                                                cg3::Vec3d(m[0][2], m[1][2], m[2][2]));
   rotationMatrixLocalToGlobal = rotationMatrixGlobalToLocal.inverse();*/




   //PROVA 2
   //cg3::Transform identity;
   //cg3::Transform matrix(_u, _v, _w);

   //rotationMatrixGlobalToLocal = matrix.cumulateWith(identity.inverse());
   //rotationMatrixLocalToGlobal = identity.cumulateWith(matrix.inverse());


   //PROVA 3
   //cg3::Vec3d x1(1,0,0);cg3::Vec3d y1(0,1,0);cg3::Vec3d z1(0,0,1);
   //LocalToGlobal //Dovrebbe essere identico alla matrice sopra
   /*rotationMatrixLocalToGlobal(0,0) = _u.dot(x1);
   rotationMatrixLocalToGlobal(0,1) = _u.dot(y1);
   rotationMatrixLocalToGlobal(0,2) = _u.dot(z1);
   rotationMatrixLocalToGlobal(1,0) = _v.dot(x1);
   rotationMatrixLocalToGlobal(1,1) = _v.dot(y1);
   rotationMatrixLocalToGlobal(1,2) = _v.dot(z1);
   rotationMatrixLocalToGlobal(2,0) = _w.dot(x1);
   rotationMatrixLocalToGlobal(2,1) = _w.dot(y1);
   rotationMatrixLocalToGlobal(2,2) = _w.dot(z1);

   //GlobalToLocal
   rotationMatrixGlobalToLocal = rotationMatrixLocalToGlobal.inverse();*/

}

}
