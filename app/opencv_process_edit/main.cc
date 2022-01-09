#include <QApplication>
#include <iostream>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
  QTextCodec::setCodecForCStrings(codec);
  QTextCodec::setCodecForTr(codec);
#endif
  QApplication::processEvents(QEventLoop::AllEvents);

  QFont font("Segoe UI", 10);
  QApplication::setFont(font);

  MainWindow w;
  w.show();

  return app.exec();
}


