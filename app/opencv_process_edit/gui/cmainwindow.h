#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include "qcanpool/qcanpool_global.h"

QCANPOOL_USE_NAMESPACE

class QMenu;
class QLabel;
class QToolBar;
class QStatusBar;
class QStackedWidget;
class QTimer;

class ChartsMode;
class CustomMode;
class MenuMode;

QCANPOOL_BEGIN_NAMESPACE
class FancyModeManager;
class FancyTabWidget;
QCANPOOL_END_NAMESPACE

class CMainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit CMainWindow(QWidget* parent = nullptr);
  ~CMainWindow();

  static CMainWindow* instance();
private:
  void createWindow();
  void createToolBar();
  void createStatusBar();
  void createDockWidget();
  void createCentralWidget();
  void createModeBar();

  void createOthers();
  void deleteOthers();

  void createConnects();

  void readSettings();
  void writeSettings();

private:
  static CMainWindow* m_instance;
  FancyModeManager* m_modeManager;
  FancyTabWidget* m_modeStack;
  QStatusBar* m_statusBar;

  ChartsMode* m_pChartsMode;
  CustomMode* m_pCustomMode;
  MenuMode* m_pMenuMode;
};

#endif // CMAINWINDOW_H
