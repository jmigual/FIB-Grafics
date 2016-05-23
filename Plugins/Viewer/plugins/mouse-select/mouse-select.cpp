#include "mouse-select.h"
#include "glwidget.h"
//#include <QMatrix4x4>

void MouseSelect::onPluginLoad()
{    
  m_pVs = new QGLShader(QGLShader::Vertex, this);
  m_pVs->compileSourceFile(":/color.vert");
  
  m_pFs = new QGLShader(QGLShader::Fragment, this);
  m_pFs->compileSourceFile(":/color.frag");
  cout << "FS log: " << m_pFs->log().toStdString() << endl;
  
  m_pProgram = new QGLShaderProgram(this);
  m_pProgram->addShader(m_pVs);
  m_pProgram->addShader(m_pFs);
  m_pProgram->link();
  cout << "Link log: " << m_pProgram->log().toStdString() << endl;
}

void MouseSelect::mousePressEvent( QMouseEvent *e)
{
  if (! (e->button() & Qt::RightButton)) return;
  if ( e->modifiers() & (Qt::ShiftModifier)) return;
  if (! (e->modifiers() & Qt::ControlModifier)) return;
  
  glClearColor(0,0,0,0);
  glClear(GL_DEPTH_BUFFER_BIT);
  glClear(GL_COLOR_BUFFER_BIT);
  
  m_pProgram->bind();
  const vector<Object> &objs = scene()->objects();
  for (uint i = 0; i < objs.size(); ++i) {
    GLubyte color[3];
    encodeID(i,color);
    m_pProgram->setUniformValue("modelViewProjectionMatrix", camera()->projectionMatrix()*camera()->modelviewMatrix());
    m_pProgram->setUniformValue("color", QVector4D(color[0]/255.0, color[1]/255., color[2]/255., 1.0));
    drawPlugin()->drawObject(i);
  }
  m_pProgram->release();
  
  int x = e->x();
  int y = glwidget()->height() - e->y();
  GLubyte read[4];
  glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, read);
  int ID = decodeID(read);
  
  cout << "ID1: " << ID << endl;
  
  scene()->setSelectedObject(ID);
  
  glwidget()->updateGL();
}

void MouseSelect::encodeID(uint ID, GLubyte *color)
{
  ID += 1;
  color[0] = ID & 0xFF;
  color[1] = (ID >> 8) & 0xFF;
  color[2] = (ID >> 16) & 0xFF;
}

uint MouseSelect::decodeID(GLubyte *color)
{
  int ID = color[0] | (color[1] << 8) | (color[2] << 16);
  return ID - 1;
}

void MouseSelect::cleanUp()
{
  glDeleteBuffers(m_size, &m_coordBufferID);
  glDeleteVertexArrays(1, &m_VAO);
  
  delete m_pProgram;
  delete m_pFs;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(mouseselect, MouseSelect)   // plugin name, plugin class
#endif

