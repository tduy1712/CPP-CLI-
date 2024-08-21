#include "CenterModule.h"

CenterModule::CenterModule() {}

void CenterModule::addPlaylist(const std::string &name, const std::shared_ptr<Playlist> &playlist) {
    playlists[name] = playlist;
}

void CenterModule::addMediaFile(const std::shared_ptr<MediaFile> &mediaFile) {
    mediaFiles.push_back(mediaFile);
}

std::shared_ptr<Playlist> CenterModule::getPlaylist(const std::string &name) const {
    auto it = playlists.find(name);
    if (it != playlists.end()) {
        return it->second;
    }
    return nullptr;
}

std::unordered_map<std::string, std::shared_ptr<Playlist>> CenterModule::getAllPlaylists() const {
    return playlists;
}

std::vector<std::shared_ptr<MediaFile>> CenterModule::getAllMediaFiles() const {
    return mediaFiles;
}
