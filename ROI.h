#pragma once
#include<QGraphicsItem>
#include<QPoint>
#include<QGraphicsSceneMouseEvent>
#include<QPainter>
#include<QPaintEvent>
#include<qDebug>
class ROI :
	public QGraphicsItem
{
public:
	explicit ROI(QGraphicsItem *parent = Q_NULLPTR);
	//需要初始化画布的大小
	explicit ROI(qreal width, qreal height, 
		QGraphicsItem *parent = Q_NULLPTR);
	~ROI();
	//设置自定义类型枚举
	enum {Type=UserType};
	int type() const
	{ return Type; }

	//重载边界
	QRectF boundingRect() const;
	//根据ui的按钮控制是否绘图
	void setROI(bool checkBoxROI);
	//提供roi的坐标信息
	double getX();
	double getY();
	double getWidth();
	double getHeight();
private:
	qreal boundingW=2000;
	qreal boundingH=2000;
	QRectF ROIRect;
	int brushSize = 5;

	//绘图过程控制变量
	bool checkBoxROI = false;
	bool drawing = false;
	bool lastDraw = false;

protected:
	//重载绘图与鼠标消息
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		QWidget *widget);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

