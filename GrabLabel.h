#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GrabLabel.h"
#include<QString>
#include<QFileDialog>
#include<QDir>
#include<QFile>
#include<QMessageBox>
#include<QImage>
#include<QGraphicsView>
#include<QGraphicsScene>
#include<QPixmap>
#include<QImage>
#include<QAction>
#include<QEvent>
#include<QStandardItemModel>
#include<iostream>
#include<fstream>
#include<vector>
#include<MultiLabel.h>
#include<MyScene.h>
#include<QDebug>
#include<ROI.h>
#include<opencv2/opencv.hpp>
#include"ConvertType.h"
using namespace cv;
using namespace std;

QPixmap itemToQPixmap(QGraphicsItem *item);
//�����Ƶ�ͼ����ת��Ϊmask
Mat groupToMask(QGraphicsScene *scene, int type);

class GrabLabel : public QMainWindow
{
	Q_OBJECT

public:
	GrabLabel(QWidget *parent = Q_NULLPTR);

private:
	//���ÿ���
	void buttonsOff();
	//��������
	Ui::GrabLabelClass ui;
	MyScene *scene = new MyScene();
	QStandardItemModel *tableModel;
	//ROI
	ROI *roi = 0;
	//�洢�ָ�������
	MultiLabel multiLabel;
	//����ض����͵���Ŀ
	void clearType(int type);
	//�ָ�ģʽ,��ͨģʽ������ģʽ
	enum{NORMAL_CUT=1,LIGHTNING_CUT=2};
	int cutMode = LIGHTNING_CUT;

protected:
	void closeEvent(QCloseEvent *event);
private slots:
	//�˵�����
	void OpenImgAction();
	void CloseImgAction();
	void LoadLabelAction();
	void CloseLabelAction();
	void SaveAsGrayAction();
	void SaveAsRGBAction();
	void HelpAction();
	void ContactAction();

	//���水ť
	void on_toolButtonSetLabel_clicked();
	void on_radioButtonROI_clicked();
	void on_radioButtonBrush_clicked();
	void on_checkBoxClean_clicked();
	void on_toolButtonGrabCut_pressed();
	void on_toolButtonFinish_pressed();
	void on_toolButtonBrushSize_pressed();
	void on_checkBoxLightningMode_clicked();
};
