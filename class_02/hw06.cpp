# include <iostream>
struct Student{
    int id;
    int chi;
    int mat;
    int eng;
    int tot;
};

bool Compare(const Student &a,const Student &b){
    if (a.tot != b.tot)
        return a.tot < b.tot;
    if (a.chi != b.chi)
        return a.chi < b.chi;
    return a.id > b.id;
    
}

int main(void){
    int n;
    Student s[301];
    std::cin>>n;
    for(int i=0;i<n;i++){
        s[i].id=i+1;
        std::cin>>s[i].chi>>s[i].mat>>s[i].eng;
        s[i].tot=s[i].chi+s[i].mat+s[i].eng;
    }

    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(Compare(s[i],s[j])){
                Student t;
                t=s[i];
                s[i]=s[j];
                s[j]=t;
            }
        }
    }
    for(int i=0;i<5;i++){
        std::cout<<s[i].id<<" "<<s[i].tot<<std::endl;
    }
    return 0;
}
