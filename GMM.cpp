#include "GMM.h"

GMM5170::GMM5170(Mat& model)
{
	if (model.empty())
	{
		model.create(1, modelSize*componentsNum, CV_64FC1);
		model.setTo(Scalar(0));
	}
	
	this->model = model;

	//GMM��ÿ�����صĸ�˹ģ�͵�
	//Ȩֵ����ֵ��Э���������ʼ�洢ָ��
	coefs = model.ptr<double>(0);
	means = coefs + componentsNum;
	covs = means + 3 * componentsNum;

	for (int ci = 0; ci < componentsNum; ci++)
		if (coefs[ci] > 0)
			calcInverseCovAndDet(ci, 0.0);
	totalSampleNum = 0;
}

// ����һ���������ڵ�ci����˹ģ�͵ĸ���
double GMM5170::belongToComponent(int ci, const Vec3d color) const
{
	double res = 0;
	if (coefs[ci] > 0)
	{
		CV_Assert(covDets[ci] > std::numeric_limits<double>::epsilon());
		Vec3d diff = color;
		double* m = means + 3 * ci;
		diff[0] -= m[0]; diff[1] -= m[1]; diff[2] -= m[2];
		double mult = diff[0] * (diff[0] * inverseCovs[ci][0][0] + diff[1] * inverseCovs[ci][1][0] + diff[2] * inverseCovs[ci][2][0])
			+ diff[1] * (diff[0] * inverseCovs[ci][0][1] + diff[1] * inverseCovs[ci][1][1] + diff[2] * inverseCovs[ci][2][1])
			+ diff[2] * (diff[0] * inverseCovs[ci][0][2] + diff[1] * inverseCovs[ci][1][2] + diff[2] * inverseCovs[ci][2][2]);
		res = 1.0f / sqrt(covDets[ci]) * exp(-0.5f*mult);
	}
	return res;
}

// ��GMM��5��ģ�����ҳ���������һ��
int GMM5170::maxProbComponent(const Vec3d color) const
{
	int k = 0;
	double max = 0;

	for (int ci = 0; ci < componentsNum; ci++)
	{
		double p = belongToComponent(ci, color);
		if (p > max)
		{
			k = ci;
			max = p;
		}
	}
	return k;
}





//  ѧϰ���̳�ʼ��
void GMM5170::initParams()
{
	for (int ci = 0; ci < componentsNum; ci++)
	{
		channelSums[ci][0] = channelSums[ci][1] = channelSums[ci][2] = 0;
		prods[ci][0][0] = prods[ci][0][1] = prods[ci][0][2] = 0;
		prods[ci][1][0] = prods[ci][1][1] = prods[ci][1][2] = 0;
		prods[ci][2][0] = prods[ci][2][1] = prods[ci][2][2] = 0;
		sampleNums[ci] = 0;
	}
	totalSampleNum = 0;
}

//������������ci����˹ģ��
void GMM5170::addSample(int ci, const Vec3d color)
{
	channelSums[ci][0] += color[0]; channelSums[ci][1] += color[1]; channelSums[ci][2] += color[2];
	prods[ci][0][0] += color[0] * color[0]; prods[ci][0][1] += color[0] * color[1]; prods[ci][0][2] += color[0] * color[2];
	prods[ci][1][0] += color[1] * color[0]; prods[ci][1][1] += color[1] * color[1]; prods[ci][1][2] += color[1] * color[2];
	prods[ci][2][0] += color[2] * color[0]; prods[ci][2][1] += color[2] * color[1]; prods[ci][2][2] += color[2] * color[2];
	sampleNums[ci]++;
	totalSampleNum++;
}

// �����˹ģ�Ͳ���
void GMM5170::calcuParams()
{
	for (int ci = 0; ci < componentsNum; ci++)
	{
		// ��ci����˹ģ�͵��������ظ���
		int n = sampleNums[ci];
		if (n == 0)
			coefs[ci] = 0;
		else
		{
			// ����Ȩֵ
			double inv_n = 1.0 / n;
			coefs[ci] = (double)n / totalSampleNum;

			//�����ֵ
			double* m = means + 3 * ci;
			m[0] = channelSums[ci][0] * inv_n; m[1] = channelSums[ci][1] * inv_n; m[2] = channelSums[ci][2] * inv_n;

			// ����Э����
			double* c = covs + 9 * ci;
			c[0] = prods[ci][0][0] * inv_n - m[0] * m[0]; c[1] = prods[ci][0][1] * inv_n - m[0] * m[1]; c[2] = prods[ci][0][2] * inv_n - m[0] * m[2];
			c[3] = prods[ci][1][0] * inv_n - m[1] * m[0]; c[4] = prods[ci][1][1] * inv_n - m[1] * m[1]; c[5] = prods[ci][1][2] * inv_n - m[1] * m[2];
			c[6] = prods[ci][2][0] * inv_n - m[2] * m[0]; c[7] = prods[ci][2][1] * inv_n - m[2] * m[1]; c[8] = prods[ci][2][2] * inv_n - m[2] * m[2];

			calcInverseCovAndDet(ci, 0.01);
		}
	}
}





//����Э�����������ʽ����
void GMM5170::calcInverseCovAndDet(int ci, const double singularFix)
{
	if (coefs[ci] > 0)
	{
		//�����ci����˹ģ��Э������������ʽ
		double *c = covs + 9 * ci;
		double dtrm = c[0] * (c[4] * c[8] - c[5] * c[7]) - c[1] * (c[3] * c[8] - c[5] * c[6]) + c[2] * (c[3] * c[7] - c[4] * c[6]);
		if (dtrm <= 1e-6 && singularFix > 0)
		{
			//�൱���������ʽС�ڵ���0�����Խ���Ԫ�أ����Ӱ�����
			//���ȵ�Э��������޷�����
			c[0] += singularFix;
			c[4] += singularFix;
			c[8] += singularFix;
			dtrm = c[0] * (c[4] * c[8] - c[5] * c[7]) - c[1] * (c[3] * c[8] - c[5] * c[6]) + c[2] * (c[3] * c[7] - c[4] * c[6]);
		}
		covDets[ci] = dtrm;

		//Э�����������
		double inv_dtrm = 1.0 / dtrm;
		inverseCovs[ci][0][0] = (c[4] * c[8] - c[5] * c[7]) * inv_dtrm;
		inverseCovs[ci][1][0] = -(c[3] * c[8] - c[5] * c[6]) * inv_dtrm;
		inverseCovs[ci][2][0] = (c[3] * c[7] - c[4] * c[6]) * inv_dtrm;
		inverseCovs[ci][0][1] = -(c[1] * c[8] - c[2] * c[7]) * inv_dtrm;
		inverseCovs[ci][1][1] = (c[0] * c[8] - c[2] * c[6]) * inv_dtrm;
		inverseCovs[ci][2][1] = -(c[0] * c[7] - c[1] * c[6]) * inv_dtrm;
		inverseCovs[ci][0][2] = (c[1] * c[5] - c[2] * c[4]) * inv_dtrm;
		inverseCovs[ci][1][2] = -(c[0] * c[5] - c[2] * c[3]) * inv_dtrm;
		inverseCovs[ci][2][2] = (c[0] * c[4] - c[1] * c[3]) * inv_dtrm;
	}
}


// -----------------�ڲ���̬����--------------------
// ����beta
//�����ĸ��������������صĲ��
static double calcBeta(const Mat& img)
{
	double beta = 0;
	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			//ȷ����ͼ��߽�ʱ����Խ��
			Vec3d color = img.at<Vec3b>(y, x);
			if (x > 0) // left
			{
				Vec3d diff = color - (Vec3d)img.at<Vec3b>(y, x - 1);
				beta += diff.dot(diff);
			}
			if (y > 0 && x > 0) // upleft
			{
				Vec3d diff = color - (Vec3d)img.at<Vec3b>(y - 1, x - 1);
				beta += diff.dot(diff);
			}
			if (y > 0) // up
			{
				Vec3d diff = color - (Vec3d)img.at<Vec3b>(y - 1, x);
				beta += diff.dot(diff);
			}
			if (y > 0 && x < img.cols - 1) // upright
			{
				Vec3d diff = color - (Vec3d)img.at<Vec3b>(y - 1, x + 1);
				beta += diff.dot(diff);
			}
		}
	}
	if (beta <= std::numeric_limits<double>::epsilon())
		beta = 0;
	else
		beta = 1.f / (2 * beta / (4 * img.cols*img.rows - 3 * img.cols - 3 * img.rows + 2));

	return beta;
}


// ����ͼÿ���Ƕ˵㶥�������򶥵�ıߵ�Ȩֵ
static void calcNWeights(const Mat& img, graphParams &gps)
{
	const double gammaDivSqrt2 = gps.gamma / std::sqrt(2.0f);
	gps.leftW.create(img.rows, img.cols, CV_64FC1);
	gps.upleftW.create(img.rows, img.cols, CV_64FC1);
	gps.upW.create(img.rows, img.cols, CV_64FC1);
	gps.uprightW.create(img.rows, img.cols, CV_64FC1);
	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			Vec3d color = img.at<Vec3b>(y, x);
			if (x - 1 >= 0) // left
			{
				Vec3d diff = color - (Vec3d)img.at<Vec3b>(y, x - 1);
				gps.leftW.at<double>(y, x) = gps.gamma * exp(-gps.beta * diff.dot(diff));
			}
			else
				gps.leftW.at<double>(y, x) = 0;
			if (x - 1 >= 0 && y - 1 >= 0) // upleft
			{
				Vec3d diff = color - (Vec3d)img.at<Vec3b>(y - 1, x - 1);
				gps.upleftW.at<double>(y, x) = gammaDivSqrt2 * exp(-gps.beta * diff.dot(diff));
			}
			else
				gps.upleftW.at<double>(y, x) = 0;
			if (y - 1 >= 0) // up
			{
				Vec3d diff = color - (Vec3d)img.at<Vec3b>(y - 1, x);
				gps.upW.at<double>(y, x) = gps.gamma * exp(-gps.beta * diff.dot(diff));
			}
			else
				gps.upW.at<double>(y, x) = 0;
			if (x + 1 < img.cols && y - 1 >= 0) // upright
			{
				Vec3d diff = color - (Vec3d)img.at<Vec3b>(y - 1, x + 1);
				gps.uprightW.at<double>(y, x) = gammaDivSqrt2 * exp(-gps.beta * diff.dot(diff));
			}
			else
				gps.uprightW.at<double>(y, x) = 0;
		}
	}
}

// �����Ĥ
static int checkMask(const Mat& img, const Mat& mask)
{
	if (mask.empty() || mask.type() != CV_8UC1)
		return 0;
	if (mask.cols != img.cols || mask.rows != img.rows)
		resize(mask, img, img.size());

	//��Ĥ����ֻ�ܰ���GC_BGD,GC_FGD,GC_PR_BGD,GC_PR_FGD����ֵ
	for (int y = 0; y < mask.rows; y++)
	{
		for (int x = 0; x < mask.cols; x++)
		{
			uchar val = mask.at<uchar>(y, x);
			if (val != GC_BGD && val != GC_FGD && val != GC_PR_BGD && val != GC_PR_FGD)
				return 0;
		}
	}
	return 1;
}



// GMM��ʼ����ʹ��Kmeas���η���
static void initGMMs(const Mat& img, const Mat& mask, GMM5170& bgdGMM, GMM5170& fgdGMM)
{
	const int kMeansItCount = 10;
	const int kMeansType = KMEANS_PP_CENTERS;

	//��¼������ǰ����������������ÿ�����ض�Ӧ��GMM
	Mat bgdLabels, fgdLabels;
	std::vector<Vec3f> bgdSamples, fgdSamples;
	Point p;
	for (p.y = 0; p.y < img.rows; p.y++)
	{
		for (p.x = 0; p.x < img.cols; p.x++)
		{
			if (mask.at<uchar>(p) == GC_BGD || mask.at<uchar>(p) == GC_PR_BGD)
				bgdSamples.push_back((Vec3f)img.at<Vec3b>(p));
			else // GC_FGD | GC_PR_FGD
				fgdSamples.push_back((Vec3f)img.at<Vec3b>(p));
		}
	}

	Mat _bgdSamples((int)bgdSamples.size(), 3, CV_32FC1, &bgdSamples[0][0]);
	kmeans(_bgdSamples, GMM5170::componentsNum, bgdLabels,
		TermCriteria(CV_TERMCRIT_ITER, kMeansItCount, 0.0), 0, kMeansType);
	Mat _fgdSamples((int)fgdSamples.size(), 3, CV_32FC1, &fgdSamples[0][0]);
	kmeans(_fgdSamples, GMM5170::componentsNum, fgdLabels,
		TermCriteria(CV_TERMCRIT_ITER, kMeansItCount, 0.0), 0, kMeansType);

	//���η�������GMM��ÿ����˹ģ�͵Ĳ���
	bgdGMM.initParams();
	for (int i = 0; i < (int)bgdSamples.size(); i++)
		bgdGMM.addSample(bgdLabels.at<int>(i, 0), bgdSamples[i]);
	bgdGMM.calcuParams();

	fgdGMM.initParams();
	for (int i = 0; i < (int)fgdSamples.size(); i++)
		fgdGMM.addSample(fgdLabels.at<int>(i, 0), fgdSamples[i]);
	fgdGMM.calcuParams();
}

// ����ÿ�����������ĸ�˹ģ�ͣ�������compIdx��
static void calcuCompIdx(const Mat& img, const Mat& mask, const GMM5170& bgdGMM, const GMM5170& fgdGMM, Mat& compIdxs)
{
	Point p;
	Vec3d color;
	//���������ڸ�˹ģ�͵ĸ������Ӧ��Ȩֵ��������
	for (p.y = 0; p.y < img.rows; p.y++)
	{
		for (p.x = 0; p.x < img.cols; p.x++)
		{
			color = img.at<Vec3b>(p);
			compIdxs.at<int>(p) = mask.at<uchar>(p) == GC_BGD || mask.at<uchar>(p) == GC_PR_BGD ?
				bgdGMM.maxProbComponent(color) : fgdGMM.maxProbComponent(color);
		}
	}
}

// GMM����ѧϰ
static void learnGMMParams(const Mat& img, const Mat& mask, const Mat& compIdxs, GMM5170& bgdGMM, GMM5170& fgdGMM)
{
	// ��ʼ������
	bgdGMM.initParams();
	fgdGMM.initParams();

	// ��������
	Point p;
	for (int ci = 0; ci < GMM5170::componentsNum; ci++)
	{
		for (p.y = 0; p.y < img.rows; p.y++)
		{
			for (p.x = 0; p.x < img.cols; p.x++)
			{
				if (compIdxs.at<int>(p) == ci)
				{
					if (mask.at<uchar>(p) == GC_BGD || mask.at<uchar>(p) == GC_PR_BGD)
						bgdGMM.addSample(ci, img.at<Vec3b>(p));
					else
						fgdGMM.addSample(ci, img.at<Vec3b>(p));
				}
			}
		}
	}

	// �������
	bgdGMM.calcuParams();
	fgdGMM.calcuParams();
}


//  ����һ����������ĳ��GMM�ĸ���
double GMM5170::belongToGMM(const Vec3d color) const
{
	double res = 0;
	for (int ci = 0; ci < componentsNum; ci++)
		res += coefs[ci] * belongToComponent(ci, color);
	return res;
}



//  ��ͼ
static void buildGraph(const Mat& img, const Mat& mask, const GMM5170& bgdGMM, const GMM5170& fgdGMM, 
	const graphParams& gps, GCGraph<double>& graph)
{
	//������
	int vtxCount = img.cols*img.rows;
	//��������ȥͼ��߽磩
	int	edgeCount = 2 * (4 * img.cols*img.rows - 3 * (img.cols + img.rows) + 2);
	graph.create(vtxCount, edgeCount);
	Point p;
	for (p.y = 0; p.y < img.rows; p.y++)
	{
		for (p.x = 0; p.x < img.cols; p.x++)
		{
			// ��Ӷ���
			int vtxIdx = graph.addVtx();
			Vec3b color = img.at<Vec3b>(p);

			//��ӱ�
			// ���ö˵�Ȩ��
			double fromSource, toSink;
			if (mask.at<uchar>(p) == GC_PR_BGD || mask.at<uchar>(p) == GC_PR_FGD)
			{
				fromSource = -log(bgdGMM.belongToGMM(color));
				toSink = -log(fgdGMM.belongToGMM(color));
			}
			else if (mask.at<uchar>(p) == GC_BGD)
			{
				fromSource = 0;
				toSink = gps.lambda;
			}
			else // GC_FGD
			{
				fromSource = gps.lambda;
				toSink = 0;
			}
			graph.addTermWeights(vtxIdx, fromSource, toSink);

			// ���÷Ƕ˵�Ȩ��
			if (p.x > 0)
			{
				double w = gps.leftW.at<double>(p);
				graph.addEdges(vtxIdx, vtxIdx - 1, w, w);
			}
			if (p.x > 0 && p.y > 0)
			{
				double w = gps.upleftW.at<double>(p);
				graph.addEdges(vtxIdx, vtxIdx - img.cols - 1, w, w);
			}
			if (p.y > 0)
			{
				double w = gps.upW.at<double>(p);
				graph.addEdges(vtxIdx, vtxIdx - img.cols, w, w);
			}
			if (p.x < img.cols - 1 && p.y>0)
			{
				double w = gps.uprightW.at<double>(p);
				graph.addEdges(vtxIdx, vtxIdx - img.cols + 1, w, w);
			}
		}
	}
}

//  �ָ�
static void minCut(GCGraph<double>& graph, Mat& mask)
{
	//�����=��С��
	graph.maxFlow();
	Point p;
	//����mask
	for (p.y = 0; p.y < mask.rows; p.y++)
	{
		for (p.x = 0; p.x < mask.cols; p.x++)
		{
			if (mask.at<uchar>(p) == GC_PR_BGD || mask.at<uchar>(p) == GC_PR_FGD)
			{
				if (graph.inSourceSegment(p.y*mask.cols + p.x))
					mask.at<uchar>(p) = GC_PR_FGD;
				else
					mask.at<uchar>(p) = GC_PR_BGD;
			}
		}
	}
}

//-----------------------------------------------------


// --------------------�ⲿ���õĺ���---------------------
void mygrabCut(Mat img, Mat& mask, Rect rect,
	Mat& bgdModel, Mat& fgdModel,
	int iterCount, int mode)
{
	// ������
	if (img.empty() || mask.empty())
		return;
	if (img.type() != CV_8UC3)
		return;
	if (iterCount <= 0)
		return;
	if (!checkMask(img, mask))
		return;

	// ����GMMģ��
	GMM5170 bgdGMM(bgdModel), fgdGMM(fgdModel);
	Mat compIdxs(img.size(), CV_32SC1);

	// �״ηָ�GC_INIT_WITH_MASK
	// �ֲ��޸�GC_EVAL
	if( mode == GC_INIT_WITH_MASK)
		initGMMs(img, mask, bgdGMM, fgdGMM);

	if (mode == GC_EVAL)
		iterCount = 1;

	// �������
	graphParams gps;
	gps.beta = calcBeta(img);
	calcNWeights(img, gps);

	// �����ָ�
	for (int i = 0; i < iterCount; i++)
	{
		GCGraph<double> graph;
		calcuCompIdx(img, mask, bgdGMM, fgdGMM, compIdxs);
		if (mode != GC_EVAL)
			learnGMMParams(img, mask, compIdxs, bgdGMM, fgdGMM);
		buildGraph(img, mask, bgdGMM, fgdGMM, gps, graph);
		minCut(graph, mask);
	}
}
