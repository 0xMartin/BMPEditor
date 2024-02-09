#ifndef ERROR_H
#define ERROR_H

#include <QString>

// ok status
#define STATUS_OK 0x0

// image data errors
#define ERR_NOT_IMPLEMENTED 0x1
#define ERR_NULL_PTR 0x2
#define ERR_MEM_CPY 0x3
#define ERR_ALLOC 0x4
#define ERR_EMPTY_IMG 0x5

// image file errors
#define ERR_INVALID_FILE_TYPE 0x6
#define ERR_INVALID_FILE_OFFSET 0x7
#define ERR_INVALID_BMP_HEADER_SIZ 0x8
#define ERR_INVALID_BMP_BITS_PER_PIXEL 0x9
#define ERR_UNSUPPORTED_BMP_COMPRESSION 0xA
#define ERR_INVALID_BMP_SIZE 0xB

// file system
#define ERR_FILE_OPEN 0xC
#define ERR_FILE_READ 0xD
#define ERR_FILE_WRITE 0xE


/**
 * @brief Ziska informaci v podobe textu o error codu, ktery v aplikaci nastal
 * @param errCode - Error code
 * @param buffer - Textovy buffer, do ktereho bude informace o vznikle chybe vlozena
 */
extern void getErrorCodeInfo(int errCode, QString & buffer);

#endif // ERROR_H
