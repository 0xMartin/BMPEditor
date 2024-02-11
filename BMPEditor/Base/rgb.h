#ifndef RGB_H
#define RGB_H

#include <cstdint>
#include <vector>

/**
 * @brief The RGBQUAD class
 */
struct RGBQUAD {
    std::uint8_t blue;
    std::uint8_t green;
    std::uint8_t red;
    std::uint8_t reserved;

    bool operator==(const RGBQUAD& other) const {
        return (blue == other.blue &&
                green == other.green &&
                red == other.red &&
                reserved == other.reserved);
    }
};

/**
 * @brief Vypocita vzdalenost mezi dvema barvami
 * @param c1 - Barva 1
 * @param c2 - Barva 2
 * @return Vzdalenost
 */
extern double RGB_colorDistance(const RGBQUAD& c1, const RGBQUAD& c2);

/**
 * @brief Funkce pro kvantizaci obrazku
 * @param pixels - Obrazova data ve formatu RGB (3x uint8_t)
 * @param numColors - Pocet barev ve vysledne palete
 * @return Paleta barev
 */
extern std::vector<RGBQUAD> RGB_quantizeImage(const unsigned char * pixels, int width, int height, int numColors);

#endif // RGB_H
