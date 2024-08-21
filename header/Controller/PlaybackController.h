#ifndef PLAYBACKCONTROLLER_H
#define PLAYBACKCONTROLLER_H

#include <iostream>
#include <memory>
#include <vector>
#include "CenterModule.h"
#include "MediaFile.h"
#include "Playlist.h"
#include <SDL2/SDL.h> 
#include <SDL2/SDL_mixer.h>
#include <vlc/vlc.h>
#include <thread>

enum PlaybackStatus {
    Playing,
    Paused,
    Stopped
};
enum PlaybackType {
    Audio,
    Video
};

enum PlaybackMode {
    MediaFileMode,
    PlaylistMode
};

class PlaybackController {
private:
    CenterModule* module;
    std::shared_ptr<MediaFile> currentFile;
    std::shared_ptr<Playlist> currentPlaylist;
    PlaybackStatus status;
    PlaybackMode playmode;
    uint currentIndex = 0;
    Mix_Music* music;
    uint32_t startTime;
    uint32_t pauseTime;
    int audioVolume=128;
    int videoVolume=100;

    libvlc_instance_t* vlcInstance;
    libvlc_media_player_t* mediaPlayer;

    void loadAudioFile();
    void loadVideoFile();
    void playAudio();
    void resumeAudio();
    void playVideo();
    void resumeVideo();
    void stopAudio();
    void stopVideo();

public:
    PlaybackController(CenterModule* mod);
    ~PlaybackController();
    void play();
    void pause();
    void next(PlaybackType type);
    void stop();
    void resume();
    void previous(PlaybackType type);
    void increaseVolume();
    void decreaseVolume();
    int getcurrentTime();
    void setCurrentPlaylist(const std::shared_ptr<Playlist>& playlist);
    void setMode(PlaybackMode mode);
    void setCurrentFile(std::shared_ptr<MediaFile> current);
    void setCurrentIndex(int index);
    std::shared_ptr<MediaFile> getCurrentFile();
    PlaybackStatus getStatus();  
    void startMonitor();

};

#endif // PLAYBACKCONTROLLER_H

