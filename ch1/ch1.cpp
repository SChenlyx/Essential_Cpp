#include "ch1.h"

//生成Fibonacci数列
pvec Fibonacci_gen_elems(int pos) {
    static vector<unsigned int> _elems;

    //如果输入不在范围内，则返回0
    if(!check_integrity(pos)) {
        return 0;
    }

    if(_elems.empty()) {
        _elems.push_back(1);
        _elems.push_back(1);
    }

    if(_elems.size() < pos) {
        int ix = _elems.size();
        int n_2 = _elems[ix - 2],
            n_1 = _elems[ix - 1];

        int elem;
        for ( ; ix < pos; ++ix) {
            elem = n_2 + n_1;
            _elems.push_back(elem);
            n_2 = n_1;
            n_1 = elem;
        }

    }
    return &_elems;
}

//生成Pell数列
pvec Pell_gen_elems( int pos ) {
    static vector< unsigned int> _elems;

    if ( ! check_integrity( pos )) {
        return 0;
    }

    if ( _elems.empty() ) {
        _elems.push_back( 1 );
        _elems.push_back( 2 );
    }

    if ( _elems.size() < pos ) {
        int ix = _elems.size();
        int n_2 = _elems[ ix - 2 ],
            n_1 = _elems[ ix - 1 ];

        int elem;
        for ( ; ix < pos; ++ix ) {
            elem = n_2 + 2 * n_1;
            _elems.push_back( elem );
            n_2 = n_1;
            n_1 = elem;
        }
    }

    return &_elems;
}

//生成Lucas数列
pvec Lucas_gen_elems( int pos ) {
    static vector<unsigned int> _elems;

    if ( ! check_integrity( pos )) {
        return 0;
    }

    if ( _elems.empty() ) {
        _elems.push_back( 1 );
        _elems.push_back( 3 );
    }

    if ( _elems.size() < pos ) {
        int ix = _elems.size();
        int n_2 = _elems[ ix - 2 ],
            n_1 = _elems[ ix - 1 ];

        int elem;
        for ( ; ix < pos; ++ix ) {
            elem = n_2 +  n_1;
            _elems.push_back( elem );
            n_2 = n_1;
            n_1 = elem;
        }
    }

    return &_elems;
}

//生成Triangular数列
pvec Triangular_gen_elems( int pos ) {
    static vector<unsigned int> _elems;

    if ( ! check_integrity( pos )) {
        return 0;
    }

    if ( _elems.size() < pos ) {
        int ix = _elems.size() ? _elems.size() + 1 : 1;
        for ( ; ix <= pos; ++ix ) {
            _elems.push_back( ix * (ix + 1) / 2 );
        }
    }

    return &_elems;
}

//生成Square数列
pvec Square_gen_elems( int pos ) {
    static vector<unsigned int> _elems;

    if ( ! check_integrity( pos )) {
        return 0;
    }

    if ( _elems.size() < pos ) {
        int ix = _elems.size() ? _elems.size() + 1 : 1;
        for ( ; ix <= pos; ++ix ) {
            _elems.push_back( ix * ix );
        }
    }

    return &_elems;
}

//生成Pentagonal数列
pvec Pentagonal_gen_elems( int pos ) {
    static vector<unsigned int> _elems;

    if ( ! check_integrity( pos )) {
        return 0;
    }

    if ( _elems.size() < pos ) {
        int ix = _elems.size() ? _elems.size() + 1 : 1;
        for ( ; ix <= pos; ++ix ) {
            _elems.push_back( ix * (3 * ix - 1) / 2 );
        }
    }

    return &_elems;
}

//指向函数指针定义
pfunc gen_elems[] = {
    0,
    Fibonacci_gen_elems,
    Pell_gen_elems,
    Lucas_gen_elems,
    Triangular_gen_elems,
    Square_gen_elems,
    Pentagonal_gen_elems
};

//指向数列名字的指针
const char *name_seq[] = { "Invalid Sequence",
                           "Fibonacci", "Pell", "Lucas",
                           "Triangular", "Square", "Pentagonal"
                         };

//各个等级的数列宽度
int level_size[] = { 8, 8, 32, 128, 512 };

//指向报错信息的枝真
const char *wrong_msg[] = {
    "Oops! Nice guess but not quite it.",
    "Hmm. Sorry. Wrong again.",
    "Ah, this is harder than it looks, isn't it?",
    "It must be getting pretty frustrating by now!"
};

//展示统计数据的函数
void display_statistics( user_profile *puser ) {
    cout << "Game Statistics for " << puser->name << "\n\t"
         << "# guesses: " << puser->guesses << "\n\t"
         << "# correct: " << puser->correct << "\n\t"
         << "% correct: "
         << (static_cast<float>( puser->correct ) / static_cast<float>( puser->guesses )) * 100 << endl;
}


//欢迎用户界面
bool greet_user( user_profile *puser ) {
    cout << "Hi. What's your name? ";

    string nm;
    cin >> nm;

    if ( nm.empty() || nm[ 0 ] == ' ' ) {
        cout << "ok. I guess you don't want to play. See ya!\n";
        return false;
    }

    cout << "Hi, " << nm
         << " Would you like to play Guess the Sequence? (y/n) ";

    char ch;
    cin >> ch;

    if ( ch != 'y' && ch != 'Y' ) {
        cout << "ok. I'm sorry you don't want to play.\n";
        return false;
    }

    cout << "\n\n" << "Hey, that's great, " << nm << ".\n"
         << "We'll start in just a moment.\nIt\'s simple, really!\n"
         << "I will print out two elements of a sequence\n"
         << "You just answer with the element value that comes next!\n\n";

    cout << "Oh, by the way, do you consider yourself a\n\t"
         << "beginner     -- enter 1\n\t"
         << "intermediate -- enter 2\n\t"
         << "advanced     -- enter 3\n\t"
         << "guru         -- enter 4\n\t" << endl;

    int level;
    cin >> level;

    if ( level < 1 || level > 4) {
        level = 4;
    }

    //初始化用户数据
    init_user( puser, nm, level );
    return true;
}

//打印数列
void print_seq( user_profile *puser ) {
    for ( int i = 0; i < puser->cur_seq_vec->size(); ++i ) {
        cout << (*puser->cur_seq_vec)[i] << ' ';
    }
    cout << endl;
}

//展示数列
void display_seq( user_profile *puser ) {
    pvec p = seq_vec( puser );
    cout << "The first two elements of the series are: "
         << (*p)[ puser->pos - 3 ] << ", " << (*p)[ puser->pos - 2 ]
         << "\nWhat is the next element? ";
}

//随机抽选数列中的一个位置
void set_up_index( user_profile *puser ) {
    static string wherefrom( "set_up_index" );

    //在序列中随机选择一个位置
    puser->pos = rand() % ( level_size[ puser->level ] );

    //保证选中位置前至少有两个数
    if ( puser->pos < 3 ) {
        puser->pos += 3;
    }

    //调用某个gen_elem函数使得数列变成向量
    set_seq_vec( puser, (*gen_elems[ puser->cur_seq ])( puser->pos ));
    trace( wherefrom, "new position: ", puser->pos );
}

//随机选择数列类型
void reset_seq( user_profile *puser ) {
    static string wherefrom( "reset_seq" );

    //reinterpret_cast转换运算符，将puser类型转换成unsigned int作为随机数种子生成新数列
    int new_seq = gen_seq_id( reinterpret_cast<unsigned int>( puser ));
    //如果新旧数列相等，就让新数列+1
    if ( new_seq == puser->cur_seq ) {
        new_seq = new_seq < ns_cnt ? new_seq + 1 : 1;
    }

    //将新数列通过static_cast转换为num_sequence
    puser->cur_seq = static_cast<num_sequence>( new_seq );


    set_up_index( puser );

    print_seq( puser );
    trace( wherefrom, "new sequence: ", name_seq[ puser->cur_seq ]);
}

//初始化用户数据的函数
void init_user( user_profile *puser, const string &nm, int level ) {
    static string wherefrom( "init_user" );

    puser->name = nm;
    puser->guesses = 0;
    puser->correct = 0;
    puser->level = level;

    reset_seq( puser );

    trace( wherefrom, nm, puser->cur_seq, level );
}

//猜中
bool correct_guess( user_profile *puser, int guess ) {
    pvec p = seq_vec( puser );
    if ( guess == (*p)[ puser->pos - 1 ] ) {
        return true;
    }
    return false;
}

//开始游戏
void play_game( user_profile *puser ) {
    bool next_seq  = true;      // show next sequence?
    bool go_for_it = true;      // user wants to guess?
    bool got_it    = false;     // user guessed correctly?
    int  num_tries;				// number of tries per sequence

    while ( next_seq == true ) {
        num_tries = 0;
        display_seq( puser );
        while (( got_it == false ) &&
                ( go_for_it == true )) {
            unsigned int usr_guess;
            cin >> usr_guess;

            if ( correct_guess( puser, usr_guess )) {
                bump_correct( puser );
                got_it = true;
                cout << "Hey, most excellent! \n\t"
                     << usr_guess << " is element # "
                     << puser->pos << " of the "
                     << name_seq[ puser->cur_seq ] << " sequence.\n";
            } else {
                bump_guess( puser );
                cout << wrong_msg[ num_tries < ns_wrong_msg ? num_tries : ns_wrong_msg - 1 ]
                     << " Would you like to try again? (y/n) ";

                char usr_rsp;
                cin >> usr_rsp;

                if ( usr_rsp == 'N' || usr_rsp == 'n' ) {
                    go_for_it = false;
                } else {
                    ++num_tries;
                    cout << "Your next guess? ";
                }
            }
        }

        cout << "Want to try another sequence? (y/n) ";
        char try_again;
        cin >> try_again;

        if ( try_again == 'N' || try_again == 'n' ) {
            next_seq = false;
        } else {
            got_it = false;
            reset_seq( puser );
        }
    }
}



