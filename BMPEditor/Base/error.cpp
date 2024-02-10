#include "error.h"

void getErrorCodeInfo(int errCode, QString & buffer) {
    switch(errCode) {
    case ERR_NOT_IMPLEMENTED:
        buffer = "NOT IMPLEMENTED";
        break;
    case ERR_NULL_PTR:
        buffer = "NULL POINTER";
        break;
    case ERR_MEM_CPY:
        buffer = "MEMORY COPY";
        break;
    case ERR_ALLOC:
        buffer = "ALLOC";
        break;
    case ERR_EMPTY_IMG:
        buffer = "EMPTY IMAGE";
        break;
    case ERR_TYPE:
        buffer = "INVALID TYPE";
        break;
    case ERR_INVALID_FILE_TYPE:
        buffer = "INVALID FILE TYPE";
        break;
    case ERR_INVALID_FILE_OFFSET:
        buffer = "INVALID FILE OFFSET";
        break;
    case ERR_INVALID_BMP_HEADER_SIZ:
        buffer = "INVALID BMP IMAGE HEADER SIZE";
        break;
    case ERR_INVALID_BMP_BITS_PER_PIXEL:
        buffer = "INVALID BMP IMAGE BIT COUNT PER PIXEL";
        break;
    case ERR_UNSUPPORTED_BMP_COMPRESSION:
        buffer = "UNSUPPORTED BMP COMPRESSION";
        break;
    case ERR_INVALID_BMP_SIZE:
        buffer = "INVALID BMP IMAGE SIZE";
        break;
    case ERR_FILE_OPEN:
        buffer = "FAILED TO OPEN FILE";
        break;
    case ERR_FILE_READ:
        buffer = "FILE READ ERROR";
        break;
    }
}

