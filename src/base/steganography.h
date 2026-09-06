#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include <cstdint>
#include <QString>

/**
 * @brief Zapise zpravu do RGB obrazku (pouze pro obrazky, ktere nevyuzivaji color paletu)
 * @param pixels - Pixely RGB obrazku (3*uint8 na pixel), do ktereho bude zprava zapsana
 * @param width - Sirka obrazku v pixelech
 * @param height - Vyska obrazku v pixelech
 * @param msg - Zprava, ktera bude zapsana do obrazku
 * @return Error code
 */
extern int STEGANOGRAPHY_writeMessage(unsigned char * pixels, uint32_t width, uint32_t height, QString &msg);

/**
 * @brief Precte zpravu z RGB obrazku (pouze pro obrazky, ktere nevyuzivaji color paletu)
 * @param pixels - Pixely RGB obrazku (3*uint8 na pixel), ze ktereho bude zprava ctena
 * @param width - Sirka obrazku v pixelech
 * @param height - Vyska obrazku v pixelech
 * @param msg - Vystupni parametr, reference na QString, do ktereho bude zapsana zprava z obrazku
 * @return Error code
 */
extern int STEGANOGRAPHY_readMessage(const unsigned char * pixels, uint32_t width, uint32_t height, QString &msg);

/**
 * @brief Odstrani celou zpravu z obrazku
 * @param pixels - Pixely RGB obrazku (3*uint8 na pixel), ze ktereho bude zprava odstranena
 * @param width - Sirka obrazku v pixelech
 * @param height - Vyska obrazku v pixelech
 * @return Error code
 */
extern int STEGANOGRAPHY_clearMessage(unsigned char * pixels, uint32_t width, uint32_t height);

#endif // STEGANOGRAPHY_H
