#include "MyScene.h"



MyScene::MyScene(QObject *parent) : QGraphicsScene(parent)
{
	//初始化边界
	QPointF topLeft(0, 0);
	bounding.setTopLeft(topLeft);
	QPointF bottomRight(0, 0);
	bounding.setBottomRight(bottomRight);
}


MyScene::~MyScene()
{
}

void MyScene::setBrush(bool checkBoxBrush, bool checkBoxClean)
{
	this->checkBoxBrush = checkBoxBrush;
	if (checkBoxBrush) {
		if (checkBoxClean) {
			cleanMode = true;
			brushMode = false;
		}
		else {
			cleanMode = false;
			brushMode = true;
		}
	}
	else {
		cleanMode = false;
		brushMode = false;
	}
	
}
void MyScene::setBrushSize(int brushSize)
{
	this->brushSize = brushSize;
}

void MyScene::setBounding(QPointF topLeft, QPointF bottomRight)
{
	//要留出大约一个笔刷的距离，不然画出的图形也会出界
	QPointF tmp(1*brushSize, 1*brushSize);
	bounding.setTopLeft(topLeft+tmp);
	bounding.setBottomRight(bottomRight-tmp);
}
void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (brushMode && bounding.contains(event->scenePos())) {
		if (event->button() == Qt::LeftButton) {
			brushing = true;
			// Save the coordinates of the point of pressing
			previousPoint = event->scenePos();
		}
		else if(event->button() == Qt::RightButton){
			brushing = true;
			brushBackground = true;
			addEllipse(event->scenePos().x(),
				event->scenePos().y(),
				brushSize,
				brushSize,
				QPen(Qt::NoPen),
				QBrush(Qt::blue));
		}
		
		
	}	
	else if (cleanMode && event->button() != Qt::MiddleButton) {
		cleaning = true;
		/*
		QGraphicsItem *itemToRemove = 0;
		foreach (QGraphicsItem *item, items(event->scenePos())){
			if (item->type() == QGraphicsLineItem::Type) {
				itemToRemove = item;
				break;
			}
		}
		if (itemToRemove != 0)
			removeItem(itemToRemove);
		*/
		//只要图形的位置在鼠标位置的一个邻域内，就会被删除
		QGraphicsItem *itemToRemove = 0;
		foreach(QGraphicsItem *item, this->items()) {
			QPointF itemPos;
			itemPos.setX(item->boundingRect().x());
			itemPos.setY(item->boundingRect().y());
			if ((abs(event->scenePos().x() - itemPos.x()) < brushSize*1.5)
				&& (abs(event->scenePos().y() - itemPos.y()) < brushSize*1.5)
				&& (item->type() == QGraphicsLineItem::Type
					|| item->type() == QGraphicsEllipseItem::Type)) {
				itemToRemove = item;
				break;
			}
		}
		if (itemToRemove != 0)
			removeItem(itemToRemove);
	}
	else {
		event->ignore();
		//将事件继续传递
		QGraphicsScene::mousePressEvent(event);
	}
	

}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (brushMode && brushing && bounding.contains(event->scenePos())) {
		if (!brushBackground) {
			// We draw the line with the previous coordinates
			addLine(previousPoint.x(),
				previousPoint.y(),
				event->scenePos().x(),
				event->scenePos().y(),
				QPen(Qt::red, brushSize, Qt::SolidLine, Qt::RoundCap));
			// Update on the previous coordinate data
			previousPoint = event->scenePos();
		}
		else {
			addEllipse(event->scenePos().x(),
				event->scenePos().y(),
				brushSize,
				brushSize,
				QPen(Qt::NoPen),
				QBrush(Qt::blue));
		}
		
	}
	else if (cleanMode && cleaning) {
		/*
		QGraphicsItem *itemToRemove = 0;
		foreach(QGraphicsItem *item, items(event->scenePos())) {
			if (item->type() == QGraphicsLineItem::Type
				|| item->type() == QGraphicsEllipseItem::Type) {
				itemToRemove = item;
				break;
			}
		}
		if (itemToRemove != 0)
			removeItem(itemToRemove);
		*/
		QGraphicsItem *itemToRemove = 0;
		foreach(QGraphicsItem *item, this->items()) {
			QPointF itemPos;
			itemPos.setX(item->boundingRect().x());
			itemPos.setY(item->boundingRect().y());
			if ( (abs(event->scenePos().x()- itemPos.x()) < brushSize*1.5)
				&& (abs(event->scenePos().y() - itemPos.y()) < brushSize*1.5)
				&& (item->type() == QGraphicsLineItem::Type
					|| item->type() == QGraphicsEllipseItem::Type)) {
				itemToRemove = item;
				break;
			}
		}
		if (itemToRemove != 0)
			removeItem(itemToRemove);
	}
	else {
		event->ignore();
		//将事件继续传递
		QGraphicsScene::mouseMoveEvent(event);
	}
	
}
void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (brushing || cleaning) {
		cleaning = false;
		brushing = false;
		brushBackground = false;
	}
	else {
		event->ignore();
		//将事件继续传递
		QGraphicsScene::mouseReleaseEvent(event);
	}
	
}
