#include "PlaybackView.h"

char PlaybackView::choicePlayback(){
    std::cout <<"++++++++++++++++++++++++++"<<std::endl;
    std::cout <<"Please select type to play:"<<std::endl;
    std::cout <<"1: PLay audio mediafile"<<std::endl;
    std::cout <<"2: PLay audio playlist"<<std::endl;
    std::cout <<"3: PLay video"<<std::endl;
    std::cout <<"0: Exit"<<std::endl;
    std::cout <<"Please enter your choice:";
    char choice;
    do
        std::cin>>choice;
    while(!(choice =='1'||choice =='2'||choice =='3'||choice =='0'));

    return choice;
    }