#include "drawBoundingBox.h"
#include "glwidget.h"
#include <cmath>

void DrawBBox::cleanUp()
{
  glDeleteBuffers(size,  &coordBufferID);
  
  glDeleteVertexArrays(1, &VAO);
  
}

DrawBBox::~DrawBBox()
{
  cleanUp();
}

void DrawBBox::onSceneClear()
{
  cleanUp();
}

void DrawBBox::postFrame()
{
  //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glBindVertexArray(VAO);
  vector<Object> &O = scene()->objects();
  program->bind();
  QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->modelviewMatrix();
  program->setUniformValue("modelViewProjectionMatrix", MVP);
  
  for (Object &o : O) {
    const Box &b = o.boundingBox();
    
    program->setUniformValue("boundingBoxMax", b.max());
    program->setUniformValue("boundingBoxMin", b.min());
    
    glDrawArrays(GL_TRIANGLES, 0, size);
  }
  
  program->release();
  
  glDisable(GL_BLEND);
  glBindVertexArray(0);
  //glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}


void DrawBBox::onPluginLoad()
{
  vector<float> vertices;
  vector<vector<float>> triangles;
  
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  
  glGenBuffers(1, &coordBufferID);
  
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
  size = vertices.size();
  
  glBindBuffer(GL_ARRAY_BUFFER, coordBufferID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);  // VAO
  glEnableVertexAttribArray(0);
  
  vs = new QGLShader(QGLShader::Vertex, this);
  vs->compileSourceFile(":/drawBB.vert");
  cout << "VS log: " << vs->log().toStdString() << endl;
  
  fs = new QGLShader(QGLShader::Fragment, this);
  fs->compileSourceFile(":/drawBB.frag");
  cout << "FS log: " << fs->log().toStdString() << endl;
  
  program = new QGLShaderProgram(this);
  program->addShader(vs);
  program->addShader(fs);
  program->link();
  cout << "Link log: " << program->log().toStdString() << endl;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(drawBoundingBox, DrawBBox)   // plugin name, plugin class
#endif



