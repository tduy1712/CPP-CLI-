#ifndef USBCONTROLLER_H
#define USBCONTROLLER_H

extern "C" {
#include <libavformat/avformat.h>
}
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <algorithm> 
#include "CenterModule.h"
#include "MediaFile.h"
#include "AudioMetadata.h"
#include "VideoMetadata.h"

struct meta_data {
    std::string name = "Unknown";
    int duration = 0;
    std::string album = "Unknown";
    std::string artist = "Unknown";
    std::string genre = "Unknown";
    int bitrate = 0;
    std::string codec = "Unknown";
};

class USBController {
private:
    CenterModule* module;

public:
    USBController(CenterModule* mod);
    void mountDevice(const std::string& pathdevice, const std::string& mountPoint);
    std::shared_ptr<MediaFile> parseFile(const std::string& path);
    std::vector<std::shared_ptr<MediaFile>> parseFiles(const std::string& path);
    void processMetadata(const std::string& key, const std::string& value, meta_data& data);
};

#endif // USBCONTROLLER_H
