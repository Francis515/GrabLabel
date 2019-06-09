#include "GrabLabel.h"

GrabLabel::GrabLabel(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.graphicsView->resetTransform();
	ui.graphicsView->setScene(scene);
	ui.spinBoxBrush->setValue(5);
	//���ð�ť���ɱ�����
	buttonsOff();

	//���Ӳ˵����������Ͳ˵���Ϣ
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
	//���ð�ť���ɱ�����
	ui.radioButtonBrush->setCheckable(false);
	ui.radioButtonROI->setCheckable(false);
	ui.checkBoxClean->setCheckable(false);

	ui.toolButtonGrabCut->blockSignals(true);
	ui.toolButtonSetLabel->blockSignals(true);
	ui.toolButtonFinish->blockSignals(true);
}
//-----------------------------������------------------------
void GrabLabel::OpenImgAction() {

	//��ȡͼ���ļ��������ص�scene
	multiLabel.inputImgName = QFileDialog::getOpenFileName(this, "Open Input \
		Image", QDir::currentPath(), "Images(*.jpg *.png *.bmp)");
	if (QFile::exists(multiLabel.inputImgName)) {
		QPixmap orinImg;
		if (orinImg.load(multiLabel.inputImgName)) {
			scene->clear();
			//���ó����߽�
			QPointF topLeft(0, 0);
			QPointF bottomRight(orinImg.width(), orinImg.height());
			scene->setBounding(topLeft, bottomRight);
			//���ó����Ĵ�С
			//ע�⣬Ĭ�������Qt�Ǳ���������ӹ���item�����ߴ���Ϊ�����ߴ磬��ᵼ�¹���
			QRectF sceneRect(topLeft, bottomRight);
			scene->setSceneRect(sceneRect);
			scene->addPixmap(orinImg);

			//���ÿ���
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
	//���scene
	scene->clear();
	multiLabel.clearImg();
	//��0��������
	iteracTimes = 0;
	//���ÿ���
	buttonsOff();
}

void GrabLabel::LoadLabelAction() {
	//��ȡtxt�е�labels����ʽΪ��num name R G B
	multiLabel.inputLabelName = QFileDialog::getOpenFileName(this, "Open Labels",
		QDir::currentPath(), "*.txt");

	//һ���ȼ���ļ��Ƿ���룬��������while����Ϊ����ѭ��
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

		//��table����ʾ
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

		//���ÿ���
		ui.toolButtonSetLabel->blockSignals(false);
	}	
}

void GrabLabel::CloseLabelAction()
{
	ui.lineEditSetLabel->clear();
	tableModel->clear();
	multiLabel.clearLabel();
	delete tableModel;
	
	//���ÿ���
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
//-----------------------��ť��----------------------
void GrabLabel::on_toolButtonSetLabel_clicked()
{
	QString label = ui.lineEditSetLabel->text();
	if (!label.isEmpty() && count(multiLabel.labelNum.begin(),
		multiLabel.labelNum.end(), label.toInt())) {
		multiLabel.currentLabel = label.toInt();//����Ƿ�ת���ɹ�

		//ÿ�������µ�label������ճ��������¼���ͼ��
		if (QFile::exists(multiLabel.inputImgName)) {
			QPixmap orinImg;
			if (orinImg.load(multiLabel.inputImgName)) {
				scene->clear();
				scene->addPixmap(orinImg);

			}
		}
		//ÿ��Ҫ��GCmask��0������roi��С�仯ʱ���������ۼ�
		multiLabel.currentGCMask.setTo(0);
		//��0��������
		iteracTimes = 0;

		QString notice = "Set label successfully as: " + label;
		QMessageBox::about(this, "Notice", notice);

		//���ÿ���
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
		//ÿ�ΰ��°�ť�����¿�ʼ����
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
	//������Բ����õȺţ��Ⱥ��ǹ���һ��ͼ��
	//һ��Ҫ���Ƶ�����һ�ݳ���
	//tmp.mask = multiLabel.currentMask;
	multiLabel.currentMask.copyTo(tmp.mask);
	//��ע˳������ǰ���󱳾������Ժ�����Ӧ�ò���ǰ������Ǻ���
	//multiLabel.maskVec.push_back(tmp);
	multiLabel.maskVec.insert(multiLabel.maskVec.begin(), tmp);

	
	QString notice = "The latest cut has been saved.\n Please set label again to begin next one.";
	QMessageBox::about(this, "Notice", notice);
	multiLabel.refresh();

	//���ÿ���
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

//-----------------���Ĳ��֣�grabcut--------------
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
	//��ϳ�group�����Ҫ���٣���Ȼ�����
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
		//����ͼ��
		Mat cvImg = imread(multiLabel.inputImgName.toStdString());
		//����ROI���Σ��������ľ���СһȦ
		//Rect cvRect(roi->getX() + 1, roi->getY() + 1,
		//	roi->getWidth() - 2, roi->getHeight() - 2);
		Rect cvRect(int(roi->getX()), int(roi->getY()),
			int(roi->getWidth())+1, int(roi->getHeight())+1);
		
		qDebug() << cvRect.x <<endl;
		qDebug() << cvRect.y << endl;
		qDebug() << cvRect.width << endl;
		qDebug() << cvRect.height << endl;
		//ǰ���뱳����mask ------------����Ƿ�Ϊ��
		Mat fgMask = groupToMask(scene, QGraphicsLineItem::Type);
		Mat bgMask = groupToMask(scene, QGraphicsEllipseItem::Type);

		//��roi���Σ�ǰ��������mask�ں�
		//���û���¹涨roi������ԭ���Ļ��������ǰ���ͱ���
		//������Ҫ���»���ǰ���ͱ���
		if (multiLabel.currentGCMask.empty()) {
			multiLabel.currentGCMask = Mat::zeros(cvImg.size(), CV_8UC1);
		}
		
		if (cvRect == multiLabel.currentRect) {
			
			multiLabel.currentGCMask(cvRect).setTo(GC_FGD, fgMask(cvRect));	//ȷ����ǰ��
			multiLabel.currentGCMask(cvRect).setTo(GC_BGD, bgMask(cvRect));	//ȷ���ı���
		}
		else {
			multiLabel.currentRect = cvRect;
			multiLabel.currentGCMask(cvRect) = GC_PR_FGD; //���ܵ�ǰ��
			multiLabel.currentGCMask(cvRect).setTo(GC_FGD, fgMask(cvRect));	//ȷ����ǰ��
			multiLabel.currentGCMask(cvRect).setTo(GC_BGD, bgMask(cvRect));	//ȷ���ı���
		}


		//�м����
		Mat bgdModel, fgdModel;
		//ȷ����������
		int iterCount = 5;
		//�ָ�
		if (cutMode == NORMAL_CUT) {
			if(iteracTimes==0)
				grabCut(cvImg, multiLabel.currentGCMask, cvRect, bgdModel, fgdModel,
					iterCount, GC_INIT_WITH_MASK);
			else
				grabCut(cvImg, multiLabel.currentGCMask, cvRect, bgdModel, fgdModel,
					iterCount, GC_EVAL);
		}
		else if (cutMode == LIGHTNING_CUT) {
			//����ģʽ��GCMask����������ֱ�ע����һ�ֶ��ᱨ����������
			//���б����������һ�ηָʹ������ģʽ������ͨģʽ����
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


		//����ǿ���ǰ����ȷ��ǰ���Ĳ���
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

		//���ÿ���
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
//������Ĥ ��ǰ���󱳾�
	QList<QGraphicsItem*> items = scene->items();

	//ǰ�����
	foreach(QGraphicsItem *item, items) {
		if(item->type()!=QGraphicsLineItem::Type){
			item->setOpacity(0);
		}
	}
	QGraphicsItemGroup *fgGroup = scene->createItemGroup(items);
	QPixmap fgMap = itemToQPixmap(fgGroup);

	//�������
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


	//qpixmapתΪmat
	Mat fgMat = cvert::QPixmapToCvMat(fgMap);
	Mat bgMat = cvert::QPixmapToCvMat(bgMap);

	//matתΪ�Ҷ�ͼ
	cvtColor(fgMat, fgMat, CV_BGR2GRAY);
	cvtColor(bgMat, bgMat, CV_BGR2GRAY);

	//��ֵ��Ϊ0��1
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