#ifndef WACCGL_DISABLE_COMPATIBILITY_MODULE

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _CONSOLE_FONT_INFOEX {
  ULONG cbSize;
  DWORD nFont;
  COORD dwFontSize;
  UINT  FontFamily;
  UINT  FontWeight;
  WCHAR FaceName[LF_FACESIZE];
} CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

BOOL WINAPI GetCurrentConsoleFont(HANDLE hConsoleOutput,BOOL bMaximumWindow,PCONSOLE_FONT_INFO lpConsoleCurrentFont);
BOOL WINAPI GetCurrentConsoleFontEx(HANDLE hConsoleOutput,BOOL bMaximumWindow,PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);
BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput,BOOL bMaximumWindow,PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);
#ifdef __cplusplus
}
#endif

#ifndef COMMON_LVB_UNDERSCORE
#define COMMON_LVB_UNDERSCORE 0
#endif

#else

#warning "The WACCGL compatibility module was turned off - macro WACCGL_DISABLE_COMPATIBILITY_MODULE was defined (this may break some functions of WACCGL)"

#endif
