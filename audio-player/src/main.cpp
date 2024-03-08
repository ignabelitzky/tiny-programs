#define MINIAUDIO_IMPLEMENTATION
#include "../include/miniaudio.h"
#include <iostream>

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) {
        return;
    }

    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

    (void)pInput;
}

int main(int argc, char** argv)
{
    ma_result result;
    ma_decoder decoder;
    ma_device_config deviceConfig;
    ma_device device;

    if (argc < 2) {
        std::cout << "No input file...\n";
        return -1;
    }

    result = ma_decoder_init_file(argv[1], NULL, &decoder);
    if (result != MA_SUCCESS) {
        std::cout << "Could not load file: " << argv[1] << std::endl;
        return -2;
    }

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = decoder.outputFormat;
    deviceConfig.playback.channels = decoder.outputChannels;
    deviceConfig.sampleRate        = decoder.outputSampleRate;
    deviceConfig.dataCallback      = data_callback;
    deviceConfig.pUserData         = &decoder;

    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        std::cout << "Failed to open playback device.\n";
        ma_decoder_uninit(&decoder);
        return -3;
    }

    if (ma_device_start(&device) != MA_SUCCESS) {
        std::cout << "Failed to start playback device.\n";
        ma_device_uninit(&device);
        ma_decoder_uninit(&decoder);
        return -4;
    }

    std::cout << "Press Enter to quit...\n";
    getchar();

    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);

    return 0;
}