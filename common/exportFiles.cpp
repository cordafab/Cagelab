#include "exportFiles.h"

using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

void saveMesh(const char                * filename,
              const std::vector<double> & vertices,
              const std::vector<int>    & faces)
{
   string str(filename);
   string filetype = str.substr(str.size()-3,3);

   if ( filetype.compare("obj") == 0 ||
        filetype.compare("OBJ") == 0    )
   {
      saveOBJ(filename, vertices, faces);
   }
   else
   if ( filetype.compare("ply") == 0 ||
        filetype.compare("PLY") == 0   )
   {
      savePLY(filename, vertices, faces);
   }
   else
   if ( filetype.compare("off") == 0 ||
        filetype.compare("OFF") == 0   )
   {
      //loadOFF(filename, vertices, faces);
   }
   else
   {
      cerr << "ERROR : " << __FILE__ << ", line " << __LINE__ << " : saveMesh() : file format not supported yet " << endl;
      exit(-1);
   }
}

void saveOBJ ( const char                 * filename ,
               const std::vector<double>  & vertices ,
               const std::vector<int>     & faces    )
{
   ofstream fp;
   fp.open (filename);
   fp.precision(6);
   fp.setf( std::ios::fixed, std:: ios::floatfield ); // floatfield set to fixed

   if(!fp)
   {
      cerr << "ERROR : " << __FILE__ << ", line " << __LINE__ << " : saveOBJ() : couldn't open output file " << filename << endl;
      exit(-1);
   }

   for(int i=0; i<(int)vertices.size(); i+=3)
   {
      fp << "v " << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2] << endl;
   }

   for(int i=0; i<(int)faces.size(); i+=3)
   {
      fp << "f " << faces[i]+1 << " " << faces[i+1]+1 << " " << faces[i+2]+1 << endl;
   }

   fp.close();
}


void savePLY(const char                *filename,
             const std::vector<double> & vertices,
             const std::vector<int>    & faces)
{

}


void saveWeights(const char    * filename,
                 const Weights & weights)
{
   ofstream fp;
   fp.open (filename);
   fp.precision(6);
   fp.setf( std::ios::fixed, std::ios::floatfield ); // floatfield set to fixed

   if(!fp)
   {
      cerr << "ERROR : " << __FILE__ << ", line " << __LINE__ << " : saveWeights() : couldn't open output file " << filename << endl;
      exit(-1);
   }

   for( int i = 0; i < (int) weights.getNumberOfVertices(); i++ )
   {

      for( int j = 0; j < (int) weights.getNumberOfHandles(); j++ )
      {

         fp << weights.getWeight(j,i) << " ";

      }

      fp << endl;

   }

   fp.close();
}
