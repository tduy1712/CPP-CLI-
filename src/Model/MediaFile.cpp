#include "MediaFile.h"

MediaFile::MediaFile(const std::string &path, const std::shared_ptr<Metadata> &metadata)
    : path(path), metadata(metadata) {}

std::string MediaFile::getPath() const {
    return path;
}

std::shared_ptr<Metadata> MediaFile::getMetadata() const {
    return metadata;
}

// void MediaFile::setMetadata(const std::shared_ptr<Metadata> &metadata) {
//     if (metadata) {
//         this->metadata = metadata;
//     } else {
//         throw std::invalid_argument("Metadata cannot be null");
//     }
// }

bool MediaFile::isAudio() {
    return (metadata->getType() == MediaType::AUDIO);
}
