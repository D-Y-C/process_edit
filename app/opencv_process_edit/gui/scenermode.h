#ifndef SCENER_MODE_H
#define SCENER_MODE_H

#include <QtCore/QObject>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>

#include "qcanpool/fancymode.h"

QCANPOOL_USE_NAMESPACE

class ScenerMode : public FancyMode
{
  Q_OBJECT

public:
  explicit ScenerMode(QWidget* parent = nullptr);
  ~ScenerMode();

public slots:
  void enableTorus(bool enabled);
  void enableCone(bool enabled);
  void enableCylinder(bool enabled);
  void enableCuboid(bool enabled);
  void enablePlane(bool enabled);
  void enableSphere(bool enabled);

private:
  void createWindow();

private:
  Qt3DCore::QEntity* m_rootEntity;
  Qt3DExtras::QTorusMesh* m_torus;
  Qt3DCore::QEntity* m_coneEntity;
  Qt3DCore::QEntity* m_cylinderEntity;
  Qt3DCore::QEntity* m_torusEntity;
  Qt3DCore::QEntity* m_cuboidEntity;
  Qt3DCore::QEntity* m_planeEntity;
  Qt3DCore::QEntity* m_sphereEntity;
};

#endif // SCENER_MODE_H

