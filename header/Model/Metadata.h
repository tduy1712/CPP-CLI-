#ifndef METADATA_H
#define METADATA_H

#include <map>
#include <string>

enum MediaType
{
    AUDIO,
    VIDEO
};

class Metadata
{
protected:
    std::string name;
    MediaType type;
    int duration;
    std::map<std::string, std::string> metadataMap;

public:
    Metadata(std::string name = "", MediaType type = AUDIO, int duration = 0);
    virtual ~Metadata() = default;

    virtual void updateMetadata(const std::string &key,
                                const std::string &value);
    virtual std::string getMetadata(const std::string &key) const;
    virtual void addMetadata(const std::string &key, const std::string &value);
    virtual void displayMetadata() const;
    MediaType getType();
    std::string getName();
    int getDuration();
};

#endif  // METADATA_H