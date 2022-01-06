#include "OcvLoaderModel.hpp"
#include <QString>
#include <QtCore/QDir>
#include <QtCore/QEvent>
#include <memory>

#include <QDebug>
#include <QtWidgets/QFileDialog>

OcvLoaderModel::OcvLoaderModel()
{
  _outputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));

  addParameter<QString>(EPT_FILE, "ImageFile", 0, 0, QString("Files"));
  addParameter<eIXY>(EPT_IXY, "size", 0, 10000000000, eIXY(0, 0));

  mat_ = new cv::Mat();

  return;

  addParameter<QString>(EPT_TEXT, "EPT_TEXT", 0, 0, QString("params1"));
  addParameter<QString>(EPT_STRING, "EPT_STRING", 0, 0, QString("params2"));
  addParameter<bool>(EPT_BOOL, "EPT_BOOL", 0, 0, true);
  addParameter<eInt>(EPT_INT, "EPT_INT", 0, 100, 50);
  addParameter<eF32>(EPT_FLOAT, "EPT_FLOAT", 0, 100, 50.0f);
  addParameter<eFXY>(EPT_FXY, "EPT_FXY", 0, 100, eFXY(50.0f, 50.0f));
  addParameter<eFXYZ>(EPT_FXYZ, "EPT_FXYZ", 0, 100, eFXYZ(50.0f, 50.0f, 50.0f));
  addParameter<eFXYZW>(EPT_FXYZW, "EPT_FXYZW", 0, 100, eFXYZW(50.0f, 50.0f, 50.0f, 50.0f));
  addParameter<eInt>(EPT_ENUM, "EPT_ENUM", 0, 255, 0);
  _parameters.back()->setDescription("params7-1");
  addParameter<eInt>(EPT_ENUM, "EPT_ENUM", 0, 255, 0);
  _parameters.back()->setDescription("params7-2");
  addParameter<QString>(EPT_FILE, "EPT_FILE", 0, 0, QString("path"));
  addParameter<QString>(EPT_FILESAVE, "EPT_FILESAVE", 0, 0, QString("path"));
  addParameter<unsigned char>(EPT_FLAGS, "EPT_FLAGS", 0, 255, (unsigned char)('c'));
  _parameters.back()->setDescription("EPT_FLAGS-1");
  addParameter<unsigned char>(EPT_FLAGS, "EPT_FLAGS", 0, 255, (unsigned char)('c'));
  _parameters.back()->setDescription("EPT_FLAGS-2");
  addParameter<eColor>(EPT_RGBA, "EPT_RGBA", 0, 255, eColor(128, 128, 128, 128));
  addParameter<QString>(EPT_BUTTON, "EPT_BUTTON", 0, 0, QString("label"));
}

void OcvLoaderModel::process()
{
  Parameter* parameter = getParameter("ImageFile");
  if (parameter) {
    QString fileName = std::get<QString>(parameter->baseValue);
    *mat_ = cv::imread(fileName.toStdString()).clone();
    std::get<eIXY>(getParameter("size")->baseValue) = eIXY(mat_->rows, mat_->cols);
    dataUpdated(0);
  }
}

std::shared_ptr<NodeData> OcvLoaderModel::outData(PortIndex port)
{
  return std::make_shared<OcvData>(mat_);
}
