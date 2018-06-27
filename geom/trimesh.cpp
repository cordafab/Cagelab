#include "geom/trimesh.h"

//METHODS DEFINITION

Trimesh::Trimesh()
{

}

Trimesh::Trimesh(const std::vector<double>    & _vertices ,
                 const std::vector<int>       & _tris     )
   : vertices(_vertices),
     tris(_tris)
{
   init();
}

void Trimesh::init()
{
   buildAdjacency();
   updateNormals();
   updateBoundingBox();
}

void Trimesh::clear()
{
   vertices.clear();
   tris.clear();
   verticesNorm.clear();
   trisNorm.clear();
}

void Trimesh::buildAdjacency()
{
   //CODE FROM CAGELAB
   _v2v.clear();
   _v2t.clear();
   _t2t.clear();

   _v2v.resize(getNumVertices());
   _v2t.resize(getNumVertices());
   _t2t.resize(getNumTriangles());

   std::set<edge>     edges;
   std::map<edge,int> edge2tri;

   for(int tId=0; tId<getNumTriangles(); ++tId)
   {
      int tIdPtr = tId * 3;
      for(int i=0; i<3; ++i)
      {
         int vId = tris[tIdPtr + i];
         _v2t[vId].push_back(tId);

         int adj = tris[tIdPtr + (i+1)%3];
         edge e = uniqueEdge(vId,adj);
         edges.insert(e);

         std::map<edge,int>::iterator query = edge2tri.find(e);
         if (query == edge2tri.end())
         {
            edge2tri[e] = tId;
         }
         else
         {
            int nbrTri = query->second;
            _t2t[tId].push_back(nbrTri);
            _t2t[nbrTri].push_back(tId);
         }
      }
   }
   //OLD
   for(std::set<edge>::iterator it=edges.begin(); it!=edges.end(); ++it)
   {
      edge e = *it;
      _v2v[e.first].push_back(e.second);
      _v2v[e.second].push_back(e.first);
   }

   //NEW
   /*for(int v=0; v<getNumVertices(); ++v) //per ogni punto v
   {
      std::vector<int> adjTris = _v2t[v]; //prendo i triangoli adiacenti al punto v
      std::vector<edge> unorderedEdgeLoop;
      unorderedEdgeLoop.reserve(adjTris.size());
      for(int t : adjTris)
      {
         //prendo l'edge opposto al vertice v
         int tPtr = t * 3;
         if(tris[tPtr+0] != v && tris[tPtr+1] != v) unorderedEdgeLoop.push_back(edge(tris[tPtr+0], tris[tPtr+1])); else
         if(tris[tPtr+1] != v && tris[tPtr+2] != v) unorderedEdgeLoop.push_back(edge(tris[tPtr+1], tris[tPtr+2])); else
         if(tris[tPtr+2] != v && tris[tPtr+0] != v) unorderedEdgeLoop.push_back(edge(tris[tPtr+2], tris[tPtr+0]));
      }

      //riordino gli edge opposti a v in modo che l'endpoint di un edge corrisponda con lo start del successivo
      std::vector<edge> orderedEdgeLoop;
      orderedEdgeLoop.reserve(adjTris.size());
      orderedEdgeLoop.push_back(unorderedEdgeLoop[0]);
      while(orderedEdgeLoop.size() != unorderedEdgeLoop.size())
      {
         int i = orderedEdgeLoop.size()-1;
         bool found = false;
         int j=0;
         while(!found)
         {
            if(orderedEdgeLoop[i].second == unorderedEdgeLoop[j].first)
            {
               found = true;
               orderedEdgeLoop.push_back(unorderedEdgeLoop[j]);
            }
            else
            {
               ++j;
            }
         }
      }

      //scorro gli edge e li inserisco nelle adiacenze
      for(int i = 0; i < orderedEdgeLoop.size(); ++i)
      {
         _v2v[v].push_back(orderedEdgeLoop[i].second);
      }
   }
   */

}

void Trimesh::updateNormals()
{
   updateTrisNormals();
   updateVerticesNormals();
}

void Trimesh::updateTrisNormals()
{
   //CODE FROM CAGELAB
   trisNorm.clear();
   trisNorm.resize(getNumTriangles()*3);

   for(int tId=0; tId<getNumTriangles(); ++tId)
   {
      int tIdPtr = tId * 3;

      cg3::Vec3<double> v0 = getVertex(tris[tIdPtr+0]);
      cg3::Vec3<double> v1 = getVertex(tris[tIdPtr+1]);
      cg3::Vec3<double> v2 = getVertex(tris[tIdPtr+2]);

      cg3::Vec3<double> u = v1 - v0;    u.normalize();
      cg3::Vec3<double> v = v2 - v0;    v.normalize();
      cg3::Vec3<double> n = u.cross(v); n.normalize();

      trisNorm[tIdPtr + 0] = n.x();
      trisNorm[tIdPtr + 1] = n.y();
      trisNorm[tIdPtr + 2] = n.z();
   }
}

void Trimesh::updateVerticesNormals()
{
   //CODE FROM CAGELAB
   verticesNorm.clear();
   verticesNorm.resize(getNumVertices()*3);

   for(int vId=0; vId<getNumVertices(); ++vId)
   {
      std::vector<int> nbrs = v2t(vId);

      cg3::Vec3<double> sum(0,0,0);
      for(int i=0; i<(int)nbrs.size(); ++i)
      {
         sum += getTriangleNormal(nbrs[i]);
      }

      //TODO: assert(nbrs.size() > 0);
      sum /= nbrs.size();
      sum.normalize();

      int vIdPtr = vId * 3;
      verticesNorm[vIdPtr + 0] = sum.x();
      verticesNorm[vIdPtr + 1] = sum.y();
      verticesNorm[vIdPtr + 2] = sum.z();
   }
}

void Trimesh::updateBoundingBox()
{
   //CODE FROM CAGELAB
   boundingBox.reset();
   for(int vId=0; vId<getNumVertices(); ++vId)
   {
      cg3::Vec3<double> v = getVertex(vId);
      boundingBox.min = boundingBox.min.min(v);
      boundingBox.max = boundingBox.max.max(v);
   }
}

void Trimesh::exportVerticesToEigen(Eigen::VectorXd & vx,
                                    Eigen::VectorXd & vy,
                                    Eigen::VectorXd & vz)
{
   unsigned int numVert = getNumVertices();
   vx.resize(numVert);
   vy.resize(numVert);
   vz.resize(numVert);

   for(unsigned int i=0; i < numVert; ++i)
   {
      vx[i] = vertices[i*3+0];
      vy[i] = vertices[i*3+1];
      vz[i] = vertices[i*3+2];
   }

   /*v = Eigen::Map<Eigen::VectorXd, Eigen::Unaligned>
         (vertices.data(), vertices.size());*/
}
