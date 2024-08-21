#include "View.h"

View::View(CenterModule& centerModule) : centerModule(centerModule) {}

void View::displayMenu() {
        std::cout << "\n=== Media Player Menu ===\n";
        std::cout << "1. Manage Media and Playlist\n";
        std::cout << "2. Play Media Files\n";
        std::cout << "3. Exit\n";
        std::cout << "Please enter your choice: ";}

// view for PLayback       
char View::choicePlayback()
{
    return playbackView.choicePlayback();
}

void View::playback_Playlist()
{
    playlistView.displayPlaylistList(centerModule.getAllPlaylists());
    std::cout<<"Please enter name playlist to play: \n ";
    std::cout<<"Please enter exit to exit: \n ";

}
int View::displayPlaylist(const std::shared_ptr<Playlist>& playlist)
{
    if(!playlist->getFiles().empty()){
        playlistView.displayPlaylist(playlist);

        while(1)
            {
            std::cout<<"Please enter number audio play: \n ";
            std::cout<<"Please enter -1 to exit: \n ";
            int number;
            std::cin >> number;

            if(number>=0 && number< playlist->getFiles().size()){
                return number;
            }
            return -1;
        }
    }
    else {
        std::cout<< "No have data\n";
        return -1;}
}

int View::playback_Audio_list()
{
    if(!centerModule.getAllMediaFiles().empty()){

        audioView.displayAudioList(centerModule.getAllMediaFiles());

        while(1)
            {
            std::cout<<"Please enter number audio play or 1 to exit:";
            int number;
            std::cin >> number;

            if(number >= 0 && number< centerModule.getAllMediaFiles().size()){
                for(int i=0; i<=centerModule.getAllMediaFiles().size(); i++ )
                {
                    if(number==0 && (centerModule.getAllMediaFiles()[i]->isAudio()))
                    {
                        return i;
                    }
                    else if(centerModule.getAllMediaFiles()[i]->isAudio()) number--;
                }
                return -1;
            }
            if(number == -1)
                return -1;
        }
    }
    else {
        std::cout<< "No have data\n";
        return -1;}
}

int View::playback_Video_list()
{
    if(!centerModule.getAllMediaFiles().empty()){

        videoView.displayVideoList(centerModule.getAllMediaFiles());

        while(1)
            {
            std::cout<<"\nPlease enter number to video play or -1 to exit: ";
            int number;
            std::cin >> number;

            if(number >= 0 && number< centerModule.getAllMediaFiles().size()){
                for(int i=0; i<=centerModule.getAllMediaFiles().size(); i++ )
                {
                    if(number==0 && (!centerModule.getAllMediaFiles()[i]->isAudio()))
                    {
                        return i;
                    }
                    else if(!centerModule.getAllMediaFiles()[i]->isAudio()) number--;
                }
                return -1;
            }
            if(number == -1)
                return -1;
        }
    }
    else {
        std::cout<< "No have data\n";
        return -1;}
}

char View::playback_Menu(){
    std::cout << "\n=== Playback Menu ===\n";
    std::cout << "u:(pause), r:(resume), n:(next), p:(previous)\n";
    std::cout << "+:(incre VOL), -:(decre VOL), t:(currentime) \n";
    std::cout << "0:(STOP)\n";
    std::cout << "Enter your choice: ";

    char choice;
    do
        std::cin>>choice;
    while(!(choice =='t'||choice =='u'||choice =='r'||choice =='n'||choice =='p'||choice =='+'||choice =='-'||choice =='0'));

    return choice;    
}

void View::display_currentPlay(const std::shared_ptr<MediaFile>& currentFile){
    std::cout<< "current play:" <<currentFile->getMetadata()->getName() <<"\n";
}
void View::display_currentTime(const int& currentTime, const std::shared_ptr<MediaFile>& currentFile){
    std::cout<< "Current Time:" <<currentTime <<" / "<< currentFile->getMetadata()->getDuration();
}

