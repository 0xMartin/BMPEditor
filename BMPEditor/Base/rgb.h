#ifndef RGB_H
#define RGB_H

#include <cstdint>
#include <vector>

#pragma pack(push, 1)

/**
 * @brief RGBQUAD_t struktura
 */
struct RGBQUAD_t {
    std::uint8_t blue;
    std::uint8_t green;
    std::uint8_t red;
    std::uint8_t reserved;

    bool operator==(const RGBQUAD_t& other) const {
        return (blue == other.blue &&
                green == other.green &&
                red == other.red &&
                reserved == other.reserved);
    }
};

#pragma pack(pop)

/**
 * @brief Funkce pro vygenerovani color palety pro libovolny obrazek. Vyuziva algoritmus Median cut.
 * @param pixels - Pixel obrazku, pro ktery bude paleta barev generovana (format pixelu: RGB 3 * uint8_t)
 * @param width - Sirka obrazku
 * @param height - Vyska obrazku
 * @param numColors - Pocet barev v palete
 * @return Vysledna paleta barev
 */
extern std::vector<RGBQUAD_t> RGB_generateColorPalette(const unsigned char * pixels, int width, int height, int numColors);

#endif // RGB_H
