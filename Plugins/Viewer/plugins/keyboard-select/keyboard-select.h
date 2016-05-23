#ifndef _MOUSESELECT_H
#define _MOUSESELECT_H

#include "basicplugin.h"

class KeyboardSelect : public QObject, public BasicPlugin
{
  Q_OBJECT
#if QT_VERSION >= 0x050000
  Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif
  Q_INTERFACES(BasicPlugin)
  
public:
    
  void    keyPressEvent(QKeyEvent *e);
  
private:
};

#endif


