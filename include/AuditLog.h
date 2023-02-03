#ifndef AUDITLOG_H
#define AUDITLOG_H

enum ErrorCode
{
    success = 0,

    unavailableModule = 2,

    notEnoughArguments,
    cannotConvertStrToInt,
    cannotOpenFile
};

#endif // !AUDITLOG_H