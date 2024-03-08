#ifndef HELPER_H
#define HELPER_H

#include <string>
#include "../include/miniaudio.h"

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

#endif