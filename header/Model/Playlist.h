#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include "MediaFile.h"

class Playlist {
private:
    std::string name;
    std::unordered_map<std::string, std::shared_ptr<MediaFile>> files;

public:
    Playlist();
    Playlist(const std::string &name);

    std::string getName() const;
    void setFiles(const std::vector<std::shared_ptr<MediaFile>>& newFiles);
    std::vector<std::shared_ptr<MediaFile>> getFiles() const;
    void addFile(const std::shared_ptr<MediaFile> &file);
    void removeFile(const std::string &filePath);
};

#endif // PLAYLIST_H
