#pragma once
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include<QString>
#include<vector>
#include<algorithm>
using namespace cv;
using namespace std;
typedef struct 
{
	int labelNum=0;
	Mat mask; //仅包含1和0
} multiMask;

//整合数据，没必要严格封装
class MultiLabel
{
public:
	MultiLabel();
	~MultiLabel();
	//读入的图像
	QString inputImgName;

	//分割出的掩膜
	//GCMask可以包含0-3的值
	//Mask仅包含0和1，是GCMask中1和3的位置
	Mat currentGCMask;
	Mat currentMask;
	Rect currentRect;

	//用于合成结果的方法
	vector<multiMask> maskVec;
	Mat currentGrayLabel();
	Mat currentColorLabel();
	Mat mergedColorLabel();
	Mat mergedGrayLabel();

	//每次完成一个标注要清空以下
	void refresh();
	//关闭图像或标签后清空
	void clearImg();
	void clearLabel();
	
	//关于LABEL的信息
	QString inputLabelName;
	int currentLabel=-1;
	vector<int> labelNum;
	vector<int> labelColor;
	vector<string> labelName;
private:
	
	
};

