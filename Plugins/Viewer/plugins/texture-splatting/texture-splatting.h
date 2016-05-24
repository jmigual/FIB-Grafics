#ifndef _MULTITEX_H
#define _MULTITEX_H

#include "basicplugin.h"
#include <QGLShader>
#include <QGLShaderProgram>


class TextureSplatting : public QObject, public BasicPlugin
 {
     Q_OBJECT
     Q_INTERFACES(BasicPlugin)

 public:
    void onPluginLoad();
    void preFrame();
    void postFrame();
    
 private:
    QGLShaderProgram *m_pProgram;
    QGLShader *m_pVs;
    QGLShader *m_pFs; 
    GLuint m_textureId0;
    GLuint m_textureId1;
    GLuint m_textureId2;
 };
 
 #endif
