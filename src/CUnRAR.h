#ifndef _C_UNRAR_H_
#define _C_UNRAR_H_

#define STRICT
#include <windows.h>
#include "unrar.h"



#ifdef __cplusplus
extern "C" {
#endif // !__cplusplus


int UnRAR(const wchar_t* pFileName, const wchar_t* pPassword);


#ifdef __cplusplus
}
#endif // !__cplusplus

#endif // !_C_UNRAR_H_
