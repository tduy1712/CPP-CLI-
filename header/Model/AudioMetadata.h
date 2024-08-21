#ifndef AUDIOMETADATA_H
#define AUDIOMETADATA_H

#include "Metadata.h"

class AudioMetadata : public Metadata
{
private:
    std::string album;
    std::string artist;
    std::string genre;

public:
    AudioMetadata(std::string name = "", int duration = 0,
                  std::string album = "", std::string artist = "",
                  std::string genre = "");

    void updateMetadata(const std::string &key,
                        const std::string &value) override;
    std::string getMetadata(const std::string &key) const override;
    void displayMetadata() const override;

    // Getter
    std::string getAlbum() const { return album; }
    std::string getArtist() const { return artist; }
    std::string getGenre() const { return genre; }
};

#endif  // AUDIOMETADATA_H