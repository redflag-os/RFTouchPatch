/*
 * main.cpp: tool func file
 * Copyright (C) 2021, Red Flag Software Co., Ltd
 *
 */

#include "Tool.h"

int findstr(string filename, string featurestr)
{
    ifstream infile;
    infile.open(filename.data());   //将文件流对象与文件连接起来
    string s;
    while(getline(infile,s))
    {
        int paraloc=s.find(featurestr);
        if(paraloc!=-1){
            infile.close();
            return 1;
        }
    }
    infile.close();
    return 0;
}


int is_FileEmpty(string filename)
{
    fstream file;
    file.open(filename,ios::in);
    file.get(); //试图去读一个字符
    if(file.eof()) //或 if ( ch==EOF )  //一个字符都未读到，表示文件为空
    {
        file.close();
        return 0;
    }
    else
    {
        file.close();
        return 1;
    }
}
