#ifndef ERROREVENTS_H
#define ERROREVENTS_H
#include <QString>

struct ErrorEvents{

    enum ErrorCode{
        NoError,
        ItemNotExists,
        NotEnoughItems,
        UnKnown,
        NoAllowedNullValue,
        BackupFileAlreadyExist,
        ResctoreBackupAbrot,
        BackupFail,
        QueryFail

    }errorCode;

    ErrorEvents(){
        errorCode = NoError;
    }
    QString log;
    bool isValid(){ return errorCode != NoError;}

};
#endif // ERROREVENTS_H
