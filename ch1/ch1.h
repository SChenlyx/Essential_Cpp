#ifndef CH1_H
#define CH1_H

#include <vector>
#include <iostream>
#include <string>
using namespace std;

typedef const vector<unsigned int> *(*pfunc)(int);  //指向函数的指针
typedef const vector<unsigned int> *pvec;   //指向vec的指针

//数列类型
enum num_sequence {
    ns_unk, ns_fib, ns_pell, ns_lucas, ns_tri, ns_sq, ns_pent,
    ns_cnt = 6, ns_wrong_msg = 4
};

//用户数据储存结构体
struct user_profile {
    string name;    //用户名字
    int guesses;    //用户选择次数
    int correct;    //用户正确次数
    int level;      //游戏水平

    num_sequence cur_seq;
    pvec cur_seq_vec;
    int pos;
};


extern pfunc gen_elems[];
extern const char *name_seq[];
extern const char *wrong_msg[];
extern int level_size[];

//欢迎玩家
extern bool greet_user(user_profile *);
//开始游戏
extern void play_game(user_profile *);
//展示统计数据
extern void display_statistics(user_profile *);

//生成各个类型的数列
extern pvec Fibonacci_gen_elems(int);
extern pvec Pell_gen_elems(int);
extern pvec Lucas_gen_elems(int);
extern pvec Triangular_gen_elems(int);
extern pvec Square_gen_elems(int);
extern pvec Pentagonal_gen_elems(int);

extern void set_seq(user_profile *, int);
extern const char *seq_id(user_profile *);
extern void init_user(user_profile *puser, const string &nm, int level);    //初始化用户数据的函数
extern bool correct_guess(user_profile *puser, int guess);

//设定当前数列的vector
inline void
set_seq_vec(user_profile *pu, pvec p) {
    pu->cur_seq_vec = p;
};

//返回当前数列的vector
inline pvec
seq_vec(user_profile *pu) {
    return pu->cur_seq_vec;
}

//返回玩家名字
inline string
user_name(user_profile *puser) {
    return puser->name;
}

//返回当前数列类型
inline num_sequence
seq(user_profile *puser) {
    return puser->cur_seq;
}

//猜测次数加一
inline void
bump_guess(user_profile *puser) {
    ++puser->guesses;
}

//正确次数加1
inline void
bump_correct(user_profile *puser) {
    bump_guess(puser);
    ++puser->correct;
}

#include <cstdlib>
//随机生成数列，随机数种子使用puser的地址转换的unsigned int
inline num_sequence
gen_seq_id(unsigned int ui) {
    srand(ui++);
    //static_cast相当于C语言中强制类型转换，会有位数取舍
    return static_cast<num_sequence>((rand() % ns_cnt) + 1);
}

//追踪定位
inline void
trace (const string &where, const string &msg, const string &data) {
    cerr << where << " " << msg << " " << data << endl;
}

inline void
trace (const string &where, const string &msg, int val) {
    cerr << where << " " << msg << " " << val << endl;
}

inline void
trace (const string &where, const string &msg, int val1, int val2) {
    cerr << where << " " << msg << " " << val1 << ' ' << val2 << endl;
}

inline void
trace(const string &where, int val1, int val2) {
    cerr << where << " " << val1 << " " << val2 << endl;
}

//检查输入的数字是否在[0,255]内，如是，返回true,否则返回false
inline bool
check_integrity(int pos) {
    const int max_elems = 512;

    if(pos <= 0 || pos > max_elems) {
        cerr << "!! invalid position: " << pos
             << "Cannot honor request\n";

        return false;
    }
    return true;
}

//检查数列类型
inline num_sequence
check_sequence(int id) {
    if (id <= 0 || id > ns_cnt) {
        cerr << "!! invalid sequence value: " << id
             << " Choosing one at random\n";

        id = (id % ns_cnt) + 1;
    }

    return static_cast<num_sequence>(id);
}


#endif // CH1_H
