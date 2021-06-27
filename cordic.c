#include "cordic.h"


/////////cordic////////


float power(int a, int b)
{
    if(b==0)
        {
            return 1;
        }
    float ans=a;
  while(b>1)
  {
      ans=ans*a;
      b--;
  }
  return ans;
}


float cordic(float x, float y, float teta)
{
    int n=19; // number of stages
    float itan[19] = {45,26.565051,14.036243,7.125016,3.576334,1.789911,0.895174,0.447614,0.223811,0.111906,0.055953,0.027976,0.013988,0.006994,0.003497,0.001749,0.000874,0.000437,0.000219};
    int i;
    float X[n+1];
    float Y[n+1];
    float Z[n+1];
    float phase;
    phase = teta;
   while(phase >= 360)
   {
       phase = phase - 360;
   }
    if(phase>=0 && phase <= 90)
    {
        X[0] = x;
        Y[0] = y;
        Z[0] = phase;

    }
    else if(phase > 90 && phase <= 180)
    {
        X[0] = -y;
        Y[0] = x;
        Z[0] = phase - 90;
    }
     else if(phase > 180 && phase <= 270)
    {
        X[0] = -x;
        Y[0] = -y;
        Z[0] = phase - 180;
    }
     else if(phase > 270 && phase <= 360)
    {
        X[0] = y;
        Y[0] = -x;
        Z[0] = phase - 270;
    }

    for(int j=0;j<=n;j++)
    {
        if(Z[j]<0)
        {
            X[j+1] = X[j] + Y[j]*(1/power(2,j));
            Y[j+1] = Y[j] - X[j]*(1/power(2,j));
            Z[j+1] = Z[j] + itan[j];
        }
        else
        {
            X[j+1] = X[j] - Y[j]*(1/power(2,j));
            Y[j+1] = Y[j] + X[j]*(1/power(2,j));
            Z[j+1] = Z[j] - itan[j];
        }
    }

    return Y[n+1]*0.6073;

}

///////////////cordic end/////////////////




