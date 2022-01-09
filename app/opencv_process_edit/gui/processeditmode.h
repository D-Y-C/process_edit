#ifndef PROCESS_EDIT_MODE_H_
#define PROCESS_EDIT_MODE_H_

#include <QtCore/QObject>
#include "qcanpool/fancymode.h"

namespace QtNodes {
class FlowScene;
class FlowView;
}  // namespace QtNodes

QCANPOOL_USE_NAMESPACE

class ProcessEditMode : public FancyMode
{
  Q_OBJECT

public:
  explicit ProcessEditMode(QWidget* parent = nullptr);
 ~ProcessEditMode();

 bool save(QString& file) override;
 bool open(QString& file) override;

private:
 void createWindow();

private:
 QtNodes::FlowScene* flow_scene_;
 QtNodes::FlowView* flow_view_;
};

#endif