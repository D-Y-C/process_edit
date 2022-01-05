#include <QApplication>
#include <iostream>
#include <opencv2\opencv.hpp>

#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/NodeData>

#include "BaseNode.h"
#include "ImageData.hpp"

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;

static std::shared_ptr<DataModelRegistry> registerDataModels();

using namespace cv;

class BaseNodeDemo : public BaseNode
{
 public:
  const QString Name()const override { return QString("BaseNodeDemo"); }

  std::shared_ptr<NodeData> outData(PortIndex port) override
  {
    return std::make_shared<ImageData>(mat_);
  };

 private:
  cv::Mat mat_;
};

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  FlowScene scene(registerDataModels());

  FlowView view(&scene);

  view.setWindowTitle("Node-based flow editor");
  view.resize(800, 600);
  view.show();

  return app.exec();
}

static std::shared_ptr<DataModelRegistry> registerDataModels()
{
  auto ret = std::make_shared<DataModelRegistry>();
  ret->registerModel<BaseNodeDemo>();

  //	ret->registerModel<ImageLoaderModel>();

  //	ret->registerModel<ImageThresholdModel>();

  return ret;
}
