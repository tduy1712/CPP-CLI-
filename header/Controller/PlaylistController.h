#ifndef PLAYLISTCONTROLLER_H
#define PLAYLISTCONTROLLER_H

#include "CenterModule.h"
#include "Playlist.h"
#include "MediaController.h"
#include <memory>
#include <string>

class PlaylistController {
private:
    CenterModule* module;
    MediaController* mediaController;
public:
    PlaylistController(CenterModule* mod, MediaController* mediaCtrl);
    virtual ~PlaylistController();

    void createPlaylist(const std::string& name);
    void updatePlaylist(const std::shared_ptr<Playlist>& updatedPlaylist);
    void deletePlaylist(const std::string& name);
    void viewPlaylist(const std::string& name);

    void createPlaylistFromSelectedFiles(const std::string& name, MediaController& mediaController);
    void addFileToPlaylist(const std::string& playlistName, const std::string& filePath);
    void removeFileFromPlaylist(const std::string& playlistName, const std::string& filePath);
};

#endif // PLAYLISTCONTROLLER_H
