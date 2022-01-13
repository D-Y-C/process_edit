#include "processeditmode.h"
#include <opencv2\opencv.hpp>

#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/NodeData>

#include "OcvBilateralFilterModel.hpp"
#include "OcvBlurModel.hpp"
#include "OcvCvtColorModel.hpp"
#include "OcvEqualizeHistModel.h"
#include "OcvFindContours.hpp"
#include "OcvGaussianBlurModel.hpp"
#include "OcvInpaintModel.hpp"
#include "OcvLoaderModel.hpp"
#include "OcvMedianBlurModel.hpp"
#include "OcvMorphologyModel.hpp"
#include "OcvResizeModel.hpp"
#include "OcvShowModel.hpp"
#include "OcvSplitModel.h"
#include "OcvThresholdModel.hpp"

using QtNodes::DataModelRegistry;

using namespace cv;

static std::shared_ptr<DataModelRegistry> registerDataModels();

ProcessEditMode::ProcessEditMode(QWidget* parent) : FancyMode(parent)
{
  setObjectName(QLatin1String("ProcessEdit"));
  setDisplayName(tr("ProcessEdit"));
  setIcon(QIcon(":/mode/graph"));

  createWindow();
}

ProcessEditMode::~ProcessEditMode() {}

void ProcessEditMode::createWindow()
{
  flow_scene_ = new QtNodes::FlowScene(registerDataModels(), this);
  flow_view_ = new QtNodes::FlowView(flow_scene_);

  flow_view_->setWindowTitle("Node-based flow editor");
  flow_view_->show();

  QVBoxLayout* layout = new QVBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->addWidget(flow_view_);

  QWidget* w = new QWidget();
  w->setLayout(layout);
  setWidget(w);
}

static std::shared_ptr<DataModelRegistry> registerDataModels()
{
  std::shared_ptr<DataModelRegistry> ret = std::make_shared<DataModelRegistry>();
  /* Base types */
  ret->registerModel<OcvShowModel>("Base");
  ret->registerModel<OcvLoaderModel>("Base");
  ret->registerModel<OcvSplitModel>("Base");

  /* Image Filter types */
  ret->registerModel<OcvBlurModel>("Filter");
  ret->registerModel<OcvGaussianBlurModel>("Filter");
  ret->registerModel<OcvMedianBlurModel>("Filter");
  ret->registerModel<OcvThresholdModel>("Filter");
  ret->registerModel<OcvMophologyModel>("Filter");

  /* Image Transform types */
  ret->registerModel<OcvInpaintModel>("Transform");
  ret->registerModel<OcvResizeModel>("Transform");
  ret->registerModel<OcvCvtColorModel>("Transform");
  ret->registerModel<OcvEqualizeHistModel>("Transform");

  /* Unknow types */
  ret->registerModel<OcvFindContoursModel>("Ocv");

  return ret;
}

bool ProcessEditMode::save(QString& file)
{
  flow_scene_->save();
  return true;
}

bool ProcessEditMode::open(QString& file)
{
  flow_scene_->load();
  return true;
}