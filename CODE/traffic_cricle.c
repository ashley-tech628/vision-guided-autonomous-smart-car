#include "headfile.h"

uint8 youhuihuan_flag=0,lefthuihuan_flag=0;
uint8 zuohuandao_flag = 0,zuohuandao_flag2=0,zuohuandao_flag3=0,buxianflag=0;
uint8 zuochu_flag = 0,zuochu_flag2=0;
uint8 youhuandao_flag = 0,youhuandao_flag2= 0,youhuandao_flag3=0,youhuandao_flag4=0,buxianflag2=0;
uint8 youchu_flag = 0,youchu_flag2 = 0;
uint8 zuohuandao_flag_queding = 0;
uint8 m=0,k=0;
uint8 bianzhai=0,biankuan=0;
uint8 cnt2=0;
uint8 line_you=11,line_zuo=11,n1=0,n2=0,n11=0,n22=0;
uint8 jiesu_num1=0,jiesu_num2=0,jiesu_num11=0,jiesu_num22=0;
uint8 huan_leijia=0;

uint8 num_y=0,N1=0,N2=0;
uint8 youhuandao_flag_queding = 0;
uint8 tiao = 10;//调变点
uint8 right_turn_middle[2]={0};
uint8  left_turn_middle[2]={0};
uint8 leftx=0,lefty=0,rightx=0,righty=0,left_lianjiedian_x,left_lianjiedian_y,right_lianjiedian_x,right_lianjiedian_y;
uint8 left_huan_num=0,right_huan_num=0;
uint8 fine1=0,fine2=0;
uint8 flag_find_huan_rightmiddle_point=0;
uint8 flag_find_huan_leftmiddle_point=0;
uint8 flag_find_huan_leftup_point=0;
uint8 flag_find_huan_rightup_point=0;
extern uint8 right_turn_up[2];
void find_rightup_point(uint8 start_point, uint8 end_point)
{
    uint8 j;

    for (j = end_point; j >=start_point; j--)
        {
         /***找右上拐点***********/

            if (((j < (uint8)right_turn_down[0])   && right_line[j + 1] - right_line[j-1] >=40&& right_line[j + 2] - right_line[j-2] >=40 && right_line[j + 3] - right_line[j-3] >=40 )
              //     &&right_line[j + 1]>160&&right_line[j + 2]>160&&right_line[j + 3]>160
                    && (Right_Add[j-1] == 0 && Right_Add[j - 2] == 0 && Right_Add[j - 3] == 0))
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

}
void find_rightup_point2(uint8 start_point, uint8 end_point)
{
    uint8 j;

    for (j = start_point; j <=end_point; j++)
        {
         /***找右上拐点***********/

            if (((j < (uint8)right_turn_down[0])  && right_line[j + 3] - right_line[j-3] >=30&& right_line[j + 4] - right_line[j-4] >=30 && right_line[j + 5] - right_line[j-5] >=30 )
                    &&right_line[j + 3]>170&&right_line[j + 4]>170&&right_line[j + 5]>170
                    && (Right_Add[j-3] == 0 && Right_Add[j - 4] == 0 && Right_Add[j - 5] == 0))
            {
                right_turn_up[0] = j-3 ;
                right_turn_up[1] = right_line[j-3];
                flag_find_huan_rightup_point=1;
                if (right_turn_up[0] >= right_turn_down[0])
                {
                    ;
                }
                else break;
            }
        }

}
void find_rightup_point3(uint8 start_point, uint8 end_point)
{
    uint8 j;

    for (j = start_point; j <=end_point; j++)
        {
         /***找右上拐点***********/

            if (((j < (uint8)right_turn_down[0])  && right_line[j + 3] - right_line[j-3] >=15&& right_line[j + 4] - right_line[j-4] >=15 && right_line[j + 5] - right_line[j-5] >=15 )
                    &&right_line[j + 3]>180&&right_line[j + 4]>180&&right_line[j + 5]>180
                    && (Right_Add[j-3] == 0 && Right_Add[j - 4] == 0 && Right_Add[j - 5] == 0))
            {
                right_turn_up[0] = j-3 ;
                right_turn_up[1] = right_line[j-3];
                flag_find_huan_rightup_point=1;
                if (right_turn_up[0] >= right_turn_down[0])
                {
                    ;
                }
                else break;
            }
        }

}
void find_leftup_point2(uint8 start_point, uint8 end_point)
{
    uint8 j;

    for (j = start_point; j <=end_point; j++)
        {
         /***找右上拐点***********/

            if (((j < (uint8)left_turn_down[0])  && left_line[j - 3] - left_line[j+3] >=30&& left_line[j -4] - left_line[j+4] >=30 && left_line[j - 5] - left_line[j+5] >=30 )
                    &&left_line[j + 3]<15&&left_line[j + 4]<15&&left_line[j + 5]<15
                    && (Left_Add[j-3] == 0 && Left_Add[j - 4] == 0 && Left_Add[j - 5] == 0))
            {
                left_turn_up[0] = j-3 ;
                left_turn_up[1] = left_line[j-3];
                flag_find_huan_leftup_point=1;
                if (left_turn_up[0] >= left_turn_down[0])
                {
                    ;
                }
                else break;
            }
        }

}
void find_leftup_point3(uint8 start_point, uint8 end_point)
{
    uint8 j;

    for (j = start_point; j <=end_point; j++)
        {
         /***找右上拐点***********/

            if (((j < (uint8)left_turn_down[0])  && left_line[j - 3] - left_line[j+3] >=15&& left_line[j -4] - left_line[j+4] >=15 && left_line[j - 5] - left_line[j+5] >=15 )
                    &&left_line[j + 3]<30&&left_line[j + 4]<30&&left_line[j + 5]<30
                    && (Left_Add[j] == 0 && Left_Add[j - 1] == 0 && Left_Add[j - 2] == 0))
            {
                left_turn_up[0] = j-3 ;
                left_turn_up[1] = left_line[j-3];
                flag_find_huan_leftup_point=1;
                if (left_turn_up[0] >= left_turn_down[0])
                {
                    ;
                }
                else break;
            }
        }

}
void find_rightmiddle_point(uint8 start_point, uint8 end_point)
{
    uint8 i;
    for (i = start_point; i >= end_point; i--)
    {
        //找you拐点
        if (i <= 67&& (right_line[i - 6] - right_line[i-1 ]) >=0&& (right_line[i - 6] - right_line[i-1 ]) <=10
                &&(right_line[i -4] - right_line[i ]) >= 0 &&(right_line[i  -4] - right_line[i]) <=10
                &&(right_line[i +4] - right_line[i ]) >= 0 &&(right_line[i  +4] - right_line[i]) <=10
                && (right_line[i + 6] - right_line[i ]) >=0 && (right_line[i + 6] - right_line[i ]) <=10
                && right_line[i + 6]>=right_line[i +2]&& right_line[i - 6]>=right_line[i -2]
                && right_line[i ] <180&& right_line[i-2] <180&& right_line[i -6] <180&& right_line[i + 2] <180&& right_line[i + 6] <180
            )
        {
            right_turn_middle[0] = (uint8)(i );
            right_turn_middle[1] = right_line[i ];
            flag_find_huan_rightmiddle_point = 1;
            break;
        }
    }

}
void find_leftup_point(uint8 start_point, uint8 end_point)
{
    uint8 j;

    for (j =end_point ; j >=start_point; j--)
        {
         /***找右上拐点***********/

        if (((j < (uint8)left_turn_down[0])  && left_line[j - 1] - left_line[j+1] >=40&& left_line[j -2] - left_line[j+2] >=40 && left_line[j - 3] - left_line[j+3] >=40 )
                          //  &&left_line[j + 1]<30&&left_line[j + 2]<30&&left_line[j + 3]<30
                            && (Left_Add[j-1] == 0 && Left_Add[j - 2] == 0 && Left_Add[j - 3] == 0))
                    {
                        left_turn_up[0] = j-2 ;
                        left_turn_up[1] = left_line[j-2];
                        flag_find_huan_leftup_point=1;
                        if (left_turn_up[0] >= left_turn_down[0])
                        {
                            ;
                        }
                        else break;
                    }
        }

}

void find_leftmiddle_point(uint8 start_point, uint8 end_point)
{
    uint8 i;
    for (i = start_point; i >= end_point; i--)
    {
        //找you拐点
        if (i <= 67 && (left_line[i - 1] - left_line[i - 3]) >=0&& (left_line[i - 1] - left_line[i - 3]) <=4
                    &&(left_line[i ] - left_line[i -2]) >= 0 &&(left_line[i ] - left_line[i -2]) <=4
                    && (left_line[i + 1] - left_line[i + 3]) >=0 && (left_line[i + 1] - left_line[i + 3]) <=4

                    && left_line[i -1] >5&& left_line[i] >5&& left_line[i + 1] >5&& left_line[i + 2] >5&& left_line[i + 3] >5
            )
        {
            left_turn_middle[0] = (uint8)(i - 1);
            left_turn_middle[1] = left_line[i - 1];
            flag_find_huan_leftmiddle_point = 1;
            break;
        }
    }

}
void left_buxian(uint8 x1,uint8 y1,uint8 x2,uint8 y2)//左补线（环岛）
     {
       uint8 i,max,a1,a2,hx;
      a1=y1;
      a2=y2;
      if(a1>a2)
      {max=a1;
      a1=a2;
      a2=max;}
    for(i=a1;i<a2;i++)
      {

        hx=(i-y1)*(x2-x1)/(y2-y1)+x1;
        if(hx>=184)hx=184;
        if(hx<=2)hx=2;
          Left_Line_New[i]=hx;

      }
    }
void left_buxian2(uint8 x1,uint8 y1,uint8 x2,uint8 y2)//左补线（环岛）
     {
       uint8 i,max,a1,a2,hx;
      a1=y1;
      a2=y2;
      if(a1>a2)
      {max=a1;
      a1=a2;
      a2=max;}
    for(i=a1;i<a2;i++)
      {

        hx=(i-y1)*(x2-x1)/(y2-y1)+x1;
        if(hx>=184)hx=184;
        if(hx<=2)hx=2;
          Right_Line_New[i]=hx;

      }
    }
void right_buxian2(uint8 x1,uint8 y1,uint8 x2,uint8 y2)//右补线（环岛）
     {
      uint8 i,max,a1,a2,hx;
      a1=y1;
      a2=y2;
      if(a1>a2)
      {max=a1;
      a1=a2;
      a2=max;}
    for(i=a1;i<a2;i++)
      {

        hx=(i-y1)*(x2-x1)/(y2-y1)+x1;
        if(hx>=184)hx=184;
        if(hx<=2)hx=2;
          Left_Line_New[i]=hx;

      }
    }


void right_buxian(uint8 x1,uint8 y1,uint8 x2,uint8 y2)//右补线（环岛）
     {
      uint8 i,max,a1,a2,hx;
      a1=y1;
      a2=y2;
      if(a1>a2)
      {max=a1;
      a1=a2;
      a2=max;}
    for(i=a1;i<a2;i++)
      {

        hx=(i-y1)*(x2-x1)/(y2-y1)+x1;
        if(hx>=184)hx=184;
        if(hx<=2)hx=2;
          Right_Line_New[i]=hx;

      }
    }


void youhuandao_deal()//环岛处理
{
    uint8 y=0;
    find_rightdown_point(65,1,2);
    find_rightmiddle_point(right_turn_down[0]-5,22);
    find_rightup_point(10,65);
  if(right_huan_num==1)
  {

    //if(flag_find_huan_rightmiddle_point)
    //{
    //  right_buxian(right_turn_middle[1],right_turn_middle[0],160,right_turn_down[0]);
    //  flag_find_huan_rightmiddle_point=0;
    //}
      right_buxian(left_line[20]+55,20,155,68);
  }
  if(right_huan_num==2)
  {
    //if(flag_find_huan_rightmiddle_point)
   // {
    //  right_buxian(right_turn_middle[1],right_turn_middle[0],160,68);
    //   flag_find_huan_rightmiddle_point=0;
   // }
      right_buxian(left_line[20]+55,20,155,68);
  }
    if(right_huan_num==3)
  {
//       if(right_turn_up[0]>=18)
//      {right_buxian2(right_turn_up[1]+26,right_turn_up[0],left_line[68],68);
//      sousuojieshuhang=right_turn_up[0];
//      }

             if(right_turn_up[0]>=13)
               right_buxian2(right_turn_up[1]+28,right_turn_up[0],left_line[68],68);
                 for(int ql=right_turn_up[0];ql>=10;ql--)
                  {
                     Right_Line_New[ql]=180;
                     Left_Line_New[ql]=140;
                  }

  }
    if(right_huan_num==4)
  {
     // right_buxian2(right_turn_up[1],right_turn_up[0],left_line[68],68);
       for(int ql=68;ql>=17;ql--)
      {
         Right_Line_New[ql]=184;
      }

      for(y = 68;y >5;y--)    //x是减59—56  num是加0—4
        {

            for(uint8 x = 170;x >= 1 ; x--)            //中间向左找跳变
            {
              if(image_use[y][x-1] == 0 &&image_use[y][x] == 0 &&  image_use[y][x+1] == 255&&  image_use[y][x+2] == 255)  //两个连续黑点触发
                {
                    Left_Line_New[y]=x+1;
                    break;
                }
              else if(x+1==2)                 //到最左边了都没扫到黑点
                {
                     Left_Line_New[y]=x+1;
                    break;
                }
            }

                                  if(abs(Right_Line_New[y]-Left_Line_New[y])<3)
                                        break;
                                  if(image_use[y][(Left_Line_New[y]+Right_Line_New[y])/2]==0)
                                        break;
                                  if(y<=1)
                                    break;

        }

                 sousuojieshuhang=y+2;


  }
  if(right_huan_num==5)
  {
      for(int ql=68;ql>=17;ql--)
        {
           Right_Line_New[ql]=184;
        }
      for( y = 68;y >5;y--)    //x是减59—56  num是加0—4
        {
          for(uint8 x = 170;x <=184;x++)    //中间向右找跳变
            {
              if(image_use[y][x-1] == 255&&image_use[y][x] == 255&& image_use[y][x+1] == 0 && image_use[y][x+2] == 0 )  //两个连续黑点触发
                {

                   Right_Line_New[y]=x;
                   break;
                }
                else if(x==184)       //到最右边了都没扫到黑点a
                {

                    Right_Line_New[y]=x;


                    break;
                }
            }

            for(uint8 x = 170;x >= 1 ; x--)            //中间向左找跳变
            {
              if(image_use[y][x-1] == 0 &&image_use[y][x] == 0 &&  image_use[y][x+1] == 255&&  image_use[y][x+2] == 255)  //两个连续黑点触发
                {
                    Left_Line_New[y]=x+1;
                    break;
                }
              else if(x+1==2)                 //到最左边了都没扫到黑点
                {
                     Left_Line_New[y]=x+1;
                    break;
                }
            }
                  if(abs(Right_Line_New[y]-Left_Line_New[y])<3)
                        break;
                  if(image_use[y][(Right_Line_New[y]+Left_Line_New[y])/2]==0)
                        break;
                  if(y<=1)
                    break;
           }
             sousuojieshuhang=y+2;
             left_buxian(Right_Line_New[sousuojieshuhang]-30,sousuojieshuhang,30,68);
  }
    if(right_huan_num==7)
  {
    find_leftdown_point(65,20,1);   //1是十字
      right_buxian2(140,sousuojieshuhang,left_turn_down[1],left_turn_down[0]);
  }

    if(right_huan_num==8)
     {

       right_buxian(left_line[20]+55,20,170,68);

     }

}

void zuohuandao_deal()//环岛处理
{
    uint8 y=0;
    find_leftdown_point(65,1,2);
    find_leftmiddle_point(left_turn_down[0]-5,22);
    find_leftup_point(10,65);
  if(left_huan_num==1)
  {

    //if(flag_find_huan_leftmiddle_point)
    //{
    //  left_buxian(left_turn_middle[1],left_turn_middle[0],30,68);
   //   flag_find_huan_leftmiddle_point=0;
   // }
   // else
    {
         left_buxian(right_line[20]-55,20,30,68);
       //  flag_find_huan_leftmiddle_point=0;
       }
  }
  if(left_huan_num==2)
  {
   // if(flag_find_huan_leftmiddle_point)
   // {
   //     left_buxian(left_turn_middle[1],left_turn_middle[0],30,68);
  //      flag_find_huan_leftmiddle_point=0;
  //  }
   // else
     {
         left_buxian(right_line[20]-55,20,30,68);
        //  flag_find_huan_leftmiddle_point=0;
        }
  }
    if(left_huan_num==3)
  {

     //  if(left_turn_up[0]>=20)//21
   //  {
    //       left_buxian2(left_turn_up[1]-15,left_turn_up[0],160,68);
   //        sousuojieshuhang=left_turn_up[0];
    //  }



       if(left_turn_up[0]>=16)//21
      {
           left_buxian2(left_turn_up[1]-25,left_turn_up[0],170,68);

           for(int ql=left_turn_up[0];ql>=10;ql--)
            {
               Left_Line_New[ql]=5;
               Right_Line_New[ql]=120;
            }

     }

  }
    if(left_huan_num==4)
  {
     // right_buxian2(right_turn_up[1],right_turn_up[0],left_line[68],68);
       for(int ql=68;ql>=17;ql--)
      {
         Left_Line_New[ql]=2;
         center[ql]=10;
      }

      for(y = 68;y >5;y--)    //x是减59—56  num是加0—4
      {
                   for(uint8 x =10;x <=184;x++)    //中间向右找跳变
                     {
                       if(image_use[y][x-1] == 255&&image_use[y][x] == 255&& image_use[y][x+1] == 0 && image_use[y][x+2] == 0 )  //两个连续黑点触发
                         {

                            Right_Line_New[y]=x;

                            break;
                         }
                         else if(x==184)       //到最右边了都没扫到黑点a
                         {

                             Right_Line_New[y]=x;



                             break;
                         }
                     }

                                  if(abs(Right_Line_New[y]-Left_Line_New[y])<3)
                                        break;
                                  if(image_use[y][(Left_Line_New[y]+Right_Line_New[y])/2]==0)
                                        break;
                                  if(y<=1)
                                    break;

        }

      for (uint8 j = 18; j <=60; j++)
       {
           if (( Right_Line_New[j + 3] - Right_Line_New[j] >=20&& Right_Line_New[j + 2] - Right_Line_New[j] >=20 && Right_Line_New[j + 1] - Right_Line_New[j] >=20 )
              )
           {
               right_turn_up[0] = j-2 ;
               right_turn_up[1] = Right_Line_New[j-2];
               if (right_turn_up[0] >= right_turn_down[0])
               {
                   ;
               }
               else break;
           }
       }
      right_buxian(right_turn_up[1],right_turn_up[0],Right_Line_New[68],68);

                 sousuojieshuhang=y+2;


  }
  if(left_huan_num==5)
  {
      for(int ql=68;ql>=17;ql--)
          {
             Left_Line_New[ql]=2;
             center[ql]=10;
          }

      for( y = 68;y >5;y--)    //x是减59—56  num是加0—4
        {
          for(uint8 x = 20;x <=184;x++)    //中间向右找跳变
            {
              if(image_use[y][x-1] == 255&&image_use[y][x] == 255&& image_use[y][x+1] == 0 && image_use[y][x+2] == 0 )  //两个连续黑点触发
                {

                   Right_Line_New[y]=x;

                   break;
                }
                else if(x==184)       //到最右边了都没扫到黑点a
                {

                    Right_Line_New[y]=x;


                    break;
                }
            }

            for(uint8 x = 20;x >= 1 ; x--)            //中间向左找跳变
            {
              if(image_use[y][x-1] == 0 &&image_use[y][x] == 0 &&  image_use[y][x+1] == 255&&  image_use[y][x+2] == 255)  //两个连续黑点触发
                {
                    Left_Line_New[y]=x+1;
                    break;
                }
              else if(x+1==2)                 //到最左边了都没扫到黑点
                {
                     Left_Line_New[y]=x+1;
                    break;
                }
            }
                  if(abs(Right_Line_New[y]-Left_Line_New[y])<3)
                        break;
                  if(image_use[y][(Right_Line_New[y]+Left_Line_New[y])/2]==0)
                        break;
                  if(y<=1)
                    break;
           }
             sousuojieshuhang=y+2;
             right_buxian(Left_Line_New[sousuojieshuhang]+30,sousuojieshuhang,160,68);
  }

    if(left_huan_num==7)
  {
    find_rightdown_point(65,25,1);   //1是十字
    left_buxian2(45,sousuojieshuhang,right_turn_down[1],right_turn_down[0]);//40
  }
    if(left_huan_num==8)
   {

    left_buxian(right_line[20]-55,20,10,68);
   }
}

void youhuandao()//右环岛
    {

      if(!youhuihuan_flag&&!left_huan_num&&!three_cross&&!poer_flag)//
     {

             right_turn_down[0]=69;
           if(!youhuandao_flag_queding)
          {
              m=Right_Add_num-Left_Add_num;
              if(right_huan_num==0&&!right_huan_num&&(m>11)&&sousuojieshuhang<=3&&l_start>= 60&&r_start>= 60&&(Right_Add_num>=15)&&(Left_Add_num<=3)&&(zuodiuxianshu<3)&&(youdiuxianshu>15)&&k_left<-0.25&&k_left>-1.25)
              {//&&k_right>0.6&&k_right<2.0&&k_left<-0.6&&k_left>-2.0
                youhuandao_flag = 1 ;
                right_huan_num=1;
                uart_putchar(WIRELESS_UART, '2');
                 uart_putchar(WIRELESS_UART, '1');
                 time3=0;
              }
              if(right_huan_num==1&&l_start>= 65&&r_start<=45)//&&(ad_guiyi[2]>100||ad_guiyi[0]>100)
              {
               right_huan_num=2;
               uart_putchar(WIRELESS_UART, '2');
                               uart_putchar(WIRELESS_UART, '2');
                  time3=0;
              }
//                        if(time3>50&&(right_huan_num==1||right_huan_num==2))
//                  {
//
//                      right_huan_num=0;
//                      youhuandao_flag=0;
//                   }

              if(right_huan_num==2)
              {
                  find_rightmiddle_point(50,20);
                 guaidian= right_turn_middle[0];
              }
             if(right_huan_num==2&&r_start>= 67&&guaidian>=40)//l_start>= 50&&r_start<=35
              {
                 cnt2++;   //连续3次判定
              }else  cnt2=0;

             if(cnt2>=2)
                 {
                 right_huan_num=3;
              uart_putchar(WIRELESS_UART, '2');
                                uart_putchar(WIRELESS_UART, '3');
                                cnt2=0;
                 }
            // bianzhai=0;
            //   biankuan=0;
            // guaidian=0;
               find_rightup_point(10,65);
/*               if(right_huan_num==21&&(zuodiuxianshu<3)&&(youdiuxianshu>15))
                   right_huan_num=3;*/
               if(right_huan_num==3&&right_turn_up[0]>=45)//>30)//right_turn_up[0]////right_huan_num==3&&r_start<=40
              {
                   guaidian=0;
               right_huan_num=4;  //更换搜线方式
               uart_putchar(WIRELESS_UART, '2');
                              uart_putchar(WIRELESS_UART, '4');//&&r_start<=40
              }
               if(right_huan_num==4&&!youhuandao_flag_queding)
              {
                right_huan_num=5;//进环了
               youhuandao_flag_queding=1;
               uart_putchar(WIRELESS_UART, '2');
                              uart_putchar(WIRELESS_UART, '5');
              }


              } //左环岛入环   可以把搜索结束行到跳变点这


                  if(youhuandao_flag_queding)
                  {
                       if(right_huan_num==5&&white_num_col_line>125)
                        {
                           right_huan_num=6;
                           uart_putchar(WIRELESS_UART, '2');
                                            uart_putchar(WIRELESS_UART, '6');
                        }
                       find_rightdown_point(65,22,2);

                       if(right_huan_num==6&&Left_Add_num>15&&left_turn_down[0]>35&&left_turn_down[0]!=69)//&&left_turn_down[0]<50

                                          {
                                             right_huan_num=7;
                                             uart_putchar(WIRELESS_UART, '2');
                                                              uart_putchar(WIRELESS_UART, '7');
                                          }
                                        //  right_turn_up[0]=0;
                                       //   find_rightup_point(16,65);
          if(right_huan_num==7&&sousuojieshuhang<=4&&zuodiuxianshu<5&&Left_Add_num<6)//&&k_left>-1.5&&zuodiuxianshu<5
          {
              right_huan_num=8;//&&white_num_col[93]>50
              uart_putchar(WIRELESS_UART, '2');
                                                                           uart_putchar(WIRELESS_UART, '8');
          }
          if(right_huan_num==8&&r_start<60)
              {right_huan_num=9;
              uart_putchar(WIRELESS_UART, '2');
                                                                                        uart_putchar(WIRELESS_UART, '9');
              }

                                             if(right_huan_num==9&&l_start>60&&r_start>60)
                                             {

                                                  youhuandao_flag = 0;
                                                  youhuandao_flag_queding = 0;
                                                  youhuandao_flag2=0;
                                                  right_huan_num=0;
                                                  time2=0;
                                                  youhuandao_flag3=0;
                                                  uart_putchar(WIRELESS_UART, ' ');
                                              }



                 }
             }
      youhuandao_deal();
    }


void  you_huihuan()
{

    if(right_huan_num==2&&r_start<60&&youhuihuan_flag==0&&sousuojieshuhang>5&&huihuan_num<5)
    {

        find_rightup_point2(20,65);
        if(flag_find_huan_rightup_point)  //可以连续三次检测回环  加三次
           {
            youhuihuan_flag=1;
            flag_find_huan_rightup_point=0;
            right_huan_num=0;
            uart_putchar(WIRELESS_UART, '8');
             uart_putchar(WIRELESS_UART, '3');

           }

    }
//    else if(youhuihuan_flag==0&&right_huan_num==0&&sousuojieshuhang<10&&r_start<49&&l_start>62&&youdiuxianshu>17&&zuodiuxianshu<1)
//    {
//
//        find_rightup_point3(30,65);
//        if(flag_find_huan_rightup_point)  //可以连续三次检测回环  加三次
//            {
//            youhuihuan_flag=1;
//             flag_find_huan_rightup_point=0;
//              uart_putchar(WIRELESS_UART, '8');
//                     uart_putchar(WIRELESS_UART, '4');
//
//            }
//
//
//     }
    if(youhuihuan_flag==1&&Left_Add_num>15&&zuodiuxianshu>15&&youdiuxianshu>15)//&&Left_Add_num>29
    {
        {youhuihuan_flag=2;
                     uart_putchar(WIRELESS_UART, '8');
                             uart_putchar(WIRELESS_UART, '4');
        }
     }
    if(youhuihuan_flag==2)
    {
           for(int ql=68;ql>=10;ql--)
        {
           Left_Line_New[ql]=6;
           Right_Line_New[ql]=70;
        }
    }
    if(youhuihuan_flag==2&&r_start>67&&sousuojieshuhang<=3)
    {
        youhuihuan_flag=0;
      left_huan_num=1;
      uart_putchar(WIRELESS_UART, '3');
                                 uart_putchar(WIRELESS_UART, '1');
       uart_putchar(WIRELESS_UART, ' ');
    }
}

void  zuo_huihuan()
{

    if(left_huan_num==2&&l_start<60&&lefthuihuan_flag==0&&sousuojieshuhang>5&&huihuan_num<5)//
    {

        find_leftup_point2(20,65);
       if(flag_find_huan_leftup_point)  //可以连续三次检测回环  加三次
           { uart_putchar(WIRELESS_UART, '8');
        uart_putchar(WIRELESS_UART, '1');
            lefthuihuan_flag=1;
            flag_find_huan_leftup_point=0;
            left_huan_num=0;
           }


    }
//    else if(left_huan_num==0&&lefthuihuan_flag==0&&sousuojieshuhang<10&&l_start<49&&r_start>62&&zuodiuxianshu>17&&youdiuxianshu<1)
//    {
//
//        find_leftup_point3(30,65);
//       if(flag_find_huan_leftup_point)  //可以连续三次检测回环  加三次
//           {
//           uart_putchar(WIRELESS_UART, '8');
//          uart_putchar(WIRELESS_UART, '2');
//            lefthuihuan_flag=1;
//            flag_find_huan_leftup_point=0;
//
//           }
//
//
//    }
    if(lefthuihuan_flag==1&&Right_Add_num>15&&left_huan_num==0&&zuodiuxianshu>15&&youdiuxianshu>15)
        {lefthuihuan_flag=2;
        }
    if(lefthuihuan_flag==2)
     {
            for(int ql=68;ql>=10;ql--)
         {
            Left_Line_New[ql]=130;
            Right_Line_New[ql]=180;
         }
     }
    if(lefthuihuan_flag==2&&sousuojieshuhang<=3&&l_start>67)
    {
        lefthuihuan_flag=0;
        uart_putchar(WIRELESS_UART, ' ');
    }
}
void zuohuandao()//zuo环岛
    {

      if(!lefthuihuan_flag&&!right_huan_num&&!three_cross&&!poer_flag)//
     {

          left_turn_down[0]=69;
           if(!zuohuandao_flag_queding)
          {
              m=Left_Add_num-Right_Add_num;//
              if(!left_huan_num&&left_huan_num==0&&(m>11)&&sousuojieshuhang<=3&&l_start>= 60&&r_start>= 60&&(Left_Add_num>=15)&&(Right_Add_num<=3)&&(zuodiuxianshu>15)&&(youdiuxianshu<3)&&k_right>0.25&&k_right<1.25)
              {//&&k_right>0.7&&k_right<2.0&&k_left<-0.7&&k_left>-2.0
                zuohuandao_flag = 1 ;
                left_huan_num=1;
                time1=0;
                uart_putchar(WIRELESS_UART, '3');
                                                            uart_putchar(WIRELESS_UART, '1');
              }
              if(left_huan_num==1&&r_start>= 65&&l_start<=50)//&&(ad_guiyi[2]>100||ad_guiyi[0]>100)
              {
                  time1=0;
                  uart_putchar(WIRELESS_UART, '3');
                       uart_putchar(WIRELESS_UART, '2');
                  left_huan_num=2;
              }

//              if(time1>150&&(left_huan_num==1||left_huan_num==2))//80
//                                  {
//                                      time1=0;
//                                   left_huan_num=0;
//                                   zuohuandao_flag=0;
//                                  }
                           //  guaidian=0;
                              if(left_huan_num==2)
                              { find_leftmiddle_point(50,20);
                           guaidian= left_turn_middle[0];
                              }


               if(left_huan_num==2&&l_start>=67&&guaidian>35)//35//
               {
                           cnt2++;   //连续3次判定
                        }else  cnt2=0;

               if(cnt2>=3)
               {  cnt2=0;
                             //left_huan_num=21;
               left_huan_num=3;
                uart_putchar(WIRELESS_UART, '3');             uart_putchar(WIRELESS_UART, '3');
                           }
//               if(left_huan_num==21&&(zuodiuxianshu>15)&&(youdiuxianshu<3))
//                   left_huan_num=3;

                          guaidian=0;
               find_leftup_point(10,65);
               if(left_huan_num==3&&(left_turn_up[0]>=45))//>30)//right_turn_up[0]////right_huan_num==3&&r_start<=40
              {
                   left_huan_num=4;  //更换搜线方式
                   uart_putchar(WIRELESS_UART, '3');
                   uart_putchar(WIRELESS_UART, '4');
              }
               if(left_huan_num==4&&!zuohuandao_flag_queding)
              {
                   left_huan_num=5;//进环了
                   zuohuandao_flag_queding=1;
                   uart_putchar(WIRELESS_UART, '3');
                   uart_putchar(WIRELESS_UART, '5');
              }


              } //左环岛入环   可以把搜索结束行到跳变点这


                  if(zuohuandao_flag_queding)
                  {
                       if(left_huan_num==5&&(white_num_col_line<85))
                        {
                           left_huan_num=6;
                           uart_putchar(WIRELESS_UART, '3');
                                                                       uart_putchar(WIRELESS_UART, '6');
                        }
                       find_rightdown_point(65,22,2);

                       if(left_huan_num==6&&Right_Add_num>20&&right_turn_down[0]>32&&right_turn_down[0]!=69)
                                             {
                                                 left_huan_num=7;
                                                 uart_putchar(WIRELESS_UART, '3');
                                                        uart_putchar(WIRELESS_UART, '7');
                                             }
                                             if(left_huan_num==7&&sousuojieshuhang<=4&&youdiuxianshu<2&&Right_Add_num<3)//&&white_num_col[93]>50
                                             {
                                                 left_huan_num=8;
                                                 uart_putchar(WIRELESS_UART, '3');
                                                uart_putchar(WIRELESS_UART, '8');
                                             }
                                             if(left_huan_num==8&&l_start<60)
                                                 left_huan_num=9;

                                            // find_leftup_point(18,65);
                                                 if(left_huan_num==9&&l_start>67&&r_start>67)
                                                 {
                                                  cnt2++;
                                                  cnt2=0;
                                                    zuohuandao_flag = 0;
                                                    zuohuandao_flag_queding = 0;
                                                    zuohuandao_flag2=0;
                                                    left_huan_num=0;
                                                    time7=0;
                                                    zuohuandao_flag3=0;
                                                    uart_putchar(WIRELESS_UART, ' ');
                                                 }




                 }
             }
      zuohuandao_deal();
    }


//【Function7】找右中拐点函数
//输入： start点 end点
//void find_rightmiddle_point(uint8 start_point, uint8 end_point)
//{
//    uint8 i;
//    for (i = start_point; i <= end_point; i--)
//    {
//        //找you拐点
//        if (i >= 8 && (right_line[i + 5] - right_line[i + 1]) > 0 && (right_line[i + 4] - right_line[i + 1]) > 0 && (right_line[i + 3] - right_line[i + 1]) > 0
//            && (right_line[i + 5] - right_line[i + 4]) >= 0 && (right_line[i + 4] - right_line[i + 3]) >= 0 && (right_line[i - 3] - right_line[i - 2]) >= 0
//            && (right_line[i - 4] - right_line[i + 1]) >= 0 && (right_line[i - 3] - right_line[i + 1]) >= 0 && (right_line[i - 2] - right_line[i + 1]) >= 0
//            && (right_line[i - 4] - right_line[i - 3]) >= 0 && (right_line[i - 3] - right_line[i - 2]) >= 0
//            )
//        {
//            right_turn_middle[0] = (uint8)(i - 1);
//            right_turn_middle[1] = right_line[i - 1];
//            flag_find_huan_rightmiddle_point = 1;
//            break;
//        }
//    }
//
//}
