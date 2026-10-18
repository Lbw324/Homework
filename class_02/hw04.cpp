# include <iostream>
int main(){
    int a[5],i;
    for(i=0;i<5;i++){
        std::cin>>a[i];
    }
    int maxn=0,minn=10,sum=0;
    for(i=0;i<5;i++){
        if(a[i]>=maxn){
            maxn=a[i];
        }
        if(a[i]<=minn){
            minn=a[i];
        }
        sum+=a[i];
    }
    double average;
    average=1.0*(sum-maxn-minn)/3;
    printf("%.2lf\n",average);
    return 0;
}
