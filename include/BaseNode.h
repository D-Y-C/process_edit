#ifndef BASENODE_H
#define BASENODE_H

#include <nodes/NodeDataModel>
#include "ParamWidget.h"
#include "Parameter.h"
#include "Types.h"

using QtNodes::NodeData;
using QtNodes::NodeDataModel;
using QtNodes::NodeDataType;
using QtNodes::NodeValidationState;
using QtNodes::Port;
using QtNodes::PortIndex;
using QtNodes::PortType;

enum NodeClass
{
  NodeClassMat
};

static const NodeDataType NODE_DATA_TYPE[] = {
    {"mat", "cv::mat"},
};

//----------------------------------------------------------------------------------------------
// ePort
//----------------------------------------------------------------------------------------------
struct ePort
{
  PortType type;
  NodeDataType dataType;
  QString name;
  std::shared_ptr<NodeData> data;
  NodeClass nodeClass;

  ePort() {}

  ePort(PortType type, NodeDataType dataType, QString name, NodeClass nodeClass)
      : type(type), dataType(dataType), name(name), nodeClass(nodeClass)
  {
    // dataType = NODE_DATA_TYPE[paramType];
  }
};

//----------------------------------------------------------------------------------------------
// Base class for nodes
//----------------------------------------------------------------------------------------------
class BaseNode : public NodeDataModel
{
  Q_OBJECT

 public:
  BaseNode();
  virtual ~BaseNode();
  virtual void process() {}
  virtual void init() { process(); }
  unsigned int getParameterCount();
  Parameter* getParameter(unsigned int index);
  Parameter* getParameter(const QString name);

 public:
  virtual bool captionVisible() const override { return true; }
  virtual bool portCaptionVisible(PortType, PortIndex) const override { return true; }
  QString portCaption(PortType portType, PortIndex portIndex) const override;
  unsigned int nPorts(PortType portType) const override;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
  void setInData(std::shared_ptr<NodeData> nodeData, PortIndex portIndex) override;
  virtual QWidget* embeddedWidget() override { return _paramWidget; }
  void createParamWidgets() { _paramWidget = new ParamWidget(this); }

  template <typename T>
  void addParameter(::ParamType type, QString name, float min, float max, T value)
  {
    Parameter* p = new Parameter(type, name, min, max, this);
    p->baseValue = (T)value;
    _parameters.push_back(p);
  }

  template <class T>
  std::shared_ptr<T> getInput(unsigned int portIndex)
  {
    Q_ASSERT(portIndex < _inputs.size());
    Q_ASSERT(_inputs[portIndex]->nodeClass == T::metatype());
    std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(_inputs[portIndex]->data);
    return ptr;
  }

 public:
  std::vector<ePort*> _inputs;
  std::vector<ePort*> _outputs;
  ParamWidget* _paramWidget;
  std::vector<Parameter*> _parameters;

 public:
  NodeValidationState modelValidationState = NodeValidationState::Valid;
  QString modelValidationError = QString("ok");
  NodeValidationState validationState() const;
  QString validationMessage() const;
  void setValidationState(NodeValidationState state, const QString& msg = "")
  {
    modelValidationState = state;
    modelValidationError = msg;
  }

  QJsonObject save() const override
  {
    QJsonObject modelJson = NodeDataModel::save();

    if (_paramWidget) _paramWidget->save(modelJson);

    return modelJson;
  }

 public:
  void restore(QJsonObject const& p) override
  {
    if (_paramWidget) _paramWidget->restore(p);
  }

 public Q_SLOTS:
  virtual void onParameterChanged()
  {
    process();
    Q_EMIT(dataUpdated(0));
  }
};

//----------------------------------------------------------------------------------------------
// add input/output macros
//----------------------------------------------------------------------------------------------
#define IN_PORT(datatype, label) \
  _inputs.push_back(new ePort(PortType::In, NODE_DATA_TYPE[datatype], QString(label), datatype));

#define OUT_PORT(datatype, label) \
  _outputs.push_back(new ePort(PortType::Out, NODE_DATA_TYPE[datatype], QString(label), datatype));

//----------------------------------------------------------------------------------------------
// add parameter macros
//----------------------------------------------------------------------------------------------
#define PARAM_TEXT(name, label) addParameter<QString>(EPT_TEXT, name, 0, 0, QString(label))

#define PARAM_STRING(name, label) addParameter<QString>(EPT_STRING, name, 0, 0, QString(label))

#define PARAM_BOOL(name, boolean) addParameter<bool>(EPT_BOOL, name, 0, 0, (bool)boolean)

#define PARAM_INT(name, min, max, v) addParameter<eInt>(EPT_INT, name, min, max, (eInt)v)

#define PARAM_FLOAT(name, min, max, f) addParameter<eF32>(EPT_FLOAT, name, min, max, (eF32)f)

#define PARAM_FXY(name, min, max, x, y) \
  addParameter<eFXY>(EPT_FXY, name, min, max, eFXY((eF32)x, (eF32)y))

#define PARAM_FXYZ(name, min, max, x, y, z) \
  addParameter<eFXYZ>(EPT_FXYZ, name, min, max, eFXYZ((eF32)x, (eF32)y, (eF32)z))

#define PARAM_FXYZW(name, min, max, x, y, z, w) \
  addParameter<eFXYZW>(EPT_FXYZW, name, min, max, eFXYZW((eF32)x, (eF32)y, (eF32)z, (eF32)w))

#define PARAM_IXY(name, min, max, x, y) \
  addParameter<eIXY>(EPT_IXY, name, min, max, eIXY((eInt)x, (eInt)y))

#define PARAM_IXYZ(name, min, max, x, y, z) \
  addParameter<eIXYZ>(EPT_IXYZ, name, min, max, eIXYZ((eInt)x, (eInt)y, (eInt)z))

#define PARAM_IXYZW(name, min, max, x, y, z, w) \
  addParameter<eIXYZW>(EPT_IXYZW, name, min, max, eIXYZW((eInt)x, (eInt)y, (eInt)z, (eInt)w))

#define PARAM_ENUM(name, descr, index)                     \
  addParameter<eInt>(EPT_ENUM, name, 0, 255, (eF32)index); \
  _parameters.back()->setDescription(descr)

#define PARAM_FILE(name, path) addParameter<QString>(EPT_FILE, name, 0, 0, QString(path));

#define PARAM_FILESAVE(name, path) addParameter<QString>(EPT_FILESAVE, name, 0, 0, QString(path));

#define PARAM_FLAGS(name, descr, index)                                         \
  addParameter<unsigned char>(EPT_FLAGS, name, 0, 255, (unsigned char)(index)); \
  _parameters.back()->setDescription(descr);

#define PARAM_RGBA(name, r, g, b, a) \
  addParameter<eColor>(EPT_RGBA, name, 0, 255, eColor(r, g, b, a));

#define PARAM_BUTTON(name, label) addParameter<QString>(EPT_BUTTON, name, 0, 0, QString(label))

#endif  // BASENODE_H
