# include <iostream>
int main(){
    int n,a[1001],i;
    std::cin>>n;
    for(i=0;i<n;i++){
        std::cin>>a[i];
    }
    int sum=0;
    for(i=0;i<n;i++){
        sum+=a[i];
        std::cout<<sum;
        if(i<n-1){
            std::cout<<" ";
        }
    }
    return 0;
}