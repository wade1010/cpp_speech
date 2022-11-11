#include <iostream>
#include "iostream"
#include "speechManager.h"

using namespace std;

void testPrint(const map<int, Speaker> &m) {
    for (const auto &it : m) {
        cout << "选手编号：" << it.first
             << "姓名：" << it.second.m_Name
             << "第一轮成绩：" << it.second.m_Score[0]
             << " 第二轮成绩：" << it.second.m_Score[1] << endl;
    }
}

int main() {
    SpeechManager sm;
//    testPrint(sm.m_Speaker);

    int choice;
    while (true) {
        sm.showMenu();

        cout << "请输入您的选择：" << endl;
        cin >> choice;

        switch (choice) {
            case 1://开始比赛
                sm.startSpeech();
                break;
            case 2://查看记录
                break;
            case 3://清空记录
                break;
            case 0://退出系统
                sm.exitSystem();
                return 0;
            default:
                break;
        }
    }
}
