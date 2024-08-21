#ifndef MEDIA_CONTROLLER_H
#define MEDIA_CONTROLLER_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "CenterModule.h"
#include "MediaFile.h"

struct ada {
    std::string name ;
    int duration ;
    std::string album ;
    std::string artist;
    std::string genre;
    int bitrate;
    std::string codec ;
};

class MediaController {
private:
    CenterModule* module;
    std::vector<std::shared_ptr<MediaFile>> selectedFiles; 

public:
    MediaController(CenterModule* module);
    virtual ~MediaController();
    
    void selectFolderMedia(const std::string& folderPath);
    void processMetadataMedia(const std::string& key, const std::string& value, ada& data);
    std::shared_ptr<MediaFile> parseFileMedia(const std::string& path);

    void selectFile(const std::shared_ptr<MediaFile>& mediaFile);
    std::vector<std::shared_ptr<MediaFile>> getSelectedFiles() const;
};

#endif // MEDIA_CONTROLLER_H
