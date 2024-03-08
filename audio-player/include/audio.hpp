#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <stdexcept>
#include "miniaudio.hpp"
#include "helper.hpp"

class Audio {
    public:
        Audio(std::string filename);
        ~Audio();
        void play();
    private:
        ma_result result;
        ma_decoder decoder;
        ma_device_config deviceConfig;
        ma_device device;
};

#endif