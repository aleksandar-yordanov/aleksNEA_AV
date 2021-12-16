#pragma once
#include "includes.h"

#define pass (void)0

typedef struct _sigs_t {
    int16_t sig[16];
    const char *name;
    double score;
} sigs_t;


namespace utils
{

    std::string boolToStr(bool state);

    bool strToBool(std::string state);

    std::string getHomeDir();

    bool is_empty(std::ifstream& pFile);
}
