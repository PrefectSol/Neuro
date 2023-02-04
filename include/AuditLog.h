#ifndef AUDITLOG_H
#define AUDITLOG_H

enum ErrorCode
{
    success = 0,

    unavailableModule = 2,

    invalidArguments,
    notEnoughArguments,
    cannotConvertStrToInt,
    cannotOpenFile,

    cannotCreateMatrix,
    indexOutsideMatrix,
    invalidMatrix,

    incorrectVectorSize,
    indexOutsideVector,
    
    invalidNetworkOffset,
};

#endif // !AUDITLOG_H