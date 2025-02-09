#ifndef INTERFACE_H
#define INTERFACE_H

#include "art.h"
#include "db.h"
#include "geometry.h"
#include "obj_types.h"

#include <stdbool.h>

typedef enum Hand {
    // Item1 (Punch)
    HAND_LEFT,
    // Item2 (Kick)
    HAND_RIGHT,
    HAND_COUNT,
} Hand;

typedef enum InterfaceAction {
    INTERFACE_ACTION_USE,
    INTERFACE_ACTION_PRIMARY,
    INTERFACE_ACTION_PRIMARY_AIMING,
    INTERFACE_ACTION_SECONDARY,
    INTERFACE_ACTION_SECONDARY_AIMING,
    INTERFACE_ACTION_RELOAD,
    INTERFACE_ACTION_COUNT,
} InterfaceAction;

// The values of it's members are offsets to beginning of numbers in
// numbers.frm.
typedef enum InterfaceNumbersColor {
    INTERFACE_NUMBERS_COLOR_WHITE = 0,
    INTERFACE_NUMBERS_COLOR_YELLOW = 120,
    INTERFACE_NUMBERS_COLOR_RED = 240,
} InterfaceNumbersColor;

// The maximum number of indicator boxes the indicator bar can display.
//
// For unknown reason this number is 6, even though there are only 5 different
// indicator types. In addition to that, default screen width 640px cannot hold
// 6 boxes 130px each.
#define INDICATOR_SLOTS_COUNT (6)

// Available indicators.
//
// Indicator boxes in the bar are displayed according to the order of this enum.
typedef enum Indicator {
    INDICATOR_ADDICT,
    INDICATOR_SNEAK,
    INDICATOR_LEVEL,
    INDICATOR_POISONED,
    INDICATOR_RADIATED,
    INDICATOR_COUNT,
} Indicator;

// Provides metadata about indicator boxes.
typedef struct IndicatorDescription {
    // An identifier of title in `intrface.msg`.
    int title;

    // A flag denoting this box represents something harmful to the player. It
    // affects color of the title.
    bool isBad;

    // Prerendered indicator data.
    //
    // This value is provided at runtime during indicator box initialization.
    // It includes indicator box background with it's title positioned in the
    // center and is green colored if indicator is good, or red otherwise, as
    // denoted by [isBad] property.
    unsigned char* data;
} IndicatorDescription;

typedef struct STRUCT_5970F8 {
    Object* item;
    unsigned char isDisabled;
    unsigned char isWeapon;
    int primaryHitMode;
    int secondaryHitMode;
    int field_10;
    int itemFid;
} STRUCT_5970F8;

extern bool gInterfaceBarInitialized;
extern bool gInterfaceBarSwapHandsInProgress;
extern bool gInterfaceBarEnabled;
extern bool dword_518F14;
extern int gInventoryButton;
extern CacheEntry* gInventoryButtonUpFrmHandle;
extern CacheEntry* gInventoryButtonDownFrmHandle;
extern int gOptionsButton;
extern CacheEntry* gOptionsButtonUpFrmHandle;
extern CacheEntry* gOptionsButtonDownFrmHandle;
extern int gSkilldexButton;
extern CacheEntry* gSkilldexButtonUpFrmHandle;
extern CacheEntry* gSkilldexButtonDownFrmHandle;
extern CacheEntry* gSkilldexButtonMaskFrmHandle;
extern int gMapButton;
extern CacheEntry* gMapButtonUpFrmHandle;
extern CacheEntry* gMapButtonDownFrmHandle;
extern CacheEntry* gMapButtonMaskFrmHandle;
extern int gPipboyButton;
extern CacheEntry* gPipboyButtonUpFrmHandle;
extern CacheEntry* gPipboyButtonDownFrmHandle;
extern int gCharacterButton;
extern CacheEntry* gCharacterButtonUpFrmHandle;
extern CacheEntry* gCharacterButtonDownFrmHandle;
extern int gSingleAttackButton;
extern CacheEntry* gSingleAttackButtonUpHandle;
extern CacheEntry* gSingleAttackButtonDownHandle;
extern CacheEntry* off_518F74;
extern int gInterfaceCurrentHand;
extern const Rect gInterfaceBarMainActionRect;
extern int gChangeHandsButton;
extern CacheEntry* gChangeHandsButtonUpFrmHandle;
extern CacheEntry* gChangeHandsButtonDownFrmHandle;
extern CacheEntry* gChangeHandsButtonMaskFrmHandle;
extern bool gInterfaceBarEndButtonsIsVisible;
extern const Rect gInterfaceBarEndButtonsRect;
extern int gEndTurnButton;
extern CacheEntry* gEndTurnButtonUpFrmHandle;
extern CacheEntry* gEndTurnButtonDownFrmHandle;
extern int gEndCombatButton;
extern CacheEntry* gEndCombatButtonUpFrmHandle;
extern CacheEntry* gEndCombatButtonDownFrmHandle;
extern unsigned char* gGreenLightFrmData;
extern unsigned char* gYellowLightFrmData;
extern unsigned char* gRedLightFrmData;
extern const Rect gInterfaceBarActionPointsBarRect;
extern unsigned char* gNumbersFrmData;
extern IndicatorDescription gIndicatorDescriptions[INDICATOR_COUNT];
extern int gInterfaceBarWindow;
extern int gIndicatorBarWindow;
extern int gInterfaceLastRenderedHitPoints;
extern int gInterfaceLastRenderedHitPointsColor;
extern int gInterfaceLastRenderedArmorClass;

extern int gIndicatorSlots[INDICATOR_SLOTS_COUNT];
extern STRUCT_5970F8 stru_5970F8[HAND_COUNT];
extern CacheEntry* gYellowLightFrmHandle;
extern CacheEntry* gRedLightFrmHandle;
extern CacheEntry* gNumbersFrmHandle;
extern bool gIndicatorBarIsVisible;
extern unsigned char* gChangeHandsButtonUpFrmData;
extern CacheEntry* gGreenLightFrmHandle;
extern unsigned char* gEndCombatButtonUpFrmData;
extern unsigned char* gEndCombatButtonDownFrmData;
extern unsigned char* gChangeHandsButtonDownFrmData;
extern unsigned char* gEndTurnButtonDownFrmData;
extern unsigned char byte_597154[12596];
extern unsigned char* gEndTurnButtonUpFrmData;
extern unsigned char* gChangeHandsButtonMaskFrmData;
extern unsigned char* gCharacterButtonUpFrmData;
extern unsigned char* gSingleAttackButtonUpData;
extern unsigned char* off_59A298;
extern unsigned char* gMapButtonDownFrmData;
extern unsigned char* gPipboyButtonUpFrmData;
extern unsigned char* gCharacterButtonDownFrmData;
extern unsigned char* gSingleAttackButtonDownData;
extern unsigned char* gPipboyButtonDownFrmData;
extern unsigned char* gMapButtonMaskFrmData;
extern unsigned char byte_59A2B4[12596];
extern unsigned char* gMapButtonUpFrmData;
extern unsigned char* gSkilldexButtonMaskFrmData;
extern unsigned char* gSkilldexButtonDownFrmData;
extern unsigned char* gInterfaceWindowBuffer;
extern unsigned char* gInventoryButtonUpFrmData;
extern unsigned char* gOptionsButtonUpFrmData;
extern unsigned char* gOptionsButtonDownFrmData;
extern unsigned char* gSkilldexButtonUpFrmData;
extern unsigned char* gInventoryButtonDownFrmData;
extern unsigned char gInterfaceActionPointsBarBackground[450];

int interfaceInit();
void interfaceReset();
void interfaceFree();
int interfaceLoad(File* stream);
int interfaceSave(File* stream);
void _intface_show();
void interfaceBarEnable();
void interfaceBarDisable();
bool interfaceBarEnabled();
void interfaceBarRefresh();
void interfaceRenderHitPoints(bool animate);
void interfaceRenderArmorClass(bool animate);
void interfaceRenderActionPoints(int actionPointsLeft, int bonusActionPoints);
int interfaceGetCurrentHitMode(int* hitMode, bool* aiming);
int _intface_update_items(bool a1, int a2, int a3);
int interfaceBarSwapHands(bool animated);
int _intface_get_item_states(int* a1, int* a2);
int _intface_toggle_item_state();
void _intface_use_item();
int interfaceGetCurrentHand();
int interfaceGetActiveItem(Object** a1);
int _intface_update_ammo_lights();
void interfaceBarEndButtonsShow(bool animated);
void interfaceBarEndButtonsHide(bool animated);
void interfaceBarEndButtonsRenderGreenLights();
void interfaceBarEndButtonsRenderRedLights();
int interfaceBarRefreshMainAction();
int _intface_redraw_items_callback(Object* a1, Object* a2);
int _intface_change_fid_callback(Object* a1, Object* a2);
void interfaceBarSwapHandsAnimatePutAwayTakeOutSequence(int previousWeaponAnimationCode, int weaponAnimationCode);
int endTurnButtonInit();
int endTurnButtonFree();
int endCombatButtonInit();
int endCombatButtonFree();
void interfaceUpdateAmmoBar(int x, int ratio);
int _intface_item_reload();
void interfaceRenderCounter(int x, int y, int previousValue, int value, int offset, int delay);
int indicatorBarInit();
void interfaceBarFree();
void indicatorBarReset();
int indicatorBarRefresh();
int indicatorBoxCompareByPosition(const void* a, const void* b);
void indicatorBarRender(int count);
bool indicatorBarAdd(int indicator);
bool indicatorBarShow();
bool indicatorBarHide();

#endif /* INTERFACE_H */
