#pragma once

#include "iostream"
#include "vector"
#include "map"
#include "speaker.h"

using namespace std;

class SpeechManager {
public:
    SpeechManager();

    //菜单功能
    void showMenu();

    void exitSystem();


    ~SpeechManager();

    //初始化容器和属性
    void initSpeech();

    //创建选手
    void createSpeaker();

    //开始比赛
    void startSpeech();

    //抽签
    void speechDraw();

    //比赛
    void speechContest();

    //显示分数
    void showScore();

public:
    //比赛选手 12人
    vector<int> v1;
    //第一轮晋级容器 6人
    vector<int> v2;
    //胜利前三名 3人
    vector<int> vVictory;

    //存放编号，以及对应的具体选手
    map<int, Speaker> m_Speaker;

    //记录比赛轮数
    int m_Index;
};

