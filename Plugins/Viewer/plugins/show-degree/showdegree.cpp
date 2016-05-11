#include "showdegree.h"


ShowDegree::ShowDegree() :
    m_degree(0)
{
}

void ShowDegree::onPluginLoad()
{
  Scene *scene = this->scene();
  
  Object &o = scene->objects().front();
  const vector<Face> &faces = o.faces();
  vector<int> VCount(o.vertices(), 0);
  
  for (const Face &f : faces) {
    for (int i = 0; i < f.numVertices(); ++i) {
      ++VCount[f.vertexIndex(i)];
    }
  }
  
  int total = o.vertices().size();
  int touch = 0;
  
  for (int n : VCount) touch += n;
  
  m_degree = touch / float(total);
}

void ShowDegree::postFrame()
{
  QImage image(SIZE, QImage::Format_RGB32);
  image.fill(Qt::white);
  
  QPainter painter(&image);
  QFont font;
  font.setPixelSize(32);
  painter.setFont(font);
  painter.setPen(QColor(50,50,50));
  
  int x = 15;
  int y = 50;
  painter.drawText(x, y, "Degree: " + QString::number(m_degree));
  
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(show-degree, ShowDegree)
#endif // QT_VERSION < 0x050000
