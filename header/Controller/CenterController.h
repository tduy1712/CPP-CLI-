#ifndef CENTERCONTROLLER_H
#define CENTERCONTROLLER_H

#include "CenterModule.h"
#include "View.h"
#include "MediaController.h"
#include "PlaylistController.h"
#include "USBController.h"
#include "PlaybackController.h"

#define AUDIO_PLAY_FILE '1'
#define AUDIO_PLAY_PLAYLIST '2'
#define VIDEO_PLAY '3'
#define EXIT '0'
#define PLAY_EXIT -1
#define NEXT 'n'
#define PREVIOUS 'p'
#define PAUSE 'u'
#define RESUME 'r'
#define INCRE_VOL '+'
#define DECRE_VOL '-'
#define CURRENT_TIME 't'

#define CREATE_PLAYLIST '1'
#define SELECT_FOLDER_AND_ADD_TO_PLAYLIST '2'
#define VIEW_PLAYLIST '3'
#define ADD_PLAYLIST '4'
#define DELETE_PLAYLIST '5'
#define REMOVE_FILE_FROM_PLAYLIST '6'
#define ADD_MEDIA '7'
#define USB '8'
#define EXIT_MANAGE_PLAYLISTS '9'



class CenterController {
private:
    CenterModule* module;
    View* view;
    MediaController* mediaController;
    PlaylistController* playlistController;
    USBController* usbController;
    PlaybackController* playbackController;

public:
    CenterController(CenterModule* mod, View* v);
    ~CenterController();

    // Function playback
    void Playback();
    void Playback_Playlist();
    void Playback_Audiofile();
    void Playback_Video();

    // Function to manage playlists
    void managePlaylists();
};

#endif // CENTERCONTROLLER_H
