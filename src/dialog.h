#ifndef DIALOG_H
#define DIALOG_H

#include "interpreter.h"

typedef void DialogFunc1(int win);
typedef void DialogFunc2(int win);

typedef struct STRUCT_56DAE0_FIELD_4_FIELD_C {
    char* field_0;
    char* field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    short field_18;
    short field_1A;
} STRUCT_56DAE0_FIELD_4_FIELD_C;

typedef struct STRUCT_56DAE0_FIELD_4 {
    void* field_0;
    char* field_4;
    void* field_8;
    STRUCT_56DAE0_FIELD_4_FIELD_C* field_C;
    int field_10;
    int field_14;
    int field_18; // probably font number
} STRUCT_56DAE0_FIELD_4;

typedef struct STRUCT_56DAE0 {
    Program* field_0;
    STRUCT_56DAE0_FIELD_4* field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
} STRUCT_56DAE0;

extern const float flt_501623;
extern const float flt_501627;

extern int dword_5184B4;
extern int dword_5184B8;
extern int dword_5184BC;
extern DialogFunc1* off_5184E4;
extern DialogFunc2* off_5184E8;
extern int gDialogBorderX;
extern int gDialogBorderY;
extern int gDialogOptionSpacing;
extern int dword_5184F8;
extern int dword_5184FC;
extern int dword_518500;
extern int dword_518504;
extern int dword_518508;

extern STRUCT_56DAE0 stru_56DAE0[4];
extern short word_56DB60;
extern int dword_56DB64;
extern int dword_56DB68;
extern int dword_56DB6C;
extern int dword_56DB70;
extern int dword_56DB74;
extern int dword_56DB7C;
extern int dword_56DB80;
extern int dword_56DB84;
extern int dword_56DB88;
extern int dword_56DB8C;
extern int dword_56DB90;
extern int dword_56DB94;
extern int gDialogReplyColorG;
extern int gDialogReplyColorB;
extern int gDialogOptionColorG;
extern int gDialogReplyColorR;
extern int gDialogOptionColorB;
extern int gDialogOptionColorR;
extern int dword_56DBB4;
extern int dword_56DBB8;
extern int dword_56DBBC;
extern void* off_56DBC0;
extern void* off_56DBC4;
extern void* off_56DBC8;
extern void* off_56DBCC;
extern char* gDialogReplyTitle;
extern int dword_56DBD4;
extern int dword_56DBD8;
extern int dword_56DBDC;
extern void* off_56DBE0;
extern void* off_56DBE4;
extern void* off_56DBE8;
extern void* off_56DBEC;

STRUCT_56DAE0_FIELD_4* _getReply();
void _replyAddOption(const char* a1, const char* a2, int a3);
void _replyAddOptionProc(const char* a1, const char* a2, int a3);
void _optionFree(STRUCT_56DAE0_FIELD_4_FIELD_C* a1);
void _replyFree();
int _endDialog();
void _printLine(int win, char** strings, int strings_num, int a4, int a5, int a6, int a7, int a8, int a9);
void _printStr(int win, char* a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9);
int _abortReply(int a1);
void _endReply();
void _drawStr(int win, char* a2, int font, int width, int height, int left, int top, int a8, int a9, int a10);
int _dialogStart(Program* a1);
int _dialogRestart();
int _dialogGotoReply(const char* a1);
int dialogSetReplyTitle(const char* a1);
int _dialogReply(const char* a1, const char* a2);
int _dialogOption(const char* a1, const char* a2);
int _dialogOptionProc(const char* a1, const char* a2);
int _dialogGetExitPoint();
int _dialogQuit();
int dialogSetOptionWindow(int a1, int a2, int a3, int a4, int a5);
int dialogSetReplyWindow(int a1, int a2, int a3, int a4, int a5);
int dialogSetBorder(int a1, int a2);
int _dialogSetScrollUp(int a1, int a2, void* a3, void* a4, void* a5, void* a6, int a7);
int _dialogSetScrollDown(int a1, int a2, void* a3, void* a4, void* a5, void* a6, int a7);
int dialogSetOptionSpacing(int value);
int dialogSetOptionColor(float a1, float a2, float a3);
int dialogSetReplyColor(float a1, float a2, float a3);
int _dialogSetOptionFlags(int flags);
void _dialogClose();
int _dialogGetDialogDepth();
void _dialogRegisterWinDrawCallbacks(DialogFunc1* a1, DialogFunc2* a2);
int _dialogToggleMediaFlag(int a1);
int _dialogGetMediaFlag();

#endif /* DIALOG_H */
