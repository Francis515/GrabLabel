#pragma once
#include <qgraphicsscene.h>
#include<QGraphicsSceneEvent>
#include<QPixmap>
#include<QPaintEvent>
#include<QPainter>
#include<QGraphicsItemGroup>
#include<ROI.h>
#include<qDebug>

class MyScene :
	public QGraphicsScene
{
	Q_OBJECT
public:
	explicit MyScene(QObject *parent= Q_NULLPTR);
	~MyScene();
	void setBrush(bool checkBoxBrush, bool checkBoxClean);
	void setBrushSize(int brushSize);
	void setBounding(QPointF topLeft, QPointF bottomRight);
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
	QRectF bounding;
	QPointF previousPoint;
	int brushSize = 5;
	bool checkBoxBrush = false;
	bool brushMode = false;
	bool cleanMode = false;
	bool brushing = false;
	bool cleaning = false;
	bool brushBackground = false;
};
