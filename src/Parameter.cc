#include "Parameter.h"

enum eParamClass
{
  ePC_NONE,
  ePC_FLOAT,
  ePC_INT,
  ePC_STRING,
  ePC_BOOL,
  ePC_UCHAR,
  ePC_COLOR,
};

struct ParameterInfo
{
  eU32 numComponents;
  eParamClass classs;  // three 's' because 'class' is keyword
} PARAM_INFOS[] = {
    {0, ePC_NONE},    // EPT_NONE
    {1, ePC_STRING},  // EPT_STRING
    {1, ePC_BOOL},    // EPT_BOOL
    {1, ePC_INT},     // EPT_FLAGS
    {1, ePC_INT},     // EPT_ENUM
    {1, ePC_FLOAT},   // EPT_FLOAT
    {2, ePC_FLOAT},   // EPT_FXY
    {3, ePC_FLOAT},   // EPT_FXYZ
    {4, ePC_FLOAT},   // EPT_FXYZW
    {1, ePC_INT},     // EPT_INT
    {2, ePC_INT},     // EPT_IXY
    {3, ePC_INT},     // EPT_IXYZ
    {4, ePC_INT},     // EPT_IXYZW
    {1, ePC_INT},     // EPT_FILE
    {1, ePC_STRING},  // EPT_TEXT
    {3, ePC_COLOR},   // EPT_RGB
    {4, ePC_COLOR},   // EPT_RGBA
};

Parameter::Parameter() {}

Parameter::Parameter(ParamType type, QString name, float min, float max, BaseNode* node)
    : type(type), name(name), min(min), max(max), node(node), isConnected(false)
{}

void Parameter::setDescription(const QString& descr)
{
  Q_ASSERT(type == EPT_ENUM || type == EPT_FLAGS);
  Q_ASSERT(descr.length() > 0);
  m_descr = descr;
}

const eString& Parameter::getDescription() const { return m_descr; }

ParamType Parameter::getType() { return type; }

eF32 Parameter::getMin() const { return min; }

eF32 Parameter::getMax() const { return max; }

BaseNode* Parameter::getOwnerOp() const { return node; }

void Parameter::setChanged(eBool reconnect)
{
  //@@m_ownerOp->setChanged(reconnect);
}

const eParamValue& Parameter::getDefaultValue() const { return defVal; }

eParamValue& Parameter::getBaseValue() { return baseValue; }

const eParamValue& Parameter::getBaseValue() const { return baseValue; }

bool Parameter::getValueAsBool() const
{
  Q_ASSERT(type == EPT_BOOL);
  return std::get<bool>(baseValue);
}

int Parameter::getValueAsEnum() const
{
  Q_ASSERT(type == EPT_ENUM);
  return std::get<int>(baseValue);
}

unsigned char Parameter::getValueAsFlags() const
{
  Q_ASSERT(type == EPT_FLAGS);
  return std::get<unsigned char>(baseValue);
}

QString Parameter::getValueAsString() const
{
  Q_ASSERT(type == EPT_STRING || type == EPT_FILE || type == EPT_FILESAVE || type == EPT_BUTTON);
  return std::get<QString>(baseValue);
}

eF32 Parameter::getValueAsFloat() const
{
  Q_ASSERT(type == EPT_FLOAT);
  return std::get<eF32>(baseValue);
}

eFXY Parameter::getValueAsFXY() const
{
  Q_ASSERT(type == EPT_FXY);
  return std::get<eFXY>(baseValue);
}

eFXYZ Parameter::getValueAsFXYZ() const
{
  Q_ASSERT(type == EPT_FXYZ);
  return std::get<eFXYZ>(baseValue);
}

eFXYZW Parameter::getValueAsFXYZW() const
{
  Q_ASSERT(type == EPT_FXYZW);
  return std::get<eFXYZW>(baseValue);
}

eInt Parameter::getValueAsInt() const
{
  Q_ASSERT(type == EPT_INT);
  return std::get<eInt>(baseValue);
}

eIXY Parameter::getValueAsIXY() const
{
  Q_ASSERT(type == EPT_IXY);
  return std::get<eIXY>(baseValue);
}

eIXYZ Parameter::getValueAsIXYZ() const
{
  Q_ASSERT(type == EPT_IXYZ);
  return std::get<eIXYZ>(baseValue);
}

eIXYZW Parameter::getValueAsIXYZW() const
{
  Q_ASSERT(type == EPT_IXYZW);
  return std::get<eIXYZW>(baseValue);
}

eColor Parameter::getValueAsColor() const
{
  Q_ASSERT(type == EPT_RGB || type == EPT_RGBA);
  return std::get<eColor>(baseValue);
}

unsigned int Parameter::getComponentCount() { return PARAM_INFOS[type].numComponents; }
