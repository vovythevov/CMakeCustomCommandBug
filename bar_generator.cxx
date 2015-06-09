
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QString>
#include <QStringList>

#include <cstdio>

//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
  int retval = 0;
  QCoreApplication app(argc, argv);
  QStringList args = app.arguments().mid(1);

  if (args.count() < 1)
    {
    qCritical() << "no output file specified";
    retval = 2;
    }
  else
    {
    // Open manager file
    QString managerName = args.takeFirst();
    QFile managerFile(managerName);
    if (!managerFile.open(QIODevice::WriteOnly | QIODevice::Text))
      {
      qCritical() << "unable to open file";
      retval = 1;
      }

    QTextStream ms(&managerFile);
      ms << "#ifndef _bat_h" << '\n'
         << "#define _bat_h" << '\n'
         << '\n'
         << "class bar" << '\n'
         << "{" << '\n'
         << "};" << '\n'
         << '\n'
         << "#endif " << '\n';
    }

  return retval;
}
