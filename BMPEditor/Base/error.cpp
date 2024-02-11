#include "error.h"

#include <QCoreApplication>

/******************************************************************************************************************************************/
// FUNCTION DEFINITION
/******************************************************************************************************************************************/

void getErrorCodeInfo(int errCode, QString & buffer) {
    switch(errCode) {
    case ERR_NOT_IMPLEMENTED:
        buffer = QObject::tr("NOT IMPLEMENTED");
        break;
    case ERR_NULL_PTR:
        buffer = QObject::tr("NULL POINTER");
        break;
    case ERROR_INVALID_PARAMETERS:
        buffer = QObject::tr("INVALID PARAMETERS");
        break;
    case ERR_MEM_CPY:
        buffer = QObject::tr("MEMORY COPY");
        break;
    case ERR_ALLOC:
        buffer = QObject::tr("ALLOC");
        break;
    case ERR_EMPTY_IMG:
        buffer = QObject::tr("EMPTY IMAGE");
        break;
    case ERR_TYPE:
        buffer = QObject::tr("INVALID TYPE");
        break;
    case ERR_INVALID_FILE_TYPE:
        buffer = QObject::tr("INVALID FILE TYPE");
        break;
    case ERR_INVALID_FILE_OFFSET:
        buffer = QObject::tr("INVALID FILE OFFSET");
        break;
    case ERR_INVALID_BMP_HEADER_SIZ:
        buffer = QObject::tr("INVALID BMP IMAGE HEADER SIZE");
        break;
    case ERR_INVALID_BMP_BITS_PER_PIXEL:
        buffer = QObject::tr("INVALID BMP IMAGE BIT COUNT PER PIXEL");
        break;
    case ERR_UNSUPPORTED_BMP_COMPRESSION:
        buffer = QObject::tr("UNSUPPORTED BMP COMPRESSION");
        break;
    case ERR_INVALID_BMP_SIZE:
        buffer = QObject::tr("INVALID BMP IMAGE SIZE");
        break;
    case ERR_FILE_OPEN:
        buffer = QObject::tr("FAILED TO OPEN FILE");
        break;
    case ERR_FILE_READ:
        buffer = QObject::tr("FILE READ ERROR");
        break;
    case ERR_SAME_FORMAT:
        buffer = QObject::tr("SAME IMAGE FORMAT");
        break;
    case ERR_INVALID_BIT_DEPTH:
        buffer = QObject::tr("INVALID BIT DEPTH");
        break;
    case ERROR_MESSAGE_TOO_LONG:
        buffer = QObject::tr("MESSAGE IS TOO LONG");
        break;
    case ERROR_NO_MESSAGE_FOUND:
        buffer = QObject::tr("MESSAGE NOT FOUND");
        break;
    case ERROR_INVALID_CRC:
        buffer = QObject::tr("INVALID CRC");
        break;
    default:
        buffer = QObject::tr("UNKNOWN");
        break;
    }
}

