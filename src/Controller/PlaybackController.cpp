#include "PlaybackController.h"
PlaybackController::PlaybackController(CenterModule* mod)
    : module(mod), status(PlaybackStatus::Stopped), playmode(PlaybackMode::MediaFileMode), currentIndex(0U),
      music(nullptr), vlcInstance(nullptr), mediaPlayer(nullptr) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        exit(1);
    }

    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

PlaybackController::~PlaybackController() {
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }

    Mix_CloseAudio();

    if (mediaPlayer) {
        libvlc_media_player_stop(mediaPlayer);
        libvlc_media_player_release(mediaPlayer);
    }

    if (vlcInstance) {
        libvlc_release(vlcInstance);
    }
    SDL_Quit();
}

void PlaybackController::setMode(PlaybackMode mode) {
    playmode = mode;
}

void PlaybackController::setCurrentPlaylist(const std::shared_ptr<Playlist>& playlist) {
    if (playlist == nullptr) {
        std::cerr << "Set current playlist to a null pointer.\n";
        return;
    }
    currentPlaylist = playlist;
    setMode(PlaybackMode::PlaylistMode);
}

void PlaybackController::setCurrentFile(std::shared_ptr<MediaFile> current) {
    if (current == nullptr) {
        std::cerr << "Set current file to a null pointer.\n";
        return;
    }
    currentFile = current;
}


void PlaybackController::loadAudioFile() {
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }

    std::string filePath = currentFile->getPath();
    music = Mix_LoadMUS(filePath.c_str());

    if (music == nullptr) {
        std::cerr << "Failed to load music: " << filePath << " SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

void PlaybackController::loadVideoFile() {
    if (vlcInstance) {
        libvlc_release(vlcInstance);
    }

    // Initialize libVLC
    vlcInstance = libvlc_new(0, nullptr);
    if (!vlcInstance) {
        std::cerr << "Could not initialize libVLC" << std::endl;
        return;
    }

    if (mediaPlayer) {
        libvlc_media_player_stop(mediaPlayer);}
        
    // Create media player
    mediaPlayer = libvlc_media_player_new(vlcInstance);
    if (!mediaPlayer) {
        std::cerr << "Could not create media player" << std::endl;
        return;
    }

    // Create media from video file
    std::string filePath = currentFile->getPath();
    libvlc_media_t* media = libvlc_media_new_path(vlcInstance, filePath.c_str());
    if (!media) {
        std::cerr << "Could not create media from file" << std::endl;
        return;
    }

    libvlc_media_player_set_media(mediaPlayer, media);
    libvlc_media_release(media);
}

void PlaybackController::playAudio() {
    if (music != nullptr) {
        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic(music, 1);
			startTime = SDL_GetTicks();
        }
    }
}

void PlaybackController::resumeAudio() {
    if (Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
		startTime += (SDL_GetTicks() - pauseTime);
    }
}

void PlaybackController::playVideo() {
    if (mediaPlayer) {
        libvlc_media_player_play(mediaPlayer);
    }
}

void PlaybackController::resumeVideo() {
    if (mediaPlayer && !libvlc_media_player_is_playing(mediaPlayer)) {
        libvlc_media_player_play(mediaPlayer);
    }
}

void PlaybackController::play() {
    if (currentFile == nullptr) {
        std::cerr << "No file selected to play!" << std::endl;
        return;
    }
    if (currentFile->isAudio()) {
        loadAudioFile();
        playAudio();
    } else {
        loadVideoFile();
        playVideo();
    }
    startMonitor();
    status = PlaybackStatus::Playing;
}

void PlaybackController::resume() {
    if (currentFile->isAudio()) {
        resumeAudio();
    } else {
        resumeVideo();
    }
    startMonitor();
    status = PlaybackStatus::Playing;
}

void PlaybackController::pause() {
    if (Mix_PlayingMusic() == 1 && Mix_PausedMusic() == 0) {
        Mix_PauseMusic();
        pauseTime = SDL_GetTicks();
        status = PlaybackStatus::Paused;
    } else if (mediaPlayer && libvlc_media_player_is_playing(mediaPlayer)) {
        libvlc_media_player_pause(mediaPlayer);
        status = PlaybackStatus::Paused;
    }
}

void PlaybackController::stopAudio() {
    if (music != nullptr) {
        Mix_HaltMusic();
    }
}

void PlaybackController::stopVideo() {
    if (mediaPlayer) {
        libvlc_media_player_stop(mediaPlayer);
    }
}

void PlaybackController::stop() {
    if (currentFile->isAudio()) {
        stopAudio();
    } else {
        stopVideo();
    }
    status = PlaybackStatus::Stopped;
}

void PlaybackController::increaseVolume(){
    if (currentFile->isAudio()) {
        if(audioVolume<=128-16){
            audioVolume+=16;
            std::cout<<"audioVolume"<< audioVolume<<std::endl;
            Mix_VolumeMusic(audioVolume);
        }
        
    } else {
        if (mediaPlayer && videoVolume <= 100-10) {
            videoVolume += 10;
            libvlc_audio_set_volume(mediaPlayer, videoVolume);
        }
    }
}

void PlaybackController::decreaseVolume(){
    if (currentFile->isAudio()) {
        if(audioVolume >= 16){
            audioVolume-=16;
            std::cout<<"audioVolume"<< audioVolume<<std::endl;
            Mix_VolumeMusic(audioVolume);
        }
        
    } else {
        if (mediaPlayer && videoVolume >= 10) {
            videoVolume -= 10;
            libvlc_audio_set_volume(mediaPlayer, videoVolume);
        }
    }
}

void PlaybackController::next(PlaybackType type) {
    if (playmode == PlaybackMode::MediaFileMode) {
        while(1){
            if(currentIndex == module->getAllMediaFiles().size()-1)
            {
                currentIndex = 0;
            }
            else ++currentIndex;
            if(type == PlaybackType::Audio && module->getAllMediaFiles()[currentIndex]->isAudio())
            {
                currentFile = module->getAllMediaFiles()[currentIndex];
                play();
                return;
            }
            else if(type == PlaybackType::Video && (!module->getAllMediaFiles()[currentIndex]->isAudio()))
            {
                currentFile = module->getAllMediaFiles()[currentIndex];
                play();
                return;
            }
        }
    } else {
        if (currentIndex + 1 < currentPlaylist->getFiles().size()) {
            currentFile = currentPlaylist->getFiles()[++currentIndex];
            play();
        } else {
            currentIndex = 0;
            currentFile = currentPlaylist->getFiles()[currentIndex];
            play();
        }
    }
}

void PlaybackController::previous(PlaybackType type) {
    if (playmode == MediaFileMode) {
        while(1) {
            if (currentIndex == 0) {
                currentIndex = module->getAllMediaFiles().size() - 1;
            }
            else --currentIndex;
            if (type == PlaybackType::Audio && module->getAllMediaFiles()[currentIndex]->isAudio()) {
                currentFile = module->getAllMediaFiles()[currentIndex];
                play();
                return;
            } else if (type == PlaybackType::Video && !module->getAllMediaFiles()[currentIndex]->isAudio()) {
                currentFile = module->getAllMediaFiles()[currentIndex];
                play();
                return;
            }
        }
    } else {
        if (currentIndex > 0) {
            currentFile = currentPlaylist->getFiles()[--currentIndex];
            play();
        } else {
            currentIndex = currentPlaylist->getFiles().size() - 1;
            currentFile = currentPlaylist->getFiles()[currentIndex];
            play();
        }
    }
}

int PlaybackController::getcurrentTime() {
    if (currentFile->isAudio()) {
        if (Mix_PlayingMusic() == 1) {
            uint32_t currentTime = SDL_GetTicks() - startTime;
        	return static_cast<int>(currentTime / 1000);
    	} else {
        	return -1;
        }
    } else{
        if (mediaPlayer) {
            libvlc_time_t currentTime = libvlc_media_player_get_time(mediaPlayer) / 1000;
            return static_cast<int>(currentTime);
        } else {
            return -1;
        }
    }
    return -1;
}


std::shared_ptr<MediaFile> PlaybackController::getCurrentFile() {
    return currentFile;
}

PlaybackStatus PlaybackController::getStatus() {
    return status;
}

void PlaybackController::setCurrentIndex(int index){
    currentIndex = index;
}

void PlaybackController::startMonitor() {
    static bool isMonitoring = false;
    if (!isMonitoring) {
        isMonitoring = true;
        std::thread([this]() {
            while (status == PlaybackStatus::Playing) {
                if (((!currentFile->isAudio()) && (!libvlc_media_player_is_playing(mediaPlayer)))) {
                    next(PlaybackType::Video);
                    break;
                }
                if(Mix_PlayingMusic()==0 && currentFile->isAudio())
                {
                    next(PlaybackType::Audio);
                    break;
                }
                std::cout<< "Current Time:" << getcurrentTime() <<" / "<< currentFile->getMetadata()->getDuration()<<std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));} 
            isMonitoring = false;}).detach();}
    return;
}

