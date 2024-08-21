#ifndef AUDIO_VIEW_H
#define AUDIO_VIEW_H

#include <iostream>
#include <vector>
#include <memory>
#include "MediaFile.h"
#include "AudioMetadata.h"

class AudioView {
public:
    void displayAudioList(const std::vector<std::shared_ptr<MediaFile>>& files);
    void displayAudioMetadata(AudioMetadata* metadata);
};

#endif // AUDIO_VIEW_H
