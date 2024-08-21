#include "AudioMetadata.h"
#include <iostream>

AudioMetadata::AudioMetadata(std::string name, int duration, std::string album,
                             std::string artist, std::string genre)
    : Metadata(std::move(name), AUDIO, duration), album(std::move(album)),
      artist(std::move(artist)), genre(std::move(genre)) {};

void AudioMetadata::updateMetadata(const std::string &key,
                                   const std::string &value)
{
    if (key == "album")
    {
        album = value;
    }
    else if (key == "artist")
    {
        artist = value;
    }
    else if (key == "genre")
    {
        genre = value;
    }
    else
    {
        Metadata::updateMetadata(key, value);
    }
}
std::string AudioMetadata::getMetadata(const std::string &key) const
{
    if (key == "album")
    {
        return album;
    }
    else if (key == "artist")
    {
        return artist;
    }
    else if (key == "genre")
    {
        return genre;
    }
    else
    {
        return Metadata::getMetadata(key);
    }
}
void AudioMetadata::displayMetadata() const
{
    Metadata::displayMetadata();
    std::cout << "Album: " << album << std::endl;
    std::cout << "Artist: " << artist << std::endl;
    std::cout << "Genre: " << genre << std::endl;
}