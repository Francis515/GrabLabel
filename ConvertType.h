#pragma once

//-----------------��ԭ������--------------
//ConvertType.h�ļ��е����ݷǱ���ԭ������������������
//https://blog.csdn.net/qq_17550379/article/details/78683153
#include <QDebug>
#include <QImage>
#include <QPixmap>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"

namespace cvert
{
	// ��Matת��λQImage
	inline QImage  cvMatToQImage(const cv::Mat &inMat)
	{
		switch (inMat.type())
		{
			// 8-bit, 4 channel
		case CV_8UC4:
		{
			QImage image(inMat.data,
				inMat.cols, inMat.rows,
				static_cast<int>(inMat.step),
				QImage::Format_ARGB32);

			return image;
		}

		// 8-bit, 3 channel
		case CV_8UC3:
		{
			QImage image(inMat.data,
				inMat.cols, inMat.rows,
				static_cast<int>(inMat.step),
				QImage::Format_RGB888);

			return image.rgbSwapped();
		}

		// 8-bit, 1 channel
		case CV_8UC1:
		{
			QImage image(inMat.data,
				inMat.cols, inMat.rows,
				static_cast<int>(inMat.step),
				QImage::Format_Grayscale8);

			return image;
		}

		default:
			qWarning() << "CVS::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
			break;
		}

		return QImage();
	}

	//��Matת��ΪQPixmap
	inline QPixmap cvMatToQPixmap(const cv::Mat &inMat)
	{
		return QPixmap::fromImage(cvMatToQImage(inMat));
	}
	//��QImageת��ΪMat
	inline cv::Mat QImageToCvMat(const QImage &inImage, bool inCloneImageData = true)
	{
		switch (inImage.format())
		{
			// 8-bit, 4 channel
		case QImage::Format_ARGB32:
		case QImage::Format_ARGB32_Premultiplied:
		{
			cv::Mat  mat(inImage.height(), inImage.width(),
				CV_8UC4,
				const_cast<uchar*>(inImage.bits()),
				static_cast<size_t>(inImage.bytesPerLine())
			);

			return (inCloneImageData ? mat.clone() : mat);
		}

		// 8-bit, 3 channel
		case QImage::Format_RGB32:
		case QImage::Format_RGB888:
		{
			if (!inCloneImageData)
			{
				qWarning() << "CVS::QImageToCvMat() - Conversion requires cloning because we use a temporary QImage";
			}

			QImage   swapped = inImage;

			if (inImage.format() == QImage::Format_RGB32)
			{
				swapped = swapped.convertToFormat(QImage::Format_RGB888);
			}

			swapped = swapped.rgbSwapped();

			return cv::Mat(swapped.height(), swapped.width(),
				CV_8UC3,
				const_cast<uchar*>(swapped.bits()),
				static_cast<size_t>(swapped.bytesPerLine())
			).clone();
		}

		// 8-bit, 1 channel
		case QImage::Format_Indexed8:
		{
			cv::Mat  mat(inImage.height(), inImage.width(),
				CV_8UC1,
				const_cast<uchar*>(inImage.bits()),
				static_cast<size_t>(inImage.bytesPerLine())
			);

			return (inCloneImageData ? mat.clone() : mat);
		}

		default:
			qWarning() << "CVS::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
			break;
		}

		return cv::Mat();
	}

	//��QPixmapת��ΪMat
	inline cv::Mat QPixmapToCvMat(const QPixmap &inPixmap, bool inCloneImageData = true)
	{
		return QImageToCvMat(inPixmap.toImage(), inCloneImageData);
	}
}

