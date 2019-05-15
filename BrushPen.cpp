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
	//����ͼ��ķ�Χ�趨���߽�
	return QRectF(0, 0, boundingW, boundingH);
}

void BrushPen::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
	QWidget *widget)
{
	//drawing�������»��ƾ��Σ�ֱ��lastDraw
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
	//��Ҫ��ѡ��ROIѡ����������ʼ���ƾ���
	if (checkBoxBrush) {
		drawing = true;
		mousePos = event->pos();
	}

}
void BrushPen::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	//�ƶ������в��ϸ��¾��εı߽���Ϣ
	mousePos = event->pos();
}
void BrushPen::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	//���̧��������̬����
	drawing = false;
	lastDraw = true;
}
