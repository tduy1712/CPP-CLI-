#include "USBController.h"

USBController::USBController(CenterModule* mod) : module(mod) {}

void USBController::mountDevice(const std::string& pathdevice, const std::string& mountPoint) {
    // Code to mount a USB device

    // Command to mount
    std::string command = "sudo mount " + pathdevice + " " + mountPoint;
    int result = std::system(command.c_str());
    
    if (result == 0) {
        std::cout << "USB device mounted successfully at " << mountPoint << std::endl;
    } else {
        std::cerr << "Failed to mount USB device at " << mountPoint << std::endl;
    }
}

std::shared_ptr<MediaFile> USBController::parseFile(const std::string& path) {
    // Implementation details for parsing file
    meta_data data;

    AVFormatContext* format_context = nullptr;
    
    // open file
    if (avformat_open_input(&format_context, path.c_str(), nullptr, nullptr) != 0) {
        std::cerr << "Could not open file " << path << std::endl;
        return nullptr;
    }

    // information stream
    if (avformat_find_stream_info(format_context, nullptr) < 0) {
        std::cerr << "Could not find stream information" << std::endl;
        avformat_close_input(&format_context);
        return nullptr;
    }

    // information metadata
    AVDictionary* metadata = format_context->metadata;
    if (metadata) {
        AVDictionaryEntry* tag = nullptr;
        while ((tag = av_dict_get(metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
            processMetadata(tag->key, tag->value, data);
        }
    } else {
        std::cout << "No metadata found." << std::endl;
    }

    data.duration = format_context->duration / AV_TIME_BASE;
    data.bitrate = format_context->bit_rate;

    std::shared_ptr<Metadata> metadata_ptr;
    if (format_context->streams[0]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
        metadata_ptr = std::make_shared<AudioMetadata>(data.name, data.duration, data.album, data.artist, data.genre);
    } else if (format_context->streams[0]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
        metadata_ptr = std::make_shared<VideoMetadata>(data.name, data.duration, data.bitrate, data.codec);
    } else {
        return nullptr;
    }
    // close file
    avformat_close_input(&format_context);

    return std::make_shared<MediaFile>(path, metadata_ptr);
}

std::vector<std::shared_ptr<MediaFile>> USBController::parseFiles(const std::string& path) {
    std::vector<std::shared_ptr<MediaFile>> files;

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();
            std::string fileExtension = entry.path().extension().string();

            // Convert extension to lowercase for case-insensitive comparison
            std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);

            if (fileExtension == ".mp3" || fileExtension == ".mp4") {
                std::shared_ptr<MediaFile> mediaFile = parseFile(filePath);
                if (mediaFile) {
                    files.push_back(mediaFile);
                }
            }
        }
    }

    return files;
}

void USBController::processMetadata(const std::string& key, const std::string& value, meta_data& data) {
    if (key == "title") {
        std::cout << "Name: " << value << std::endl;
        data.name = value;
    } else if (key == "album") {
        std::cout << "Album: " << value << std::endl;
        data.album = value;
    } else if (key == "artist") {
        data.artist = value;
    } else if (key == "genre") {
        std::cout << "Genre: " << value << std::endl;
        data.genre = value;
    } else if (key == "codec_name") {
        data.codec = value;
        std::cout << "Codec: " << value << std::endl;
    } else {
        // do nothing
    }
}
