#include "speechManager.h"

#include <random>
#include "functional"
#include "deque"
#include "numeric"

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
    this->speechContest();
    //3 显示晋级结果
    this->showScore();

    //第二轮比赛
    this->m_Index++;

    //1 抽签
    this->speechDraw();
    //2 比赛
    this->speechContest();
    //3 显示最终结果
    this->showScore();
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
    random_device r;
    seed_seq seed{r(), r(), r()};
    mt19937 eng{seed};
    uniform_int_distribution<> dist(1, 400);
    //临时容器， 保存key分数 value选手编号
    multimap<float, int, greater<float>> groupScore;
    int num = 0;
    vector<int> v = this->m_Index == 1 ? v1 : v2;
    for (auto id:v) {
        num++;
        //评委打分
        deque<float> d;
//        cout << "编号：" << id << "得分为：";
        for (int i = 0; i < 10; i++) {
            float score = (dist(eng) + 600.f) / 10.f;
//            cout << score << " ";
            d.push_back(score);
        }
//        cout << endl;
        sort(d.begin(), d.end(), greater<float>());
        d.pop_back();
        d.pop_front();

        float sum = accumulate(d.begin(), d.end(), 0.0f);
        float avg = sum / (float) d.size();

        this->m_Speaker[id].m_Score[this->m_Index - 1] = avg;

        //6个人一组，用临时容器保存
        groupScore.insert(make_pair(avg, id));
        if (num % 6 == 0) {

            //取前三
            int count = 0;
            cout << "第" << num / 6 << "小组比赛名次：" << endl;
            for (auto &gs:groupScore) {
                cout << "编号：" << gs.second << " 姓名：" << this->m_Speaker[gs.second].m_Name << " 成绩："
                     << this->m_Speaker[gs.second].m_Score[this->m_Index - 1] << endl;
                if (++count <= 3) {
                    if (this->m_Index == 1) {
                        v2.push_back(gs.second);
                    } else {
                        vVictory.push_back(gs.second);
                    }
                }
            }
            groupScore.clear();
            cout << endl;
        }
    }
    cout << "----------------第" << this->m_Index << "轮比赛完毕！---------------" << endl;
}

void SpeechManager::showScore() {
    cout << "---------------第" << this->m_Index << "轮晋级选手信息如下：" << endl;
    vector<int> v;
    if (this->m_Index == 1) {
        v = this->v2;
    } else {
        v = this->vVictory;
    }
    for (auto id:v) {
        cout << "选手编号：" << id << " 姓名：" << this->m_Speaker[id].m_Name << " 得分："
             << this->m_Speaker[id].m_Score[this->m_Index - 1] << endl;
    }
}
