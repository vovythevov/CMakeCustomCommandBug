
#include <QObject>
#include <bar.h>

class foo : public QObject
{
  Q_OBJECT

public:
  void foo_something();
};