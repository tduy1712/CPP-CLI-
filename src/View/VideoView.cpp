#include "VideoView.h"

void VideoView::displayVideoList(const std::vector<std::shared_ptr<MediaFile>>& files) {
    if (files.empty()) {
        std::cout << "No audio files available.\n";
        return;
    }
    std::cout << "Video List:\n";
    int count=0;
    for (auto& file : files) {
        if(!file->isAudio())
        std::cout <<count++<<":"<< file->getPath()<< "\n";
    }
}

void VideoView::displayVideoMetadata(VideoMetadata* metadata) {
    std::cout << "Bitrate: " << metadata->getBitrate() << "\n";
    std::cout << "Codec: " << metadata->getCodec() << "\n";
}
