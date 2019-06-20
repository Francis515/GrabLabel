#pragma once
#include<opencv2/opencv.hpp>
#include<gcgraph.hpp>
using namespace cv;
// 高斯混合模型与GrabCut
// 实现过程参考了OpenCV源码

// 外部调用的函数
void mygrabCut(Mat img, Mat& mask, Rect rect,
	Mat& bgdModel, Mat& fgdModel,
	int iterCount, int mode);

// 建图的参数结构体
typedef struct {
	// 边的权重
	Mat leftW;
	Mat upleftW;
	Mat upW;
	Mat uprightW;
	// 能量函数系数
	double beta = 0;
	const double gamma = 50;
	const double lambda = 9 * gamma;
} graphParams;

// 高斯混合模型类
class GMM5170
{
public:
	GMM5170(Mat& model);
	static const int componentsNum = 5;
	static const int modelSize = 13;
	// 像素分类
	double belongToGMM(const Vec3d color) const;
	double belongToComponent(int ci, const Vec3d color) const;
	int maxProbComponent(const Vec3d color) const;
	// 参数学习
	void initParams();
	void addSample(int ci, const Vec3d color);
	void calcuParams();

private:
	Mat model;
	// 模型参数
	double* coefs; //1
	double* means; //3
	double* covs; //9
	double inverseCovs[componentsNum][3][3];
	double covDets[componentsNum];
	void calcInverseCovAndDet(int ci, double singularFix);
	// 辅助参数
	double channelSums[componentsNum][3];
	double prods[componentsNum][3][3];
	int sampleNums[componentsNum];
	int totalSampleNum;
};

