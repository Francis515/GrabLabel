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
	Mat mask; //������1��0
} multiMask;

//�������ݣ�û��Ҫ�ϸ��װ
class MultiLabel
{
public:
	MultiLabel();
	~MultiLabel();
	//�����ͼ��
	QString inputImgName;

	//�ָ������Ĥ
	//GCMask���԰���0-3��ֵ
	//Mask������0��1����GCMask��1��3��λ��
	Mat currentGCMask;
	Mat currentMask;
	Rect currentRect;

	//���ںϳɽ���ķ���
	vector<multiMask> maskVec;
	Mat currentGrayLabel();
	Mat currentColorLabel();
	Mat mergedColorLabel();
	Mat mergedGrayLabel();

	//ÿ�����һ����עҪ�������
	void refresh();
	//�ر�ͼ����ǩ�����
	void clearImg();
	void clearLabel();
	
	//����LABEL����Ϣ
	QString inputLabelName;
	int currentLabel=-1;
	vector<int> labelNum;
	vector<int> labelColor;
	vector<string> labelName;
private:
	
	
};

