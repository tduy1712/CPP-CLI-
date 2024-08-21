#include "MediaController.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <filesystem>
#include <AudioMetadata.h>
#include <VideoMetadata.h>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

MediaController::MediaController(CenterModule* module) : module(module) {
}
MediaController::~MediaController() {}

std::shared_ptr<MediaFile> MediaController::parseFileMedia(const std::string& path) {
    ada data;
    AVFormatContext* format_context = nullptr;

    // Oprn file
    if (avformat_open_input(&format_context, path.c_str(), nullptr, nullptr) != 0) {
        std::cerr << "Could not open file " << path << std::endl;
        return nullptr;
    }

    // Find info stream
    if (avformat_find_stream_info(format_context, nullptr) < 0) {
        std::cerr << "Could not find stream information" << std::endl;
        avformat_close_input(&format_context);
        return nullptr;
    }

    // Get info metadata
    AVDictionary* metadata = format_context->metadata;
    if (metadata) {
        AVDictionaryEntry* tag = nullptr;
        while ((tag = av_dict_get(metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
            processMetadataMedia(tag->key, tag->value, data);
        }
    } else {
        std::cout << "No metadata found." << std::endl;
    }

    data.duration = format_context->duration / AV_TIME_BASE;
    data.bitrate = format_context->bit_rate;

    std::shared_ptr<Metadata> metadata_ptr;
    if(format_context->streams[0]!=nullptr)
    {
    if (format_context->streams[0]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
        metadata_ptr = std::make_shared<AudioMetadata>(data.name, data.duration, data.album, data.artist, data.genre);
    } else if (format_context->streams[0]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
        metadata_ptr = std::make_shared<VideoMetadata>(data.name, data.duration, data.bitrate, data.codec);
    } else {
        return nullptr;
    }

    avformat_close_input(&format_context);
    }
    return std::make_shared<MediaFile>(path, metadata_ptr);
}

void MediaController::processMetadataMedia(const std::string& key, const std::string& value, ada& data) {
    if (key == "title") {
        data.name = value;
    } else if (key == "album") {
        std::cout << "Album: " << value << std::endl;
        data.album = value;
    } else if (key == "artist") {
        data.artist = value;
    } else if (key == "genre") {
        data.genre = value;
        std::cout << "Genre: " << value << std::endl;
    } else if (key == "codec_name") {
        data.codec = value;
        std::cout << "Codec: " << value << std::endl;
    }
    return ;
}

void MediaController::selectFolderMedia(const std::string& folderPath) {
    if (!std::filesystem::exists(folderPath) || !std::filesystem::is_directory(folderPath)) {
        std::cerr << "The provided path is not a valid directory." << std::endl;
        return;
    }
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();
            std::string fileExtension = entry.path().extension().string();

            std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);

            if (fileExtension == ".mp3" || fileExtension == ".mp4") {
                std::shared_ptr<MediaFile> mediaFile = parseFileMedia(filePath);
                if (mediaFile) {
                    selectedFiles.push_back(mediaFile);  
                }
            }
            
        }
    }
    for(auto& selectfile: selectedFiles )
       {module->addMediaFile(selectfile);}
    std::cout << "Total selected files: " << selectedFiles.size() << std::endl;  
}


void MediaController::selectFile(const std::shared_ptr<MediaFile>& mediaFile) {
    selectedFiles.push_back(mediaFile);
}

std::vector<std::shared_ptr<MediaFile>> MediaController::getSelectedFiles() const {
    return selectedFiles;
}

