#include "rgb.h"

#include <cmath>
#include <QDebug>

double RGB_colorDistance(const RGBQUAD& c1, const RGBQUAD& c2) {
    return sqrt(pow(c1.red - c2.red, 2) + pow(c1.green - c2.green, 2) + pow(c1.blue - c2.blue, 2));
}

std::vector<RGBQUAD> RGB_quantizeImage(const unsigned char * pixels, int width, int height, int numColors) {
    qDebug() << "QUANIZATION - start for number of colors (" << numColors << ")";

    // inicalizace palety barev
    std::vector<RGBQUAD> palette(numColors);

    // inicalizace indexu palety baver
    std::vector<int> colorIndices(width * height);

    // inicializace centroidu palety barev
    for (int i = 0; i < numColors; ++i) {
        palette[i].blue = pixels[i * 3];
        palette[i].green = pixels[i * 3 + 1];
        palette[i].red = pixels[i * 3 + 2];
        palette[i].reserved = 0;
    }

    // iterativni generovani palety barev
    bool converged = false;
    int i = 0;
    while (!converged) {
        qDebug() << "QUANIZATION - iteration: " << (i++);

        // prirazeni pixelu nejblizsimu centroidu
        for (int i = 0; i < width * height; ++i) {
            double minDist = colorDistance({pixels[i * 3], pixels[i * 3 + 1], pixels[i * 3 + 2], 0}, palette[0]);
            int minIndex = 0;
            for (int j = 1; j < numColors; ++j) {
                double dist = colorDistance({pixels[i * 3], pixels[i * 3 + 1], pixels[i * 3 + 2], 0}, palette[j]);
                if (dist < minDist) {
                    minDist = dist;
                    minIndex = j;
                }
            }
            colorIndices[i] = minIndex;
        }

        // vypocet novych centroidu
        std::vector<int> count(numColors, 0);
        std::vector<RGBQUAD> newPalette(numColors);
        for (int i = 0; i < width * height; ++i) {
            int index = colorIndices[i];
            newPalette[index].red += pixels[i * 3];
            newPalette[index].green += pixels[i * 3 + 1];
            newPalette[index].blue += pixels[i * 3 + 2];
            count[index]++;
        }
        for (int i = 0; i < numColors; ++i) {
            if (count[i] != 0) {
                newPalette[i].red /= count[i];
                newPalette[i].green /= count[i];
                newPalette[i].blue /= count[i];
            }
        }

        // kontrola konvergence
        converged = std::equal(palette.begin(), palette.end(), newPalette.begin());

        // aktualizace palety
        palette = newPalette;
    }

    qDebug() << "QUANIZATION - done";

    return palette;
}

