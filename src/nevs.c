#include "nevs.h"

#include "debug.h"
#include "memory_manager.h"

#include <stdlib.h>
#include <string.h>

static_assert(sizeof(Nevs) == 60, "wrong size");

// 0x6391C8
Nevs* off_6391C8;

// 0x6391CC
int dword_6391CC;

// nevs_alloc
// 0x488340
Nevs* _nevs_alloc()
{
    if (off_6391C8 == NULL) {
        debugPrint("nevs_alloc(): nevs_initonce() not called!");
        exit(99);
    }

    for (int i = 0; i < NEVS_COUNT; i++) {
        Nevs* nevs = &(off_6391C8[i]);
        if (nevs->field_0 == 0) {
            memset(nevs, 0, sizeof(Nevs));
            return nevs;
        }
    }

    return NULL;
}

// 0x4883AC
void _nevs_close()
{
    if (off_6391C8 != NULL) {
        internal_free_safe(off_6391C8, __FILE__, __LINE__); // "..\\int\\NEVS.C", 97
        off_6391C8 = NULL;
    }
}

// 0x4883D4
void _nevs_removeprogramreferences(Program* program)
{
    if (off_6391C8 != NULL) {
        for (int i = 0; i < NEVS_COUNT; i++) {
            Nevs* nevs = &(off_6391C8[i]);
            if (nevs->field_0 != 0 && nevs->program == program) {
                memset(nevs, 0, sizeof(*nevs));
            }
        }
    }
}

// nevs_initonce
// 0x488418
void _nevs_initonce()
{
    // TODO: Incomplete.
    // _interpretRegisterProgramDeleteCallback(_nevs_removeprogramreferences);

    if (off_6391C8 == NULL) {
        off_6391C8 = internal_calloc_safe(sizeof(Nevs), NEVS_COUNT, __FILE__, __LINE__); // "..\\int\\NEVS.C", 131
        if (off_6391C8 == NULL) {
            debugPrint("nevs_initonce(): out of memory");
            exit(99);
        }
    }
}

// nevs_find
// 0x48846C
Nevs* _nevs_find(const char* a1)
{
    if (!off_6391C8) {
        debugPrint("nevs_find(): nevs_initonce() not called!");
        exit(99);
    }

    for (int index = 0; index < NEVS_COUNT; index++) {
        Nevs* nevs = &(off_6391C8[index]);
        if (nevs->field_0 != 0 && stricmp(nevs->field_4, a1) == 0) {
            return nevs;
        }
    }

    return NULL;
}

// 0x4884C8
int _nevs_addevent(const char* a1, Program* program, int proc, int a4)
{
    Nevs* nevs;

    nevs = _nevs_find(a1);
    if (nevs == NULL) {
        nevs = _nevs_alloc();
    }

    if (nevs == NULL) {
        return 1;
    }

    nevs->field_0 = 1;
    strcpy(nevs->field_4, a1);
    nevs->program = program;
    nevs->proc = proc;
    nevs->field_2C = a4;
    nevs->field_38 = NULL;

    return 0;
}

// nevs_clearevent
// 0x48859C
int _nevs_clearevent(const char* a1)
{
    debugPrint("nevs_clearevent( '%s');\n", a1);

    Nevs* nevs = _nevs_find(a1);
    if (nevs) {
        memset(nevs, 0, sizeof(Nevs));
        return 0;
    }

    return 1;
}

// nevs_signal
// 0x48862C
int _nevs_signal(const char* a1)
{
    debugPrint("nevs_signal( '%s');\n", a1);

    Nevs* nevs = _nevs_find(a1);
    if (nevs == NULL) {
        return 1;
    }

    debugPrint("nep: %p,  used = %u, prog = %p, proc = %d", nevs, nevs->field_0, nevs->program, nevs->proc);

    if (nevs->field_0 && (nevs->program && nevs->proc || nevs->field_38) && !nevs->field_34) {
        nevs->field_30++;
        dword_6391CC++;
        return 0;
    }

    return 1;
}

// nevs_update
// 0x4886AC
void _nevs_update()
{
    int v1;
    int v2;

    if (dword_6391CC == 0) {
        return;
    }

    debugPrint("nevs_update(): we have anyhits = %u\n", dword_6391CC);

    dword_6391CC = 0;

    for (int index = 0; index < NEVS_COUNT; index++) {
        Nevs* nevs = &(off_6391C8[index]);
        if (nevs->field_0 && (nevs->program && nevs->proc || nevs->field_38) && !nevs->field_34) {
            v1 = nevs->field_30;
            if (nevs->field_34 < v1) {
                v2 = v1 - 1;
                nevs->field_34 = 1;

                nevs->field_30--;

                dword_6391CC += v2;

                if (nevs->field_38 == NULL) {
                    _executeProc(nevs->program, nevs->proc);
                } else {
                    nevs->field_38();
                }

                nevs->field_34 = 0;

                if (nevs->field_2C == 0) {
                    memset(nevs, 0, sizeof(Nevs));
                }
            }
        }
    }
}
