#include <iostream>

using namespace std;

int main()
{
    int n = 0, m = 0, w = 0, d = 0;
    cin >> n >> m >> w >> d;

    int* X = new int[m];
    int* Y = new int[m];
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
    cout << "Next, Type below the number of turning points and each coordinates:" << endl;
    /************/

    int turn = 0;
    cin >> turn;
    int* turnX = new int[turn];
    int* turnY = new int[turn];
    for(int i = 0; i < turn; i++)
    {
        cin >> turnX[i] >> turnY[i];
    }

    /*** test ***/
    cout << "< test >:" << endl;
    cout << "turns = " << turn << endl;
    cout << "turning points: ";
    for(int i = 0; i < turn; i++)
        cout << "(" <<turnX[i] << "," <<  turnY[i] << ")";
    cout << endl;
    /************/


    return 0;
}
