# include <iostream>
int main(){
    int a[100001]={0};
    int num;
    int count=0;
    do{    
        std::cin>>num;
        a[count]=num;
        if(num!=0){
            count++;
        }
    }while(num!=0);

    for(int i=count-1;i>=0;i--){
            std::cout<<a[i]<<" ";
    }
    return 0;
}