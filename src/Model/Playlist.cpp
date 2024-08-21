#include "Playlist.h"

Playlist::Playlist() {}

Playlist::Playlist(const std::string &name) : name(name) {}

std::string Playlist::getName() const {
    return name;
}

void Playlist::setFiles(const std::vector<std::shared_ptr<MediaFile>>& newFiles) {
    files.clear();
    for (const auto& file : newFiles) {
        files[file->getPath()] = file;
    }
}

std::vector<std::shared_ptr<MediaFile>> Playlist::getFiles() const {
    std::vector<std::shared_ptr<MediaFile>> mediaFiles;
    for (const auto &entry : files) {
        mediaFiles.push_back(entry.second);
    }
    return mediaFiles;
}

void Playlist::addFile(const std::shared_ptr<MediaFile> &file) {
    files[file->getPath()] = file;
}

void Playlist::removeFile(const std::string &filePath) {
    files.erase(filePath);
}


