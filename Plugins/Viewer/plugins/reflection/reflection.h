#ifndef _GLOWING_H
#define _GLOWING_H

#include "basicplugin.h"
#include <QGLShader>
#include <QGLShaderProgram>


class Reflection : public QObject, public BasicPlugin
 {
     Q_OBJECT
     Q_INTERFACES(BasicPlugin)

 public:
    void onPluginLoad();
    bool paintGL();
 
 private:
    QGLShaderProgram *m_pProgram;
    QGLShader *m_pVs;
    QGLShader *m_pFs;  
    GLuint m_textureId;
    GLuint m_VAO_rect;
 };
 
 #endif
