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
			//opencv����BGR������Ҫ����һ��
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
	//�Ƚ����Ҷȱ�ǩͼ��Ȼ��������ǩɫ����������ɫ
	Mat currentGray = currentGrayLabel();
	Mat currentColor = Mat::zeros(currentGray.size(), CV_8UC3);
	for (int i = 0; i < currentColor.rows; i++) {
		for (int j = 0; j < currentColor.cols; j++) {
			int label = currentGray.at<uchar>(i, j);
			int index = find(labelNum.begin(), labelNum.end(), label)
				- labelNum.begin();
			//opencv����BGR������Ҫ����һ��
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
	//ɾȥͼ������֣���ʾ����û��ͼ��
	inputImgName.clear();
	//�´�ͼƬ������Ҫ�ͷţ����ܽ���Ϊ0����Ϊ�ߴ緢���˱仯
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
