#ifndef ERROR_H
#define ERROR_H

#include <QString>

// ok status
#define STATUS_OK 0x0

// program errors
#define ERR_NOT_IMPLEMENTED 0x1
#define ERR_NULL_PTR 0x2
#define ERROR_INVALID_PARAMETERS 0x3

// image data errors
#define ERR_MEM_CPY 0x4
#define ERR_ALLOC 0x5
#define ERR_EMPTY_IMG 0x6
#define ERR_TYPE 0x7

// image file errors
#define ERR_INVALID_FILE_TYPE 0x8
#define ERR_INVALID_FILE_OFFSET 0x9
#define ERR_INVALID_BMP_HEADER_SIZ 0xA
#define ERR_INVALID_BMP_BITS_PER_PIXEL 0xB
#define ERR_UNSUPPORTED_BMP_COMPRESSION 0xC
#define ERR_INVALID_BMP_SIZE 0xD

// file system
#define ERR_FILE_OPEN 0xE
#define ERR_FILE_READ 0xF
#define ERR_FILE_WRITE 0x10

// formating
#define ERR_SAME_FORMAT 0x11
#define ERR_INVALID_BIT_DEPTH 0x12

// steganografie
#define ERROR_MESSAGE_TOO_LONG 0x13
#define ERROR_NO_MESSAGE_FOUND 0x14
#define ERROR_INVALID_CRC 0x15


/**
 * @brief Ziska informaci v podobe textu o error codu, ktery v aplikaci nastal
 * @param errCode - Error code
 * @param buffer - Textovy buffer, do ktereho bude informace o vznikle chybe vlozena
 */
extern void getErrorCodeInfo(int errCode, QString & buffer);

#endif // ERROR_H
