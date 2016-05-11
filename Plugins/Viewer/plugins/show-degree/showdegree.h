#ifndef SHOWDEGREE_H
#define SHOWDEGREE_H

#include "basicplugin.h"

class ShowDegree : public QObject,  public BasicPlugin
{
  Q_OBJECT
#if QT_VERSION >= 0x050000
  Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif
  Q_INTERFACES(BasicPlugin)

  const int SIZE = 1024;
  
public:  
  ShowDegree();
  
  void onPluginLoad();
  void postFrame();
  
  GLuint textureID;
  float m_degree;
  QGLShaderProgram* program;
  QGLShader* vs;
  QGLShader* fs;
};

#endif // SHOWDEGREE_H
