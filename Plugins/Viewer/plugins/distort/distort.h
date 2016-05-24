#ifndef _GLOWING_H
#define _GLOWING_H

#include "basicplugin.h"
#include <QGLShader>
#include <QGLShaderProgram>
#include <QElapsedTimer>

class Distort : public QObject, public BasicPlugin
{
  Q_OBJECT
  Q_INTERFACES(BasicPlugin)
  
public:
  ~Distort();
  inline void onSceneClear() { cleanUpAll(); }
  
  void onPluginLoad();
  bool paintGL();
  
private:
  QGLShaderProgram* program;
  QGLShader* vs;
  QGLShader* fs;  
  GLuint textureId;
  GLuint VAO_rect;
  float time;
  QElapsedTimer *eTimer;  
  
  void cleanUpAll();
};

#endif
