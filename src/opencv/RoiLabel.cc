#include "RoiLabel.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QStandardPaths>
#include <QFileDialog>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPixmap>

RoiLabel::RoiLabel(QWidget *parent)
	: QLabel(parent)
{
	this->initViewer();
}

RoiLabel::RoiLabel(const QString& text, QWidget* parent, Qt::WindowFlags f) : QLabel(text,parent,f)
{
  this->initViewer();
}

RoiLabel::~RoiLabel()
{
}

void RoiLabel::initViewer()
{
	m_bPainterPressed = false;
	m_bMovedPressed = false;
	m_bScalePressed = false;
	m_roiRect = QRect(0, 0, 0, 0);
	m_emCurDir = EmDirection::DIR_NONE;

	this->setMouseTracking(true);
	this->setFocusPolicy(Qt::StrongFocus);

	m_pOptMenu = new QMenu(this);
	m_pDelAction = new QAction(QStringLiteral("Delete"), this);
	connect(m_pDelAction, &QAction::triggered, this, [&]() { m_roiRect = QRect(0, 0, 0, 0); });
	m_pSaveAction = new QAction(QStringLiteral("Save"), this);
	connect(m_pSaveAction, &QAction::triggered, this, &RoiLabel::saveROIImage);

	m_pOptMenu->addAction(m_pDelAction);
	m_pOptMenu->addAction(m_pSaveAction);
}

/**
 * @brief				����roiͼ��
 *
 * @return				void
 */
void RoiLabel::saveROIImage()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save", QStandardPaths::writableLocation(QStandardPaths::PicturesLocation), "*.png");
	if (fileName.isEmpty())
	{
		return;
	}

	QImage saveImg = m_backImage.copy(m_roiRect);
	saveImg.save(fileName);
}

/**
 * @brief				��ȡ���Ƶľ���
 *
 * @return				���Ƶľ���
 */
QRect RoiLabel::getRoiRect() const
{
	return m_roiRect;
}

/**
 * @brief				���ñ���ͼƬ
 * @param img        	QImageͼƬ
 *
 * @return				void
 */
void RoiLabel::setBackImage(const QImage & img)
{
	m_backImage = img;
	this->setMinimumSize(img.width(), img.height());
	update();
}

/**
 * @brief				���ƾ���
 * @param event         ��ͼ�¼�
 *
 * @return				void
 */
void RoiLabel::paintEvent(QPaintEvent * event)
{
#if 1
	QLabel::paintEvent(event);

	if (m_backImage.isNull())
		return;

	QPixmap rawImg = QPixmap::fromImage(m_backImage);
	QString strPoint = QString("X:%0, Y:%1").arg(m_roiRect.x()).arg(m_roiRect.y());           //λ����Ϣ
	QString strSize = QString("W:%0, H:%1").arg(m_roiRect.width()).arg(m_roiRect.height());   //��С��Ϣ

	QPen pen;
	pen.setColor(Qt::yellow);
	pen.setWidth(EDGE_WIDTH);
	
	QFont font;
	font.setPixelSize(16);

	QPainter painter;
	painter.begin(this);
	painter.setBrush(QBrush(QColor(0, 0, 200, 120)));
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawPixmap(0, 0, rawImg);
	painter.drawText(m_roiRect.topLeft().x(), m_roiRect.topLeft().y() - 5, strSize);
	painter.drawText(m_roiRect.topLeft().x(), m_roiRect.topLeft().y() - 18, strPoint);
	painter.drawRect(m_roiRect);

	if (m_roiRect.width() != 0 && m_roiRect.height() != 0)
	{
#ifdef DRAW_SUB_LINE
		//�����м�ʮ�ּ�
		QPen dashPen(Qt::white);
		dashPen.setWidth(MIDDLELINE_WIDTH);
		dashPen.setStyle(Qt::DashDotLine);
		painter.setPen(dashPen);
		painter.drawLine(m_roiRect.topLeft().x() + m_roiRect.width() / 2, m_roiRect.topLeft().y() + EDGE_WIDTH, m_roiRect.bottomRight().x() - m_roiRect.width() / 2, m_roiRect.bottomRight().y());
		painter.drawLine(m_roiRect.topLeft().x() + EDGE_WIDTH, m_roiRect.topLeft().y() + m_roiRect.height() / 2, m_roiRect.bottomRight().x(), m_roiRect.bottomRight().y() - m_roiRect.height() / 2);
#endif

#ifdef DRAW_TEN_POINT
		//���Ʊ�Եʮ����
		painter.setBrush(Qt::green);
		pen.setWidth(0);
		painter.setPen(pen);

		painter.drawRect(m_roiRect.topLeft().x(), m_roiRect.topLeft().y(), POINT_WIDTH, POINT_HEIGHT); //���Ͻ�
		painter.drawRect(m_roiRect.topLeft().x(), m_roiRect.topLeft().y() + m_roiRect.height() / 2 - POINT_WIDTH / 2, POINT_WIDTH, POINT_HEIGHT); //������ĵ�
		painter.drawRect(m_roiRect.bottomLeft().x(), m_roiRect.bottomLeft().y()- POINT_WIDTH, POINT_WIDTH, POINT_HEIGHT); //���½�
		painter.drawRect(m_roiRect.topLeft().x() + m_roiRect.width() / 2 - POINT_WIDTH / 2, m_roiRect.topLeft().y(), POINT_WIDTH, POINT_HEIGHT);  //��������
		painter.drawRect(m_roiRect.topLeft().x() + m_roiRect.width() / 2 - POINT_WIDTH /2, m_roiRect.topLeft().y() + m_roiRect.height() / 2 - POINT_WIDTH / 2, POINT_WIDTH, POINT_HEIGHT);  //���ĵ�
		painter.drawRect(m_roiRect.bottomLeft().x() + m_roiRect.width() / 2 - POINT_WIDTH / 2, m_roiRect.bottomLeft().y() - POINT_WIDTH, POINT_WIDTH, POINT_HEIGHT); //�ײ����ĵ�
		painter.drawRect(m_roiRect.topRight().x() - POINT_WIDTH, m_roiRect.topRight().y(), POINT_WIDTH, POINT_HEIGHT); //���Ͻ�
		painter.drawRect(m_roiRect.topRight().x() - POINT_WIDTH / 2, m_roiRect.topRight().y() + m_roiRect.height() / 2 - POINT_WIDTH /2, POINT_WIDTH, POINT_HEIGHT); //�ұ����ĵ�
		painter.drawRect(m_roiRect.bottomRight().x() - POINT_WIDTH, m_roiRect.bottomRight().y() - POINT_WIDTH, POINT_WIDTH, POINT_HEIGHT); //���½ǵ�
#endif
	}
	

	painter.end();

#else
	QLabel::paintEvent(event);

	if (m_backImage.isNull())
		return;
	QPixmap rawImg = QPixmap::fromImage(m_backImage);
	QPainter painter(this);
	painter.begin(&rawImg);
	painter.setBrush(Qt::gray);
	painter.drawRect(30,30,100,100);
	painter.end();
	this->setPixmap(rawImg);
#endif
}

/**
 * @brief				��갴���¼� �����϶�����������ʼ
 * @param ev	        ����¼�
 *
 * @return				void
 */
void RoiLabel::mousePressEvent(QMouseEvent * ev)
{
	if (ev->buttons() & Qt::LeftButton)
	{
		EmDirection dir = region(ev->pos());     //��ȡ��굱ǰ��λ��

		if (dir == DIR_MIDDLE)
		{
			//����ھ�������λ��
			this->setCursor(Qt::ClosedHandCursor);
			m_moveStartPoint.setX(ev->pos().x());
			m_moveStartPoint.setY(ev->pos().y());
			m_bMovedPressed = true;
		}
		else if (dir == DIR_NONE)
		{
			//����ھ����ⲿ
			this->setCursor(Qt::ArrowCursor);
			m_bPainterPressed = true;
			m_paintStartPoint.setX(ev->pos().x());
			m_paintStartPoint.setY(ev->pos().y());
		}
		else
		{
			//�����ھ��α�Ե
			m_moveStartPoint.setX(ev->pos().x());
			m_moveStartPoint.setY(ev->pos().y());
			m_bScalePressed = true;
			m_emCurDir = dir;
		}
	}
}

/**
 * @brief				����ƶ��¼�
 * @param ev         	����¼�
 *
 * @return				void
 */
void RoiLabel::mouseMoveEvent(QMouseEvent * ev)
{
	if (ev->buttons() & Qt::LeftButton)
	{
		if (m_bPainterPressed)
		{
			//���ڻ���״̬
			paintRect(ev->pos());
			
		}
		else if (m_bMovedPressed)
		{
			//�����ƶ�״̬
			moveRect(ev->pos());
		}
		else if (m_bScalePressed)
		{
			//�������Ŵ�С״̬
			scaleRect(ev->pos());
		}

		//���½���
		update();
		return;
	}

	//��������λ�����õ�ǰ�������״
	EmDirection dir = region(ev->pos());

	if (dir == DIR_NONE)
	{
		setCursor(Qt::ArrowCursor);
	}
	else if (dir == DIR_MIDDLE)
	{
		setCursor(Qt::OpenHandCursor);
	}
}

/**
 * @brief				����ɿ��¼�
 * @param ev	        ����¼�
 *
 * @return				void
 */
void RoiLabel::mouseReleaseEvent(QMouseEvent * ev)
{
	//�ж�����Ƿ��ھ�����
	if (m_roiRect.contains(ev->pos()))
	{
		//�ɿ����ǰ�Ƿ������Ϸ�
		if (m_bMovedPressed)
		{
			this->setCursor(Qt::OpenHandCursor);
		}
		else
		{
			this->setCursor(Qt::ArrowCursor);
		}
	}

	m_paintStartPoint = QPoint();
	m_bMovedPressed = false;
	m_bPainterPressed = false;
	m_bScalePressed = false;
}

/**
 * @brief				���̰����¼�
 * @param ev	        �����¼�
 *
 * @return				void
 */
void RoiLabel::keyPressEvent(QKeyEvent * ev)
{
	if (ev->key() == Qt::Key_Delete)
	{
		m_roiRect = QRect(0,0,0,0);
		update();
	}
}

/**
 * @brief				�Ҽ��˵�
 * @param ev	        �˵��¼�
 *
 * @return				void
 */
void RoiLabel::contextMenuEvent(QContextMenuEvent * ev)
{
	QPoint mousePos = ev->pos();

	if (m_roiRect.contains(mousePos))
	{
		m_pOptMenu->exec(QCursor::pos());
	}
	
	ev->accept();
}

/**
 * @brief				�ж�����λ��
 * @param point         ����λ��	
 *
 * @return				EmDirection ����
 */
EmDirection RoiLabel::region(const QPoint & point)
{
	int mouseX = point.x();
	int mouseY = point.y();

	QPoint roiTopLeft = m_roiRect.topLeft();
	QPoint roiBottomRight = m_roiRect.bottomRight();

	EmDirection dir = DIR_NONE;

	if (mouseX <= roiTopLeft.x() + CORPADDING && mouseX >= roiTopLeft.x() && mouseY <= roiTopLeft.y() + CORPADDING && mouseY >= roiTopLeft.y())
	{
		//���Ͻ�
		this->setCursor(Qt::SizeFDiagCursor);
		dir = DIR_LEFTTOP;
	}
	else if (mouseX >= roiBottomRight.x() - CORPADDING && mouseX < roiBottomRight.x() && mouseY <= roiTopLeft.y() + CORPADDING && mouseY >= roiTopLeft.y())
	{
		//���Ͻ�
		this->setCursor(Qt::SizeBDiagCursor);
		dir = DIR_RIGHTTOP;
	}
	else if (mouseX <= roiTopLeft.x() + CORPADDING && mouseX >= roiTopLeft.x() && mouseY >= roiBottomRight.y() - CORPADDING && mouseY <= roiBottomRight.y())
	{
		//���½�
		this->setCursor(Qt::SizeBDiagCursor);
		dir = DIR_LEFTBOTTOM;
	}
	else if (mouseX >= roiBottomRight.x() - CORPADDING && mouseX < roiBottomRight.x() && mouseY >= roiBottomRight.y() - CORPADDING && mouseY <= roiBottomRight.y())
	{
		//���½�
		this->setCursor(Qt::SizeFDiagCursor);
		dir = DIR_RIGHTBOTTOM;
	}
	else if (mouseX >= roiBottomRight.x() - EDGPADDING && mouseX <= roiBottomRight.x() && mouseY >= roiTopLeft.y() && mouseY <= roiBottomRight.y())
	{
		//�ұ�
		this->setCursor(Qt::SizeHorCursor);
		dir = DIR_RIGHT;
	}
	else if (mouseY <= roiTopLeft.y() + EDGPADDING && mouseY >= roiTopLeft.y() && mouseX >= roiTopLeft.x() && mouseX <= roiBottomRight.x())
	{
		//�ϱ�
		this->setCursor(Qt::SizeVerCursor);
		dir = DIR_TOP;
	}
	else if (mouseY >= roiBottomRight.y() - EDGPADDING && mouseY <= roiBottomRight.y() && mouseX >= roiTopLeft.x() && mouseX <= roiBottomRight.x())
	{
		//�±�
		this->setCursor(Qt::SizeVerCursor);
		dir = DIR_BOTTOM;
	}
	else if (mouseX <= roiTopLeft.x() + EDGPADDING && mouseX >= roiTopLeft.x() && mouseY >= roiTopLeft.y() && mouseY <= roiBottomRight.y())
	{
		//���
		this->setCursor(Qt::SizeHorCursor);
		dir = DIR_LEFT;
	}
	else if(m_roiRect.contains(point))
	{
		//�м�
		dir = DIR_MIDDLE;
	}
	else
	{
		dir = DIR_NONE;
	}

	return dir;
}

/**
 * @brief				���ž���
 * @param mousePoint    ����λ��
 *
 * @return				void
 */
void RoiLabel::scaleRect(const QPoint & mousePoint)
{
	QRect newRect(m_roiRect.topLeft(), m_roiRect.bottomRight());
	int width = mousePoint.x() - m_moveStartPoint.x();   //�ƶ��Ŀ��
	int height = mousePoint.y() - m_moveStartPoint.y();  //�ƶ��ĸ߶�

	//���ݵ�ǰ������״̬���ı���ε�λ�ô�С��Ϣ
	switch (m_emCurDir)
	{
	case DIR_LEFT:
		newRect.setLeft(mousePoint.x());
		break;
	case DIR_RIGHT:
		newRect.setRight(mousePoint.x());
		break;
	case DIR_TOP:
		newRect.setTop(mousePoint.y());
		break;
	case DIR_BOTTOM:
		newRect.setBottom(mousePoint.y());
		break;
	case DIR_LEFTTOP:
		newRect.setTopLeft(mousePoint);
		break;
	case DIR_LEFTBOTTOM:
		newRect.setBottomLeft(mousePoint);
		break;
	case DIR_RIGHTTOP:
		newRect.setTopRight(mousePoint);
		break;
	case DIR_RIGHTBOTTOM:
		newRect.setBottomRight(mousePoint);
		break;
	}

	if (newRect.width() < MIN_WIDTH || newRect.height() < MIN_HEIGHT)
	{
		//���ŵĴ�С����
		return;
	}

	m_roiRect = newRect;
	m_moveStartPoint = mousePoint;  //����������ʼλ��
}

/**
 * @brief				���ƾ���
 * @param mousePoint    ����λ��
 *
 * @return				void
 */
void RoiLabel::paintRect(const QPoint & mousePoint)
{
	this->setCursor(Qt::ArrowCursor);                    //�������Ϊָ����״

	int width = mousePoint.x() - m_paintStartPoint.x();  //�ƶ��Ŀ��
	int height = mousePoint.y() - m_paintStartPoint.y(); //�ƶ��ĸ߶�

	if (width < 0 && height < 0)
	{
		//��������Ͻ��ƶ�
		m_roiRect.setX(mousePoint.x());
		m_roiRect.setY(mousePoint.y());
	}
	else if (width < 0)
	{
		//�����Xλ���ƶ�
		m_roiRect.setX(mousePoint.x());
		m_roiRect.setY(m_paintStartPoint.y());
	}
	else if (height < 0)
	{
		//�����Yλ���ƶ�
		m_roiRect.setX(m_paintStartPoint.x());
		m_roiRect.setY(mousePoint.y());
	}
	else
	{
		//����  �������ƶ�
		m_roiRect.setX(m_paintStartPoint.x());
		m_roiRect.setY(m_paintStartPoint.y());
	}

	//���þ��δ�С ����ֵ ���ⷴ����Ĳ����ĸ�ֵ
	m_roiRect.setSize(QSize(abs(width), abs(height)));
}

/**
 * @brief				���ƾ���
 * @param mousePoint    ����λ��
 *
 * @return				void
 */
void RoiLabel::moveRect(const QPoint & mousePoint)
{
	this->setCursor(Qt::ClosedHandCursor);

	int width = mousePoint.x() - m_moveStartPoint.x();
	int height = mousePoint.y() - m_moveStartPoint.y();

	QRect ret;
	ret.setX(m_roiRect.x() + width);
	ret.setY(m_roiRect.y() + height);
	ret.setSize(m_roiRect.size());
	m_roiRect = ret;
	m_moveStartPoint = mousePoint;
}


void RoiLabel::getRoiImage(QImage &img) const { img = m_backImage.copy(m_roiRect); }


RoiDialog::RoiDialog(QWidget* parent) : QDialog(parent) {
  roi_label_ = new RoiLabel();

	ok_btn_ = new QPushButton("Sure");
  cancel_btn_ = new QPushButton("Cancel");

	QHBoxLayout *h_layout = new QHBoxLayout();
  h_layout->addWidget(cancel_btn_);
  h_layout->addWidget(ok_btn_);

  QVBoxLayout *layout = new QVBoxLayout();
  layout->setContentsMargins(1, 0, 1, 1);
  layout->setSpacing(0);
  layout->addWidget(roi_label_);
  layout->addLayout(h_layout);
  setLayout(layout);

	connect(ok_btn_, SIGNAL(clicked()), this, SLOT(SureBtnSlot()));
  connect(cancel_btn_, SIGNAL(clicked()), this, SLOT(CancelBtnSlot()));
}

RoiDialog ::~RoiDialog() {  }


void RoiDialog::SetImage(const QImage &img)
{
  roi_label_->setBackImage(img.scaled(400, 400, Qt::KeepAspectRatio));
}

void RoiDialog::SureBtnSlot(void) 
{ 
	QImage img;
  roi_label_->getRoiImage(img);
  emit SelectRoiImag(img);
}

void RoiDialog::CancelBtnSlot(void) 
{ close(); }
