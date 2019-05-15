#pragma once
#include <qgraphicsview.h>
#include<QGraphicsView>
#include<QWheelEvent>
#include<QtMath>
#include<QPointF>
#include<QMouseEvent>



class ImageViewer :
	public QGraphicsView
{
public:
	explicit ImageViewer(QWidget *parent = nullptr);
	~ImageViewer();
protected:
	//�������������
	void wheelEvent(QWheelEvent *event);
	//����м��϶�
	/*
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	*/
private:
	QPointF sceneMousePos;
	QPointF previousPos;
	bool moving = false;
};

