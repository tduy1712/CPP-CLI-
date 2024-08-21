#ifndef VIEW_H
#define VIEW_H

#include "AudioView.h"
#include "VideoView.h"
#include "PlaylistView.h"
#include "PlaybackView.h"
#include "CenterModule.h"
#include <vector>
#include <iostream>


class View {
private:
    AudioView audioView;
    VideoView videoView;
    PlaylistView playlistView;
    PlaybackView playbackView;
    CenterModule& centerModule;

public:
    View(CenterModule& centerModule);
    void displayMenu();
    char choicePlayback();
    void playback_Playlist();
    int playback_Audio_list();
    int playback_Video_list();
    char playback_Menu();
    void display_currentPlay(const std::shared_ptr<MediaFile>& currentFile);
    void display_currentTime(const int& currentTime, const std::shared_ptr<MediaFile>& currentFile);
    int displayPlaylist(const std::shared_ptr<Playlist>& playlist);
    
};

#endif // VIEW_H
