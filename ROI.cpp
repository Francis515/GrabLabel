#include "ROI.h"



ROI::ROI(QGraphicsItem *parent)
{
}
ROI::ROI(qreal width, qreal height, QGraphicsItem *parent)
{
	boundingH = height;
	boundingW = width;
	QPointF topLeft(0, 0);
	QPointF bottmRight(width, height);
	ROIRect.setTopLeft(topLeft);
	ROIRect.setBottomRight(bottmRight);
}

ROI::~ROI()
{
}

void ROI::setROI(bool checkBoxROI) {
	this->checkBoxROI = checkBoxROI;
}
QRectF ROI::boundingRect() const
{
	//����ͼ��ķ�Χ�趨���߽�
	return QRectF(0,0,boundingW-1,boundingH-1);
}

double ROI::getX() {
	//��opencv�Խӣ�x���������Ͻǵ������ұ߳�����Ϊ��
	if (ROIRect.width() > 0)
		return ROIRect.x();
	else
		return ROIRect.x() + ROIRect.width();
}
double ROI::getY() {
	if (ROIRect.height() > 0)
		return ROIRect.y();
	else
		return ROIRect.y() + ROIRect.height();
}
double ROI::getWidth() {
	return abs(ROIRect.width());
}
double ROI::getHeight() {
	return abs(ROIRect.height());
}
void ROI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
	QWidget *widget)
{
	//if (checkBoxROI) {
		//drawing�������»��ƾ��Σ�ֱ��lastDraw
		if (drawing) {
			QPen pen(Qt::red, brushSize);
			painter->setPen(pen);
			painter->drawRect(ROIRect);
		}
		update();
		if (lastDraw) {
			QPen pen(Qt::red, brushSize);
			painter->setPen(pen);
			painter->drawRect(ROIRect);
		}
		
	//}

}

void ROI::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	//��Ҫ��ѡ��ROIѡ����������ʼ���ƾ���
	if (checkBoxROI && boundingRect().contains(event->pos())
		&& event->button()==Qt::LeftButton) {
		drawing = true;
		ROIRect.setTopLeft(event->pos());
		ROIRect.setBottomRight(event->pos());
	}
	
}
void ROI::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (drawing && boundingRect().contains(event->pos())) {
		//�ƶ������в��ϸ��¾��εı߽���Ϣ
		ROIRect.setBottomRight(event->pos());
	}
	
}
void ROI::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		//���̧��������̬����
		drawing = false;
		lastDraw = true;
	}
}