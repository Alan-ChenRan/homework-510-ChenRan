#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<malloc.h>
#include<sys/time.h>
int O,K;
double ans_V,ans_T;
struct timeval start;
struct timeval end;
typedef struct example{
    int id;
    double v;
}ctx;
double h;
double f(double x){return 4.0/(1.0+x*x);}
void *add_I(void* arg)
{
    ctx* k=(ctx*)(arg);
    int z=k->id;
    for(int i=z;i<O;i+=K)
    {
        double t=i;t*=h;
        k->v=k->v+f(t)*h;
    }
    return NULL;
}

void work()
{
    double o1=O;h=1.0/o1;//printf("zzz\n");
    ctx *ctxs;
    ctxs=(ctx*)malloc(sizeof(ctx)*K);
    for(int i=0;i<K;++i)
    {
         ctxs[i].id=i;
         ctxs[i].v=0;
    }
    pthread_t* threads=(pthread_t*)malloc(sizeof(pthread_t)*K);
    for(int i=0;i<K;++i)
    {
         int retVal=pthread_create(&threads[i],NULL
                                  ,add_I,ctxs+i);
         assert(retVal==0);
    }
    for(int i=0;i<K;++i)
    {
         ans_V=ans_V+ctxs[i].v;
    }
    free(ctxs);free(threads);
}
int main(int argc,char**argv)
{
    O=atoi(argv[1]);K=atoi(argv[2]);
    gettimeofday(&start,NULL);
    work();
    gettimeofday(&end,NULL);
    long long ss=start.tv_sec*1000000+start.tv_usec;
    long long ee=end.tv_sec*1000000+end.tv_usec;
    ans_T=ee-ss;ans_T/=1000000.0;
    printf("%.6lf\n",ans_V);
    printf("Elapsed time: %.6lf\n",ans_T);
    return 0;
}
























