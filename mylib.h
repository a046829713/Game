/* mylib.h */
#ifndef MYLIB_H
#define MYLIB_H


#ifdef _WIN32
#  ifdef MYLIB_EXPORTS          // 編 DLL 時定義
#    define MYAPI __declspec(dllexport)
#  else                         // 使用 DLL 時
#    define MYAPI __declspec(dllimport)
#  endif
#else
#  define MYAPI                 // 其他平台留空
#endif


MYAPI double add(double a, double b); // 函數聲明
#endif