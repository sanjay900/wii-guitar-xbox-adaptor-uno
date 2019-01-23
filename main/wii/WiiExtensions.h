#pragma once
#include <inttypes.h>
enum class ExtensionType
{
    NoController,
    UnknownController,
    Nunchuk,
    ClassicController,
    GuitarController,
    DrumController,
    DJTurntableController,
};
inline ExtensionType identifyController(volatile uint8_t *idData)
{
    if (idData[2] == 0xA4 && idData[3] == 0x20)
    { // All valid IDs
        // Nunchuk ID: 0x0000
        if (idData[4] == 0x00 && idData[5] == 0x00)
        {
            return ExtensionType::Nunchuk;
        }

        // Classic Con. ID: 0x0101
        else if (idData[4] == 0x01 && idData[5] == 0x01)
        {
            return ExtensionType::ClassicController;
        }

        // Guitar Hero Controllers: 0x##00, 0xA420, 0x0103
        else if (idData[1] == 0x00 && idData[4] == 0x01 && idData[5] == 0x03)
        {

            // Guitar: 0x00
            if (idData[0] == 0x00)
            {
                return ExtensionType::GuitarController;
            }
            // Drums: 0x01
            else if (idData[0] == 0x01)
            {
                return ExtensionType::DrumController;
            }
            // DJ Turntable: 0x03
            else if (idData[0] == 0x03)
            {
                return ExtensionType::DJTurntableController;
            }
        }
    }

    return ExtensionType::UnknownController; // No matches
}