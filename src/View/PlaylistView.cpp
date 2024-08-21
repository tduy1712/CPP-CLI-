#include "PlaylistView.h"

void PlaylistView::displayPlaylistList(const std::unordered_map<std::string, std::shared_ptr<Playlist>> &playlists) {
    std::cout << "Playlist List:\n";
    if (playlists.empty()) {
        std::cout << "No playlists available.\n";
        return;
    }
    for (const auto& pair : playlists) {
        std::cout << pair.first << "\n";
    }
}

void PlaylistView::displayPlaylist(const std::shared_ptr<Playlist>& playlist){
    if (!playlist) {
        std::cout << "Playlist is null.\n";
        return;
    }

    std::cout << "Playlist: " << playlist->getName() << "\n";
    const auto& files = playlist->getFiles();
    if (files.empty()) {
        std::cout << "This playlist is empty.\n";
        return;
    }
    int count=0;
    for (const auto& file : files) {
        std::cout<<count++<<":" << file->getMetadata()->getName() << "\n";
    }
}
