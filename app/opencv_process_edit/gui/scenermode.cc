#include "scenermode.h"

#include <QGuiApplication>

#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>

#include <Qt3DInput/QInputAspect>

#include <Qt3DExtras/qtorusmesh.h>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qpointlight.h>

#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>

#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DExtras/qforwardrenderer.h>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>

#include <QtCore/QDebug>
#include <QtGui/qscreen.h>

#include <QVBoxLayout>

ScenerMode::ScenerMode(QWidget* parent)
  : FancyMode(parent)
{
  setObjectName(QLatin1String("ViewerMode"));
  setDisplayName(tr("Viewer"));
  setIcon(QIcon(":/mode/chart"));

  Qt3DExtras::Qt3DWindow* view = new Qt3DExtras::Qt3DWindow();
  view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
  QWidget* container = QWidget::createWindowContainer(view);

  QSize screenSize = view->screen()->size();
  container->setMinimumSize(QSize(200, 100));
  container->setMaximumSize(screenSize);

  // Root entity
  m_rootEntity = new Qt3DCore::QEntity();

  // Camera
  Qt3DRender::QCamera* cameraEntity = view->camera();

  cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
  cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
  cameraEntity->setUpVector(QVector3D(0, 1, 0));
  cameraEntity->setViewCenter(QVector3D(0, 2, 2));

  Qt3DCore::QEntity* lightEntity = new Qt3DCore::QEntity(m_rootEntity);
  Qt3DRender::QPointLight* light = new Qt3DRender::QPointLight(lightEntity);
  light->setColor("white");
  light->setIntensity(1);
  lightEntity->addComponent(light);
  Qt3DCore::QTransform* lightTransform = new Qt3DCore::QTransform(lightEntity);
  lightTransform->setTranslation(cameraEntity->position());
  lightEntity->addComponent(lightTransform);

  // For camera controls
  Qt3DExtras::QFirstPersonCameraController* camController = new Qt3DExtras::QFirstPersonCameraController(m_rootEntity);
  camController->setCamera(cameraEntity);

  // Cuboid shape data
  Qt3DExtras::QCuboidMesh* cuboid = new Qt3DExtras::QCuboidMesh();

  // CuboidMesh Transform
  Qt3DCore::QTransform* cuboidTransform = new Qt3DCore::QTransform();
  cuboidTransform->setScale(4.0f);
  cuboidTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));
  cuboidTransform->setRotationX(1.7);
  cuboidTransform->setRotationY(1.7);
  cuboidTransform->setRotationZ(1.7);

  Qt3DExtras::QPhongMaterial* cuboidMaterial = new Qt3DExtras::QPhongMaterial();
  cuboidMaterial->setDiffuse(QColor(QRgb(0x665423)));

  //Cuboid
  m_cuboidEntity = new Qt3DCore::QEntity(m_rootEntity);
  m_cuboidEntity->addComponent(cuboid);
  m_cuboidEntity->addComponent(cuboidMaterial);
  m_cuboidEntity->addComponent(cuboidTransform);

  // Set root object of the scene
  view->setRootEntity(m_rootEntity);
  //  createWindow();

  QVBoxLayout* layout = new QVBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->addWidget(container);

  QWidget* w = new QWidget();
  w->setLayout(layout);
  setWidget(w);
}

ScenerMode::~ScenerMode()
{
}

//! [4]
void ScenerMode::enableTorus(bool enabled)
{
  m_torusEntity->setEnabled(enabled);
}
//! [4]

void ScenerMode::enableCone(bool enabled)
{
  m_coneEntity->setEnabled(enabled);
}

void ScenerMode::enableCylinder(bool enabled)
{
  m_cylinderEntity->setEnabled(enabled);
}

void ScenerMode::enableCuboid(bool enabled)
{
  m_cuboidEntity->setEnabled(enabled);
}

void ScenerMode::enablePlane(bool enabled)
{
  m_planeEntity->setEnabled(enabled);
}

void ScenerMode::enableSphere(bool enabled)
{
  m_sphereEntity->setEnabled(enabled);
}

void ScenerMode::createWindow()
{

}
