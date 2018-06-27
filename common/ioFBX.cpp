#include "ioFBX.h"

ioFBX::ioFBX(const char * filename)
{
   file = filename;
   error = false;
   init();
}

ioFBX::~ioFBX()
{
   lSdkManager->Destroy();
   //TODO: Fare anche il destroy di ios e lscene? Oppure vengono eseguiti in automatico? Memory leak?
}

void ioFBX::init(){

   // Create the FBX SDK manager
   lSdkManager = FbxManager::Create();

   ios = FbxIOSettings::Create(lSdkManager, IOSROOT );
   lSdkManager->SetIOSettings(ios);

   // Import options determine what kind of data is to be imported.
   // True is the default, but here we’ll set some to true explicitly, and others to false.
   /*
   (*(lSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_MATERIAL,        false);
   (*(lSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_TEXTURE,         false);
   (*(lSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_LINK,            false);
   (*(lSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_SHAPE,           false);
   (*(lSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_GOBO,            false);
   (*(lSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_ANIMATION,       true);
   (*(lSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
   */

   // Create an importer.
   FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

   // Declare the path and filename of the file containing the scene.
   // In this case, we are assuming the file is in the same directory as the executable.

   // Initialize the importer.
   bool lImportStatus = lImporter->Initialize(file, -1, lSdkManager->GetIOSettings());

   if(!lImportStatus) {

      error = true;

   } else {

      // Create a new scene so it can be populated by the imported file.
      lScene = FbxScene::Create(lSdkManager,"myScene");

      // Import the contents of the file into the scene.
      lImporter->Import(lScene);

      // The file has been imported; we can get rid of the importer.
      lImporter->Destroy();
   }

}

bool ioFBX::loadCharacter(DrawableCharacter * & character, const char * name)
{
   if(error) return false;

   FbxNode* lRootNode = lScene->GetRootNode();

   if(lRootNode)
   {
      for(int i = 0; i < lRootNode->GetChildCount(); i++)
      {

         FbxNode * lNode = lRootNode->GetChild(i);

         if(strcmp(lNode->GetName(),name)==0)
         {

            //FbxMesh* lMesh = (FbxMesh*) lNode->GetNodeAttribute();
            FbxMesh* lMesh = lNode->GetMesh();

            std::vector<double> v;
            int lControlPointsCount = lMesh->GetControlPointsCount();
            v.reserve(lControlPointsCount*3);

            FbxVector4* lControlPoints = lMesh->GetControlPoints();
            FbxAMatrix t = lNode->EvaluateGlobalTransform();

            for (int i = 0; i < lControlPointsCount; i++)
            {
               FbxVector4 controlPoint = t.MultT(lControlPoints[i]);

               v.push_back(controlPoint[0]);
               v.push_back(controlPoint[1]);
               v.push_back(controlPoint[2]);
            }

            std::vector<int> f;
            int lPolygonCount = lMesh->GetPolygonCount();

            f.reserve(lPolygonCount*3);

            for (int i = 0; i < lPolygonCount; i++)
            {
               int lPolygonSize = lMesh->GetPolygonSize(i);
               if (lPolygonSize!=3) return false;
               for (int j = 0; j < lPolygonSize; j++)
               {
                  int lControlPointIndex = lMesh->GetPolygonVertex(i, j);
                  f.push_back(lControlPointIndex);
               }
            }

            //Character creation
            character = new DrawableCharacter(v,f);

            return true;
         }
      }
   }
   return false;
}

bool ioFBX::loadCage(DrawableCage * & cage, const char * name)
{
   if(error) return false;

   FbxNode* lRootNode = lScene->GetRootNode();

   if(lRootNode)
   {
      for(int i = 0; i < lRootNode->GetChildCount(); i++)
      {

         FbxNode * lNode = lRootNode->GetChild(i);

         if(strcmp(lNode->GetName(),name)==0)
         {

            //FbxMesh* lMesh = (FbxMesh*) lNode->GetNodeAttribute();
            FbxMesh* lMesh = lNode->GetMesh();

            std::vector<double> v;
            int lControlPointsCount = lMesh->GetControlPointsCount();
            v.reserve(lControlPointsCount*3);

            FbxVector4* lControlPoints = lMesh->GetControlPoints();
            FbxAMatrix t = lNode->EvaluateGlobalTransform();

            for (int i = 0; i < lControlPointsCount; i++)
            {
               FbxVector4 controlPoint = t.MultT(lControlPoints[i]);

               v.push_back(controlPoint[0]);
               v.push_back(controlPoint[1]);
               v.push_back(controlPoint[2]);
            }

            std::vector<int> f;
            int lPolygonCount = lMesh->GetPolygonCount();

            f.reserve(lPolygonCount*3);

            for (int i = 0; i < lPolygonCount; i++)
            {
               int lPolygonSize = lMesh->GetPolygonSize(i);
               if (lPolygonSize!=3) return false;
               for (int j = 0; j < lPolygonSize; j++)
               {
                  int lControlPointIndex = lMesh->GetPolygonVertex(i, j);
                  f.push_back(lControlPointIndex);
               }
            }

            //Trimesh creation
            cage = new DrawableCage(v,f);
            return true;
         }
      }
   }
   return false;
}

cg3::Transform ioFBX::fromFbxMatrixToTransform(const FbxAMatrix & matrix)
{
   cg3::Transform convertedTransform;

   for(int i=0;i<4;++i)
   {
      for(int j=0;j<4;++j)
      {
         convertedTransform(i,j) = matrix.Get(j,i);  //column major //la get di fbx inverte i valori
      }
   }

   return convertedTransform;
}
