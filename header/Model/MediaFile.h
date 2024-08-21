#ifndef MEDIAFILE_H
#define MEDIAFILE_H

#include <string>
#include <memory>
#include <stdexcept>
#include "Metadata.h"

class MediaFile {
private:
    std::string path;
    std::shared_ptr<Metadata> metadata;

public:
    MediaFile(const std::string &path, const std::shared_ptr<Metadata> &metadata);

    std::string getPath() const;
    std::shared_ptr<Metadata> getMetadata() const;
    void setMetadata(const std::shared_ptr<Metadata> &metadata);
    bool isAudio();
};

#endif // MEDIAFILE_H
