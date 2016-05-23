#include "resaltar-seleccio.h"
#include "glwidget.h"
#include <cmath>

void ResaltarSeleccio::cleanUp()
{
  glDeleteBuffers(m_size,  &m_coordBufferID);
  glDeleteVertexArrays(1, &m_VAO);
  
  delete m_pVs;
  delete m_pFs;
  delete m_pProgram;
}

ResaltarSeleccio::~ResaltarSeleccio()
{
  cleanUp();
}

void ResaltarSeleccio::onSceneClear()
{
  cleanUp();
}

void ResaltarSeleccio::postFrame()
{
  int selected = scene()->selectedObject();
  if (selected < 0) return;
  const Box &b = scene()->objects()[selected].boundingBox();
  
  //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  m_pProgram->bind();
  QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->modelviewMatrix();
  m_pProgram->setUniformValue("modelViewProjectionMatrix", MVP);
  
  m_pProgram->setUniformValue("boundingBoxMax", b.max());
  m_pProgram->setUniformValue("boundingBoxMin", b.min());
  
  glBindVertexArray(m_VAO);
  glDrawArrays(GL_TRIANGLES, 0, m_size);
  
  m_pProgram->release();
  
  glDisable(GL_BLEND);
  //glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER,0);
}


void ResaltarSeleccio::onPluginLoad()
{
  vector<float> vertices;
  vector<vector<float>> triangles;
  
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);
  
  glGenBuffers(1, &m_coordBufferID);
  
  // 6 planes to visualize the bounding box
  triangles.push_back({ 0,0,0,  1,0,0,  1,1,0 });
  triangles.push_back({ 0,0,0,  1,1,0,  0,1,0 });
  
  triangles.push_back({ 0,0,1,  1,0,1,  1,1,1 });
  triangles.push_back({ 0,0,1,  1,1,1,  0,1,1 });
  
  triangles.push_back({ 0,1,0,  1,1,0,  1,1,1 });
  triangles.push_back({ 0,1,0,  1,1,1,  0,1,1 });
  
  triangles.push_back({ 0,0,0,  1,0,0,  1,0,1 });
  triangles.push_back({ 0,0,0,  1,0,1,  0,0,1 });
  
  triangles.push_back({ 1,0,0,  1,0,1,  1,1,1 });
  triangles.push_back({ 1,0,0,  1,1,0,  1,1,1 });
  
  triangles.push_back({ 0,0,0,  0,0,1,  0,1,1 });
  triangles.push_back({ 0,0,0,  0,1,0,  0,1,1 });
  
  for (vector<float> &V : triangles) for (float f : V) vertices.push_back(f);
  m_size = vertices.size();
  
  glBindBuffer(GL_ARRAY_BUFFER, m_coordBufferID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);  // VAO
  glEnableVertexAttribArray(0);
  
  m_pVs = new QGLShader(QGLShader::Vertex, this);
  m_pVs->compileSourceFile(":/drawBB.vert");
  cout << "VS log: " << m_pVs->log().toStdString() << endl;
  
  m_pFs = new QGLShader(QGLShader::Fragment, this);
  m_pFs->compileSourceFile(":/drawBB.frag");
  cout << "FS log: " << m_pFs->log().toStdString() << endl;
  
  m_pProgram = new QGLShaderProgram(this);
  m_pProgram->addShader(m_pVs);
  m_pProgram->addShader(m_pFs);
  m_pProgram->link();
  cout << "Link log: " << m_pProgram->log().toStdString() << endl;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(resaltarSeleccio, ResaltarSeleccio)   // plugin name, plugin class
#endif



