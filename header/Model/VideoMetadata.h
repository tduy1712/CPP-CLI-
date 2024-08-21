#ifndef VIDEOMETADATA_H
#define VIDEOMETADATA_H

#include "Metadata.h"

class VideoMetadata : public Metadata
{
private:
    int bitrate;
    std::string codec;

public:
    VideoMetadata(std::string name = "", int duration = 0, int bitrate = 0,
                  std::string codec = "");

    void updateMetadata(const std::string &key,
                        const std::string &value) override;
    std::string getMetadata(const std::string &key) const override;
    void displayMetadata() const override;

    // Getter
    int getBitrate() const { return bitrate; }
    std::string getCodec() const { return codec; }
};

#endif  // VIDEOMETADATA_H