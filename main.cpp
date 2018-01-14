#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
int main(int argc, char *argv[])
{
//Part 1 (INPUT)
    FILE *t;
    int n,i,k;
    if ((t=fopen("text.txt","r"))==NULL)
        printf("Could not open file – aborting\n");
    else
        t=fopen("text.txt","r");
    fscanf(t,"%d",&n);
    clock_t start,finish, previous;
    double *x,*y,*radius;
    double step;
    double *speedX, *speedY; //  pixels/sec
    double *m;// mass
    float *c;
    double spX1,spX2,spY1,spY2;
    x = (double *)malloc(n * sizeof(double));
    y= (double *)malloc(n * sizeof(double));
    radius= (double *)malloc(n * sizeof(double));
    m = (double *)malloc(n * sizeof(double));
    speedX= (double *)malloc(n * sizeof(double));
    speedY= (double *)malloc(n * sizeof(double));
    c= (float *)malloc(n * sizeof(float));
    for(i=0;i<n;i++)
    {
      fscanf(t,"%lf %lf %f %lf %lf %lf %lf",&x[i], &y[i],&c[i],&m[i],&radius[i],&speedX[i],&speedY[i]);
      if (!((x[i]>=0) && (x[i]<=600)))
      {
        printf("You gave wrong value for coordinates of x number %d (0<=x<=600)",i+1);
        return 0;
      }
      if (!((y[i]>=0) && (y[i]<=400)))
      {
        printf("You gave wrong value for coordinates of y number %d (0<=y<=400)",i+1);
        return 0;
      }
      if (!((c[i]>=0) && (c[i]<=15)))
      {
        printf("You gave wrong value for the color number %d (0<=c<=15)",i+1);
        return 0;
      }
      if (!((m[i]>=0) && (m[i]<=10000)))
      {
        printf("You gave wrong value for the mass of the sphere number %d (0<=m<=10000)",i+1);
        return 0;
      }
      if (!((radius[i]>=1) && (radius[i]<=100)))
      {
        printf("You gave wrong value for radius of the sphere number %d (1<=x<=100)",i+1);
        return 0;
      }
      if (!(speedX[i]>=-100))
      {
        printf("You gave wrong value for the speed X of the sphere number %d (speedX[i]=>-100)",i+1);
        return 0;
      }
      if (!(speedY[i]<=100))
      {
        printf("You gave wrong value for the speed Y of the sphere number %d (speedY[i]<=100)",i+1);
        return 0;
      }
    }
    fclose(t);
    //PART 2 (CREATING GRAPHICS)


    int gdriver = DETECT, gmode, errorcode;   /* request autodetection */
    initgraph(&gdriver, &gmode, "");        /* initialize graphics and local variables */
    errorcode = graphresult();            /* read result of initialization */
    if (errorcode != grOk) {            /* an error occurred */
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      system ("pause");
      exit(1);               /* terminate with an error code */
    }


    //PART 3 START OF SPHERE COLLISION

    float d;
    start=clock();
    previous=start;
    do
    {
        finish = clock();
        step = (finish-previous)*1.0/CLOCKS_PER_SEC;
        if (step >=0.03)
        {
            previous = finish;
            for (i=0;i<n;i++)
            {
                setfillstyle(SOLID_FILL,BLACK);
                setcolor(BLACK);
                fillellipse(x[i],y[i],radius[i],radius[i]);
                x[i]+= speedX[i]*step;
                y[i]+= speedY[i]*step;
            }
            for (i=0;i<n;i++)
            {
                setfillstyle(SOLID_FILL,BLACK);
                setcolor(BLACK);
                fillellipse(x[i],y[i],radius[i],radius[i]);
                if (x[i]+radius[i]>=getmaxx() || x[i]-radius[i]<=0)
                    speedX[i] *= -1;
                if (y[i]+radius[i]>=getmaxy() || y[i]-radius[i]<=0)
                    speedY[i] *= -1;
                for (k=i+1;k<n;k++)
                {
                    d=sqrt(pow(x[i]-x[k],2)+pow(y[i]-y[k],2));
                    if (int(d)<=radius[i]+radius[k])
                    {
                        spX1=((2*m[k])/(m[i]+m[k])*speedX[k]) + (m[i]-m[k])/(m[i]+m[k])*speedX[i];
                        spX2=((2*m[i])/(m[i]+m[k])*speedX[i]) + (m[k]-m[i])/(m[i]+m[k])*speedX[k];
                        spY1=((2*m[k])/(m[i]+m[k])*speedY[k]) + (m[i]-m[k])/(m[i]+m[k])*speedY[i];
                        spY2=((2*m[i])/(m[i]+m[k])*speedY[i]) + (m[k]-m[i])/(m[i]+m[k])*speedY[k];
                        speedX[i]=spX1;
                        speedX[k]=spX2;
                        speedY[i]=spY1;
                        speedY[k]=spY2;
                    }
                }
                setfillstyle(SOLID_FILL,c[i]);
                setcolor(c[i]);
                fillellipse(x[i],y[i],radius[i],radius[i]);
                }
            }
    }
    while (!kbhit());
    closegraph();
    return 0;
}
