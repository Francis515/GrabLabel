#pragma once
#include <qgraphicsitem.h>
#include<QGraphicsItem>
#include<QPoint>
#include<QPointF>
#include<QGraphicsSceneMouseEvent>
#include<QPainter>
#include<QPaintEvent>
class BrushPen :
	public QGraphicsItem
{
public:
	explicit BrushPen(QGraphicsItem *parent = Q_NULLPTR);
	~BrushPen();
	explicit BrushPen(qreal width, qreal height,
		QGraphicsItem *parent = Q_NULLPTR);
	QRectF boundingRect() const;
	//����ui�İ�ť�����Ƿ��ͼ
	void setBrush(bool checkBoxROI);

private:
	qreal boundingW = 2000;
	qreal boundingH = 2000;
	QPointF mousePos;
	qreal brushSize = 3;
	QPointF ellipSize=QPointF(brushSize, brushSize);
	bool checkBoxBrush = true;
	bool drawing = false;
	bool lastDraw = false;
protected:
	//����
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		QWidget *widget);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

