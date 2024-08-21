#include "VideoMetadata.h"
#include <iostream>

VideoMetadata::VideoMetadata(std::string name, int duration, int bitrate,
                             std::string codec)
    : Metadata(std::move(name), VIDEO, duration), bitrate(std::move(bitrate)),
      codec(std::move(codec)) {};

void VideoMetadata::updateMetadata(const std::string &key,
                                   const std::string &value)
{
    if (key == "bitrate")
    {
        try
        {
            bitrate = std::stoi(value);
        }
        catch (const std::invalid_argument &)
        {
            throw std::runtime_error("Invalid value for bitrate");
        }
    }
    else if (key == "codec")
    {
        codec = value;
    }
    else
    {
        Metadata::updateMetadata(key, value);
    }
}
std::string VideoMetadata::getMetadata(const std::string &key) const
{
    if (key == "bitrate")
    {
        return std::to_string(bitrate);
    }
    else if (key == "codec")
    {
        return codec;
    }
    else
    {
        return Metadata::getMetadata(key);
    }
}
void VideoMetadata::displayMetadata() const
{
    Metadata::displayMetadata();
    std::cout << "Bitrate: " << bitrate << std::endl;
    std::cout << "Codec: " << codec << std::endl;
}