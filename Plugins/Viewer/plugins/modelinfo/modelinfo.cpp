#include "modelinfo.h"

ModelInfo::ModelInfo() :
  m_frameCount(0),
  m_objects(0),
  m_vertices(0),
  m_percentage(0)
{ }

void ModelInfo::onObjectAdd()
{
  countData();
  printInfo();
}

void ModelInfo::countData()
{
  Scene *scene = this->scene();
  
  m_objects = scene->objects().size();
  m_vertices = 0;
  int triangles = 0;
  int facesCount = 0;
  
  for (Object &o : scene->objects()) {
    const vector<Face> &faces = o.faces();
    facesCount += faces.size();
    
    for (const Face &f : faces) {
      int v = f.numVertices();
      m_vertices += v;
      if (v == 3) ++triangles;
    }
  }
  
  m_percentage = triangles / float(facesCount);
}

void ModelInfo::printInfo()
{  
  cout << "Scene info:" << endl;
  cout << "Number of objects: " << m_objects << endl;
  cout << "Number of vertices: " << m_vertices << endl;
  cout << "Percentage of triangles: " << m_percentage << endl;
  
}



#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(modelinfo, ModelInfo)   // plugin name, plugin class
#endif

