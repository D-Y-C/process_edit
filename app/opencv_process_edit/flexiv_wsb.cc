// flexiv_gripper.cpp: 定义应用程序的入口点。
//
#if 0
#include "wsb_client.h"
#include <QApplication>
#include <iostream>
#include "logger.h"
#include "mainwindow.h"
#include "cmainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QSplashScreen>
#include <QFile>
#include <QStyleFactory>


using namespace std;

int main1(int argc, char* argv[])
{
#if 0
  logger::debug() << "Flexiv Gripper Server";

  gripper_modbus.RegisterPollCb(master_poll_cb);
  gripper_modbus.StartModbusMaster("COM3");

  while (1)
  {
    /*
    driver.StartModbusMaster();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    driver.StopModbusMaster();
    */
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  }
#endif
  QApplication app(argc, argv);

  QTextCodec* codec = QTextCodec::codecForName("UTF-8");
  QTextCodec::setCodecForLocale(codec);
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
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
int main2(int argc, char* argv[])
{
  QApplication app(argc, argv);

  /* WSB tcp client init */
  Socket::Address address;
  address = Socket::Address::Ipv4("192.168.0.5", 80);
  WsbClient client(Socket::Tcp(address));

  /* GUI init */
  QTextCodec* codec = QTextCodec::codecForName("UTF-8");
  QTextCodec::setCodecForLocale(codec);
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
  QTextCodec::setCodecForCStrings(codec);
  QTextCodec::setCodecForTr(codec);
#endif
  QApplication::processEvents(QEventLoop::AllEvents);

  QFont font("Segoe UI", 10);
  QApplication::setFont(font);

  MainWindow w;
  w.setClient(&client);
  w.show();

  app.exec();
  client.Stop();
}
#endif
