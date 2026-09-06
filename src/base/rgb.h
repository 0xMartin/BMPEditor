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

/**
 * @brief Najde index barvy v palete barev podle predanych argumentu funkce
 * @param palette - Ukazatel na paletu barev BMP obrazku
 * @param paletteSize - Velikost palety barev
 * @param red - Cervena slozka pixelu
 * @param green - Zelena slozka pixelu
 * @param blue - Modra slozka pixelu
 * @return Index barvy pixelu v palete barev (pokud neni barva primo nalezena tak barva s nejblizsi podobnosti)
 */
extern uint16_t RGB_findColorIndex(const RGBQUAD_t *palette, uint16_t paletteSize, uint8_t red, uint8_t green, uint8_t blue);

#endif // RGB_H
