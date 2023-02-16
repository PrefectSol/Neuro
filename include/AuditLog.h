#ifndef AUDITLOG_H
#define AUDITLOG_H

// Reserved: 0 - Success, 1 - common type error, 2 - Run in debug mode
enum ErrorCode
{
    success = 0,

    unavailableModule = 3,
    cannotFindModule,
    moduleNotSelected,

    invalidArguments,
    notEnoughArguments,
    cannotConvertStrToInt,
    cannotOpenFile,

    cannotTransposeMatrix,
    cannotCreateMatrix,
    indexOutsideMatrix,
    invalidMatrixSize,
    invalidMatrix,

    invalidVectorSize,
    indexOutsideVector,
    
    invalidNetworkOffset,

    operationsFailed,
};

#endif // !AUDITLOG_H