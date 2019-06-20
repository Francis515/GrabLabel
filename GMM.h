#pragma once
#include<opencv2/opencv.hpp>
#include<gcgraph.hpp>
using namespace cv;
// ��˹���ģ����GrabCut
// ʵ�ֹ��̲ο���OpenCVԴ��

// �ⲿ���õĺ���
void mygrabCut(Mat img, Mat& mask, Rect rect,
	Mat& bgdModel, Mat& fgdModel,
	int iterCount, int mode);

// ��ͼ�Ĳ����ṹ��
typedef struct {
	// �ߵ�Ȩ��
	Mat leftW;
	Mat upleftW;
	Mat upW;
	Mat uprightW;
	// ��������ϵ��
	double beta = 0;
	const double gamma = 50;
	const double lambda = 9 * gamma;
} graphParams;

// ��˹���ģ����
class GMM5170
{
public:
	GMM5170(Mat& model);
	static const int componentsNum = 5;
	static const int modelSize = 13;
	// ���ط���
	double belongToGMM(const Vec3d color) const;
	double belongToComponent(int ci, const Vec3d color) const;
	int maxProbComponent(const Vec3d color) const;
	// ����ѧϰ
	void initParams();
	void addSample(int ci, const Vec3d color);
	void calcuParams();

private:
	Mat model;
	// ģ�Ͳ���
	double* coefs; //1
	double* means; //3
	double* covs; //9
	double inverseCovs[componentsNum][3][3];
	double covDets[componentsNum];
	void calcInverseCovAndDet(int ci, double singularFix);
	// ��������
	double channelSums[componentsNum][3];
	double prods[componentsNum][3][3];
	int sampleNums[componentsNum];
	int totalSampleNum;
};

