#ifndef CHARTSMODE_H
#define CHARTSMODE_H

#include "qcanpool/fancymode.h"

QCANPOOL_USE_NAMESPACE

class QCustomPlot;

class ChartsMode : public FancyMode
{
  Q_OBJECT
public:
  explicit ChartsMode(QWidget* parent = nullptr);

  void SetForceData(float key, float frot, float back, float left, float right);
  void SetTemperatureData(float);
  void SetLmuData(float);
private:
  void createWindow();

  QCustomPlot* force_plot_;
  QCustomPlot* tempe_plot_;
  QCustomPlot* lmu_plot_;
};

#endif // CHARTSMODE_H
