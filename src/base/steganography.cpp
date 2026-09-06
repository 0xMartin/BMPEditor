#include "steganography.h"

#include "error.h"

static uint32_t calculateCRC(const unsigned char *data, int length);

int STEGANOGRAPHY_writeMessage(unsigned char *pixels, uint32_t width, uint32_t height, QString &msg)
{
    if (pixels == nullptr || width == 0 || height == 0)
        return ERROR_INVALID_PARAMETERS;

    // prevod QString na pole znaku
    QByteArray byteArray = msg.toUtf8();
    const unsigned char *messageData = reinterpret_cast<const unsigned char*>(byteArray.constData());
    int messageLength = byteArray.length();

    // overeni zda se zprava a CRC kod zpravy vleze do pixel array (znak (8b) = rozlozeni do 8B, CRC (8b) = rozlozeni do 32B)
    // 8 B na 1 znak zpravy i +1 pro ukoncovaci znak stringu + 32 B pro uint32 CRC
    if (((messageLength + 1) * 8 + 32) > width * height * 3)
        return ERROR_MESSAGE_TOO_LONG;

    // vypocet CRC zpravy
    uint32_t crc = calculateCRC(messageData, messageLength);

    // zapis zpravy do pixelu obrazku
    int pixelIndex = 0;
    int bitIndex = 0;
    for (int i = 0; i < messageLength; ++i) {
        // zapis vsech bitu znaku do bajtu na nejmene vyznamnou pozici
        for (int j = 7; j >= 0; --j) {
            // ziskani bity aktualniho znaku
            bool bit = (messageData[i] >> j) & 1;
            // zapis bitu znaku do pixelu
            pixels[pixelIndex] &= ~1;
            pixels[pixelIndex] |= bit;
            ++pixelIndex;
            if (pixelIndex == width * height * 3)
                return ERROR_MESSAGE_TOO_LONG;
        }
    }

    // zapis ukoncovaciho znaku stringu
    for(int i = 0; i < 8; ++i) {
        pixels[pixelIndex] &= ~1;
        ++pixelIndex;
    }

    // zapis CRC do pixelu obrazku (stejny zpusobem jak zprava)
    for (int i = 0; i < 32; ++i) {
        bool bit = (crc >> (31 - i)) & 1;
        pixels[pixelIndex] &= ~1;
        pixels[pixelIndex] |= bit;
        ++pixelIndex;
        if (pixelIndex == width * height * 3)
            return ERROR_MESSAGE_TOO_LONG;
    }

    return STATUS_OK;
}

#include <QDebug>

int STEGANOGRAPHY_readMessage(const unsigned char *pixels, uint32_t width, uint32_t height, QString &msg)
{
    if (pixels == nullptr || width == 0 || height == 0)
        return ERROR_INVALID_PARAMETERS;

    int pixelIndex;

    // cteni zpravy z pixelu obrazku
    QByteArray byteArray;
    int bitIndex = 0;
    char currentChar = 0;
    for (pixelIndex = 0; pixelIndex < width * height * 3; ++pixelIndex) {
        // ziskani bitu zpravy z pixeloveho pole
        bool bit = pixels[pixelIndex] & 1;

        // zapis bitu do aktualniho znaku
        currentChar |= bit << (7 - bitIndex);
        ++bitIndex;

        // znak zpravy je sestaven cely
        if (bitIndex == 8) {
            // konec zpravy (0x0 : ukoncovaci znak)
            if (currentChar == 0) {
                ++pixelIndex;
                break;
            }
            byteArray.append(currentChar);
            currentChar = 0x0;
            bitIndex = 0;
        }
    }

    // cteni CRC z pixelu obrazu (32b = uint32, v pixelech vsak rozlozeno mezi 32B)
    uint32_t crc = 0x0;
    for (int i = pixelIndex; i < pixelIndex + 32; ++i) {
        if(i >= width * height * 3)
            return ERROR_NO_MESSAGE_FOUND;
        bool bit = pixels[i] & 1;
        crc |= (bit ? 1 : 0) << (31 - (i - pixelIndex));
    }

    // vypocet CRC prectene zpravy
    uint32_t computedCRC = calculateCRC(reinterpret_cast<const unsigned char*>(byteArray.constData()), byteArray.size());

    // kontorla CRC
    if (crc != computedCRC)
        return ERROR_INVALID_CRC;

    msg = QString::fromUtf8(byteArray.constData(), byteArray.size());
    if (msg.isEmpty())
        return ERROR_NO_MESSAGE_FOUND;

    return STATUS_OK;
}

int STEGANOGRAPHY_clearMessage(unsigned char *pixels, uint32_t width, uint32_t height)
{
    // precte puvodni zpravu z obrazku
    QString msg;
    int errCode = STEGANOGRAPHY_readMessage(pixels, width, height, msg);
    if(errCode != STATUS_OK)
        return errCode;

    // vypocita pocet bitu, ktere je treba odstranit s pixelu obrazku
    srand(time(0));
    uint32_t bitsToRemove = ((msg.length() + 1) * 8 + 32);
    for(int i = 0; i < bitsToRemove; ++i) {
        // pixel nahradi nahodne generovanym bitem
        pixels[i] &= ~1;
        pixels[i] |= ((uint8_t)(rand() % 2) & 0x1);
    }

    return STATUS_OK;
}

static uint32_t calculateCRC(const unsigned char *data, int length) {
    uint32_t crc = 0xFFFFFFFF;
    for (int i = 0; i < length; ++i) {
        for (int j = 7; j >= 0; --j) {
            bool bit = (data[i] >> j) & 1;
            crc ^= (bit ? 1 : 0) << 31;
            for (int k = 0; k < 8; ++k) {
                if (crc & 0x80000000)
                    crc = (crc << 1) ^ 0x04C11DB7;
                else
                    crc <<= 1;
            }
        }
    }
    return crc;
}
