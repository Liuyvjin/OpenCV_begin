/**
 * @brief: 输入图片找球位置
 * @author： liujin
 * @date: 2019/5/11
*/

/**头文件*/
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/**函数声明*/
void identify(Mat &src);
void HoughTrans(Mat& srcImage,vector<Vec3f>& circles);

/**主程序*/
int main() {
    Mat srcImage;
    /// 读入源图片
    srcImage = imread("../pics/ball3.png");
    if (!srcImage.data) {
        printf("读入文件错误！\n");
        return 1;
    }
    printf("按下q或者esc退出程序\n");

    /// 保存找到的圆
    vector<Vec3f>circles;
    /// 霍夫变换，并绘图
    HoughTrans(srcImage,circles);

    waitKey(0);
    return 0;
}

void identify(Mat &src) {


}

/// 输入图，找出图中的圆,并画在srcImage上
void HoughTrans(Mat& srcImage, vector<Vec3f>& circles) {

    Mat grayImage;
    cvtColor(srcImage, grayImage, CV_BGR2GRAY);//转化边缘检测后的图为灰度图

    vector<int> HoughParams = {20, 80, 12, 10, 20};//mindist,canny高阈值,累加器阈值,圆半径最小,最大
    //HoughCircles(InputArray image,OutputArray circles, int method, double dp,
    //             double minDist, double param1=100,double param2=100,
    //             int minRadius=0, int maxRadius=0 )
    //            输入      输出圆                累加器分辨率 mindist canny高阈值 累加器阈值  圆半径最小最大
    HoughCircles(grayImage, circles, CV_HOUGH_GRADIENT, 1, HoughParams.at(0), HoughParams.at(1), \
                 HoughParams.at(2), HoughParams.at(3), HoughParams.at(4));
    //依次在 houghImage 图中绘制出圆
    Mat houghImage;
    srcImage.copyTo(houghImage);
    for (size_t i = 0; i < circles.size(); i++) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1])); //circles的三个参数：x,y,radius
        int radius = cvRound(circles[i][2]);
        //绘制圆心
        circle(houghImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);  //
        //绘制圆轮廓
        circle(houghImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
    }
    //显示效果图
    imshow("霍夫变换", houghImage);
}
