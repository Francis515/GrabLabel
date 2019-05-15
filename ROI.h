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
	//��Ҫ��ʼ�������Ĵ�С
	explicit ROI(qreal width, qreal height, 
		QGraphicsItem *parent = Q_NULLPTR);
	~ROI();
	//�����Զ�������ö��
	enum {Type=UserType};
	int type() const
	{ return Type; }

	//���ر߽�
	QRectF boundingRect() const;
	//����ui�İ�ť�����Ƿ��ͼ
	void setROI(bool checkBoxROI);
	//�ṩroi��������Ϣ
	double getX();
	double getY();
	double getWidth();
	double getHeight();
private:
	qreal boundingW=2000;
	qreal boundingH=2000;
	QRectF ROIRect;
	int brushSize = 5;

	//��ͼ���̿��Ʊ���
	bool checkBoxROI = false;
	bool drawing = false;
	bool lastDraw = false;

protected:
	//���ػ�ͼ�������Ϣ
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		QWidget *widget);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

