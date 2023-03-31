#pragma once
#include <codecvt>
#include <fstream>
#include <opencv2/opencv.hpp>


struct Detection
{
    cv::Rect box;
    float conf;
    int classId;
};


class LabelAndColor
{
public:
	LabelAndColor(int Name, cv::Scalar Color) {
		class_id = Name;
		color = Color;
	};
	int class_id;
	cv::Scalar color;

};


class Labels {
public:
	std::vector<LabelAndColor> classmap{
		LabelAndColor(0, cv::Scalar(0, 255, 255)),
	};
};



namespace util
{
    const Labels LabelMap;
    size_t vectorProduct(const std::vector<int64_t>& vector);
    std::wstring charToWstring(const char* str);
    std::vector<std::string> loadNames(const std::string& path);
    void visualizeDetection(cv::Mat& image, std::vector<Detection>& detections,
                            const std::vector<std::string>& classNames);

    void letterbox(const cv::Mat& image, cv::Mat& outImage,
                   const cv::Size& newShape,
                   const cv::Scalar& color,
                   bool auto_,
                   bool scaleFill,
                   bool scaleUp,
                   int stride);

    void scaleCoords(const cv::Size& imageShape, cv::Rect& box, const cv::Size& imageOriginalShape);
    template <typename T>
    T clip(const T& n, const T& lower, const T& upper);
}
