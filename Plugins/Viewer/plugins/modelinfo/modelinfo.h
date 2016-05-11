#ifndef MODELINFO_H
#define MODELINFO_H

#include "basicplugin.h"


class ModelInfo : public QObject, public BasicPlugin
{
  Q_OBJECT
#if QT_VERSION >= 0x050000
  Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif
  Q_INTERFACES(BasicPlugin)
public:
  ModelInfo();
  
  void onObjectAdd();
  
private:
  short m_frameCount;
  
  const int FRAME_NUM = 60;
  
  int m_objects;
  int m_vertices;
  float m_percentage;
  
  void countData();
  void printInfo();
 
};

#endif // MODELINFO_H
