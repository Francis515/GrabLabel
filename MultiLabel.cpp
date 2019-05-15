#include "MultiLabel.h"



MultiLabel::MultiLabel()
{

}


MultiLabel::~MultiLabel()
{
}

Mat MultiLabel::mergedGrayLabel()
{
	Mat mergedGray = Mat::zeros(currentGCMask.size(),CV_8UC1);
	vector<multiMask>::iterator iter = maskVec.begin();
	for (; iter != maskVec.end(); ++iter) {
		mergedGray.setTo((*iter).labelNum, (*iter).mask);
	}
	
	return mergedGray;
}

Mat MultiLabel::mergedColorLabel() 
{
	Mat mergedGray = mergedGrayLabel();
	Mat mergedColor = Mat::zeros(mergedGray.size(), CV_8UC3);
	for (int i = 0; i < mergedColor.rows; i++) {
		for (int j = 0; j < mergedColor.cols; j++) {
			int label = mergedGray.at<uchar>(i, j);
			int index = find(labelNum.begin(), labelNum.end(), label)
				-labelNum.begin();
			//opencv里是BGR，所以要交换一下
			mergedColor.at<Vec3b>(i, j)[0] = labelColor[3 * index + 2];
			mergedColor.at<Vec3b>(i, j)[1] = labelColor[3 * index + 1];
			mergedColor.at<Vec3b>(i, j)[2] = labelColor[3 * index + 0];

		}
	}
	return mergedColor;
}
Mat MultiLabel::currentGrayLabel()
{
	Mat currentGray = Mat::zeros(currentGCMask.size(), CV_8UC1);
	currentGray.setTo(currentLabel, currentMask);
	return currentGray;
}
Mat MultiLabel::currentColorLabel()
{
	//先建立灰度标签图，然后依靠标签色表逐像素上色
	Mat currentGray = currentGrayLabel();
	Mat currentColor = Mat::zeros(currentGray.size(), CV_8UC3);
	for (int i = 0; i < currentColor.rows; i++) {
		for (int j = 0; j < currentColor.cols; j++) {
			int label = currentGray.at<uchar>(i, j);
			int index = find(labelNum.begin(), labelNum.end(), label)
				- labelNum.begin();
			//opencv里是BGR，所以要交换一下
			currentColor.at<Vec3b>(i, j)[0] = labelColor[3 * index + 2];
			currentColor.at<Vec3b>(i, j)[1] = labelColor[3 * index + 1];
			currentColor.at<Vec3b>(i, j)[2] = labelColor[3 * index + 0];

		}
	}
	return currentColor;
}

void MultiLabel::refresh()
{
	//currentGCMask = 0;
	//currentMask = 0;
	currentGCMask.setTo(0);
	currentMask.setTo(0);
}

void MultiLabel::clearImg()
{
	//删去图像的名字，表示现在没有图像
	inputImgName.clear();
	//新打开图片，必须要释放，不能仅置为0，因为尺寸发生了变化
	currentGCMask.release();
	currentMask.release();
	maskVec.clear();
}
void MultiLabel::clearLabel()
{
	inputLabelName.clear();
	currentLabel = -1;
	labelName.clear();
	labelNum.clear();
	labelColor.clear();
}
