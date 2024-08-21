#ifndef PLAYLIST_VIEW_H
#define PLAYLIST_VIEW_H

#include <iostream>
#include <vector>
#include <memory>
#include "Playlist.h"

class PlaylistView {
public:
    void displayPlaylistList(const std::unordered_map<std::string, std::shared_ptr<Playlist>> &playlists);
    void displayPlaylist(const std::shared_ptr<Playlist>& playlist);
};

#endif // PLAYLIST_VIEW_H
