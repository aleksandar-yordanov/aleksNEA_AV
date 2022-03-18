#include "threattype.h"
using namespace threats;

threat::threat(std::string inFileLocation, threats::threatType inType, std::string hash,int severity)
{
    this->fileLocation = inFileLocation;
    this->type = inType;
    this->fileHash = hash;
    this->severity = severity;
}

std::string threat::returnFileLocation()
{
    return this->fileLocation;
}
threatType threat::returnThreatType()
{
    return this->type;
}
std::string threat::returnFileHash()
{
    return this->fileHash;
}
void threat::setFileLocation(std::string inFileLocation)
{
    this->fileLocation = inFileLocation;
}
void threat::setThreatType(threatType inType)
{
    this->type = inType;
}
void threat::calculateFileHash()
{
    QFile file(QString::fromStdString(this->fileLocation));
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray fileData = file.readAll();

        QByteArray hashData = QCryptographicHash::hash(fileData,QCryptographicHash::Md5); // or QCryptographicHash::Sha1
        this->fileHash = hashData.toHex();
    }
    else
    {
        this->fileHash = "0";
    }
}
threatType threat::mapStrToThreatType(std::string inString)
{
    if(inString == "Type_PUP")
    {
        return threatType::Type_PUP;
    }
    else if(inString == "Type_Unknown")
    {
        return threatType::Type_Unknown;
    }
    else if(inString == "Type_Malicious")
    {
        return threatType::Type_Malicious;
    }
    else
    {
        return threatType::Type_Unknown;
    }
}


int threat::returnSeverity()
{
    return this->severity;
}

void threat::setSeverity(int severity)
{
    this->severity = severity;
}

std::string threat::mapThreatTypeToStr(threatType inThreat)
{
    switch(inThreat)
    {
    case threatType::Type_Malicious:
        return "Type_Malicious";
        break;
    case threatType::Type_PUP:
        return "Type_PUP";
        break;
    case threatType::Type_Unknown:
        return "Type_Unknown";
        break;
    }
}

std::string threat::mapThreatTypeToShortStr(threatType inThreat)
{
    switch(inThreat)
    {
    case threatType::Type_Malicious:
        return "Mal";
        break;
    case threatType::Type_PUP:
        return "PUP";
        break;
    case threatType::Type_Unknown:
        return "Unk";
        break;
    }
}

