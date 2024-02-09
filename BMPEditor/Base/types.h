#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

struct RGBQUAD {
    std::uint8_t blue;
    std::uint8_t green;
    std::uint8_t red;
    std::uint8_t reserved;
};

#endif // TYPES_H
