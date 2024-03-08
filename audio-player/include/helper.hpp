#ifndef HELPER_H
#define HELPER_H

#include <string>
#include "miniaudio.hpp"

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

#endif