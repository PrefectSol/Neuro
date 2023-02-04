#ifndef AUDITLOG_H
#define AUDITLOG_H

enum ErrorCode
{
    success = 0,

    unavailableModule = 2,

    notEnoughArguments,
    cannotConvertStrToInt,
    cannotOpenFile,

    cannotCreateTheMatrix,
    indexOutsideTheMatrix,
    
    invalidNetworkOffset,
};

#endif // !AUDITLOG_H