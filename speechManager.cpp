#include "speechManager.h"

#include <random>
#include "functional"

SpeechManager::SpeechManager() {
    this->initSpeech();
    this->createSpeaker();
}

void SpeechManager::showMenu() {
    cout << "************************************************" << endl;
    cout << "*************欢迎参加演讲比赛*************" << endl;
    cout << "*************1.开始演讲比赛**********************" << endl;
    cout << "*************2.查看往届记录***********************" << endl;
    cout << "*************3.清空比赛记录***********************" << endl;
    cout << "*************0.退出比赛程序***********************" << endl;
    cout << "************************************************" << endl;
}

void SpeechManager::exitSystem() {
    cout << "欢迎下次使用" << endl;
    exit(0);
}

SpeechManager::~SpeechManager() {

}

void SpeechManager::initSpeech() {
    this->v1.clear();
    this->v2.clear();
    this->vVictory.clear();
    this->m_Speaker.clear();
    this->m_Index = 1;
}

void SpeechManager::createSpeaker() {
    string nameSeed = "ABCDEFGHIJKL";
    for (int i = 0; i < nameSeed.size(); i++) {
        Speaker speaker;
        speaker.m_Name = "选手";
        speaker.m_Name += nameSeed[i];
        for (int j = 0; j < 2; j++) {
            speaker.m_Score[j] = 0;
        }
        int num = i + 10001;
        //12名选手编号
        this->v1.push_back(num);
        //选手编号 以及对应的选手 存放到map容器中
        this->m_Speaker.insert(make_pair(num, speaker));
    }
}

void SpeechManager::startSpeech() {
    //第一轮比赛
    //1 抽签
    this->speechDraw();
    //2 比赛
    //3 显示晋级结果

    //第二轮比赛

    //1 抽签
    //2 比赛
    //3 显示最终结果
    //4 保存分数
}

void SpeechManager::speechDraw() {
    cout << "第 << " << this->m_Index << " >> 轮比赛选手正在抽签" << endl;
    cout << "------------------------" << endl;
    cout << "抽签后演讲顺序如下：" << endl;
    if (this->m_Index == 1) {
        shuffle(this->v1.begin(), this->v1.end(), std::mt19937(std::random_device()()));
        for (auto &it:this->v1) {
            cout << it << " ";
        }
        cout << endl;
    } else {
        shuffle(this->v2.begin(), this->v2.end(), std::mt19937(std::random_device()()));
        for (auto &it:this->v2) {
            cout << it << " ";
        }
        cout << endl;
    }
    cout << "------------------------" << endl;
}

void SpeechManager::speechContest() {
    cout << "-------------第" << this->m_Index << "轮比赛正式开始：-------------------" << endl;

}
