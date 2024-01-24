#include "CUnRAR.h"
#include <string.h>


//process different UnRAR events
int CALLBACK g_pfnRARProcessEvents(UINT uiEvent, LPARAM pUserData, LPARAM pParam1, LPARAM pParam2)
{
    //Process volume change.
    if(UCM_CHANGEVOLUME == uiEvent || UCM_CHANGEVOLUMEW == uiEvent)
    {
        //
        if(RAR_VOL_ASK == pParam2)
        {
            /*
            if(UCM_CHANGEVOLUME == uiEvent)
                printf("Required volume [%s] is absent.", (char*)pParam1);
            else
                printf("Required volume [%ls] is absent.", (wchar_t*)pParam1);
            */

            //terminate operation
            return -1;
        }

        //
        if(RAR_VOL_NOTIFY == pParam2)
        {
            /*
            if(UCM_CHANGEVOLUMEW == uiEvent)
                printf("Required volume [%ls] is successfully opened.", (wchar_t*)pParam1);
            else
                printf("Required volume [%s] is successfully opened.", (char*)pParam1);
            */

            //not process
            //return 0x00;

            //terminate operation
            return -1;
        }
    }

    //DLL needs a password to process an archive
    else if(UCM_NEEDPASSWORD == uiEvent || UCM_NEEDPASSWORDW == uiEvent)
    {
        //pParam1: contains the address pointing to the buffer for a password. You need to copy a password here.
        //pParam2: contains the size of password buffer in characters.

        if(UCM_NEEDPASSWORD == uiEvent)
        {
            //printf("DLL needs a [%ld] [%s] password to process an archive.", pParam2, (char*)pUserData);

            //
            memcpy((char*)pParam1, (char*)pUserData, (size_t)pParam2);
        }
        if(UCM_NEEDPASSWORDW == uiEvent)
        {
            //printf("DLL needs A [%ld] [%ls] password to process an archive.", pParam2, (wchar_t*)pUserData);

            //
            memcpy((wchar_t*)pParam1, (wchar_t*)pUserData, (size_t)pParam2);
        }
    }

    //Process unpacked data
    else if(UCM_PROCESSDATA == uiEvent)
    {
        //pParam1: contains the address pointing to the unpacked data.
        //pParam2: contains the size of the unpacked data.

        //not process
        //return 0x00;

        //canceling the operation
        return -1;
    }

    //Dictionary size of extracting file exceeds the limit
    else if(UCM_LARGEDICT == uiEvent)
    {
        //pParam1: contains the file dictionary size in kilobytes.
        //pParam2: contains the current dictionary size limit in kilobytes.

        //canceling the operation
        return -1;
    }

    //unknown event types
    else
    {
        //not process
        return 0x00;
    }

    //continues processing
    return 0x01;
}


int UnRAR(const wchar_t* pFileName, const wchar_t* pPassword)
{
    //setlocale(LC_CTYPE, "");
    //setlocale(LC_ALL, "en_US.utf8");
    //setlocale(LC_ALL, "");

    //
    if((NULL == pFileName) || (NULL == pPassword))
    {
        //qDebug("DLL Version = %d.", RARGetDllVersion());

        //成功操作
        return ERAR_SUCCESS;
    }

    //文件加密的取消测试结果值
    int iError = ERAR_UNKNOWN;

    //
    struct RAROpenArchiveDataEx stArchiveDataEx;
    {
        memset(&stArchiveDataEx, 0x00, sizeof(stArchiveDataEx));
        {
            stArchiveDataEx.ArcNameW = pFileName;
            stArchiveDataEx.OpenMode = RAR_OM_EXTRACT; //RAR_OM_LIST_INCSPLIT //RAR_OM_EXTRACT
            stArchiveDataEx.Callback = g_pfnRARProcessEvents;
            stArchiveDataEx.UserData = (long long)pPassword;

        }
    }

    //
    HANDLE pArchive = RAROpenArchiveEx(&stArchiveDataEx);
    {
        //文件名加密时回调取密码
        if(ROADF_ENCHEADERS == (stArchiveDataEx.Flags & ROADF_ENCHEADERS))
        {
            if(NULL == pArchive)
            {
                //失败操作
                return ERAR_BAD_PASSWORD;
            }

            //[隐含]成功操作
        }
        else
        {
            //有问题的非文件名加密存档文件, 或非正确解密的文件名加密存档文件
            //if(NULL == pArchive)
            if(ERAR_SUCCESS != stArchiveDataEx.OpenResult)
            {
                //中断操作
                return iError;
            }

            //
            struct RARHeaderDataEx stHeaderDataEx;
            {
                memset(&stHeaderDataEx, 0x00, sizeof(stHeaderDataEx));
                {
                    ;
                }
            }

            //
            RARReadHeaderEx(pArchive, &stHeaderDataEx);

            //文件加密测试文件时回调获取密码
            if(RHDF_ENCRYPTED == (stHeaderDataEx.Flags & RHDF_ENCRYPTED))
            {
                iError = RARProcessFileW(pArchive, RAR_TEST/* RAR_EXTRACT */, NULL, NULL);
            }

            //[隐含]成功操作
        }
    }

    //关闭存档文件
    if(NULL != pArchive)
    {
        RARCloseArchive(pArchive);
    }

    //成功操作
    return ((ERAR_UNKNOWN != iError) ? ERAR_BAD_PASSWORD : ERAR_SUCCESS);
}


