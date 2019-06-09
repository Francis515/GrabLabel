#include "GrabLabel.h"

GrabLabel::GrabLabel(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.graphicsView->resetTransform();
	ui.graphicsView->setScene(scene);
	ui.spinBoxBrush->setValue(5);
	//设置按钮不可被按下
	buttonsOff();

	//连接菜单动作函数和菜单消息
	connect(ui.actionOpenImg, &QAction::triggered, this, &GrabLabel::OpenImgAction);
	connect(ui.actionCloseImg, &QAction::triggered, this, &GrabLabel::CloseImgAction);
	connect(ui.actionLoadLabel, &QAction::triggered, this, &GrabLabel::LoadLabelAction);
	connect(ui.actionCloseLabel, &QAction::triggered, this, &GrabLabel::CloseLabelAction);
	connect(ui.actionSaveAsGray, &QAction::triggered, this, &GrabLabel::SaveAsGrayAction);
	connect(ui.actionSaveAsRGB, &QAction::triggered, this, &GrabLabel::SaveAsRGBAction);
	connect(ui.actionHelp, &QAction::triggered, this, &GrabLabel::HelpAction);
	connect(ui.actionContact, &QAction::triggered, this, &GrabLabel::ContactAction);
}
void GrabLabel::buttonsOff()
{
	//设置按钮不可被按下
	ui.radioButtonBrush->setCheckable(false);
	ui.radioButtonROI->setCheckable(false);
	ui.checkBoxClean->setCheckable(false);

	ui.toolButtonGrabCut->blockSignals(true);
	ui.toolButtonSetLabel->blockSignals(true);
	ui.toolButtonFinish->blockSignals(true);
}
//-----------------------------动作区------------------------
void GrabLabel::OpenImgAction() {

	//读取图像文件，并加载到scene
	multiLabel.inputImgName = QFileDialog::getOpenFileName(this, "Open Input \
		Image", QDir::currentPath(), "Images(*.jpg *.png *.bmp)");
	if (QFile::exists(multiLabel.inputImgName)) {
		QPixmap orinImg;
		if (orinImg.load(multiLabel.inputImgName)) {
			scene->clear();
			//设置场景边界
			QPointF topLeft(0, 0);
			QPointF bottomRight(orinImg.width(), orinImg.height());
			scene->setBounding(topLeft, bottomRight);
			//设置场景的大小
			//注意，默认情况下Qt是保留所有添加过的item的最大尺寸作为场景尺寸，这会导致故障
			QRectF sceneRect(topLeft, bottomRight);
			scene->setSceneRect(sceneRect);
			scene->addPixmap(orinImg);

			//设置开关
			ui.radioButtonBrush->setCheckable(true);
			ui.radioButtonROI->setCheckable(true);
			ui.checkBoxClean->setCheckable(true);
			ui.toolButtonSetLabel->blockSignals(false);
		}
		
		else {

		}
	}
	
}

void GrabLabel::CloseImgAction() {
	//清空scene
	scene->clear();
	multiLabel.clearImg();
	//清0交互次数
	iteracTimes = 0;
	//设置开关
	buttonsOff();
}

void GrabLabel::LoadLabelAction() {
	//读取txt中的labels，格式为：num name R G B
	multiLabel.inputLabelName = QFileDialog::getOpenFileName(this, "Open Labels",
		QDir::currentPath(), "*.txt");

	//一定先检查文件是否读入，否则后面的while可能为无限循环
	if (QFile::exists(multiLabel.inputLabelName)) {
		string labelfile = multiLabel.inputLabelName.toStdString();
		ifstream labels(labelfile);
		int i = 0, tempNum = 0, tempColor[3];
		string tempName;
		while (!labels.eof()) {
			labels >> tempNum >> tempName >> tempColor[0] >> tempColor[1] >> tempColor[2];

			multiLabel.labelNum.insert(multiLabel.labelNum.end(), tempNum);
			multiLabel.labelColor.insert(multiLabel.labelColor.end(), tempColor[0]);
			multiLabel.labelColor.insert(multiLabel.labelColor.end(), tempColor[1]);
			multiLabel.labelColor.insert(multiLabel.labelColor.end(), tempColor[2]);
			multiLabel.labelName.insert(multiLabel.labelName.end(), tempName);
			i++;
		}

		//在table中显示
		tableModel = new QStandardItemModel();
		ui.tableViewLabel->setModel(tableModel);
		tableModel->setColumnCount(5);
		QStringList headerLabels = { "Num","Name","R","G","B" };
		tableModel->setHorizontalHeaderLabels(headerLabels);
		for (int row = 0; row < i; row++) {
			tableModel->setItem(row, 0, new QStandardItem(QString::number(multiLabel.labelNum[row])));
			tableModel->setItem(row, 1, new QStandardItem(QString::fromStdString(multiLabel.labelName[row])));
			tableModel->setItem(row, 2, new QStandardItem(QString::number(multiLabel.labelColor[3 * row + 0])));
			tableModel->setItem(row, 3, new QStandardItem(QString::number(multiLabel.labelColor[3 * row + 1])));
			tableModel->setItem(row, 4, new QStandardItem(QString::number(multiLabel.labelColor[3 * row + 2])));
			tableModel->item(row, 1)->setForeground(QBrush(QColor(multiLabel.labelColor[3 * row + 0],
				multiLabel.labelColor[3 * row + 1], multiLabel.labelColor[3 * row + 2])));
		}

		//设置开关
		ui.toolButtonSetLabel->blockSignals(false);
	}	
}

void GrabLabel::CloseLabelAction()
{
	ui.lineEditSetLabel->clear();
	tableModel->clear();
	multiLabel.clearLabel();
	delete tableModel;
	
	//设置开关
	buttonsOff();
}
void GrabLabel::SaveAsGrayAction()
{
	QString outputLabelName = QFileDialog::getSaveFileName(this,
		"Select Output Image", QDir::currentPath(),
		"*.jpg;;*.png;;*.bmp");
	if (!outputLabelName.isEmpty()) {
		Mat outputGrayLabel = multiLabel.mergedGrayLabel();
		imwrite(outputLabelName.toStdString(), outputGrayLabel);
		QString notice = "Save label successfully as 1channel gray.";
		QMessageBox::about(this, "Notice", notice);
	}
}

void GrabLabel::SaveAsRGBAction()
{
	QString outputLabelName = QFileDialog::getSaveFileName(this,
		"Select Output Image", QDir::currentPath(),
		"*.jpg;;*.png;;*.bmp");
	if (!outputLabelName.isEmpty()) {
		Mat outputColorLabel = multiLabel.mergedColorLabel();
		//cvtColor(outputColorLabel, outputColorLabel, CV_BGR2RGB);
		imwrite(outputLabelName.toStdString(), outputColorLabel);
		QString notice = "Save label successfully as 3channel RGB.";
		QMessageBox::about(this, "Notice", notice);
	}
}

void GrabLabel::HelpAction()
{
	QString line1 = "To learn how to use GrabLabel, please refer to README.txt\n";
	QString line2 = "README.txt can also be found at https://github.com/Francis515 \n";
	QMessageBox::about(this, "Help", line1+line2);
}
void GrabLabel::ContactAction()
{
	QString notice = "Author's email: yuanyouxu@zju.edu.cn\n";
	QMessageBox::about(this, "Contact", notice);
}

void GrabLabel::closeEvent(QCloseEvent *event)
{
	int result = QMessageBox::warning(this, "Exit",
		"Are you sure to close GrabLabel?",
		QMessageBox::Yes,QMessageBox::No);
	if (result == QMessageBox::Yes) {
		event->accept();
	}
	else {
		event->ignore();
	}
}
//-----------------------按钮区----------------------
void GrabLabel::on_toolButtonSetLabel_clicked()
{
	QString label = ui.lineEditSetLabel->text();
	if (!label.isEmpty() && count(multiLabel.labelNum.begin(),
		multiLabel.labelNum.end(), label.toInt())) {
		multiLabel.currentLabel = label.toInt();//检查是否转化成功

		//每次设置新的label，都清空场景并重新加载图像
		if (QFile::exists(multiLabel.inputImgName)) {
			QPixmap orinImg;
			if (orinImg.load(multiLabel.inputImgName)) {
				scene->clear();
				scene->addPixmap(orinImg);

			}
		}
		//每次要把GCmask清0，否则roi大小变化时会有遗留痕迹
		multiLabel.currentGCMask.setTo(0);
		//清0交互次数
		iteracTimes = 0;

		QString notice = "Set label successfully as: " + label;
		QMessageBox::about(this, "Notice", notice);

		//设置开关
		buttonsOff();
		ui.radioButtonBrush->setCheckable(true);
		ui.radioButtonROI->setCheckable(true);
		ui.checkBoxClean->setCheckable(true);
		ui.toolButtonSetLabel->blockSignals(false);
	}
}
void GrabLabel::on_radioButtonROI_clicked()
{
	if (ui.radioButtonROI->isChecked()) {
		//每次按下按钮就重新开始绘制
		clearType(QGraphicsItem::UserType);
		roi = new ROI(scene->width(), scene->height());
		scene->addItem(roi);
		roi->setROI(true);
		scene->setBrush(false, false);
		if (multiLabel.currentLabel != -1)
			ui.toolButtonGrabCut->blockSignals(false);
	}
	

}
void GrabLabel::on_radioButtonBrush_clicked() {
	if (ui.radioButtonBrush->isChecked()) {
		//clearType(QGraphicsLineItem::Type);
		roi->setROI(false);
		scene->setBrush(true, false);
	}
}
void GrabLabel::on_checkBoxClean_clicked() {
	if (ui.radioButtonBrush->isChecked()) {
		if (ui.checkBoxClean->isChecked())
			scene->setBrush(true, true);
		else
			scene->setBrush(true, false);
	}
}

void GrabLabel::on_toolButtonFinish_pressed()
{

	multiMask tmp;
	tmp.labelNum = multiLabel.currentLabel;
	//这里绝对不能用等号，等号是共享一个图像
	//一定要复制单独的一份出来
	//tmp.mask = multiLabel.currentMask;
	multiLabel.currentMask.copyTo(tmp.mask);
	//标注顺序是先前景后背景，所以后来的应该插在前面而不是后面
	//multiLabel.maskVec.push_back(tmp);
	multiLabel.maskVec.insert(multiLabel.maskVec.begin(), tmp);

	
	QString notice = "The latest cut has been saved.\n Please set label again to begin next one.";
	QMessageBox::about(this, "Notice", notice);
	multiLabel.refresh();

	//设置开关
	buttonsOff();
	ui.toolButtonSetLabel->blockSignals(false);
}

void GrabLabel::on_toolButtonBrushSize_pressed()
{
	int brushSize = ui.spinBoxBrush->value();
	if (brushSize > 0 && brushSize < 50) {
		scene->setBrushSize(brushSize);
		QString notice = "Brush size has been set to "+QString::number(brushSize);
		QMessageBox::about(this, "Notice", notice);
	}
}

void GrabLabel::on_checkBoxLightningMode_clicked()
{
	if (ui.checkBoxLightningMode->isChecked()) {
		cutMode = LIGHTNING_CUT;
	}
	else {
		cutMode = NORMAL_CUT;
	}
}

//-----------------核心部分，grabcut--------------
Mat groupToMask(QGraphicsScene *scene, int type)
{
	QList<QGraphicsItem*> items = scene->items();
	foreach(QGraphicsItem *item, items) {
		if (item->type() != type) {
			item->setOpacity(0);
		}
	}
	QGraphicsItemGroup *group = scene->createItemGroup(items);
	QPixmap map = itemToQPixmap(group);
	//组合成group后必须要销毁，不然会出错
	scene->destroyItemGroup(group);
	Mat mat = cvert::QPixmapToCvMat(map);
	foreach(QGraphicsItem *item, items) {
		if (item->type() != type) {
			item->setOpacity(1);
		}
	}
	Mat mask(mat.size(), CV_8UC1);
	cvtColor(mat, mask, CV_BGR2GRAY);
	threshold(mask, mask, 0.5, 1, THRESH_BINARY);
	return mask;
}

void GrabLabel::on_toolButtonGrabCut_pressed()
{	
	try {
		//读入图像
		Mat cvImg = imread(multiLabel.inputImgName.toStdString());
		//制作ROI矩形，比真正的矩形小一圈
		//Rect cvRect(roi->getX() + 1, roi->getY() + 1,
		//	roi->getWidth() - 2, roi->getHeight() - 2);
		Rect cvRect(int(roi->getX()), int(roi->getY()),
			int(roi->getWidth())+1, int(roi->getHeight())+1);
		
		qDebug() << cvRect.x <<endl;
		qDebug() << cvRect.y << endl;
		qDebug() << cvRect.width << endl;
		qDebug() << cvRect.height << endl;
		//前景与背景的mask ------------检查是否为空
		Mat fgMask = groupToMask(scene, QGraphicsLineItem::Type);
		Mat bgMask = groupToMask(scene, QGraphicsEllipseItem::Type);

		//将roi矩形，前景，背景mask融合
		//如果没有新规定roi，就在原来的基础上添加前景和背景
		//否则需要重新绘制前景和背景
		if (multiLabel.currentGCMask.empty()) {
			multiLabel.currentGCMask = Mat::zeros(cvImg.size(), CV_8UC1);
		}
		
		if (cvRect == multiLabel.currentRect) {
			
			multiLabel.currentGCMask(cvRect).setTo(GC_FGD, fgMask(cvRect));	//确定的前景
			multiLabel.currentGCMask(cvRect).setTo(GC_BGD, bgMask(cvRect));	//确定的背景
		}
		else {
			multiLabel.currentRect = cvRect;
			multiLabel.currentGCMask(cvRect) = GC_PR_FGD; //可能的前景
			multiLabel.currentGCMask(cvRect).setTo(GC_FGD, fgMask(cvRect));	//确定的前景
			multiLabel.currentGCMask(cvRect).setTo(GC_BGD, bgMask(cvRect));	//确定的背景
		}


		//中间变量
		Mat bgdModel, fgdModel;
		//确定迭代次数
		int iterCount = 5;
		//分割
		if (cutMode == NORMAL_CUT) {
			if(iteracTimes==0)
				grabCut(cvImg, multiLabel.currentGCMask, cvRect, bgdModel, fgdModel,
					iterCount, GC_INIT_WITH_MASK);
			else
				grabCut(cvImg, multiLabel.currentGCMask, cvRect, bgdModel, fgdModel,
					iterCount, GC_EVAL);
		}
		else if (cutMode == LIGHTNING_CUT) {
			//闪电模式下GCMask必须包含三种标注，少一种都会报错？？？很迷
			//所有保险起见，第一次分割不使用闪电模式，用普通模式代替
			if(iteracTimes == 0)
				grabCut(cvImg, multiLabel.currentGCMask, cvRect, bgdModel, fgdModel,
					iterCount, GC_INIT_WITH_MASK);
			else 
				grabCut(cvImg(cvRect), multiLabel.currentGCMask(cvRect),
					cvRect, bgdModel, fgdModel,
					iterCount, GC_INIT_WITH_MASK);
		}
		iteracTimes++;
		//myGrabCut(cvImg, cvRect, iterCount);
		//grabCut(cvImg(cvRect), multiLabel.currentGCMask(cvRect), cvRect, bgdModel, fgdModel,
		//	iterCount, GC_INIT_WITH_MASK);


		//结果是可能前景和确定前景的并集
		Mat resultMaskFGD = Mat::zeros(cvImg.size(), CV_8UC1);
		Mat resultMaskPRFGD = Mat::zeros(cvImg.size(), CV_8UC1);
		compare(multiLabel.currentGCMask, GC_FGD, resultMaskFGD, CMP_EQ);
		compare(multiLabel.currentGCMask, GC_PR_FGD, resultMaskPRFGD, CMP_EQ);
		multiLabel.currentMask = resultMaskFGD | resultMaskPRFGD;

		Mat mix = cvImg * 0.5 + multiLabel.currentColorLabel()*0.5;
		QPixmap result = cvert::cvMatToQPixmap(mix);

		clearType(QGraphicsLineItem::Type);
		clearType(QGraphicsEllipseItem::Type);
		scene->addPixmap(result);

		//设置开关
		ui.toolButtonFinish->blockSignals(false);
	}
	
	catch (...) {
		QString notice1 = "(o w o)? GrabCut failed!\n";
		QString notice2 = "Please set your label or ROI and try again.\n";
		QMessageBox::about(this, "Fail", notice1+notice2);
	}
}

void GrabLabel::clearType(int type)
{	
	QList<QGraphicsItem*> items = scene->items();
	foreach(QGraphicsItem *item, items) {
		if (item->type() == type) {
			scene->removeItem(item);
		}
	}
}

QPixmap itemToQPixmap(QGraphicsItem *item)
{
	QRectF r = item->boundingRect();
	QPixmap pixmap(r.width(), r.height());
	//QPixmap pixmap(item->boundingRect().size().toSize());
	pixmap.fill(QColor(0, 0, 0, 0));
	QPainter painter(&pixmap);
	//painter.setBrush(QBrush(QColor(0, 0, 0, 0)));
	painter.drawRect(r);
	item->scene()->render(&painter, QRectF(), item->sceneBoundingRect());
	painter.end();
	return pixmap;
}

/*
//制作掩膜 先前景后背景
	QList<QGraphicsItem*> items = scene->items();

	//前景组合
	foreach(QGraphicsItem *item, items) {
		if(item->type()!=QGraphicsLineItem::Type){
			item->setOpacity(0);
		}
	}
	QGraphicsItemGroup *fgGroup = scene->createItemGroup(items);
	QPixmap fgMap = itemToQPixmap(fgGroup);

	//背景组合
	foreach(QGraphicsItem *item, items) {
		item->setOpacity(1);
	}
	foreach(QGraphicsItem *item, items) {
		if (item->type() != QGraphicsEllipseItem::Type) {
			item->setOpacity(0);
		}
	}
	QGraphicsItemGroup *bgGroup = scene->createItemGroup(items);
	QPixmap bgMap = itemToQPixmap(bgGroup);


	//qpixmap转为mat
	Mat fgMat = cvert::QPixmapToCvMat(fgMap);
	Mat bgMat = cvert::QPixmapToCvMat(bgMap);

	//mat转为灰度图
	cvtColor(fgMat, fgMat, CV_BGR2GRAY);
	cvtColor(bgMat, bgMat, CV_BGR2GRAY);

	//二值化为0和1
	threshold(fgMat, fgMat, 0.5, 1, THRESH_BINARY);
	threshold(bgMat, bgMat, 0.5, 1, THRESH_BINARY);

void GrabLabel::myGrabCut(Mat cvImg, Rect cvRect,int iterCount)
{
	Mat roiImg;
	roiImg = (cvImg(cvRect)).clone();
	Mat roiGCMask; 
	roiGCMask = (multiLabel.currentGCMask(cvRect)).clone();
	Mat bgdModel, fgdModel;

	Rect roiRect(0,0, roiImg.cols,roiImg.rows);
	grabCut(roiImg, roiGCMask, roiRect, bgdModel, fgdModel,
		iterCount, GC_INIT_WITH_MASK);
	multiLabel.currentGCMask(cvRect) = roiGCMask.clone();
}*/