#include "OcvShowModel.hpp"
#include <QtCore/QDir>
#include <QtCore/QEvent>
#include <QtWidgets/QFileDialog>
#include <memory>
#include <nodes/DataModelRegistry>
#include "OcvData.hpp"
#include "RoiLabel.h"

OcvShowModel::OcvShowModel() : _label(new QLabel("Image will appear here"))
{
  _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

  QFont f = _label->font();
  f.setBold(true);
  f.setItalic(true);

  _label->setFont(f);

  _label->setFixedSize(400, 400);

  _label->installEventFilter(this);

  /* input */
  _inputs.push_back(
      new ePort(PortType::In, NODE_DATA_TYPE[NodeClassMat], QString("cv::mat"), NodeClassMat));

  /* output */
  _outputs.push_back(
      new ePort(PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("cv::mat"), NodeClassMat));

  mat_ = new cv::Mat();
  in_mat_ = new cv::Mat();
}

bool OcvShowModel::eventFilter(QObject *object, QEvent *event)
{
  if (object == _label) {
    int w = _label->width();
    int h = _label->height();
    if (event->type() == QEvent::Resize) {
      return true;
      QImage img;
      OcvData::CvMatToQImage(*mat_, img);
      _label->setPixmap(QPixmap::fromImage(img.scaled(w, h, Qt::KeepAspectRatio)));
      return true;
    } else if (event->type() == QEvent::ContextMenu) {
      if (!in_mat_->empty()) {
        RoiDialog roi_dialog;
        QImage img;

        OcvData::CvMatToQImage(*in_mat_, img);
        roi_dialog.SetImage(img);

        connect(&roi_dialog,
                SIGNAL(SelectRoiImag(const QImage &)),
                this,
                SLOT(SetImage(const QImage &)));
        roi_dialog.show();
        roi_dialog.exec();
      }
    }
  }
  return false;
}

std::shared_ptr<NodeData> OcvShowModel::outData(PortIndex port)
{
  /* BUG: Garbled characters appear when other modules are connected to the output  */
  cv::Mat mat = mat_->clone();
  *mat_ = mat.clone();

  return std::make_shared<OcvData>(mat_);
}

void OcvShowModel::process()
{
  OcvData *ocv_data = dynamic_cast<OcvData *>(_inputs[0]->data.get());

  if (ocv_data) {
    *in_mat_ = ocv_data->GetData()->clone();
    if (!in_mat_->empty()) {
      SetMat(*in_mat_);

      Q_EMIT dataUpdated(0);
      setValidationState(NodeValidationState::Valid, QString("Image is null"));
    } else {
      setValidationState(NodeValidationState::Warning, QString("Image is null"));
    }
  }
}

void OcvShowModel::SetImage(const QImage &image)
{
  OcvData::QImage2cvMat(*mat_, image);

  QImage img;
  int w = _label->width();
  int h = _label->height();
  OcvData::CvMatToQImage(*mat_, img);
  _label->setPixmap(QPixmap::fromImage(img.scaled(w, h, Qt::KeepAspectRatio)));
  dataUpdated(0);
}

void OcvShowModel::SetMat(const cv::Mat &mat)
{
  int w = _label->width();
  int h = _label->height();

  *mat_ = mat.clone();
  /* cover cv::mat to qimage */
  QImage img;
  OcvData::CvMatToQImage(*mat_, img);
  _label->setPixmap(QPixmap::fromImage(img.scaled(w, h, Qt::KeepAspectRatio)));
  dataUpdated(0);
}
