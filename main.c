#include <stdio.h>
#include <stdlib.h>

void saisie(int*t,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("donner t[%d]=",i);
        scanf("%d",t+i);
    }
}
void affiche (int*t,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d\n",*(t+i));
}
void maxmin(int*t,int n,int *admax,int*admin)
{
    *admax=*t;
    *admin=*t;
    int i;
    for(i=1;i<n;i++)
    {
        if(*(t+i)>*admax)
        {
            *admax=*(t+i);
        }
        if(*(t+i)<*admin)
        {
            *admin=*(t+i);
        }
    }

}
void main()
{
    int n;
    int*v=NULL;
    int min,max;
    do
    {
        printf("donner la dim de tab:");
        scanf("%d",&n);
    }while(n<=0);
    v=(int*)malloc(4*n);
    saisie(v,n);
    affiche(v,n);
    maxmin(v,n,&max,&min);
    printf("max:%d,min:%d",max,min);
    free(v);
}
