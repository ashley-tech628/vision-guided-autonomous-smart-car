
#include "headfile.h"

#define CAMERA_H   70
#define CAMERA_W  188
float  BlackThres = 160.0;   //黑白阈值
uint8 kk,bai_flag=0,hei_flag=0,baihei_flag=0,heibai_flag=0,width_heibai=0;
uint8 s1,s2,s3,s4;
uint8 twolines_trend=2;
extern uint16 time_flag;/////////////
uint16 time_flag1;
int Point_last1=95,Point_last2=95,Point_last3=95;
uint8 qvlv_quanju_right=0,qvlv_quanju_left=0,qulv_jinduan_right=0,qulv_jinduan_left=0,qulv_yuandaun_right=0,qulv_yuandaun_left=0;
int qvlv_quanju=0, qulv_jinduan=0,qulv_yuandaun=0;

uint8 center_th[70];
uint8 check_line=36;
float k_center=0;
uint8 times2 = 0;
uint8 cnt3=0;
int8 th_y=0;
uint8 black_blocks = 0;
       uint8 cursor = 0;    //指向栈顶的游标
int n=0;
float trend_of_left = 0;
float trend_of_right = 0;
float  k_left=0;
float  k_right=0;
float parameterB=0, parameterA=0;
uint8 Index_Y = 0;
uint8 Index_Y_last=0,Index_X_last=0;
uint8 Index_X = 0;
uint8 guaidian_leftnum = 0,three_cross=0,three_cross1=0;
float curvity_right=0;
float curvity_left=0;
uint8 r_start=0;
uint8 l_start=0;
uint8 times=0;
uint8 youxie_shizi=0;
uint8 zuoxie_shizi=0;
uint8 findleftdownguai=0;
uint8 findrightdownguai=0;
uint8 findrightupguai = 0;
uint8 findleftupguai = 0;
uint8 xk=0,xj=0;
uint8 guaidian;
/***偏差权重***/
const uint8 Weight[70] =
{
  1, 1, 1, 1,1,  1, 1,1,1,1,             //图像最远端60——70行权重
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,              //图像最远端   0——10行权重
 1, 1, 1, 1, 2, 3, 4, 6, 8,11,              //图像最远端10——20行权重
15,17,18,21,20,19,18,17,16,15,              //图像最远端20——30行权重
13,12,11,10, 9, 8, 7, 6, 5, 4,              //图像最远端30——40行权重
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,              //图像最远端40——50行权重
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,              //图像最远端50——60行权重

};//69
const uint8 Weight_huandao[70] =
{
  1, 1, 1, 1, 1, 1,1, 1, 1, 1,               //图像最远端60——70行权重
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,              //图像最远端   0——10行权重
 1, 1, 1, 1, 2, 3, 4, 6, 8,11,              //图像最远端10——20行权重
15,17,18,21,20,19,18,17,16,15,              //图像最远端20——30行权重
13,12,11,10, 9, 8, 7, 6, 5, 4,              //图像最远端30——40行权重
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,              //图像最远端40——50行权重
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,              //图像最远端50——60行权重

};//69
const uint8 Weight_huihuan[70] =
{
        1, 1, 1,1,  1,1, 1,               //图像最远端60——70行权重
       1, 1, 1, 1,1,1,1, 1, 1, 1, 1, 1, 1,              //图像最远端   0——10行权重
       1, 1, 1, 1, 2, 3, 4, 6, 8,11,              //图像最远端10——20行权重
      15,17,18,21,20,19,18,17,16,15,              //图像最远端20——30行权重
      13,12,11,10, 9, 8, 7, 6, 5, 4,              //图像最远端30——40行权重
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1,              //图像最远端40——50行权重
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1,              //图像最远端50——60行权重

};//69
uint8 huihuan_num=0;
//const uint8 Weight_huihuan_flag[70]=
//{
//        01,01,01,01,01,01,01,01,01,01,
//        1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
//        1,1,1,1, 1,1,1,1,1,1,
//        1,1,1,1,1,1,1,1,1,1,
//        2,3,4,6,8,11,15,17,18,21,
//        20,19,18,17,16,15,13,12,11,10,
//        9,8,7,6,5,4,
//
//
//};


uint8 weight_jubu[70]={0};

const uint8 Weight_park[70] =
{
2,3,4,6,8,11,15,17,18,21,
20,19,18,17,16,15,13,12,11,10,
0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,
0,0
};//69
int j_flag=0;

int8 huihuan_left=0;
int8 huihuan_right=0;
uint8 bai_flag2=0,hei_flag2=0,baihei_flag2=0,heibai_flag2=0;
uint8 stop_you=0,stop_zuo=0;
int32 Sum = 0, Weight_Count = 0;
int stop_num1=0,stop_num2=0;
uint8 park_flag=0;//停车标志
uint8 Foresight_Left=0, Foresight_Right=186;
int Point_Mid=0,Point=0,Foresight=0;
uint8 image_use[70][188];
uint8 whitenum=0;
//

uint8  const Half_width[70]=
{
        00,00,00,00,00,00,00,00,00,15,
        16,16,17,46,47,48,49,50,51,52,
        54,55,55,55,56,56,57,57,58,58,
        59,59,60,60,62,62,63,64,65,65,
        66,66,67,67,68,68,69,70,70,70,
        70,71,71,71,72,72,72,73,73,73,
        74,74,74,75,75,76,76,77,77,78
};

//uint8  const Half_width[70]=  //time_flag
//{
//        00,00,00,00,00,00,00,00,00,10,
//        11,11,12,41,42,43,44,45,46,47,
//        49,50,50,50,51,51,52,52,53,53,
//        54,54,55,55,57,57,58,59,60,60,
//        61,61,62,62,63,63,64,65,65,65,
//        65,66,66,66,67,67,67,68,68,68,
//        69,69,69,70,70,71,71,72,72,73
//};

//uint8  const Half_width[70]=  //time_flag
//{
//        00,00,00,00,00,00,00,00,00,7,
//        8,8,9,38,39,40,41,42,43,44,
//        47,48,49,50,51,52,52,3,39,40,
//        41,42,43,44,45,46,47,48,49,50,
//        51,52,53,54,55,56,57,58,59,60,
//        61,62,63,64,65,66,67,68,68,69,
//        69,70,70,71,72,73,74,74,75,76
//};

uint8  const Half_width_yuanshi[70]=
{
00,00,00,00,00,00,00,00,00,10,
11,11,12,14,15,16,17,18,19,20,
28,28,29,29,30,31,31,32,32,33,
34,35,35,36,37,38,39,40,41,41,
42,42,43,43,44,44,45,45,45,46,
46,46,47,48,49,50,52,53,53,54,
55,56,57,57,58,59,60,61,62,63
};
//uint8  const Half_width[70]=
//{
//00,00,00,00,00,00,00,00,00,10,
//11,11,12,14,15,16,17,18,19,20,
//21,22,23,24,25,25,26,37,43,43,
//44,45,45,46,47,47,48,49,50,50,
//51,52,53,54,55,55,56,57,58,59,
//60,61,62,64,64,65,67,68,68,69,
//70,73,73,73,74,74,75,76,77,78
//};
uint8 c=0;

uint8 star_lineflag=0,star_lineflag2=0;
uint8 y=0;
uint8 left_line[70],right_line[70];//左边界右边界     [0]  is  x,[1]  is  y
uint8 Left_Add2[70], Right_Add2[70];
uint8 Left_Add[70], Right_Add[70],Left_Add_num=0,Right_Add_num=0;
uint8 sousuojieshuhang;//搜索结束行
float Add_Slope=0,Left_Last_Slope=0,Right_Last_Slope=0;

uint8 center[70],Width[70];//中线
uint8 youdiuxianshu=0;//右丢线数
uint8 zuodiuxianshu=0;//左丢线数
uint8 zongdiuxianshu=0;//总丢线数

uint8 white_num_col[188],white_num_col_max=0,white_num_col_line=0,white_num_col_min_line=0,white_num_col_min=69;
 float Up_R_qulv;//当前赛道前半部分曲率半径
 float Down_R_qulv;//当前赛道后半部分曲率半径
uint8  Left_Add_Start=0,Left_Add_End=0;
uint8  Right_Add_Start=0,Right_Add_End=0;
uint8 threshold1=0,threshold1_old=77;
uint8  threshold2=0,threshold2_old=77;


uint8 Thresholds[3]={0};
uint8 xielv_1eft2=80;
uint8 xielv_right2=80;
uint8 xielv=22;

uint8 Width_Min=69;
uint8 Right_y=0,Left_y=0;
uint8 Left_Max, Right_Min,Mid_Count;
uint8 Left_Line_New[70], Right_Line_New[70];//边界补线的坐标
uint8 Left_Line_New2[70], Right_Line_New2[70];//边界补线的坐标
uint8 temp_r=185;

uint8 curvity_point2=0;
uint8 curvity_point1=0;
uint8 flag_shizi=0;
uint8 right_turn_down[2]={69,187};
uint8 left_turn_down[2]={69,0};
uint8 right_turn_up[2]={0,0};
uint8 left_turn_up[2]={0,0};
/*****************大津法参数*********************/
float bin_float[256];     //灰度比例直方图
int size = 70 * 186;
float u = 0;                //全图平均灰度
float w0 = 0;
float u0 = 0;               //前景灰度
uint8 Bin_Array[256];
int i;
float gray_hh = 0;//前景灰度和
float var = 0;//方差
float maxvar = 0;//最大方差
float maxgray = 0;//最大灰度占比
float maxbin = 0;

struct size_point
{
        int x0;
        int y0;
        int x1;
        int y1;
};

//struct size_point ostu_point[3]={
//        {0,0,15,69},
//        {16,0,160,69},
//        {161,0,186,69},
//};
struct size_point ostu_point[3]={
{0,0,40,69},
{41,0,135,69},
{136,0,186,69},
};
/*****************大津法参数end*********************/
void Ostu(void)//大津
{
    int j, k;
    uint8 (*p_image)[188] = &mt9v03x_image[0];
        threshold1= my_adapt_threshold(mt9v03x_image[0],188,70);
    for (k = 0; k < 3; k++)
    {
        maxvar = 0;
        w0 = 0;
        u = 0;
        gray_hh = 0;
        var = 0;
        Thresholds[k] = 0;
        for (i = 0; i < 256; i++)
        { bin_float[i] = 0; }
        for (i = ostu_point[k].y0; i <= ostu_point[k].y1; i++)
        {
                for (j = ostu_point[k].x0; j <= ostu_point[k].x1; j++)
                {
                        ++bin_float[*(*(p_image + i) + j)];
                }
        }
        size = (ostu_point[k].y1 - ostu_point[k].y0 + 1) * (ostu_point[k].x1 - ostu_point[k].x0 + 1);
        for (i = 0; i < 256; i++)
        {
                bin_float[i] = bin_float[i] / size;
                u += i * bin_float[i];
        }
        //创建比例灰度直方图
        for (i = 0; i < 256; i++)
        {
                w0 += bin_float[i];
                gray_hh += i * bin_float[i];             //灰度和
                u0 = gray_hh / w0;
                var = (u0 - u) * (u0 - u) * w0 / (1 - w0);
                if (var > maxvar)
                {
                        maxgray = gray_hh;
                        maxbin = w0;
                        maxvar = var;
                        Thresholds[k] = (uint8)i;

                }
        }
        if (k == 0)
        {
                if (gray_hh > 15 && gray_hh <= 33)
                {
                        if (maxbin < 0.9f)
                        {
                                Thresholds[k] = (uint8)(Thresholds[1] - 3);
                        }
                }
                else if (gray_hh > 41 && gray_hh <= 47)
                {
                        if (maxbin < 0.64f || maxbin > 0.76f)
                        {
                                Thresholds[k] = (uint8)(Thresholds[1] - 3);
                        }
                }
                else if (gray_hh > 50 && gray_hh <= 60)
                {
                        if (maxbin < 0.42f || maxbin > 0.58f)
                        {
                                Thresholds[k] = (uint8)(Thresholds[1] - 3);
                        }
                }
                                                                 if (abs(threshold1 - Thresholds[k]) >= 30)//相差太大直接用标准值
                                                                                                {
                                                                                                    Thresholds[k] = threshold1;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    Thresholds[k] = (uint8)(Thresholds[k] + 0.5f * (threshold1 - Thresholds[k]));//这里是取了平均，可以通过调整占比适应不同的光照条件
                                                                                                }
                //SetText("右边var:" + maxvar + " 阈值:" + Thresholds[k] + " 比例:" + maxbin + " 灰度和" + gray_hh);
        }
        else if (k == 1)
        {
                if(gray_hh > 69 && gray_hh < 80)
                {
                        if (maxbin > 0.15f)
                        {
                                Thresholds[k] = (uint8)(Thresholds[0] + 3);



                                                                                                }
                }
                                                                 if (abs(threshold1 - Thresholds[k]) >= 30)//相差太大直接用标准值
                                                                                                {
                                                                                                    Thresholds[k] = threshold1;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    Thresholds[k] = (uint8)(Thresholds[k] + 0.5f * (threshold1 - Thresholds[k]));//这里是取了平均，可以通过调整占比适应不同的光照条件
                                                                                                }
                //SetText("中间var:" + maxvar + " 阈值:" + Thresholds[k] + " 比例:" + maxbin + " 灰度和" + gray_hh);
        }
        else if (k == 2)
        {
                if (maxbin < 0.85f && gray_hh < 28)
                {
                        Thresholds[k] = (uint8)(Thresholds[1] - 3);
                }
                else if(gray_hh > 69 && gray_hh < 79)
                {
                        if (maxbin < 0.5f || maxbin > 0.15f)
                        {
                                Thresholds[k] = (uint8)(Thresholds[1] - 3);
                        }
                }
                                                                 if (abs(threshold1 - Thresholds[k]) >= 30)//相差太大直接用标准值
                                                                {
                                                                    Thresholds[k] = threshold1;
                                                                }
                                                                else
                                                                {
                                                                    Thresholds[k] = (uint8)(Thresholds[k] + 0.5f * (threshold1 - Thresholds[k]));//这里是取了平均，可以通过调整占比适应不同的光照条件
                                                                }
                //SetText("左边var:" + maxvar + " 阈值:" + Thresholds[k] + " 比例:" + maxbin + " 灰度和" + gray_hh);
        }






        for (i = 0; i < Thresholds[k]; i++)
        {
                Bin_Array[i] = 0;
        }
        for (i = Thresholds[k]; i < 256; i++)
        {
                Bin_Array[i] = 255;
        }
        for (i = ostu_point[k].y0; i <= ostu_point[k].y1; i++)
        {
                for (j = ostu_point[k].x0; j <= ostu_point[k].x1; j++)
                {
                        image_use[i][j] = Bin_Array[*(*(p_image + i) + j)];
                }
        }
    }
}


/*****************大津end*********************/


/***八邻域*****/
struct size_point2
{
    int x0;
    int y0;
};

struct size_point2 stack_seed[6000];//栈
uint16 stack_top = 0;
uint8 (*p_Pixels)[186] = &image_use[0];
uint8 Ostu_Threshold=0;
void pull_stack(uint8 x, uint8 y)//入栈
{
    *(*(p_Pixels + y) + x) = 255;
    stack_seed[stack_top].x0 = x;
    stack_seed[stack_top].y0 = y;
    stack_top++;
}
struct size_point2 push_stack()//出栈
{
    stack_seed[stack_top].y0 = 0;
    stack_seed[stack_top].x0 = 0;
    return stack_seed[--stack_top];
}

int panbianjie(uint8 x, uint8 y)
{
    if (x + y == 0)
    {
            return 0;
    }
    return (int)((abs(x - y) * 100 / (x + y)) + 0.5f);
}

struct size_point2 connects[8]={ //八领域扫点
//{-1,-1},
//{0,-1},
//{1,-1},
{1,0},
//{1,1},
{0,1},
//{-1,1},
{-1,0}
};

void SignalProcess_grayfine_fill(void)
 {
        int j,px,py;
        struct size_point2 center_seed;
        uint8 (*p_image)[188] = &mt9v03x_image[0];
        p_Pixels = &image_use[0];
        stack_top = 0;
        for (i = 0; i <= 69; i++)
        {
            for (j = 0; j <= 185; j++)
            {
                    *(*(p_Pixels + i) + j) = 0;
            }
        }
        Ostu_Threshold = 100;

        for (i = 0; i < 186; i++)
        {
            if (Ostu_Threshold - *(*(p_image + 0) + i + 1) < 5)
                    pull_stack((uint8)i, 0);
        }
        while (stack_top != 0)
        {
            center_seed = push_stack();
            px = center_seed.x0 + connects[0].x0;
            py = center_seed.y0 + connects[0].y0;
            if (*(*(p_Pixels + py) + px) == 1 || px < 0 || py < 0 || px >= 186 || py >= 70)
            {}
            else
            {
                    if (abs(*(*(p_image + py) + px + 1)- *(*(p_image + center_seed.y0) + center_seed.x0 + 1)) < 8 && Ostu_Threshold - *(*(p_image + py) + px + 1) < 5)
                    {
                                    pull_stack((uint8)px, (uint8)py);
                    }
            }

            px = center_seed.x0 + connects[1].x0;
            py = center_seed.y0 + connects[1].y0;
            if (*(*(p_Pixels + py) + px) == 1 || px < 0 || py < 0 || px >= 186 || py >= 70)
            {}
            else
            {
                    if (abs(*(*(p_image + py) + px + 1)- *(*(p_image + center_seed.y0) + center_seed.x0 + 1)) < 8 && Ostu_Threshold - *(*(p_image + py) + px + 1) < 5)
                    {
                            pull_stack((uint8)px, (uint8)py);
                    }
            }

            px = center_seed.x0 + connects[2].x0;
            py = center_seed.y0 + connects[2].y0;
            if (*(*(p_Pixels + py) + px) == 1 || px < 0 || py < 0 || px >= 186 || py >= 70)
            {}
            else
            {
                    if (abs(*(*(p_image + py) + px + 1)- *(*(p_image + center_seed.y0) + center_seed.x0 + 1)) < 8 && Ostu_Threshold - *(*(p_image + py) + px + 1) < 5)
                    {
                            pull_stack((uint8)px, (uint8)py);
                    }
            }
        }
}
/***八邻域*****/

void bu_breakhang(int c1, int c2, uint8 j)
{

    int k = center[c2] - center[c1];

    if(j>40)
    {
            if (k >1) //入左弯
            {
                for (uint8 i = j; i >= 11; i--)
                {
                    center[i] = 2;


                }
            }
            else if (k < 1)  //入右弯
            {
                for (uint8 i = j; i >= 11; i--)
                {
                    center[i] =184;
                }
            }
            else//          直到置0
            {
                 for (uint8 i = j; i >= 1; i--)
                {
                    center[i] = 93;
                }
            }
    }

}

void advanced_regression(int type, int startline1, int endline1, int startline2, int endline2)
{
    int i = 0;
    int sumlines1 = endline1 - startline1;
    int sumlines2 = endline2 - startline2;
    int sumX = 0;
    int sumY = 0;
    float averageX = 0;
    float averageY = 0;
    float sumUp = 0;
    float sumDown = 0;
    if (type == 0)  //拟合中线
    {
        /**计算sumX sumY**/
        for (i = startline1; i < endline1; i++)
        {
            sumX += i;
            sumY += center_th[i];
        }
        for (i = startline2; i < endline2; i++)
        {
            sumX += i;
            sumY += center_th[i];
        }
        averageX = sumX / (sumlines1 + sumlines2);     //x的平均值
        averageY = sumY / (sumlines1 + sumlines2);     //y的平均值
        for (i = startline1; i < endline1; i++)
        {
            sumUp += (center_th[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        for (i = startline2; i < endline2; i++)
        {
            sumUp += (center_th[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        if (sumDown == 0) parameterB = 0;
        else parameterB = sumUp / sumDown;
        parameterA = averageY - parameterB * averageX;

    }
    else if (type == 1)     //拟合左线
    {
        /**计算sumX sumY**/
        for (i = startline1; i < endline1; i++)
        {
            sumX += i;
            sumY += left_line[i];
        }
        for (i = startline2; i < endline2; i++)
        {
            sumX += i;
            sumY += left_line[i];
        }
        averageX = sumX / (sumlines1 + sumlines2);     //x的平均值
        averageY = sumY / (sumlines1 + sumlines2);     //y的平均值
        for (i = startline1; i < endline1; i++)
        {
            sumUp += (left_line[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        for (i = startline2; i < endline2; i++)
        {
            sumUp += (left_line[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        if (sumDown == 0) parameterB = 0;
        else parameterB = sumUp / sumDown;
        parameterA = averageY - parameterB * averageX;
    }
    else if (type == 2)         //拟合右线
    {
        /**计算sumX sumY**/
        for (i = startline1; i < endline1; i++)
        {
            sumX += i;
            sumY += right_line[i];
        }
        for (i = startline2; i < endline2; i++)
        {
            sumX += i;
            sumY += right_line[i];
        }
        averageX = sumX / (sumlines1 + sumlines2);     //x的平均值
        averageY = sumY / (sumlines1 + sumlines2);     //y的平均值
        for (i = startline1; i < endline1; i++)
        {
            sumUp += (right_line[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        for (i = startline2; i < endline2; i++)
        {
            sumUp += (right_line[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        if (sumDown == 0) parameterB = 0;
        else parameterB = sumUp / sumDown;
        parameterA = averageY - parameterB * averageX;
    }

}

void find_rightdown_point(uint8 start_point, uint8 end_point, uint8 RoadName)
{
    uint8 j;
    if (RoadName == 1)
    {
        for (j = start_point; j >= end_point; j--)
        {
            //找右边突变(下拐点)
            if (j>=sousuojieshuhang+4&&abs(right_line[j + 1] - right_line[j + 2]) <= 2 && abs(right_line[j] - right_line[j + 1]) <= 2 && (right_line[j - 1] - right_line[j])>= 1&& (right_line[j - 2] - right_line[j])>= 2&& (right_line[j - 3] - right_line[j])>= 3
                && Right_Add[j + 2] == 0 && Right_Add[j + 1] == 0 && Right_Add[j] == 0)
            {
                right_turn_down[0] = j + 1;//数组里面没有第0行
                right_turn_down[1] = right_line[j];
                break;
            }
        }
    }
    else if (RoadName == 2)
    {
         for (j = start_point; j >= end_point; j--)
        {
            //找右边突变(下拐点)
            if (r_start>65&&j>=sousuojieshuhang+4&&abs(right_line[j + 1] - right_line[j + 2]) <= 2 && abs(right_line[j] - right_line[j + 1]) <= 2 && (right_line[j - 1] - right_line[j])>= 1&& (right_line[j - 2] - right_line[j])>= 2&& (right_line[j - 3] - right_line[j])>= 3
                && Right_Add[j + 2] == 0 && Right_Add[j + 1] == 0 && Right_Add[j] == 0)
            {
                right_turn_down[0] = j + 1;//数组里面没有第0行
                right_turn_down[1] = right_line[j];
                break;
            }
        }
        //如果右下拐点坐标不为空 且 环岛状态不是4 就认定找到环岛的右下拐点
       // if (f[0] != 0 && huandao_memory != 4) flag_find_huan_rightdown_point = 1;
    }
    else
    {

    }
}



//【Function6】找左下拐点函数   abs
//输入： start点 end点  所要判断的下拐点的类型（环岛还是十字？）
void find_leftdown_point(uint8 start_point, uint8 end_point, uint8 RoadName)
{
    uint8 j;
    if (RoadName == 1)
    {
        for (j = start_point; j >= end_point; j--)
        {
            //找左边突变(下拐点)；连续且是存在的点（）
            if (j>=sousuojieshuhang+4&&abs(left_line[j + 1] - left_line[j + 2]) <= 2 && abs(left_line[j] - left_line[j + 1]) <=2 && (left_line[j ] - left_line[j-1])>=1&& (left_line[j ] - left_line[j-2])>=2&& (left_line[j ] - left_line[j-3])>=3
                && Left_Add[j + 2] == 0 && Left_Add[j + 1] == 0 && Left_Add[j] == 0)
            {

                left_turn_down[0] = j;//数组里面没有第0行
                left_turn_down[1] = left_line[j];
                break;
            }
        }
    }
    else if (RoadName == 2)
    {
        //setText用户自定义("l_start"+ l_start);
        for (j = start_point; j >= end_point; j--)
        {
            //找左边突变(下拐点)；连续且是存在的点（）
            if (l_start>65&&j>=sousuojieshuhang+4&&abs(left_line[j + 1] - left_line[j + 2]) <= 2 && abs(left_line[j] - left_line[j + 1]) <=2 && (left_line[j ] - left_line[j-1])>=1&& (left_line[j ] - left_line[j-2])>=2&& (left_line[j ] - left_line[j-3])>=3
                && Left_Add[j + 2] == 0 && Left_Add[j + 1] == 0 && Left_Add[j] == 0)
            {

                left_turn_down[0] = j;//数组里面没有第0行
                left_turn_down[1] = left_line[j];
                break;
            }
        }
    //    if (left_turn_down[0] != 0 && huandao_memory != 4) flag_find_huan_leftdown_point = 1;
    }
    else
    {

    }
}

unsigned int my_sqrt(int x)
{
 uint8 ans=0,p=0x80;
 while(p!=0)
 {
 ans+=p;
 if(ans*ans>x)
 {
 ans-=p;
 }
 p=(uint8)(p/2);
 }
 return(ans);
}
float process_curvity(uint8 x1, uint8 y1, uint8 x2, uint8 y2, uint8 x3, uint8 y3)
{
    float K;
    int S_of_ABC = ((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) / 2;
    //面积的符号表示方向
    char q1 = (char)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    char AB = my_sqrt(q1);
    q1 = (char)((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    char BC = my_sqrt(q1);
    q1 = (char)((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));
    char AC = my_sqrt(q1);
    if (AB * BC * AC == 0)
    {
        K = 0;
    }
    else
        K = (float)4 * S_of_ABC / (AB * BC * AC);
    return K;
}



char oppositeSigns(int x, int y)
{
    return ((x ^ y) < 0);
}
void Cal_losttimes(int times)
{
    uint8 i;
    uint8 flag_of_rightbreak = 0;
    uint8 flag_of_leftbreak = 0;
    for (i = 67; i > times; i--)
    {
        //左线操作
        if (Left_Add[i] == 1)       //未扫到线
        {
            zuodiuxianshu++;
            if (flag_of_leftbreak == 0)     //如果在这一行之前没有遭遇断线，则计数
            {
                l_start=i;
            }
        }
        else    //扫到线
        {
            //lostleft_times不继续增加
            flag_of_leftbreak = 1;  //break标志成立
        }
        //右线操作
        if (Right_Add[i] == 1)       //未扫到线
        {
            youdiuxianshu++;
            if (flag_of_rightbreak == 0)     //如果在这一行之前没有遭遇断线，则计数
            {
                r_start=i;
            }
        }
        else    //扫到线
        {
            //lostright_times不继续增加
            flag_of_rightbreak = 1;  //break标志成立
        }
    }

}

void Center_line_deal()//中线处理
    {
    k_center=0;
    qvlv_quanju_right=qvlv_quanju_left=qulv_jinduan_right=qulv_jinduan_left=qulv_yuandaun_right=qulv_yuandaun_left=0;
       k_left=0;
       k_right=0;
      Width_Min=100;
      th_y=0;
      whitenum=0;
     right_turn_down[0]=69;
     left_turn_down[0]=69;
     right_turn_down[1]=187;
     left_turn_down[1]=1;
      // right_turn_up[0]=0;
     //  left_turn_up[0]=0;
    xielv_1eft2=80;
     xielv_right2=80;
      findleftdownguai=0;
      findrightdownguai=0;
       findrightupguai = 0;
       findleftupguai = 0;
      times=0;
      Foresight_Left=0, Foresight_Right=186;
      youdiuxianshu=0;
      zuodiuxianshu=0;
      Left_Add_Start=0;
      Right_Add_Start=0;
      Left_Add_End=0;
      Right_Add_End=0;
      white_num_col_max=0;
      Left_Add_num=0,Right_Add_num=0;
       white_num_col_min=69;
      l_start=68;r_start=68;
      for(int ql=0;ql<=69;ql++)   //清零函数
      {
        left_line[ql]=2;
        Left_Add[ql]=0;
        Left_Add2[ql]=0;
        Left_Line_New[ql]=2;

      }
       for(int ql=0;ql<=187;ql++)   //清零函数guaidian
      {
        white_num_col[ql]=0;

      }
      for(int ql=0;ql<=69;ql++)
      {
        right_line[ql]=184;
         Right_Line_New[ql]=184;
        center[ql]=89;
        Right_Add[ql]=0;
        Right_Add2[ql]=0;

      }
      uint8 x=0,y=0;     //设x为行，y为列
      uint8 temp=0;
    ////////////////////////////扫描最底下3行/////////////////////////

    if(right_huan_num==6||left_huan_num==3)
         {
                for(x=180;x>100;x--)
              {
                for(y=68;y>1;y--)
                {
                  if(image_use[y][x]==0)
                  {
                    break;
                  }
                  else
                  {
                  white_num_col[x]++;
                  }
                }
                if(white_num_col[x]> white_num_col_max)
                {white_num_col_max=white_num_col[x];
                  white_num_col_line=x;
                }
              }
         }

     else if(right_huan_num==3||left_huan_num==6)
     {
            for(x=5;x<93;x++)
          {
            for(y=68;y>1;y--)
            {
              if(image_use[y][x]==0)
              {
                break;
              }
              else
              {
              white_num_col[x]++;
              }
            }
            if(white_num_col[x]> white_num_col_max)
            {white_num_col_max=white_num_col[x];
              white_num_col_line=x;
            }
          }
     }
     else
        {        if(park_flag==1)
                  {
                     for(x=10;x<=93;x++)
                           {
                             for(y=68;y>1;y--)
                             {
                               if(image_use[y][x]==0)
                               {
                                 break;
                               }
                               else
                               {
                               white_num_col[x]++;
                               }
                             }
                             if(white_num_col[x]> white_num_col_max)
                             {white_num_col_max=white_num_col[x];
                               white_num_col_line=x;
                             } // k_right
                           }
                                          for(x=175;x>=94;x--)
                                       {
                                         for(y=68;y>1;y--)
                                         {
                                           if(image_use[y][x]==0)
                                           {
                                             break;
                                           }
                                           else
                                           {
                                           white_num_col[x]++;
                                           }
                                         }
                                       if(white_num_col[x]> white_num_col_max)
                                       {white_num_col_max=white_num_col[x];
                                         white_num_col_line=x;
                                       }
                                          }
                  }
        else if(park_flag==0)
        {

                                                 for(x=175;x>=94;x--)
                                              {
                                                for(y=68;y>1;y--)
                                                {
                                                  if(image_use[y][x]==0)
                                                  {
                                                    break;
                                                  }
                                                  else
                                                  {
                                                  white_num_col[x]++;
                                                  }
                                                }
                                              if(white_num_col[x]> white_num_col_max)
                                              {white_num_col_max=white_num_col[x];
                                                white_num_col_line=x;
                                              }
                                                 }
                                                 for(x=10;x<=93;x++)
                                       {
                                         for(y=68;y>1;y--)
                                         {
                                           if(image_use[y][x]==0)
                                           {
                                             break;
                                           }
                                           else
                                           {
                                           white_num_col[x]++;
                                           }
                                         }
                                         if(white_num_col[x]> white_num_col_max)
                                         {white_num_col_max=white_num_col[x];
                                           white_num_col_line=x;
                                         } // k_right
                                       }
                         }

        }
        huihuan_num=0;
    for(x=150;x>=35;x--)
      {
        if(white_num_col[x]> 64)
        huihuan_num++;
      }
        for(y = 68;y >1;y--)    //x是减59—56  num是加0—4
        {
          for(x = white_num_col_line;x <=184;x++)    //中间向右找跳变
            {
              if(image_use[y][x-1] == 255&&image_use[y][x] == 255&& image_use[y][x+1] == 0 && image_use[y][x+2] == 0 )  //两个连续黑点触发
                {
                   right_line[y]=x;
                   Right_Line_New[y]=x;
                   Right_Line_New2[y]=x;
                   break;
                }
                else if(x==184)       //到最右边了都没扫到黑点a
                {
                    right_line[y]=x;
                    Right_Line_New[y]=x;
                    Right_Line_New2[y]=x;
                    Right_Add[y]=1;

                    break;
                }
            }
            for(x = white_num_col_line;x >= 1 ; x--)            //中间向左找跳变
            {
              if(image_use[y][x-2] == 0 &&image_use[y][x-1] == 0 &&  image_use[y][x] == 255&&  image_use[y][x+1] == 255)  //两个连续黑点触发
                {
                    left_line[y]=x;
                    Left_Line_New[y]=x;
                    Left_Line_New2[y]=x;
                    break;
                }
              else if(x==3)                 //到最左边了都没扫到黑点
                {

                     left_line[y]=x;
                     Left_Line_New[y]=x;
                     Left_Line_New2[y]=x;
                     Left_Add[y]=1;

                    break;
                }
            }
          //   Half_width[y]=abs(right_line[y]-left_line[y])/2;
           Width[y]=abs(right_line[y]-left_line[y]);
           if(left_line[y]<=3&&right_line[y]<184)
                     {
                       if(right_line[y]-Half_width_yuanshi[y]<=3)
                           center_th[y]=3;
                       else
                           center_th[y]=right_line[y]-Half_width_yuanshi[y];
                     }
                    else  if(left_line[y]>3&&right_line[y]>=184)
                     {
                       if(left_line[y]+Half_width_yuanshi[y]>=184)
                           center_th[y]=184;
                       else
                           center_th[y]=left_line[y]+Half_width_yuanshi[y];
                     }
                      else
                          center_th[y] = ( left_line[y] + right_line[y]) / 2;

       if (Width[y]>=Width[y+1]|| (Width[y] >= Width_Min))
       {

                        if (Left_Add2[y+1])
            {
                if (left_line[y] < Left_Line_New2[y+1]-1)    //与前一行的左边界实线比较
                {
                    Left_Add2[y] = 1;
                }
            }
            else    //前一行没有补线
            {
                if (left_line[y] < left_line[y+1]-1)    //与前一行的左边界实线比较
                {
                    Left_Add2[y] = 1;
                }
            }
                    if (Right_Add2[y+1])
            {
                if (right_line[y] > Right_Line_New2[y+1]+1)
                {
                    Right_Add2[y] = 1;
                }
            }
            else    //前一行右边界没有补线
            {
                if (right_line[y] > right_line[y+1]+1)
                {
                    Right_Add2[y] = 1;
                }
            }



       }


               if (Left_Add2[y])    //左边需要补线
        {

                                  if(y<65)
                                  { if (!Left_Add_Start)    //如果还没有记录开始补线位置
            {

                Left_Add_Start = y; //记录左边界补线开始位置
            }


                                                        Add_Slope = 1.0*(left_line[Left_Add_Start+6] - left_line[Left_Add_Start+1]) / 4;    //计算能识别的前几行图像斜率

                                        if (Add_Slope > 0)  //限幅
                                        {
                                                        Add_Slope = 0;
                                        }
                temp = (char)((y - (Left_Add_Start+1)) * Add_Slope + left_line[Left_Add_Start+1]);//通过斜率推算补线的位置
                Left_Last_Slope = Add_Slope;    //更新上次左边界斜率


            Left_Line_New2[y] = range_protect(temp, 2,184);  //不直接修改边界，只保存在补线数组里
                                  }
                                                    /* 第一次补线，只记录，不在图像上显示 */
//
        }
        if (Right_Add2[y])  //右边需要补线
        {
                                  if(y<65)
                                  {
            if (!Right_Add_Start)   //如果还没有记录开始补线位置
            {

                Right_Add_Start = y;    //记录左边界补线开始位置
            }

            Add_Slope = 1.0*(right_line[Right_Add_Start+6] - right_line[Right_Add_Start+1]) / 4;    //计算能识别的前几行图像斜率

                if (Add_Slope < 0)  //限幅
                {
                    Add_Slope = 0;
                }
                temp_r = (char)((y - (Right_Add_Start+1)) * Add_Slope + right_line[Right_Add_Start+1]);//通过斜率推算补线的位置
                Right_Last_Slope = Add_Slope;   //更细上次右边界斜率


            Right_Line_New2[y] = range_protect(temp_r, 2, 184);      //不直接修改边界，只保存在补线数组里
          }
                                }
                          if (Left_Add2[y] && Right_Add2[y])  //两边都需要补线
        {
            Width[y] = Right_Line_New2[y] - Left_Line_New2[y];    //重新计算本行赛道宽度

                                 }
        else    //不需要补线或只有一边需要补线
        {
            if (Left_Add2[y])    //此处最多只有一边会需要补线
            {
                Width[y] = right_line[y] - Left_Line_New2[y];    //重新计算本行赛道宽度

                                                }
            else if (Right_Add2[y])
            {
                Width[y] = Right_Line_New2[y] - left_line[y];    //重新计算本行赛道宽度

               }
            else
            {
                Width[y] = right_line[y] - left_line[y];        //可能会有干扰，也重新计算一次赛道宽度

                                                }
            if (Width[y] < Width_Min)
            {
                Width_Min = Width[y];   //更新最小赛道宽度
            }
                            if (left_line[y] > Foresight_Left)  //更新左边界最大值
            {
                Foresight_Left = left_line[y];
            }
            if (right_line[y] < Foresight_Right)//更新右边界最小值
            {
                Foresight_Right = right_line[y];
            }


        }
                 if (y>=30 && Right_Add[y] == 1 && Left_Add[y] == 1) times++;
                  if(abs(right_line[y]-left_line[y])<=1)
                        break;
                  if(image_use[y][(right_line[y]+left_line[y])/2]==0)
                        break;
                  if(y<=1)
                    break;
           }
             sousuojieshuhang=y+2;
          Cal_losttimes(sousuojieshuhang);////left_huan_num
         for(y=68;y>5;y--)
       {
         if(Right_Add2[y]==1)
         Right_Add_num++;
         if(Left_Add2[y]==1)
         Left_Add_num++;
       }

//         curvity_point1 = (uint8)((r_start + sousuojieshuhang) / 2);      //中点
//
//                if (sousuojieshuhang >=60)
//                {
//                  curvity_point2 = (uint8)(sousuojieshuhang + 1);
//                }
//                else
//                {
//                  curvity_point2 = (uint8)(sousuojieshuhang+1);
//                }
//         curvity_right = process_curvity(right_line[r_start], r_start, right_line[curvity_point1], curvity_point1, right_line[curvity_point2], curvity_point2);
//
//         curvity_point1 = (uint8)((l_start + sousuojieshuhang+1) / 2);      //中点
//
//                if (sousuojieshuhang >=60)
//                {
//                  curvity_point2 = (uint8)(sousuojieshuhang + 1);
//                }
//                else
//                {
//                  curvity_point2 = (uint8)(sousuojieshuhang+1);
//                }
//         curvity_left = process_curvity(left_line[l_start], l_start, left_line[curvity_point1], curvity_point1, left_line[curvity_point2], curvity_point2);


    /************十字处理**************/
       if(l_start>=55||r_start>=55)
       {
         find_leftdown_point(67,20,1);   //1是十字
         find_rightdown_point(67,20,1);
       }
       //find_leftmiddle_point(65,20);
    //   if(flag_find_huan_leftmiddle_point)
     //  {
      //   right_buxian(right_turn_middle[1],right_turn_middle[0],160,68);
      //    flag_find_huan_leftmiddle_point=0;
   //    }
       if(left_turn_down[0]==69)
       {  regression(1,sousuojieshuhang+3,l_start-3);
               k_left=parameterB;
       }
       else
       {
        regression(1,left_turn_down[0]+2,l_start-3);
               k_left=parameterB;
       }

          if(right_turn_down[0]==69)
          {
            regression(2,sousuojieshuhang+3,r_start-3);
               k_right=parameterB;
          }
         else
           {
            regression(2,right_turn_down[0]+3,r_start-3);
               k_right=parameterB;
          }

     if (!left_huan_num&&!right_huan_num)
    {
        //如果找到左下或者右下拐点，此时检测左右线趋势

        //时时注意拐点坐标第一个是行数+1，处理时要做减一处理
        if (left_turn_down[0] != 69 || right_turn_down[0] != 69)
        {
            if (left_turn_down[0] != 69 && right_turn_down[0] == 69)//左下拐点存在而右下拐点不存在
            {
                regression(1, left_turn_down[0] - 3, left_turn_down[0] + 2);//左线
                trend_of_left = parameterB;
                regression(2, left_turn_down[0] - 3, left_turn_down[0] + 2);//右线
                trend_of_right = parameterB;
            }
            else if (right_turn_down[0] != 69 && left_turn_down[0] == 69)    //右下拐点存在而左下拐点不存在
            {
                regression(1, right_turn_down[0] - 3, right_turn_down[0] + 2);//左线
                trend_of_left = parameterB;
                regression(2, right_turn_down[0] - 3, right_turn_down[0] + 2);//右线
                trend_of_right = parameterB;
            }
            else if (left_turn_down[0] != 69 && left_turn_down[0] != 69)   //左右拐点均存在
            {
                regression(1, left_turn_down[0] - 3, left_turn_down[0] + 2);//左线
                trend_of_left = parameterB;
                regression(2, right_turn_down[0] - 3, right_turn_down[0] + 2);//右线
                trend_of_right = parameterB;
            }
        }
       if((trend_of_left>0&&trend_of_right<0)||(trend_of_left<0&&trend_of_right>0))
             twolines_trend=1;
       else
             twolines_trend=0;

       if ((left_turn_down[0] != 69 && twolines_trend == 1) || (youdiuxianshu >= 15 && left_turn_down[0] != 69))
        {

            findleftdownguai = 1;   //表示找到左下拐点了
        }
        else findleftdownguai = 0;
        if ((right_turn_down[0] != 69 && twolines_trend == 1) || (zuodiuxianshu >= 15 && right_turn_down[0] != 69))
        {

            findrightdownguai = 1;//表示找到右下拐点了
        }
        else findrightdownguai = 0;



//                                     if(findrightdownguai&&right_turn_down[0]<50)
//                                    advanced_regression(0,right_turn_down[0]+2,(right_turn_down[0]+68)/2, (right_turn_down[0]+68)/2+1,68);
//                                  else if(findleftdownguai&&left_turn_down[0]<50)
//                                   advanced_regression(0,left_turn_down[0]+2,(left_turn_down[0]+68)/2, (left_turn_down[0]+68)/2+1,68);
//                                   else
                                    advanced_regression(0,61,64, 65,68);
                                   for (int j = (uint8)68; j >= 1; j--)
                                              {
                                                  int jicun = (int)(parameterB * j + parameterA);
                                                  if (jicun >= 185) jicun = 185;
                                                  else if (jicun <= 0) jicun = 0;
                                                 center_th[j] = (uint8)jicun;

                                              }

                                   for(int y=68;y>0;y--)
                                    {
                                     if(image_use[y][center_th[y]]==0)
                                      {
                                         th_y=center_th[y];
                                        break;
                                      }
                                      else
                                      {
                                     whitenum++;
                                      }
                                    }
        /*************找到左下或右下拐点后，拟合并预测中线，然后再顺着预测后的中线找**************/
                      if (findrightdownguai == 1 || findleftdownguai == 1)
                      {



                                    if (findrightdownguai == 1 && findleftdownguai == 0)//左斜入十字，仅有右下拐点，取右下拐点下的中线行
                                    {
                                         if(!three_cross||!three_cross1)//防三叉
                                         {
                                          for (uint8 j = 68; j >= 1; j--)
                                                         {
                                                            //左上拐点
                                                            if ( ((j < (uint8)left_turn_down[0])&&((left_line[j] - left_line[j+3]) >= 10) &&((left_line[j] - left_line[j+2]) >= 10) && ((left_line[j] - left_line[j+1]) >= 10 ))
                                                                && Left_Add[j] == 0 && Left_Add[j - 1] == 0 && Left_Add[j -2] == 0)
                                                            {

                                                                left_turn_up[0] = j-2;//数组里面没有第0行
                                                                left_turn_up[1] = left_line[j]-2;
                                                                //获得的上坐标先确定一下是不是比下坐标小，如果小则说明提前断掉，此时的“上拐点”为假.
                                                                //如果比下坐标大则此时的“上拐点”为真.
                                                                if (left_turn_up[0] >= left_turn_down[0])
                                                                {
                                                                    ;
                                                                }
                                                                else break;
                                                            }
                                                        }
                                                        /***找右上拐点***********/
                                                        for (uint8 j = 68; j >= 1; j--)
                                                        {
                                                            if (((j < (uint8)right_turn_down[0])  && right_line[j + 3] - right_line[j] >=10&& right_line[j + 2] - right_line[j] >=10 && right_line[j + 1] - right_line[j] >=10 )
                                                           && (Right_Add[j] == 0 && Right_Add[j - 1] == 0 && Right_Add[j - 2] == 0))
                                                            {
                                                                right_turn_up[0] = j-2 ;
                                                                right_turn_up[1] = right_line[j-2];
                                                                if (right_turn_up[0] >= right_turn_down[0])
                                                                {
                                                                    ;
                                                                }
                                                                else break;
                                                            }
                                                        }
                                               if (right_turn_up[0]>(sousuojieshuhang)&&right_turn_up[0] < right_turn_down[0] &&right_turn_up[1] <= right_turn_down[1]&&right_turn_up[0] != 0)
                                              {

                                                  findrightupguai = 1;//表示找到右上拐点了

                                              }
                                              if (left_turn_up[0]>(sousuojieshuhang)&&left_turn_up[0] < left_turn_down[0] &&left_turn_up[1] >= left_turn_down[1]&& left_turn_up[0] != 0)
                                              {

                                                  findleftupguai = 1;//表示找到左上拐点了
                                              }

                                                    /*********开始补线(找到左下拐点和左上拐点  或 找到右下拐点和右上拐点)*********/
                                                    if ((findrightupguai == 1 && findrightdownguai == 1) || (findrightupguai == 1 && findrightdownguai == 0))
                                                    {

                                                        if (findleftupguai == 1 && findleftdownguai == 1)        //找到左下拐点和左上拐点,拟合所需的点是下拐点下面三个点和上拐点上面三个点
                                                        {
                                                            uint8 start1 = left_turn_down[0] +2 ;
                                                            if (start1 >= 68) start1 = 68;

                                                            uint8 start2 = left_turn_up[0];
                                                            if (start2 >= 68) start2 = 68;

                                                            left_buxian(left_line[start1],start1,left_line[start2],start2);



                                                        }
                                                        else if (findleftupguai == 1 && findleftdownguai == 0)
                                                        {
                                                            uint8 start1 = left_turn_up[0];
                                                            if (start1 >= 68) start1 = 68;

                                                            left_buxian(2,68,left_line[start1],start1);

                                                        }
                                                        //并列关系
                                                        if (findrightdownguai == 1 && findrightupguai == 1)        //找到左下拐点和左上拐点,拟合所需的点是下拐点下面三个点和上拐点上面三个点
                                                        {
                                                            uint8 start1 = right_turn_down[0] +2;
                                                            if (start1 >= 68) start1 = 68;

                                                            uint8 start2 = right_turn_up[0];
                                                            if (start2 >= 68) start2 = 68;
                                                            uint8 end2 = right_turn_up[0];
                                                            right_buxian(right_line[start1],start1,right_line[end2],end2);

                                                        }
                                                        else if (findrightdownguai == 0 && findrightupguai == 1)
                                                        {
                                                            uint8 start1 = right_turn_up[0];
                                                            if (start1 >= 68) start1 = 68;

                                                           right_buxian(184,68,right_line[start1],start1);

                                                        }
                                                     }
                                               //  else if(!three_cross&&right_turn_down[0]<45)
                                                //      sousuojieshuhang=right_turn_down[0]+1;


                                         }

                                     }
                                        else if (findrightdownguai == 0 && findleftdownguai == 1) //右斜入十字，仅有左下拐点，取左下拐点下的中线行
                                        {
                                                  if(!three_cross||!three_cross1)
                                             {
                                                     for (uint8 j = 68; j >= 1; j--)
                                                            {
                                                                //左上拐点
                                                                if ( ((j < (uint8)left_turn_down[0])&&((left_line[j] - left_line[j+3]) >= 10) &&((left_line[j] - left_line[j+2]) >= 10) && ((left_line[j] - left_line[j+1]) >= 10 ))
                                                                    && Left_Add[j] == 0 && Left_Add[j - 1] == 0 && Left_Add[j -2] == 0)
                                                                {

                                                                    left_turn_up[0] = j-2;//数组里面没有第0行
                                                                    left_turn_up[1] = left_line[j]-2;
                                                                    //获得的上坐标先确定一下是不是比下坐标小，如果小则说明提前断掉，此时的“上拐点”为假.
                                                                    //如果比下坐标大则此时的“上拐点”为真.
                                                                    if (left_turn_up[0] >= left_turn_down[0])
                                                                    {
                                                                        ;
                                                                    }
                                                                    else break;
                                                                }
                                                            }
                                                            /***找右上拐点***********/
                                                            for (uint8 j = 68; j >= 1; j--)
                                                            {
                                                                if (((j < (uint8)right_turn_down[0])  && right_line[j + 3] - right_line[j] >=10&& right_line[j + 2] - right_line[j] >=10 && right_line[j + 1] - right_line[j] >=10 )
                                                               && (Right_Add[j] == 0 && Right_Add[j - 1] == 0 && Right_Add[j - 2] == 0))
                                                                {
                                                                    right_turn_up[0] = j-2 ;
                                                                    right_turn_up[1] = right_line[j-2];
                                                                    if (right_turn_up[0] >= right_turn_down[0])
                                                                    {
                                                                        ;
                                                                    }
                                                                    else break;
                                                                }
                                                            }
                                                   if (right_turn_up[0]>(sousuojieshuhang)&&right_turn_up[0] < right_turn_down[0] &&right_turn_up[1] <= right_turn_down[1]&&right_turn_up[0] != 0)
                                                  {

                                                      findrightupguai = 1;//表示找到右上拐点了

                                                  }
                                                  if (left_turn_up[0]>(sousuojieshuhang)&&left_turn_up[0] < left_turn_down[0] &&left_turn_up[1] >= left_turn_down[1]&& left_turn_up[0] != 0)
                                                  {

                                                      findleftupguai = 1;//表示找到左上拐点了
                                                  }

                                                        /*********开始补线(找到左下拐点和左上拐点  或 找到右下拐点和右上拐点)*********/
                                                        if ((findleftupguai == 1 && findleftdownguai == 1) || (findleftupguai == 1 && findleftdownguai == 0))
                                                        {

                                                            if (findleftupguai == 1 && findleftdownguai == 1)        //找到左下拐点和左上拐点,拟合所需的点是下拐点下面三个点和上拐点上面三个点
                                                            {
                                                                uint8 start1 = left_turn_down[0] +2 ;
                                                                if (start1 >= 68) start1 = 68;

                                                                uint8 start2 = left_turn_up[0];
                                                                if (start2 >= 68) start2 = 68;

                                                                left_buxian(left_line[start1],start1,left_line[start2],start2);



                                                            }
                                                            else if (findleftupguai == 1 && findleftdownguai == 0)
                                                            {
                                                                uint8 start1 = left_turn_up[0];
                                                                if (start1 >= 68) start1 = 68;

                                                                left_buxian(2,68,left_line[start1],start1);

                                                            }
                                                            //并列关系
                                                            if (findrightdownguai == 1 && findrightupguai == 1)        //找到左下拐点和左上拐点,拟合所需的点是下拐点下面三个点和上拐点上面三个点
                                                            {
                                                                uint8 start1 = right_turn_down[0] +2;
                                                                if (start1 >= 68) start1 = 68;

                                                                uint8 start2 = right_turn_up[0];
                                                                if (start2 >= 68) start2 = 68;
                                                                uint8 end2 = right_turn_up[0];
                                                                right_buxian(right_line[start1],start1,right_line[end2],end2);

                                                            }
                                                            else if (findrightdownguai == 0 && findrightupguai == 1)
                                                            {
                                                                uint8 start1 = right_turn_up[0];
                                                                if (start1 >= 68) start1 = 68;

                                                               right_buxian(184,68,right_line[start1],start1);

                                                            }
                                                         }
                                                    //  else   if(!three_cross&&left_turn_down[0]<45)
                                                    //      sousuojieshuhang=left_turn_down[0]+1;
                                                }


                                             }
                            else if (findrightdownguai == 1 && findleftdownguai == 1) //正入十字：用两个下拐点中最小行下的中线行，拟合出k，b，进而拟合出预测中线
                            {

                                xielv_1eft2=abs(left_line[left_turn_down[0]+5]-left_turn_down[1])+abs(left_line[left_turn_down[0]-5]-left_turn_down[1]);
                                xielv_right2=abs(right_line[right_turn_down[0]+5]-right_turn_down[1])+abs(right_line[right_turn_down[0]-5]-right_turn_down[1]);
                if((!lefthuihuan_flag&&!youhuihuan_flag)&&((left_turn_down[0]>20&&left_turn_down[0]!=69)||(right_turn_down[0]>20&&right_turn_down[0]!=69))&&((xielv_1eft2<25&& xielv_right2<25)))//||(xielv_1eft2<27&& xielv_right2<16)||(xielv_1eft2<16&& xielv_right2<27)
                {
                     xj=left_turn_down[1];
                   xk=right_turn_down[1];
                   xj=range_protect(xj, 2,184);
                   xk=range_protect(xk, 2, 184);

                       for(uint8 j=xj+20;j<=xk-20;j++)
                     {
                         if(white_num_col[j]< white_num_col_min)
                              {
                                white_num_col_min=white_num_col[j];
                               white_num_col_min_line=j;
                              }
                     }

                       if(white_num_col_min_line<=(th_y+20)&&white_num_col_min_line>=(th_y-20))   //60  th_y
                           {
                          //  if(white_num_col_line>(th_y+20)||white_num_col_line<(th_y-20))
                             {

                              cnt3++;

                             }
                        if(cnt3>3)
                        {
                            cnt3=0;

                            three_cross = 1;
                            uart_putchar(WIRELESS_UART, '6');
                                             uart_putchar(WIRELESS_UART, '1');
                        }
                       }
               }

                                        if(!three_cross&&(xielv_1eft2>25||xielv_right2>25))
                                        {


                                              for (uint8 j = 68; j >= 1; j--)
                                                {
                                                    //左上拐点
                                                    if ( ((j < (uint8)left_turn_down[0])&&((left_line[j] - left_line[j+3]) >= 10) &&((left_line[j] - left_line[j+2]) >= 10) && ((left_line[j] - left_line[j+1]) >= 10 ))
                                                        && Left_Add[j] == 0 && Left_Add[j - 1] == 0 && Left_Add[j -2] == 0)
                                                    {

                                                        left_turn_up[0] = j-2;//数组里面没有第0行
                                                        left_turn_up[1] = left_line[j]-2;
                                                        //获得的上坐标先确定一下是不是比下坐标小，如果小则说明提前断掉，此时的“上拐点”为假.
                                                        //如果比下坐标大则此时的“上拐点”为真.
                                                        if (left_turn_up[0] >= left_turn_down[0])
                                                        {
                                                            ;
                                                        }
                                                        else break;
                                                    }
                                                }
                                                /***找右上拐点***********/
                                                for (uint8 j = 68; j >= 1; j--)
                                                {
                                                    if (((j < (uint8)right_turn_down[0])  && right_line[j + 3] - right_line[j] >=10&& right_line[j + 2] - right_line[j] >=10 && right_line[j + 1] - right_line[j] >=10 )
                                                   && (Right_Add[j] == 0 && Right_Add[j - 1] == 0 && Right_Add[j - 2] == 0))
                                                    {
                                                        right_turn_up[0] = j-2 ;
                                                        right_turn_up[1] = right_line[j-2];
                                                        if (right_turn_up[0] >= right_turn_down[0])
                                                        {
                                                            ;
                                                        }
                                                        else break;
                                                    }
                                                }
                                       if (right_turn_up[0]>(sousuojieshuhang)&&right_turn_up[0] < right_turn_down[0] &&right_turn_up[1] <= right_turn_down[1]&&right_turn_up[0] != 0)
                                      {

                                          findrightupguai = 1;//表示找到右上拐点了

                                      }
                                      if (left_turn_up[0]>(sousuojieshuhang)&&left_turn_up[0] < left_turn_down[0] &&left_turn_up[1] >= left_turn_down[1]&& left_turn_up[0] != 0)
                                      {

                                          findleftupguai = 1;//表示找到左上拐点了
                                      }

                                            /*********开始补线(找到左下拐点和左上拐点  或 找到右下拐点和右上拐点)*********/
                                            if ((findleftupguai == 1 && findleftdownguai == 1) || (findrightupguai == 1 && findrightdownguai == 1) || (findrightupguai == 1 && findrightdownguai == 0) || (findleftupguai == 1 && findleftdownguai == 0))
                                            {

                                                if (findleftupguai == 1 && findleftdownguai == 1)        //找到左下拐点和左上拐点,拟合所需的点是下拐点下面三个点和上拐点上面三个点
                                                {
                                                    uint8 start1 = left_turn_down[0] +2 ;
                                                    if (start1 >= 68) start1 = 68;

                                                    uint8 start2 = left_turn_up[0];
                                                    if (start2 >= 68) start2 = 68;

                                                    left_buxian(left_line[start1],start1,left_line[start2],start2);



                                                }
                                                else if (findleftupguai == 1 && findleftdownguai == 0)
                                                {
                                                    uint8 start1 = left_turn_up[0];
                                                    if (start1 >= 68) start1 = 68;

                                                    left_buxian(2,68,left_line[start1],start1);

                                                }
                                                //并列关系
                                                if (findrightdownguai == 1 && findrightupguai == 1)        //找到左下拐点和左上拐点,拟合所需的点是下拐点下面三个点和上拐点上面三个点
                                                {
                                                    uint8 start1 = right_turn_down[0] +2;
                                                    if (start1 >= 68) start1 = 68;

                                                    uint8 start2 = right_turn_up[0];
                                                    if (start2 >= 68) start2 = 68;
                                                    uint8 end2 = right_turn_up[0];
                                                    right_buxian(right_line[start1],start1,right_line[end2],end2);

                                                }
                                                else if (findrightdownguai == 0 && findrightupguai == 1)
                                                {
                                                    int start1 = right_turn_up[0];
                                                    if (start1 >= 68) start1 = 68;

                                                   right_buxian(184,68,right_line[start1],start1);

                                                }
                                             }
                                        }

                                }



                 }
           }


           if((!left_huan_num&&!right_huan_num)&&(three_cross))//为啥左右环判断不是||
           {


                        if(park_flag==1)
                        {

                                   if(sousuojieshuhang<=15)//&&(white_num_col_min_line<165)
                                    {
                                       if( findrightdownguai)   //第二圈
                                       right_buxian(white_num_col_min_line,68-white_num_col[white_num_col_min_line],right_turn_down[1],right_turn_down[0]);
                                     else
                                      right_buxian(white_num_col_min_line,68-white_num_col[white_num_col_min_line],right_line[68],68);
                                       for(int ql=68-white_num_col[white_num_col_min_line]+2;ql>=10;ql--)
                                            {
                                               Left_Line_New[ql]=5;
                                               Right_Line_New[ql]=100;
                                            }
                                 sousuojieshuhang=15;

                                    }
                                   else
                                    {
                                      right_buxian(50,5,right_line[68],68);//68  right_buxian(x1,y1,x2,y2,
                                      sousuojieshuhang=15;
                                    }


                           if (r_start<55)//60
                           {
                             three_cross1=1;
                             uart_putchar(WIRELESS_UART, '6');
                                              uart_putchar(WIRELESS_UART, '4');

                           }
                           if(three_cross1&&r_start>55)//||white_num_col_line>=130&&white_num_col_min_line>=110
                           {
                               three_cross=0;
                               three_cross1=0;
                               uart_putchar(WIRELESS_UART, '6');
                                                uart_putchar(WIRELESS_UART, '5');
                                                uart_putchar(WIRELESS_UART, ' ');
                           }

                        }
                        else if(park_flag==0)
                        {
                            if(sousuojieshuhang<=15)//&&(white_num_col_min_line>20)
                                     {
                                       if(findleftdownguai)  //第一圈
                                              left_buxian(white_num_col_min_line,68-white_num_col[white_num_col_min_line],left_turn_down[1],left_turn_down[0]);
                                              else
                                              left_buxian(white_num_col_min_line,68-white_num_col[white_num_col_min_line],left_line[68],68);
                                                  for(int ql=68-white_num_col[white_num_col_min_line]+2;ql>=10;ql--)
                                                               {
                                                                  Right_Line_New[ql]=180;
                                                                  Left_Line_New[ql]=90;
                                                               }

                                              sousuojieshuhang=15;
                                     }
                            else
                                     {
                                      left_buxian(185,5,left_line[68],68);
                                      sousuojieshuhang=15;
                                    }


                           if(l_start<55)
                           {three_cross1=1;
                           uart_putchar(WIRELESS_UART, '6');
                                            uart_putchar(WIRELESS_UART, '2');

                           }

                           if(three_cross1&&l_start>55)//&&white_num_col_min_line<70
                            {
                               three_cross=0;
                               three_cross1=0;
                               uart_putchar(WIRELESS_UART, '6');
                                                uart_putchar(WIRELESS_UART, '3');    uart_putchar(WIRELESS_UART, ' ');
                            }

                        }

          }




        //在十字里
        if((!left_huan_num&&!right_huan_num)&&(l_start<65&&r_start<65&& abs(l_start - r_start) <= 12)&&times>=5)
         {
                  for (uint8 j = 68; j >= 1; j--)
                      {
                          //左上拐点
                          if ( ((j < (uint8)left_turn_down[0])&&((left_line[j] - left_line[j+3]) >= 10) &&((left_line[j] - left_line[j+2]) >= 10) && ((left_line[j] - left_line[j+1]) >= 10 ))
                              && Left_Add[j] == 0 && Left_Add[j - 1] == 0 && Left_Add[j -2] == 0)
                          {

                              left_turn_up[0] = j-2;//数组里面没有第0行
                              left_turn_up[1] = left_line[j]-2;
                              //获得的上坐标先确定一下是不是比下坐标小，如果小则说明提前断掉，此时的“上拐点”为假.
                              //如果比下坐标大则此时的“上拐点”为真.
                              if (left_turn_up[0] >= left_turn_down[0])
                              {
                                  ;
                              }
                              else break;
                          }
                      }
                      /***找右上拐点***********/
                      for (uint8 j = 68; j >= 1; j--)
                      {
                          if (((j < (uint8)right_turn_down[0])  && right_line[j + 3] - right_line[j] >=20&& right_line[j + 2] - right_line[j] >=20 && right_line[j + 1] - right_line[j] >=20 )
                         && (Right_Add[j] == 0 && Right_Add[j - 1] == 0 && Right_Add[j - 2] == 0))
                          {
                              right_turn_up[0] = j-2 ;
                              right_turn_up[1] = right_line[j-2];
                              if (right_turn_up[0] >= right_turn_down[0])
                              {
                                  ;
                              }
                              else break;
                          }
                      }
                      if (right_turn_up[0]>(sousuojieshuhang)&&right_turn_up[0] < right_turn_down[0] &&right_turn_up[1] <= right_turn_down[1]&&right_turn_up[0] != 0)
                      {

                          findrightupguai = 1;//表示找到右上拐点了

                      }
                      if (left_turn_up[0]>(sousuojieshuhang)&&left_turn_up[0] < left_turn_down[0] &&left_turn_up[1] >= left_turn_down[1]&& left_turn_up[0] != 0)
                      {

                          findleftupguai = 1;//表示找到左上拐点了
                      }
                  /*********开始补线(找到左下拐点和左上拐点  或 找到右下拐点和右上拐点)*********/
                  if ((findleftupguai == 1 && findleftdownguai == 1) || (findrightupguai == 1 && findrightdownguai == 1) || (findrightupguai == 1 && findrightdownguai == 0) || (findleftupguai == 1 && findleftdownguai == 0))
                  {

                      if (findleftupguai == 1 && findleftdownguai == 1)        //找到左下拐点和左上拐点,拟合所需的点是下拐点下面三个点和上拐点上面三个点
                      {
                          uint8 start1 = left_turn_down[0] +2 ;
                          if (start1 >= 68) start1 = 68;

                          uint8 start2 = left_turn_up[0];
                          if (start2 >= 68) start2 = 68;

                          left_buxian(left_line[start1],start1,left_line[start2],start2);



                      }
                      else if (findleftupguai == 1 && findleftdownguai == 0)
                      {
                          uint8 start1 = left_turn_up[0];
                          if (start1 >= 68) start1 = 68;

                          left_buxian(2,68,left_line[start1],start1);

                      }
                      //并列关系
                      if (findrightdownguai == 1 && findrightupguai == 1)        //找到左下拐点和左上拐点,拟合所需的点是下拐点下面三个点和上拐点上面三个点
                      {
                          uint8 start1 = right_turn_down[0] +2;
                          if (start1 >= 68) start1 = 68;
                          uint8 end1 = right_turn_down[0] + 1;
                          uint8 start2 = right_turn_up[0];
                          if (start2 >= 68) start2 = 68;
                          uint8 end2 = right_turn_up[0];
                          right_buxian(right_line[start1],start1,right_line[end2],end2);

                      }
                      else if (findrightdownguai == 0 && findrightupguai == 1)
                      {
                          uint8 start1 = right_turn_up[0];
                          if (start1 >= 68) start1 = 68;
                          uint8 end1 = right_turn_up[0] ;
                         right_buxian(184,68,right_line[start1],start1);

                      }
                   }
           }


     }





void Mid_Line_Repair(uint8 count)
{
           uint8 i;
       for (i = 68; i > count; i--)
        {
//                                    if(lefthuihuan_flag!=2&&youhuihuan_flag==2)
//                                    {
//
//                                                  if(Left_Line_New[i]>2&&Right_Line_New[i]>=184&&!three_cross)
//                                                       {
//                                                         if(Left_Line_New[i]+Half_width[i]>=184)
//                                                          center[i]=184;
//                                                         else
//                                                          center[i]=Left_Line_New[i]+Half_width[i]-30;
//                                                       }
//                                                    else
//                                                     center[i] = ( Left_Line_New[i] + Right_Line_New[i]) / 2-30;    //左右边界都是修复过的,得到中线
//                                    }
//                                    else if(lefthuihuan_flag==2&&youhuihuan_flag!=2)
//                                    {
//
//                                                    if(Left_Line_New[i]<=2&&Right_Line_New[i]<184&&!three_cross)
//                                                    {
//                                                      if(Right_Line_New[i]-Half_width[i]<=2)
//                                                      center[i]=2;
//                                                      else
//                                                      center[i]=Right_Line_New[i]-Half_width[i]+60;
//                                                    }
//                                                    else
//                                                      center[i] = ( Left_Line_New[i] + Right_Line_New[i]) / 2+60;    //左右边界都是修复过的,得到中线
//                                     }
                     //      else
                               {
//                                  if(Left_Line_New[i]<=3&&Right_Line_New[i]<184&&!three_cross
//                                          &&right_huan_num!=7&&left_huan_num!=7
//                                          &&right_huan_num!=3&&left_huan_num!=3)
//                                     {
//                                       if(Right_Line_New[i]-Half_width[i]<=3)
//                                       center[i]=3;
//                                       else
//                                       {
//                                           if(   right_huan_num==8||left_huan_num==8||
//                                                    right_huan_num==9||left_huan_num==9
//                                               )
//                                            center[i]=Right_Line_New[i]-Half_width_yuanshi[i];
//                                            else
//                                            center[i] =  Left_Line_New[i]-Half_width[i];
//                                       }
//                                     }
//                                  else  if(Left_Line_New[i]>3&&Right_Line_New[i]>=184&&!three_cross
//                                          &&right_huan_num!=7&&left_huan_num!=7
//                                          &&right_huan_num!=3&&left_huan_num!=3
//                                          )
//                                     {
//                                       if(Left_Line_New[i]+Half_width[i]>=184)
//                                        center[i]=184;
//                                       else
//                                       {
//
//                                           if(right_huan_num==8||left_huan_num==8||
//                                             right_huan_num==9||left_huan_num==9
//                                              )
//                                            center[i]=Left_Line_New[i]+Half_width_yuanshi[i];
//                                             else
//                                           center[i] = Left_Line_New[i]+Half_width[i];
//                                        }
//                                     }
//                                  else
//                                        center[i] = ( Left_Line_New[i] + Right_Line_New[i]) / 2;    //左右边界都是修复过的,得到中线
//                               }
//                              // center[i] = ( Left_Line_New[i] + Right_Line_New[i]) / 2;
//                               center[i] = range_protect(center[i], 3, 184);//限幅保护
//


                               if(Left_Line_New[i]<=3&&Right_Line_New[i]<184&&!three_cross
                                                        &&right_huan_num!=7&&left_huan_num!=7
                                                      //  &&right_huan_num!=6&&left_huan_num!=6
                                                        &&right_huan_num!=3&&left_huan_num!=3)

                                                   {
                                                     if(Right_Line_New[i]-Half_width[i]<=3)
                                                     center[i]=3;
                                                     else
                                                         if( right_huan_num==8||left_huan_num==8||
                                                                 right_huan_num==9||left_huan_num==9||
                                                                 right_huan_num==1||left_huan_num==1||
                                                                 right_huan_num==2||left_huan_num==2||sousuojieshuhang<=3
                                                        )
                                                     center[i]=Right_Line_New[i]-Half_width_yuanshi[i];//||huihuan_num>15
                                                     else
                                                     center[i] =  Right_Line_New[i]-Half_width[i];
                                                   }
                                                else  if(Left_Line_New[i]>3&&Right_Line_New[i]>=184&&!three_cross
                                                        &&right_huan_num!=7&&left_huan_num!=7
                                                      //  &&right_huan_num!=6&&left_huan_num!=6
                                                        &&right_huan_num!=3&&left_huan_num!=3)
                                                   {
                                                     if(Left_Line_New[i]+Half_width[i]>=184)
                                                      center[i]=184;
                                                     else
                                                    if(right_huan_num==8||left_huan_num==8||
                                                      right_huan_num==9||left_huan_num==9||
                                                      right_huan_num==1||left_huan_num==1||
                                                      right_huan_num==2||left_huan_num==2||sousuojieshuhang<=3//||huihuan_num>15
                                                       )
                                                     center[i]=Left_Line_New[i]+Half_width_yuanshi[i];
                                                      else
                                                    center[i] = Left_Line_New[i]+Half_width[i];
                                                   }
                                                else
                                                      center[i] = ( Left_Line_New[i] + Right_Line_New[i]) / 2;    //左右边界都是修复过的,得到中线
                                             }
                                             center[i] = range_protect(center[i], 3, 184);//限幅保护

                  }

       /******************************************************************曲率计算**************************************************************/
       for (i = 60; i > count; i--)
       {

            if((center[y]-center[y+1])>0)
            qulv_jinduan_right++;
            else
            if((center[y]-center[y+1])<0)
            qulv_jinduan_left++;
       }
          //  qvlv_quanju=abs(qvlv_quanju_right-qvlv_quanju_left);//曲率全局qvlv_quanju qulv_jinduan qulv_yuandaun
            qulv_jinduan=abs(qulv_jinduan_right-qulv_jinduan_left);//曲率近端
          //  qulv_yuandaun=abs(qulv_yuandaun_right-qulv_yuandaun_left);//曲率远端


            regression(0, sousuojieshuhang+3, 65);
                     k_center=parameterB;
        for (i = 68; i > 0; i--)
        {
//          image_use[i][Left_Line_New[i]+3] =0;
//          image_use[i][Right_Line_New[i]-3] =0;
//          image_use[i][center[i]] =0;
                      image_use[i][Left_Line_New[i]+3] =1;
                      image_use[i][Right_Line_New[i]-3] =2;
                      image_use[i][center[i]] =0;
        }
}

float Point_Weight(void)
{
                  char i;
                  Sum=0;
        Weight_Count=0;


//   if (Foresight_Left + 42 < Foresight_Right&&!youhuandao_flag&&!zuohuandao_flag)     //位于直线或小S且没有障碍物
//  {
//          Point = (Foresight_Left + Foresight_Right) / 2; //取左右极值中点作为目标点
//  }
//                 else
//                 {
    if(park_flag==1&&j_flag==0) time_flag1=time_flag,j_flag=1;


      if(park_flag==1&&j_flag==1&&(time_flag-time_flag1)<7)
      {
          for(int i=0;i<70;i++)
              weight_jubu[i]=Weight_park[i];
      }
      else if(left_huan_num!=0||right_huan_num!=0)
      {
          for(int i=0;i<70;i++)
        weight_jubu[i]=Weight_huandao[i];

      }
        else  if(lefthuihuan_flag==1||youhuihuan_flag==1)
        {
        for(int i=0;i<70;i++)
        weight_jubu[i]=Weight_huihuan[i];
        }
      else
      {
          for(int i=0;i<70;i++)
            weight_jubu[i]=Weight[i];
      }





                   if(sousuojieshuhang>= 15)
                    {
                               for (i = 67; i >=sousuojieshuhang+1; i--)        //使用加权平均
                            {

                                             Sum += center[i]* weight_jubu[i];
                                            Weight_Count += weight_jubu[i];


                            }
                            Point = Sum /Weight_Count;
                                   if(Point>184)
                                    Point =184;
                                    if(Point<2)
                                    Point=2;
                    }
                   else
                                 {
                                              for (i = 67; i >=15; i--)        //使用加权平均
                                           {

                                                            Sum += center[i]* weight_jubu[i];
                                                           Weight_Count += weight_jubu[i];


                                           }
                                           Point = Sum /Weight_Count;
                                                  if(Point>184)
                                                   Point =184;
                                                   if(Point<2)
                                                   Point=2;
                                   }
                   Point_last3=Point_last2;
                   Point_last2=Point_last1;
                   Point_last1=Point;

                  Point=Point_last1*0.7+Point_last2*0.2+Point_last3*0.1;



                            /***** 使用最远行数据和目标点作为前瞻 *****/
        if (sousuojieshuhang <25)
        {
            Point_Mid = center[25];
        }
        else
        {
            Point_Mid = center[sousuojieshuhang+1];
        }



    Foresight = 0.8 * (Point_Mid-91)+ 0.2 *(Point-91);

    return  Point;
}




void jieyahuansuan()
    {
      uint8 y=0;
      for(y=69;y>10;y--)
      {
        image_use[y][left_line[y+4]] =0 ; // 1
        image_use[y][right_line[y-4]] =0; // 3
        image_use[y][center[y]] =0;  //2
      }
    }

uint8 range_protect(uint8 duty, uint8 min, uint8 max)//限幅保护
{
    if (duty >= max)
    {
        return max;
    }
    if (duty <= min)
    {
        return min;
    }
    else
    {
        return duty;
    }
}
int32 range_protect2(int32 duty, int32 min, int32 max)//限幅保护
{
    if (duty >= max)
    {
        return max;
    }
    if (duty <= min)
    {
        return min;
    }
    else
    {
        return duty;
    }
}





void star_line_judg()//斑马线检测
    {
    sd_fast=33;
    clc_sd=7;
     baihei_flag=0;
     heibai_flag=0;
      for(kk=left_line[sd_fast-4];kk<=right_line[sd_fast-4];kk++)
      {
        if(image_use[sd_fast][kk]==255)
        {
          bai_flag=1;
          s1=kk;
        }
        else if(bai_flag&&image_use[sd_fast][kk]==0)
        {
          s2=kk;
         if((s2-s1)==1||(s2-s1)==2)
         {
          baihei_flag++;
          bai_flag=0;
         }
         else
          bai_flag=0;
        }

        if(image_use[sd_fast][kk]==0)
        {
          hei_flag=1;
          s3=kk;
        }
        else if(hei_flag&&image_use[sd_fast][kk]==255)
        {
          s4=kk;
          if((s4-s3)==1||(s4-s3)==2)
          {
          heibai_flag++;
          hei_flag=0;
          }
          else
          hei_flag=0;
        }

      }
      if((baihei_flag>=clc_sd&&heibai_flag>=clc_sd))//442
       star_lineflag=1;//改成1停车
    }

void parkcar()
    {
     //   park_flag = 1;
        leijia_flag=1;
      if(star_lineflag)
      {
             if(c_l==1)
        {
        //  pwm_duty(S_MOTOR_PIN,stree_max);     //左边
        }
      else  if(c_l==2)
        {

       //   pwm_duty(S_MOTOR_PIN,stree_min);    //右边
        }
      else  if(c_l==3)
        {
        //  pwm_duty(S_MOTOR_PIN,stree_center);    //中间
        }

      }
    }



uint8 my_adapt_threshold(uint8 *image, uint16 col, uint16 row)   //注意计算阈值的一定要是原图像
{
#define GrayScale 256
    uint16 width = col;
    uint16 height = row;
    int pixelCount[GrayScale];
    float pixelPro[GrayScale];
    int i, j, pixelSum = width * height/4;
    uint8 threshold = 0;
    uint8* data = image;  //指向像素数据的指针
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    uint32 gray_sum=0;
    //统计灰度级中每个像素在整幅图像中的个数
    for (i = 0; i < height; i+=2)
    {
        for (j = 0; j < width; j+=2)
        {
            pixelCount[(int)data[i * width + j]]++;  //将当前的点的像素值作为计数数组的下标
            gray_sum+=(int)data[i * width + j];       //灰度值总和
        }
    }

    //计算每个像素值的点在整幅图像中的比例

    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;

    }

    //遍历灰度级[0,255]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;


        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = 0; j < GrayScale; j++)
        {

                w0 += pixelPro[j];  //背景部分每个灰度值的像素点所占比例之和   即背景部分的比例
                u0tmp += j * pixelPro[j];  //背景部分 每个灰度值的点的比例 *灰度值

               w1=1-w0;
               u1tmp=gray_sum/pixelSum-u0tmp;

                u0 = u0tmp / w0;              //背景平均灰度
                u1 = u1tmp / w1;              //前景平均灰度
                u = u0tmp + u1tmp;            //全局平均灰度
                deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
                if (deltaTmp > deltaMax)
                {
                    deltaMax = deltaTmp;
                    threshold = j;
                }
                if (deltaTmp < deltaMax)
                {
                break;
                }

         }

    return threshold;

}





void regression(int type, int startline, int endline)
{
    int i = 0;
    int sumlines = endline - startline;
    int sumX = 0;
    int sumY = 0;
    float averageX = 0;
    float averageY = 0;
    float sumUp = 0;
    float sumDown = 0;
    if (type == 0)      //拟合中线
    {
        for (i = startline; i < endline; i++)
        {
            sumX += i;
            sumY += center[i];
        }
        if (sumlines != 0)
        {
            averageX = sumX / sumlines;     //x的平均值
            averageY = sumY / sumlines;     //y的平均值
        }
        else
        {
            averageX = 0;     //x的平均值
            averageY = 0;     //y的平均值
        }
        for (i = startline; i < endline; i++)
        {
            sumUp += (center[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        if (sumDown == 0) parameterB = 0;
        else parameterB = sumUp / sumDown;
        parameterA = averageY - parameterB * averageX;
    }
    else if (type == 1)//拟合左线
    {
        for (i = startline; i < endline; i++)
        {
            sumX += i;
            sumY += left_line[i];
        }
        if (sumlines == 0) sumlines = 1;
        averageX = sumX / sumlines;     //x的平均值
        averageY = sumY / sumlines;     //y的平均值
        for (i = startline; i < endline; i++)
        {

            sumUp += (left_line[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        if (sumDown == 0) parameterB = 0;
        else parameterB = sumUp / sumDown;
        parameterA = averageY - parameterB * averageX;
    }
    else if (type == 2)//拟合右线
    {
        for (i = startline; i < endline; i++)
        {
            sumX += i;
            sumY += right_line[i];
        }
        if (sumlines == 0) sumlines = 1;
        averageX = sumX / sumlines;     //x的平均值
        averageY = sumY / sumlines;     //y的平均值
        for (i = startline; i < endline; i++)
        {
            sumUp += (right_line[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        if (sumDown == 0) parameterB = 0;
        else parameterB = sumUp / sumDown;
        parameterA = averageY - parameterB * averageX;

    }
}



void check_starting_line()
 {
     //int[] black_nums_stack = new int[20];
     times2 = 0;
     for (uint8 y = check_line; y <=check_line+5; y++)   //27  32//斑马线识别（如果识别迟了就调小点，识别早了就大点）
     {
         black_blocks = 0;
        cursor = 0;    //指向栈顶的游标
         for (uint8 x = 3; x <= 183; x++)
         {
             if (image_use[y][x] == 0)
             {
                 if (cursor >= 20)
                 {
                     //当黑色元素超过栈长度的操作   break;
                 }
                 else
                 {
                     cursor++;
                 }
             }
             else
             {
                 if (cursor >= 3 && cursor <= 8)
                 {
                     black_blocks++;
                     cursor = 0;
                 }
                 else
                 {
                     cursor = 0;
                 }
             }
         }
         if (black_blocks >= 3 && black_blocks <= 10) times2++;
     }
     if (times2 >= 3 && times2 <= 6)//6
     {
         star_lineflag = 1;

     }
     else
     {
         star_lineflag = 0;
     }
 }




