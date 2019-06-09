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
	//根据图像的范围设定最大边界
	return QRectF(0,0,boundingW,boundingH);
}

double ROI::getX() {
	//与opencv对接，x必须是左上角的坐标且边长必须为正
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
		//drawing不断重新绘制矩形，直到lastDraw
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
	//需要已选择ROI选项，按下左键开始绘制矩形
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
		//移动过程中不断更新矩形的边界信息
		ROIRect.setBottomRight(event->pos());
	}
	
}
void ROI::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		//鼠标抬起后结束动态绘制
		drawing = false;
		lastDraw = true;
	}
	qDebug() << ROIRect;
	
}