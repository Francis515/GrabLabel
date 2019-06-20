#include "ImageViewer.h"



ImageViewer::ImageViewer(QWidget *parent):QGraphicsView(parent)
{
}


ImageViewer::~ImageViewer()
{
}

void ImageViewer::wheelEvent(QWheelEvent *event) {
	if (event->orientation() == Qt::Vertical) {
		double angleDeltaY = event->angleDelta().y();
		double zoomFactor = qPow(1.0015, angleDeltaY);
		scale(zoomFactor, zoomFactor);
		if (angleDeltaY > 0) {
			this->centerOn(sceneMousePos);
			sceneMousePos = this->mapToScene(event->pos());
		}
		this->viewport()->update();
		event->accept();
	}
	else {
		event->ignore();
	}
}


// 鼠标拖动功能，没有启用
/*
void ImageViewer::mouseMoveEvent(QMouseEvent *event) {
	
	if (moving) {
		QPointF disPointF = event->pos() - previousPos;
		previousPos = event->pos();
		this->scene()->setSceneRect(this->scene()->sceneRect().x() - disPointF.x(),
			this->scene()->sceneRect().y() - disPointF.y(),
			this->scene()->sceneRect().width(),
			this->scene()->sceneRect().height());
		this->scene()->update();
	}
	
	QGraphicsView::mouseMoveEvent(event);
}

void ImageViewer::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::MiddleButton) {
		previousPos = event->pos();
		moving = true;
	}
	QGraphicsView::mousePressEvent(event);
}

void ImageViewer::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::MiddleButton) {
		moving = false;
	}
	QGraphicsView::mouseReleaseEvent(event);
}
*/