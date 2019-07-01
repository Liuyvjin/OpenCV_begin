#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define g_thresh 100  // 阈值
#define g_Maxval 255  // 输出最大值

static void ImageRectification(cv::Mat &image_original)
{
    cv::Mat &&image = image_original.clone();  // 右值引用

    cv::Mat image_gray;
    cv::cvtColor(image, image_gray,CV_BGR2GRAY);
    /// 转为二值图
    Canny( image_gray, image_gray, 220, 200,3 );
    //cv::threshold(image_gray, image_gray, g_thresh, g_Maxval, cv::THRESH_BINARY);
    imshow("边缘检测image_gray", image_gray);


    std::vector< std::vector<cv::Point> > contours_list;
    std::vector<cv::Vec4i> hierarchy;
    ///找轮廓函数需要二值图
    cv::findContours(image_gray, contours_list, hierarchy,
                     CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); // 只取最外面的轮廓,保留轮廓的所有点

/// 对于每个轮廓
    for (uint32_t index = 0; index < contours_list.size(); ++index) {
        /// RotatedRect 是一个旋转矩形：
        //      Point2f center;矩形的质心
        //      Size2f size;   矩形的边长
        //      float angle; 角度，单位度
        // boundingRect()得到包覆此轮廓的最小正矩形，minAreaRect()得到包覆轮廓的最小斜矩形。
        cv::RotatedRect &&rect = cv::minAreaRect(contours_list[index]); // 旋转矩形

        // 如果面积够大
        if (rect.size.area() > 1000) {
//            if (rect.angle != 0.) {
//                // 此处可通过cv::warpAffine进行旋转矫正，本例不需要
//            } //if

            cv::Mat &mask = image_gray;
            cout<<index<<endl;
            ///drawContours绘制轮廓 ；mask 要绘制轮廓的图像,Scalar是颜色
            cv::drawContours(mask, contours_list, static_cast<int>(index), cv::Scalar(255), CV_FILLED);

            /// 显示画了轮廓的二值图
            cv::Mat extracted(image_gray.rows, image_gray.cols, CV_8UC1, cv::Scalar(0)); // 初始化一个空图
            image.copyTo(extracted, mask); // 把mask拷贝到extracted中
//            CV_SHOW(extracted);
            imshow("画轮廓", extracted);


            std::vector<cv::Point2f> poly; // 保存四个角点集
            /// 多边形逼近，可以得到四个角点
            cv::approxPolyDP(contours_list[index], poly, 30, true); // 多边形逼近，精度(即最小边长)设为30是为了得到4个角点
            cv::Point2f pts_src[] = { // 此处顺序调整是为了和后面配对，仅作为示例
                    poly[1],
                    poly[0],
                    poly[3],
                    poly[2]
            };
            //得到包含旋转矩形最小端正矩形
            cv::Rect &&r = rect.boundingRect(); // 注意坐标可能超出图像范围
            // 端正矩形的四个角点
            cv::Point2f pts_dst[] = {
                    cv::Point(r.x, r.y),
                    cv::Point(r.x + r.width, r.y),
                    cv::Point(r.x + r.width, r.y + r.height) ,
                    cv::Point(r.x, r.y + r.height)
            };
            // 获得变换矩阵，从dst到src
            cv::Mat &&Matrix = cv::getPerspectiveTransform(pts_dst, pts_src); // 我这里交换了输入，因为后面指定了cv::WARP_INVERSE_MAP，你可以试试不交换的效果是什么

            cv::Mat warp;
            cv::warpPerspective(image, warp, Matrix, image.size(), cv::INTER_LINEAR + cv::WARP_INVERSE_MAP, cv::BORDER_REPLICATE);
//            CV_SHOW(warp);
            imshow("【效果图】", warp);
        } //if
    }
}
int main( )
{
    //【1】载入原始图和Mat变量定义
    Mat srcImage = imread("../pics/table1.jpg");
    imshow("原图", srcImage);
    ImageRectification(srcImage);


    waitKey(0);

    return 0;
}