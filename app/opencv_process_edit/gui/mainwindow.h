#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qcanpool/fancywindow.h"

QCANPOOL_USE_NAMESPACE

class QMenu;
class QLabel;
class QToolBar;
class QStatusBar;
class QStackedWidget;

class ChartsMode;
class CustomMode;
class ScenerMode;
class PaintMode;
class MenuMode;
class ProcessEditMode;

QCANPOOL_BEGIN_NAMESPACE
class FancyTabWidget;
class FancyModeManager;
class FancyNavBar;
QCANPOOL_END_NAMESPACE

class MainWindow : public FancyWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

  static MainWindow* instance();
private:
  void createWindow();
  void createQuickAccessBar();
  void createMenuBar();
  void createAdditionalControls();
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

public slots:
  void updateTheme();

private slots:
  void slotHelp();
  void slotNew();
  void slotSave();
  void slotOpen();
  void slotSkin();
  void slotResizable(bool resizable);
  void slotChangeSkin(QString skinName);
  void slotSetStyle(QAction* action);
  void timeupFun();
private:
  static MainWindow* m_instance;
  FancyModeManager* m_modeManager;
  FancyTabWidget* m_modeStack;
  QStatusBar* m_statusBar;
  FancyNavBar* m_pNavBar;

  ChartsMode* m_pChartsMode;
  CustomMode* m_pCustomMode;
  ScenerMode* m_pScenerMode;
  ProcessEditMode* m_pProcessEditMode;
  PaintMode* m_pPaintMode;
  MenuMode* m_pMenuMode;
  QList<QAction*> m_styleActions;
  QAction* m_styleAction;

  QTimer* timer_;

  /* Action */
  QAction* new_action_;
  QAction* open_action_;
  QAction* save_action_;
  QAction* save_all_action_;
  QAction* undo_action_;
  QAction* redo_action_;
};

#endif // MAINWINDOW_H
