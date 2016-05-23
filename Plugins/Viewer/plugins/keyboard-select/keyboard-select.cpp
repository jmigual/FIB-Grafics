#include "keyboard-select.h"
#include "glwidget.h"


void KeyboardSelect::keyPressEvent(QKeyEvent *e)
{
  int key = e->key();
  if (key < (int)(Qt::Key_0) || key > (int)(Qt::Key_9)) return;
  key -= Qt::Key_0;
  
  if (int(scene()->objects().size()) < key) key = -1;
  scene()->setSelectedObject(key);
  
  glwidget()->updateGL();
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(keyboard-select, KeyboardSelect)   // plugin name, plugin class
#endif

