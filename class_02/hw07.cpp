# include <iostream>
# include <string>

int main(){
    std::string s;
    std::cin>>s;
    int x=0,y=0;
    for(int i=0;i<s.length();i++){
        if(s[i] == 'U'){
            y++;
        }
        else if(s[i] == 'D'){
            y--;
        }
        else if(s[i] == 'L'){
            x--;
        }
        else if(s[i] == 'R'){
            x++;
        }
    }
    if(x==0&&y==0){
        std::cout<<"true";
    }
    else{
        std::cout<<"false";
    }
    return 0;
}
