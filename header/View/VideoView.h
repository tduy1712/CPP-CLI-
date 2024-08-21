#ifndef VIDEO_VIEW_H
#define VIDEO_VIEW_H

#include <iostream>
#include <vector>
#include <memory>
#include "MediaFile.h"
#include "VideoMetadata.h"

class VideoView {
public:
    void displayVideoList(const std::vector<std::shared_ptr<MediaFile>>& files);
    void displayVideoMetadata(VideoMetadata* metadata);
};

#endif // VIDEO_VIEW_H
