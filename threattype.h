#pragma once
#include "includes.h"

namespace threats{

#define TYPE_COUNT 3 //change when adding more types

enum class threatType
{
    Type_PUP,
    Type_Unknown,
    Type_Malicious,
};

class threat
{
public:
    threat(std::string fileLocation, threats::threatType type,std::string hash = "",int severity = 0);
    std::string returnFileLocation();
    std::string returnFileHash();
    void calculateFileHash();
    threatType returnThreatType();
    int returnSeverity();
    void setSeverity(int severity);
    void setFileLocation(std::string inFileLocation);
    void setThreatType(threatType inType);
    static std::string mapThreatTypeToStr(threatType inThreat);
    static threatType mapStrToThreatType(std::string inString);
    static std::string mapThreatTypeToShortStr(threatType inThreat);
private:
    threatType type;
    int severity;
    std::string fileHash;
    std::string fileLocation;
};

}
