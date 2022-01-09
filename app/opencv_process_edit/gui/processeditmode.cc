#include "processeditmode.h"
#include <opencv2\opencv.hpp>

#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/NodeData>

#include "OcvCvtColorModel.hpp"
#include "OcvLoaderModel.hpp"
#include "OcvShowModel.hpp"
#include "OcvThresholdModel.hpp"
#include "OcvMorphologyModel.hpp"
#include "OcvResizeModel.hpp"
#include "OcvBilateralFilterModel.hpp"
#include "OcvBlurModel.hpp"
#include "OcvMedianBlurModel.hpp"
#include "OcvGaussianBlurModel.hpp"
#include "OcvFindContours.hpp"

using QtNodes::DataModelRegistry;

static std::shared_ptr<DataModelRegistry> registerDataModels();

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
  auto ret = std::make_shared<DataModelRegistry>();
  ret->registerModel<OcvShowModel>();
  ret->registerModel<OcvLoaderModel>();
  ret->registerModel<OcvThresholdModel>();
  ret->registerModel<OcvCvtColorModel>();
  ret->registerModel<OcvMophologyModel>();
  ret->registerModel<OcvResizeModel>();
  //  ret->registerModel<OcvBilateralFilterModel>();
  ret->registerModel<OcvBlurModel>();
  ret->registerModel<OcvGaussianBlurModel>();
  ret->registerModel<OcvMedianBlurModel>();
  ret->registerModel<OcvFindContoursModel>();

  return ret;
}

bool ProcessEditMode::save(QString& file)
{
  flow_scene_->save();
  return true;
}

bool ProcessEditMode::open(QString& file) {
  flow_scene_->load();
  return true;
}