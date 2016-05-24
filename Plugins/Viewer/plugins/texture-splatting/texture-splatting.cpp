#include "texture-splatting.h"
#include <QFileDialog>

void TextureSplatting::onPluginLoad()
{
  // VS
  m_pVs = new QGLShader(QGLShader::Vertex, this);
  m_pVs->compileSourceFile(":/splat.vert");
  
  // FS
  m_pFs = new QGLShader(QGLShader::Fragment, this);
  m_pFs->compileSourceFile(":/splat.frag");
  
  // Program  
  m_pProgram = new QGLShaderProgram(this);
  m_pProgram->addShader(m_pVs);
  m_pProgram->addShader(m_pFs);
  m_pProgram->link();
  
  // Load Texture 1
  glActiveTexture(GL_TEXTURE0);
  QString filename = QFileDialog::getOpenFileName(0, "Open Image", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
  QImage img0(filename);	
  QImage im0 = QGLWidget::convertToGLFormat(img0);
  glGenTextures( 1, &m_textureId0);
  glBindTexture(GL_TEXTURE_2D, m_textureId0);
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glBindTexture(GL_TEXTURE_2D, 0);
  
  // Load Texture 2
  glActiveTexture(GL_TEXTURE1);
  QString filename2 = QFileDialog::getOpenFileName(0, "Open Image 2", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
  QImage img1(filename2);	
  QImage im1 = QGLWidget::convertToGLFormat(img1);
  glGenTextures( 1, &m_textureId1);
  glBindTexture(GL_TEXTURE_2D, m_textureId1);
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glBindTexture(GL_TEXTURE_2D, 0);
  
  // Load Texture 3
  glActiveTexture(GL_TEXTURE3);
  QString filename3 = QFileDialog::getOpenFileName(0, "Open Image 3", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
  QImage img2(filename3);	
  QImage im2 = QGLWidget::convertToGLFormat(img2);
  glGenTextures( 1, &m_textureId2);
  glBindTexture(GL_TEXTURE_2D, m_textureId2);
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im2.width(), im2.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im2.bits());
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureSplatting::preFrame() 
{
  // bind shader and define uniforms
  m_pProgram->bind();
  m_pProgram->setUniformValue("sampler0", 0);   // texture unit del primer sampler 
  m_pProgram->setUniformValue("sampler1", 1);   // texture unit del segon  sampler 
  m_pProgram->setUniformValue("sampler2", 2);   // texture unit del tercer sampler
  
  m_pProgram->setUniformValue("radius", float(scene()->boundingBox().radius()));  // radi d'una esfera que engloba l'escena
  QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->modelviewMatrix();
  m_pProgram->setUniformValue("modelViewProjectionMatrix", MVP); 
  
  // bind textures
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_textureId0);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, m_textureId1);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, m_textureId2);
}

void TextureSplatting::postFrame() 
{
  // unbind shader
  m_pProgram->release();
  // unbind textures
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, 0);
}

Q_EXPORT_PLUGIN2(textureSplatting, TextureSplatting)   // plugin name, plugin class
