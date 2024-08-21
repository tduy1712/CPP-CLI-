#ifndef CENTER_MODULE_H
#define CENTER_MODULE_H

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include "Playlist.h"
#include "MediaFile.h"

class CenterModule {
private:
    std::unordered_map<std::string, std::shared_ptr<Playlist>> playlists;
    std::vector<std::shared_ptr<MediaFile>> mediaFiles;

public:
    CenterModule();

    void addPlaylist(const std::string &name, const std::shared_ptr<Playlist> &playlist);
    void addMediaFile(const std::shared_ptr<MediaFile> &mediaFile);
    std::shared_ptr<Playlist> getPlaylist(const std::string &name) const;
    std::unordered_map<std::string, std::shared_ptr<Playlist>> getAllPlaylists() const;
    std::vector<std::shared_ptr<MediaFile>> getAllMediaFiles() const;
};

#endif // CENTER_MODULE_H
