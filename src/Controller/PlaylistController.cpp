#include "PlaylistController.h"
#include "MediaController.h"
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

PlaylistController::PlaylistController(CenterModule* mod, MediaController* mediaCtrl) 
    : module(mod), mediaController(mediaCtrl) {}

PlaylistController::~PlaylistController() {}

void PlaylistController::createPlaylist(const std::string& name) {
    auto pl = module->getAllPlaylists();
    if (pl.find(name) != pl.end()) {
        std::cout << "Playlist with name '" << name << "' already exists." << std::endl;
        return;
    }
    auto newPlaylist = std::make_shared<Playlist>(name);
    module->addPlaylist(name, newPlaylist);
    std::cout << "Playlist '" << name << "' created successfully." << std::endl;
}

void PlaylistController::updatePlaylist(const std::shared_ptr<Playlist>& updatedPlaylist) {
    if (!updatedPlaylist) {
        std::cout << "Updated playlist is null." << std::endl;
        return;
    }
    std::string oldName = updatedPlaylist->getName();
    auto pl = module->getAllPlaylists();
    if (pl.find(oldName) != pl.end()) {
        auto existingPlaylist = pl[oldName];
        existingPlaylist->setFiles(updatedPlaylist->getFiles());
        std::cout << "Playlist '" << updatedPlaylist->getName() << "' updated successfully." << std::endl;
    } else {
        std::cout << "Playlist with name '" << oldName << "' not found." << std::endl;
    }
}

void PlaylistController::deletePlaylist(const std::string& name) {
    auto pl = module->getAllPlaylists();
    if (pl.find(name) != pl.end()) {
        module->getAllPlaylists().erase(name);
        std::cout << "Playlist '" << name << "' deleted successfully." << std::endl;
    } else {
        std::cout << "Playlist with name '" << name << "' not found." << std::endl;
    }
}

void PlaylistController::viewPlaylist(const std::string& name) {
    auto pl = module->getAllPlaylists(); 
    if (pl.find(name) != pl.end()) {  
        auto playlist = pl[name];  
        std::cout << "Playlist Name: " << playlist->getName() << std::endl; 
        std::cout << "Files in the playlist:" << std::endl;
        
        // Lấy danh sách các file trong playlist và hiển thị chúng
        auto files = playlist->getFiles();
        if (files.empty()) {
            std::cout << "No files in this playlist." << std::endl;
        } else {
            for (const auto& file : files) {
                std::cout << " - " << file->getPath() << std::endl;
            }
        }
    } else {
        std::cout << "Playlist with name '" << name << "' not found." << std::endl;
    }
}

void PlaylistController::createPlaylistFromSelectedFiles(const std::string& name, MediaController& mediaController) {
    auto pl = module->getAllPlaylists();
    if (pl.find(name) != pl.end()) {
        std::cout << "Playlist with name '" << name << "' already exists." << std::endl;
        return;
    }

    auto selectedFiles = mediaController.getSelectedFiles();  
    if (selectedFiles.empty()) {
        std::cout << "No files selected to create playlist." << std::endl;
        return;
    }

    auto newPlaylist = std::make_shared<Playlist>(name);
    for (const auto& file : selectedFiles) {
        if (file) {
            newPlaylist->addFile(file);
        }
    }

    module->addPlaylist(name, newPlaylist);

    std::cout << "Playlist '" << name << "' created successfully with " << selectedFiles.size() << " files." << std::endl;
}

void PlaylistController::addFileToPlaylist(const std::string& playlistName, const std::string& filePath) {
    auto pl = module->getAllPlaylists();
    if (pl.find(playlistName) == pl.end()) {
        std::cout << "Playlist with name '" << playlistName << "' not found." << std::endl;
        return;
    }

    auto playlist = pl[playlistName];
    auto mediaFile = mediaController->parseFileMedia(filePath);
    if (mediaFile) {
        playlist->addFile(mediaFile);
        std::cout << "File '" << filePath << "' added to playlist '" << playlistName << "'." << std::endl;
    } else {
        std::cerr << "Could not parse file '" << filePath << "'." << std::endl;
    }
}

void PlaylistController::removeFileFromPlaylist(const std::string& playlistName, const std::string& filePath) {
    auto pl = module->getAllPlaylists();
    auto it = pl.find(playlistName); 

    if (it != pl.end()) {
        auto playlist = it->second; 
        auto files = playlist->getFiles();

        auto fileIt = std::find_if(files.begin(), files.end(), [&filePath](const std::shared_ptr<MediaFile>& file) {
            return file->getPath() == filePath;
        });

        if (fileIt != files.end()) {
            playlist->removeFile(filePath);
            std::cout << "File '" << filePath << "' removed from playlist '" << playlistName << "' successfully.\n";
        } else {
            std::cout << "File '" << filePath << "' not found in playlist '" << playlistName << "'.\n";
        }
    } else {
        std::cout << "Playlist with name '" << playlistName << "' not found.\n";
    }
}

