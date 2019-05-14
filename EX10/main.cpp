/**
 * @brief: 漫水填充算法
 * @author： liujin
 * @date: 2019/5/11
*/

/**头文件*/
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/**全局变量*/
Mat srcImage, grayImage, houghImage;
//各种参数
vector<int> HoughParams = {20, 80, 12, 10, 20};//mindist,canny高阈值,累加器阈值,圆半径最小,最大

/**函数声明*/


/**主程序*/
int main() {
    /// 读入源图片
    srcImage = imread("../../pictures/zhupi.png");
    if (!srcImage.data) {
        printf("读入文件错误！\n");
        return 1;
    }
    printf("按下q或者esc退出程序,by 刘琎\n");
    imshow("原始图",srcImage);

    Rect ccomp;
    floodFill(srcImage, Point(400,50), Scalar(155, 255,55), &ccomp, Scalar(30, 30, 30),Scalar(30, 30, 30),FLOODFILL_FIXED_RANGE);

    imshow("最小输出矩形",srcImage(ccomp));
    imshow("效果图",srcImage);
    //cout<<format(roi,4)<<endl;

    /// 检测按键q或esc退出
    while (true) {
        int c = waitKey(0);
        //按下键盘按键Q或者ESC，程序退出
        if ((char) c == 'q' || (char) c == 27)
            break;
    }

    return 0;
}

