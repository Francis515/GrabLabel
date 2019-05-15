#include "BrushPen.h"



BrushPen::BrushPen(QGraphicsItem *parent)
{
}
BrushPen::BrushPen(qreal width, qreal height, QGraphicsItem *parent)
{
	boundingH = height;
	boundingW = width;
}

BrushPen::~BrushPen()
{
}


void BrushPen::setBrush(bool checkBoxROI) {
	this->checkBoxBrush = checkBoxROI;
}
QRectF BrushPen::boundingRect() const
{
	//根据图像的范围设定最大边界
	return QRectF(0, 0, boundingW, boundingH);
}

void BrushPen::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
	QWidget *widget)
{
	//drawing不断重新绘制矩形，直到lastDraw
	if (drawing) {
		QPen pen(Qt::red, brushSize);
		painter->setPen(pen);
		QRectF outRect(mousePos - ellipSize, mousePos + ellipSize);
		painter->drawEllipse(outRect);
	}
	if (lastDraw) {
		QPen pen(Qt::red, brushSize);
		painter->setPen(pen);
		QRectF outRect(mousePos - ellipSize, mousePos + ellipSize);
		painter->drawEllipse(outRect);
	}

	update();

}

void BrushPen::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	//需要已选择ROI选项，按下左键开始绘制矩形
	if (checkBoxBrush) {
		drawing = true;
		mousePos = event->pos();
	}

}
void BrushPen::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	//移动过程中不断更新矩形的边界信息
	mousePos = event->pos();
}
void BrushPen::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	//鼠标抬起后结束动态绘制
	drawing = false;
	lastDraw = true;
}
