#include "AudioView.h"

void AudioView::displayAudioList(const std::vector<std::shared_ptr<MediaFile>>& files) {
    if (files.empty()) {
        std::cout << "No audio files available.\n";
        return;
    }
    std::cout << "Audio List:\n";
    int count=0;
    for (auto& file : files) {
        if(file->isAudio())
        std::cout <<count++<<":"<< file->getMetadata()->getName()<< "\n";
    }
}

void AudioView::displayAudioMetadata(AudioMetadata* metadata) {
    std::cout << "Album: " << metadata->getAlbum() << "\n";
    std::cout << "Artist: " << metadata->getArtist() << "\n";
    std::cout << "Genre: " << metadata->getGenre() << "\n";
}
