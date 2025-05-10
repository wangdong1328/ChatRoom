#pragma once

#include <QPixmap>

enum class EFileType : unsigned short
{
    NORMAL_FILE,
    PICTURE,
    EXE,
    MUSIC
};

struct SFileInfo
{
    QString strFileName;
    EFileType eFileType;
    QString strContent;
    unsigned int uiFileSize;

    SFileInfo()
    {
        strFileName = "";
        eFileType = EFileType::NORMAL_FILE;
        strContent = "";
        uiFileSize = 0;
    }
};

enum class EMessageType : unsigned short
{
    TEXT = 0,
    FILE = 1
};

struct SMessageInfo
{
    EMessageType eType;
    QString strContent;
    SMessageInfo()
    {
        eType = EMessageType::TEXT;
        strContent = "";
    }
};

struct SUserData
{
    QPixmap pixUserHead;
    QString strUserName;
    QString strUserAccount;
    QString strReceiverUserAccount;
    bool bStatus;
    QPixmap pixStatusIcon;
    SMessageInfo stMessageInfo;
    QString strStatusText;
    int iIndex;
    Qt::Alignment alignment;
    bool bIsUnread;
    int iUnReadMessageNums;

    SUserData()
    {
        pixUserHead.load(":/res/ico/userhead.png");
        strUserName = "";
        strUserAccount = "";
        strReceiverUserAccount = "";
        bStatus = false;
        pixStatusIcon.load(":/res/ico/userhead.png");
        strStatusText = "";
        iIndex = 0;
        alignment = Qt::AlignLeft;
        bIsUnread = false;
        iUnReadMessageNums = 0;
    }
};
