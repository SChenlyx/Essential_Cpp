#include <iostream>
#include <string>

using namespace std;

#include "ch1.h"

int main() {
    //创建用户数据存储变量
    user_profile up;

    //进入用户欢迎界面，并判断用户是否想进行游戏
    if(greet_user((&up))) {
        //用户想进行游戏时开始游戏
        play_game(&up);
        //游戏结束后展示统计数据
        display_statistics(&up);
    }
}
