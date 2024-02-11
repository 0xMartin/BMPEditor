#include "rgb.h"

#include <QDebug>
#include <vector>
#include <algorithm>
#include <cstdint>

/******************************************************************************************************************************************/
// MACRO
/******************************************************************************************************************************************/

#define RED_CHANNEL 0x1
#define GREEN_CHANNEL 0x2
#define BLUE_CHANNEL 0x3

/******************************************************************************************************************************************/
// FUNCTION DECLARATION
/******************************************************************************************************************************************/

/**
 * @brief Navrati index kanalu barvy, ktery ma nejvetsi rozdil ve vstupnim vektoru pixelu
 * @param pixels - Vstupni vektor pixelu
 * @return Index RGB kanalu {RED_CHANNEL: 0x1, GREEN_CHANNEL: 0x2, BLUE_CHANNEL: 0x3}
 */
static uint8_t colorChannelWithGreatestRange(const std::vector<RGBQUAD_t>& pixels);

/**
 * @brief Kvantizacni rekurivni algoritmus zalozeny na algoritmu Median cut
 * @param pixels - Vstupni vektor RGB pixelu
 * @param initialDepth - Hloubka zanoreni algoritmu
 * @param maxDepth - Maximalni hloubka rekurze
 * @return Paleta RGB barev
 */
static std::vector<RGBQUAD_t> quantize(const std::vector<RGBQUAD_t>& pixels, int initialDepth, int maxDepth);

/******************************************************************************************************************************************/
// FUNCTION DEFINITION
/******************************************************************************************************************************************/

static uint8_t colorChannelWithGreatestRange(const std::vector<RGBQUAD_t>& pixels) {
    // inicializace minima a maxima RGB kanalu
    int rMin = 255, rMax = 0;
    int gMin = 255, gMax = 0;
    int bMin = 255, bMax = 0;

    // vypocet minima a maxima ve vstupnim vektoru pixelu
    for (const RGBQUAD_t& pixel : pixels) {
        rMin = std::min((int)(pixel.red), rMin);
        rMax = std::max((int)(pixel.red), rMax);
        gMin = std::min((int)(pixel.green), gMin);
        gMax = std::max((int)(pixel.green), gMax);
        bMin = std::min((int)(pixel.blue), bMin);
        bMax = std::max((int)(pixel.blue), bMax);
    }

    // vypocet difference (rozsahy RGB kanalu ve vstupnim vektoru)
    int diffRed = rMax - rMin;
    int diffGreen = gMax - gMin;
    int diffBlue = bMax - bMin;

    // urceni RGB kanalu s nejvetsim rozdilem
    if (diffRed >= diffGreen && diffRed >= diffBlue) {
        return RED_CHANNEL;
    } else if (diffGreen >= diffRed && diffGreen >= diffBlue) {
        return GREEN_CHANNEL;
    } else {
        return BLUE_CHANNEL;
    }
}

static std::vector<RGBQUAD_t> quantize(const std::vector<RGBQUAD_t>& pixels, int initialDepth, int maxDepth) {
    // dosazena maximalni hloubka rekurze nebo vstupni vektor pixelu jiz dale neni mozny delit na mensi casti
    if (initialDepth == maxDepth || pixels.size() <= 1) {
        // vypocet prumerne hodny pixelu
        uint64_t totalR = 0, totalG = 0, totalB = 0;
        for (const RGBQUAD_t& pixel : pixels) {
            totalR += pixel.red;
            totalG += pixel.green;
            totalB += pixel.blue;
        }
        RGBQUAD_t rgb;
        rgb.red = (uint8_t)(totalR / pixels.size());
        rgb.green = (uint8_t)(totalG / pixels.size());
        rgb.blue = (uint8_t)(totalB / pixels.size());
        return {rgb};
    }

    // urceni RGB kanalu, ktery ma nejvetsi rozdil ve vstupni pixel vektoru
    char channel = colorChannelWithGreatestRange(pixels);

    // serazeni vektoru podle RGB kanalu s nejvetsim rozdilem ve vektoru
    std::vector<RGBQUAD_t> sortedPixels = pixels;
    std::sort(sortedPixels.begin(), sortedPixels.end(), [channel](const RGBQUAD_t& lhs, const RGBQUAD_t& rhs) {
        if (channel == RED_CHANNEL) {
            return lhs.red < rhs.red;
        } else if (channel == GREEN_CHANNEL) {
            return lhs.green < rhs.green;
        } else {
            return lhs.blue < rhs.blue;
        }
    });

    // vypocet medianu
    double mid = sortedPixels.size() / 2;

    // rozdeleni serazeneho vstupniho vektoru podle medianu. pro obe rozdelene casti se rekurzivne znovu opakuje tento algoritmus
    std::vector<RGBQUAD_t> lowerPixels = quantize(std::vector<RGBQUAD_t>(sortedPixels.begin(), sortedPixels.begin() + mid),
                                                initialDepth + 1,
                                                maxDepth);
    std::vector<RGBQUAD_t> upperPixels = quantize(std::vector<RGBQUAD_t>(sortedPixels.begin() + mid, sortedPixels.end()),
                                                initialDepth + 1,
                                                maxDepth);

    // spojeni vysledku s rekurzi "lowerPixels" a "upperPixels" do finalniho vysledku
    std::vector<RGBQUAD_t> result;
    result.insert(result.end(), lowerPixels.begin(), lowerPixels.end());
    result.insert(result.end(), upperPixels.begin(), upperPixels.end());

    return result;
}

std::vector<RGBQUAD_t> RGB_generateColorPalette(const unsigned char * pixels, int width, int height, int numColors) {
    // prevod vstupni pixelovych dat obrazku na vektor RGBQUAD_t (vstupni bucket)
    std::vector<RGBQUAD_t> pixelVector;
    RGBQUAD_t pixel;
    for (int i = 0; i < width * height; ++i) {
        pixel.red = pixels[i * 3];
        pixel.green = pixels[i * 3 + 1];
        pixel.blue = pixels[i * 3 + 2];
        pixelVector.push_back(pixel);
    }

    // rekurzivni kvantizacni algoritmus vyuzivajici median cut algoritmus
    return quantize(pixelVector, 0, std::log2(numColors));
}

uint16_t RGB_findColorIndex(const RGBQUAD_t *palette, uint16_t paletteSize, uint8_t red, uint8_t green, uint8_t blue) {
    uint16_t closestIndex = 0;
    int closestDistance = std::numeric_limits<int>::max();
    for (uint16_t i = 0; i < paletteSize; ++i) {
        int distance = std::abs(palette[i].red - red) +
                       std::abs(palette[i].green - green) +
                       std::abs(palette[i].blue - blue);
        if (distance < closestDistance) {
            closestIndex = i;
            closestDistance = distance;
        }
    }
    return closestIndex;
}

