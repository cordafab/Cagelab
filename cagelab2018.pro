QT += core gui opengl xml widgets

TARGET   = Cagelab2018
TEMPLATE = app

CONFIG += c++11

HEADERS = \
    GUI/glCanvas.h \
    GUI/mainWindow.h \
    geom/trimesh.h \
    geom/boundingBox.h \
    geom/vec3.h \
    geom/edge.h \
    drawables/drawableObject.h \
    drawables/drawableTrimesh.h \
    common/importFiles.h \
    controller.h \
    GUI/qtUtils.h \
    geom/cage.h \
    drawables/drawableCage.h \
    GUI/glUtils.h \
    drawables/pickerController.h \
    drawables/pickableObject.h \
    geom/plane.h \
    common/ioFBX.h \
    geom/transform.h \
    common/types.h \
    skinning/weights.h \
    skinning/meanValueCoordinates.h \
    skinning/cageSkinning.h \
    GUI/clickConverter.h \
    common/cageOperations.h \
    common/fbxOperations.h \
    GUI/cagePanel.h \
    GUI/fbxImportPanel.h \
    common/texture.h \
    common/exportFiles.h \
    geom/character.h \
    drawables/drawableCharacter.h \
    GUI/characterPanel.h \
    common/toolsOperation.h \
    GUI/toolsPanel.h \
    common/characterOperations.h \
    math/leastSquareSolver.h \
    math/quaternion.h \
    geom/ray.h \
    skinning/greenCoordinates.h \
    skinning/noCageSkinning.h

SOURCES = \
    main.cpp \
    GUI/glCanvas.cpp \
    GUI/mainWindow.cpp \
    geom/boundingBox.cpp \
    drawables/drawableObject.cpp \
    drawables/drawableTrimesh.cpp \
    common/importFiles.cpp \
    controller.cpp \
    GUI/qtUtils.cpp \
    drawables/drawableCage.cpp \
    GUI/glUtils.cpp \
    drawables/pickableObject.cpp \
    drawables/pickerController.cpp \
    common/ioFBX.cpp \
    geom/transform.cpp \
    common/types.cpp \
    skinning/weights.cpp \
    skinning/meanValueCoordinates.cpp \
    skinning/cageSkinning.cpp \
    GUI/clickConverter.cpp \
    common/cageOperations.cpp \
    common/fbxOperations.cpp \
    GUI/cagePanel.cpp \
    GUI/fbxImportPanel.cpp \
    common/exportFiles.cpp \
    geom/trimesh.cpp \
    geom/cage.cpp \
    geom/character.cpp \
    drawables/drawableCharacter.cpp \
    GUI/characterPanel.cpp \
    common/toolsOperation.cpp \
    GUI/toolsPanel.cpp \
    common/characterOperations.cpp \
    skinning/greenCoordinates.cpp \
    skinning/noCageSkinning.cpp

FORMS *= \
    GUI/mainWindow.ui \
    GUI/cagePanel.ui \
    GUI/fbxImportPanel.ui \
    GUI/characterPanel.ui \
    GUI/toolsPanel.ui



## LIB libQGLViewer configurations

#  Windows
#INCLUDEPATH += C:/Users/login/Documents/libQGLViewer-2.6.4
#LIBS += -LC:/Users/login/Documents/libQGLViewer-2.6.4/QGLViewer -lQGLViewer2

# Linux
#INCLUDEPATH += /home/login/Documents/libQGLViewer-2.6.4
#LIBS += -L/home/login/libQGLViewer-2.6.4/QGLViewer -lQGLViewer

# Mac
macx: INCLUDEPATH += /Library/Frameworks/QGLViewer.framework/Headers
macx: LIBS += -F/Library/Frameworks -framework QGLViewer

## End libQGLViewer configurations


## LIB FBX configurations

#Mac
macx: LIBS += -L'/Applications/Autodesk/FBX SDK/2018.1.1/lib/clang/release/' -lfbxsdk
macx: INCLUDEPATH +='/Applications/Autodesk/FBX SDK/2018.1.1/include/'

## End FBX configurations


## LIB Eigen configurations

# Mac
macx: INCLUDEPATH += /libs/include/eigen

## End Eigen configurations


## LIB glm configurations

# Mac
macx: INCLUDEPATH += /libs/include/glm

## End glm configurations
