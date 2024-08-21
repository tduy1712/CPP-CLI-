#include "Metadata.h"
#include <iostream>

Metadata::Metadata(std::string name, MediaType type, int duration)
    : name(std::move(name)), type(type), duration(duration)
{
}

void Metadata::updateMetadata(const std::string &key, const std::string &value)
{
    auto it = metadataMap.find(key);
    if (it != metadataMap.end())
    {
        it->second = value;
    }
    else
    {
        throw std::runtime_error("Key not found. Update failed.");
    }
}

std::string Metadata::getMetadata(const std::string &key) const
{
    auto it = metadataMap.find(key);
    if (it != metadataMap.end())
    {
        return it->second;
    }
    return "Key not found";
}

void Metadata::addMetadata(const std::string &key, const std::string &value)
{
    auto it = metadataMap.find(key);
    if (it == metadataMap.end())
    {
        metadataMap[key] = value;
    }
    else
    {
        throw std::runtime_error("Key already exists. Add failed.");
    }
}

void Metadata::displayMetadata() const
{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Type: " << (type == AUDIO ? "Audio" : "Video") << std::endl;
    std::cout << "Duration: " << duration << std::endl;
    for (const auto &entry : metadataMap)
    {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
}

MediaType Metadata::getType()
{
    return type;
}

std::string Metadata::getName(){
    return name;
 }

int Metadata::getDuration(){
    return duration;
 }

