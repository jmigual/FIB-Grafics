#ifndef _MOUSESELECT_H
#define _MOUSESELECT_H

#include "basicplugin.h"

class MouseSelect : public QObject, public BasicPlugin
 {
     Q_OBJECT
#if QT_VERSION >= 0x050000
     Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif
     Q_INTERFACES(BasicPlugin)

 public:
    
    inline      ~MouseSelect() { cleanUp(); }
    
    void        onPluginLoad();
    inline void onSceneClear() { cleanUp(); }
    
    void        mousePressEvent ( QMouseEvent * event );
 
 private:
    int     pxClick, pyClick;
    int     m_size;

    GLuint m_VAO;           // IDs of VAOs
    GLuint m_coordBufferID; // ID of vertex coordinates buffer
    
    QGLShader *m_pVs;
    QGLShader *m_pFs;
    QGLShaderProgram *m_pProgram;
    
    void encodeID(uint ID, GLubyte *color);
    uint decodeID(GLubyte *color);
    
    void cleanUp();
 };
 
 #endif
 
 
