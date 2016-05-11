#ifndef _DRAW_VBO_EXT_H
#define _DRAW_VBO_EXT_H

#include <vector>
#include "basicplugin.h"

using namespace std;

class DrawBBox : public QObject, public BasicPlugin
{
  Q_OBJECT
#if QT_VERSION >= 0x050000
  Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif
  Q_INTERFACES(BasicPlugin)
  
public:
  ~DrawBBox();
  void cleanUp();
  void onPluginLoad();
  void onSceneClear();
  void postFrame();
  
private:
  
  GLuint VAO;           // ID of VAOs
  GLuint coordBufferID; // ID of vertex coordinates buffer 
  
  QGLShaderProgram* program;
  QGLShader *fs, *vs; 
  
  int size;
};

#endif


