
//-----------------------------------【头文件包含部分】---------------------------------------
//		描述：包含程序所依赖的头文件
//---------------------------------------------------------------------------------------------- 
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//-----------------------------------【命名空间声明部分】---------------------------------------
//		描述：包含程序所使用的命名空间
//----------------------------------------------------------------------------------------------- 
using namespace cv;

//-----------------------------------【main( )函数】--------------------------------------------
//		描述：控制台应用程序的入口函数，我们的程序从这里开始
//-----------------------------------------------------------------------------------------------
int main() {
    //载入原始图
    Mat srcImage = imread("../../pictures/zhupi.png");
    if(!srcImage.data){printf("读入图像错误！\n");return false;}

    Mat tmpImage, dstImage1, dstImage2;//临时变量和目标图的定义
    tmpImage = srcImage;//将原始图赋给临时变量

    //显示原始图
    imshow("【原始图】", srcImage);

    //进行尺寸调整操作
    resize(tmpImage, dstImage1, Size(tmpImage.cols / 1.5, tmpImage.rows / 1.5), 0, 0);
    resize(tmpImage, dstImage2, Size(tmpImage.cols * 1.5, tmpImage.rows * 1.5), 0, 0);

    //显示效果图
    imshow("【效果图】之一", dstImage1);
    imshow("【效果图】之二", dstImage2);

    waitKey(0);
    return 0;
}