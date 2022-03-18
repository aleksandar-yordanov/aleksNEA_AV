#pragma once
#include "includes.h"

//Generic utilities header

#define pass (void)0

typedef struct _sigs_t {
    int16_t sig[16];
    const char *name;
    double score;
} sigs_t;

namespace utils
{
    template<class T> void safeDelete(T* ptr); //for raw unmanaged, non QPointers.

    template<class T> T safeMalloc(T* ptr); //for raw unmanaged, non QPointers.

    std::string boolToStr(bool state);

    bool checkStrToInt(std::string str);

    bool strToBool(std::string state);

    std::string getHomeDir();

    bool is_empty(std::ifstream& pFile);

    std::string intToStr(int x);
}
