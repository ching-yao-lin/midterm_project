#include <iostream>
#include <cmath>

using namespace std;
const int OUTCOME_MAX_NUM = 70;
const double criticalPoint = 500;

double RiskCal(double Xi, double Yi, int RiskCnt, int RiskX[], int RiskY[], int RiskR[], int RiskP[]);
double AllRisk(int n, double& FragDistance, int Ini_Xs, int Ini_Ys, int Ini_Xt, int Ini_Yt, \
int Xs, int Ys, int Xt, int Yt, int RiskCnt, int RiskX[], int RiskY[], int RiskR[], int RiskP[], int tpX[], int tpY[]);
void findPoint (float x , float y , int n , int num, int[], int[]);
double slope(float x1, float y1, float x2, float y2);

/* 測資
6 3 1 10
2 5 4
5 4 2
2 3 2
2 1 2
1 1 5 5
*/
struct PointDouble
{
    double x;
    double y;
};
int main()
{

    int n = 0, m = 0, w = 0, d = 0;
    cin >> n >> m >> w >> d;

    int* X = new int[m]; // the x coordinate of all threatPoints in order
    int* Y = new int[m]; // the y coordinate of all threatPoints in order
    int* R = new int[m];
    int* P = new int[m];
    int Xs = 0, Ys = 0, Xt = 0, Yt = 0;
    for(int i = 0; i < m; i++)
    {
        cin >> X[i];
    }
    for(int i = 0; i < m; i++)
    {
        cin >> Y[i];
    }
    for(int i = 0; i < m; i++)
    {
        cin >> R[i];
    }
    for(int i = 0; i < m; i++)
    {
        cin >> P[i];
    }
    cin >> Xs >> Ys >> Xt >> Yt;

    /*** test ***/
    cout << "< test >:" << endl;
    cout << n << " " << m << " " << w << " " << d << endl;
    for(int i = 0; i < m; i++)
    {
        cout << "Threat point " << i << ":\t("<< X[i] << "," << Y[i] << ")";
        cout << "\tRadius : " << R[i] << "\tpower :\t"  << P[i] << " " << endl;
    }
    cout << "Start: (" << Xs << "," << Ys << ")\tTerminal: (" << Xt << "," << Yt << ")" << endl;
    cout << "In the end, we will show the number of turning points and each of their coordinates in order." << endl;
    /************/

 //路段allrisk函數測試
 //riskcalculate test - songtien

 int outcomeX[OUTCOME_MAX_NUM], outcomeY[OUTCOME_MAX_NUM];
 int x1, x2, y1, y2, tpX[OUTCOME_MAX_NUM], tpY[OUTCOME_MAX_NUM], tpX_before[OUTCOME_MAX_NUM], tpY_before[OUTCOME_MAX_NUM], tpX_after[OUTCOME_MAX_NUM], tpY_after[OUTCOME_MAX_NUM], wX[OUTCOME_MAX_NUM], wY[OUTCOME_MAX_NUM];
 double F = 0, Zero = 0, OrgRisk = 0;
 double BeforeRisk = 0, BeforeRisk_1 = 0, BeforeRisk_2 = 0;
 double AfterRisk = 0, AfterRisk_1 = 0, AfterRisk_2 = 0;
 double& Frag = F; //call by reference

 //cout << endl << "輸入兩個轉折點的座標(x1 y1 x2 y2)：";
 //cin >>  x1 >> y1 >> x2 >> y2;
 x1 = Xs;
 y1 = Ys;
 x2 = Xt;
 y2 = Yt;

 OrgRisk = AllRisk(n, F, Xs, Ys, Xt, Yt, x1, y1, x2, y2, m, X, Y, R, P, tpX, tpY);
 cout << endl << "原本路段上AllRisk: " << OrgRisk << endl;
 cout << "-------------------------------" << endl;
 cout << "下一路段開頭未滿1公里距離: " << F << endl << endl;

 cout << "Before路段: " << endl << endl;
 BeforeRisk = AllRisk(n, F, Xs, Ys, Xt, Yt, x1, y1, tpX, tpY, m, X, Y, R, P, tpX_before, tpY_before);
 cout << "After路段: " << endl << endl;
 AfterRisk = AllRisk(n, F, Xs, Ys, Xt, Yt, tpX, tpY, x2, y2, m, X, Y, R, P, tpX_after, tpY_after);

 F = 0;
 cout << "Before路段前半段: " << endl << endl;
 BeforeRisk_1 = AllRisk(n, F, Xs, Ys, Xt, Yt, x1, y1, tpX_before, tpY_before, m, X, Y, R, P, wX, wY);
 cout << "Before路段後半段: " << endl << endl;
 BeforeRisk_2 = AllRisk(n, F, Xs, Ys, Xt, Yt, tpX_before, tpY_before, tpX, tpY, m, X, Y, R, P, wX, wY);

// cout << "AfterF: " << F;
 cout << "After路段前半段: " << endl << endl;
 AfterRisk_1 = AllRisk(n, F, Xs, Ys, Xt, Yt, tpX, tpY, tpX_after, tpY_after, m, X, Y, R, P, wX, wY);
 cout << "After路段後半段: " << endl << endl;
 AfterRisk_2 = AllRisk(n, F, Xs, Ys, Xt, Yt, tpX_after, tpY_after, x2, y2, m, X, Y, R, P, wX, wY);

 cout << "BeforeRisk: " << BeforeRisk << ", " << "AfterRisk: " << AfterRisk << endl;
 cout << endl << "在 (" << tpX << "," << tpY << ") 轉折的路段總風險：" << BeforeRisk + AfterRisk << endl;
 if (BeforeRisk + AfterRisk <= OrgRisk)
    cout << "轉折後風險較原本路徑小－－為較優路徑，應該轉折" << endl;
 else
    cout << "風險較原本路徑大－－為較差路徑，不該轉折" << endl;
 cout << endl << "在 (" << tpX_before << "," << tpY_before << ") 轉折的Before路段總風險：" << BeforeRisk_1 + BeforeRisk_2 << endl;

 cout << "Before路段上是否應該轉折: ";
 if (BeforeRisk_1 + BeforeRisk_2 <= BeforeRisk)
    cout << "是";
 else cout << "不該";
    cout << endl << "在 (" << tpX_after << "," << tpY_after << ") 轉折的After路段總風險：" << AfterRisk_1 + AfterRisk_2 << endl;
 cout << "After路段上是否應該轉折: ";

 if (AfterRisk_1 + AfterRisk_2 <= AfterRisk)
    cout << "是";
 else
    cout << "不該";

// cout << "???" << tpX_before << "," << tpY_before << endl;
// cout << "???" << tpX_after << "," << tpY_after;
    return 0;
}
double distance(double X1, double Y1, double X2, double Y2)
{
    return sqrt( (X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2) );
}
int riskPointCount(double X1, double Y1, double X2, double Y2) // the number of riskPoints between (X1,Y) and (X2,y2)
{
    return floor(distance(X1, Y1, X2, Y2));
}
double riskCal(double Xi, double Yi, int threatPointCnt, int* riskX, int* riskY, int* riskR, int* riskP) // total threat imposed on a single given point
{
    for(i = 0; i < threatPointCnt; i++)
    {
        double temp = (pow(Xi - riskX[i], 2) + pow(Yi - riskY[i], 2));
        d = sqrt(temp);
        if(d <= RiskR[i])
        risk = risk + RiskP[i] * ((RiskR[i] - d) / RiskR[i]);
    }
    return risk;
}

double allRisk(int n, double& FragDistance, int Ini_Xs, int Ini_Ys, int Ini_Xt, int Ini_Yt, \
   int Xs, int Ys, int Xt, int Yt, int RiskCnt, \
   int riskX[], int riskY[], int riskR[], int riskP[], int tpX[], int tpY[])
{

    //必須先傳入題目的起點終點!!!!!因為起始點終點都不計算風險!!!!! - songtien

    double risk[1001] = {0}, risk_X[1001] = {0}, risk_Y[1001] = {0};
    double distance = 0, allrisk = 0, riskMax_X = 0, riskMax_Y = 0, Frag = 0, temp = 0;
    int j = 0, a = 0, i = 0, rec_i = 0, tpoint_X = 0, tpoint_Y = 0;

    distance = sqrt(pow(Xt-Xs, 2) + pow(Yt-Ys, 2));
    double d1 = ceil(distance - FragDistance);
    //要算有幾個點的距離，先減去開頭需要補足的部分

    if (distance >= FragDistance)
    {
    if (Ini_Xs==Xs && Ini_Ys==Ys)//是起點
    {
    risk_X[0] = Xs;
    risk_Y[0] = Ys;
    cout << "路段上起始座標: (" << risk_X[0] << "," << risk_Y[0] << ")" << endl;
    cout << "risk: " << risk[0] << endl << endl;
    for (j = 1; j < d1; j++)
         {
          if (risk_X[j]==Ini_Xt && risk_Y[j]==Ini_Yt) break;//若最後一個點座標是終點則不計算風險
             risk_X[j] = Xs + ((Xt - Xs) / distance) * j;
             risk_Y[j] = Ys + ((Yt - Ys) / distance) * j;
             cout << "路段上小風險點座標: (" << risk_X[j] << "," << risk_Y[j] << ")" << endl;
           risk[j] = RiskCal(risk_X[j], risk_Y[j], RiskCnt, RiskX, RiskY, RiskR, RiskP);
           cout << "risk: " << risk[j] << endl << endl;
           allrisk = allrisk + risk[j];
         }
    }

    else//不是起點
    {
    risk_X[0] = Xs + ((Xt - Xs) / distance) * FragDistance;
      risk_Y[0] = Ys + ((Yt - Ys) / distance) * FragDistance;
      cout << "路段上小風險點座標: (" << risk_X[0] << "," << risk_Y[0] << ")" << endl;
      risk[0] = RiskCal(risk_X[0], risk_Y[0], RiskCnt, RiskX, RiskY, RiskR, RiskP);
      cout << "risk: " << risk[0] << endl << endl;
      allrisk = allrisk + risk[j];

         for (j = 1; j < d1; j++)
         {
          if (risk_X[j]==Ini_Xt && risk_Y[j]==Ini_Yt) break;//若最後一個點座標是終點則不計算風險
          risk_X[j] = Xs + ((Xt - Xs) / distance) * FragDistance + ((Xt - Xs) / distance) * j;
       risk_Y[j] = Ys + ((Yt - Ys) / distance) * FragDistance + ((Yt - Ys) / distance) * j;
          cout << "路段上小風險點座標: (" << risk_X[j] << "," << risk_Y[j] << ")" << endl;
          risk[j] = RiskCal(risk_X[j], risk_Y[j], RiskCnt, RiskX, RiskY, RiskR, RiskP);
          cout << "risk: " << risk[j] << endl << endl;
          allrisk = allrisk + risk[j];
         }
    }
    }

    //路段距離不足1公里情形
    else if (distance < 1)
    {
    risk_X[0] = Xs;
    risk_Y[0] = Ys;
    j = 0;
    }

    //記錄風險最大的座標點
    for (i = 0; i < d1; i++)
    {
    if (risk[i] >= temp)
    {
    temp = risk[i];
    rec_i = i;
    }
    }

  riskMax_X = risk_X[rec_i];
  riskMax_Y = risk_Y[rec_i];
  cout << "＃最大風險點: (" << risk_X[rec_i] << "," << risk_Y[rec_i] << ")" << endl << endl;

  //方圓一公里的整數點存入陣列中 ***目前未用陣列，測試中***
  tpoint_X = ceil(riskMax_X - 1);
  tpoint_Y = floor(riskMax_Y + 1);

  //以Call by Reference回傳轉折點座標
  findPoint(riskMax_X, riskMax_Y, n, 3, tpX, tpY);

  cout << "＃最後一個風險點座標: (" << risk_X[j-1] << "," << risk_Y[j-1] << ")" << endl;
  double Dx = double(Xt) - risk_X[j-1];
  double Dy = double(Yt) - risk_Y[j-1];
  double temp2 = 0, Left = 0;
  temp2 = pow(Dx,2) + pow(Dy,2);//多的不足一公里的距離
  Frag = sqrt(temp2);
  Left = 1 - Frag;
  cout << "Frag: " << Frag << " ; Left: "<< Left << endl << endl;
  FragDistance = Left;
  //以Call by Reference回傳了剩餘的片段

  cout << "allrisk: " << allrisk << endl;
  cout << "===============================" << endl;

 return allrisk;
}

void findPoint (float x , float y, int n, int rad, int outcomeX[], int outcomeY[])
{
    int floorX = floor (x-rad);
    int ceilX = ceil (x+rad);
    int floorY = floor (y-rad);
    int ceilY = ceil (y+rad);
    if (ceilX > n)
        ceilX = n ;
    if (ceilY > n)
        ceilY = n ;
    if (floorX < 0)
        floorX = 0 ;
    if (floorY < 0)
        floorY = 0 ;
    for(int i = 0; i < OUTCOME_MAX_NUM; i++)
    {
        outcomeX[i] = -1;
        outcomeY[i] = -1;
    }

    cout << "Initialization:" << endl;
    for(int i = 0; i < OUTCOME_MAX_NUM; i++)
        cout << outcomeX[i] << " ";
    cout << endl;
    for(int i = 0; i < OUTCOME_MAX_NUM; i++)
        cout << outcomeY[i] << " ";
    cout << endl;

    int k = 0 ;
    for (int i = floorX ; i <= ceilX ; i++)
    {
        for (int j = floorY ; j <= ceilY ; j++)
        {
            if ( (pow (x-i,2)) + pow (y-j,2) <= pow(rad,2) )
            {
                outcomeX[k]=i;
                outcomeY[k]=j;
                cout << outcomeX[k] << " " << outcomeY[k] << "\n" ;
                k++;
            }
        }
    }
}

double slope(double x1, double y1, double x2, double y2)
{
    return (y2 - y1) / (x2 - x1);
}
