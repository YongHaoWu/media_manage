#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <utility>
#include <cstdlib>
using namespace std;
class Media
{
    public:
        Media() {};
        int number;
        int part;
        string name;
};

void Save(map<int,Media> &C)
{
    map<int,Media>::iterator it=C.begin();
    ofstream read;
    read.close();
    read.clear();
    read.open("file.txt");
    if(!read) {
        cerr<<"错误"<<endl;
        return;
    }
    if(it == C.end()) {
        cout<<"没有数据保存"<<endl;
        return;
    }
    while(it!=C.end()) {
        read<<it->first<<endl<<it->second.name<<endl<<it->second.part<<endl;
        ++it;
    }
    read.close();
    cout<<"保存成功！！"<<endl;
}

void Add_media(map<int,Media> &C)
{
    char temp;
    do {
        Media m;
        cout<<"输入视频名字"<<endl;
        cin>>m.name;
        cout<<"输入看到的集数"<<endl;
        cin>>m.part;
        cout<<"给视频编号(不要重复）"<<endl;
        cin>>m.number;
        C[m.number] = m;
        cout<<"成功!\n 输入y，继续；任意键退出"<<endl;
        cin>>temp;
    }while(temp=='y' || temp=='Y');
    Save(C);
}

void Delete(map<int,Media> &C)
{
    int number;
    map<int,Media>::iterator it=C.begin();
    cout<<"输入要删除视频的号码"<<endl;
    cin>>number;
    it=C.find(number);
    if(it == C.end()) {
        cout<<"没找到该号码所对应视频"<<endl;
        return;
    }
    C.erase(it);
    Save(C);
    cout<<"删除成功"<<endl;
}

void Add_number(map<int,Media> &C)
{
    char temp;
    do {
        int number;
        cout<<"输入已看1集的视频号码"<<endl;
        cin>>number;
        map<int,Media>::iterator it= C.find(number);
        if(it == C.end()) {
            cout<<"没找到该号码所对应视频"<<endl;
            return;
        }
        ++it->second.part;
        cout<<"添加后你现在看到的集数是"<<it->second.part<<endl;
        Save(C);
        cout<<"继续添加？(y/n)"<<endl;
        cin>>temp;
    }while(temp=='y' || temp=='Y');
}

void Load(map<int,Media> &C)
{
    int number;
    fstream load;
    load.clear();
    load.open("file.txt",ios::in|ios::out);
    Media media;
    while(!load.eof()) {
        load>>number;
        load>>media.name;
        load>>media.part;
        C[number] = media;
    }
}

void Print(map<int,Media> &C)
{
    map<int,Media>::iterator it = C.begin();
    while(it != C.end()) {
        cout<<it->first<<"   "<<it->second.name<<" "<<it->second.part<<endl;
        ++it;
    }
}

void All_Add(map<int,Media> &C)
{
    map<int,Media> ::iterator it = C.begin();
    while(it != C.end()) {
        ++it->second.part;
        ++it;
    }
    Save(C);
    cout<<"成功"<<endl;
}
