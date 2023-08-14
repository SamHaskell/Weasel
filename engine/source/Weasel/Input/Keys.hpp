#pragma once

namespace Weasel {
    /* The unknown key */
    #define WEASEL_KEY_UNKNOWN            -1

    /* Printable keys */
    #define WEASEL_KEY_SPACE              32
    #define WEASEL_KEY_APOSTROPHE         39  /* ' */
    #define WEASEL_KEY_COMMA              44  /* , */
    #define WEASEL_KEY_MINUS              45  /* - */
    #define WEASEL_KEY_PERIOD             46  /* . */
    #define WEASEL_KEY_SLASH              47  /* / */
    #define WEASEL_KEY_0                  48
    #define WEASEL_KEY_1                  49
    #define WEASEL_KEY_2                  50
    #define WEASEL_KEY_3                  51
    #define WEASEL_KEY_4                  52
    #define WEASEL_KEY_5                  53
    #define WEASEL_KEY_6                  54
    #define WEASEL_KEY_7                  55
    #define WEASEL_KEY_8                  56
    #define WEASEL_KEY_9                  57
    #define WEASEL_KEY_SEMICOLON          59  /* ; */
    #define WEASEL_KEY_EQUAL              61  /* = */
    #define WEASEL_KEY_A                  65
    #define WEASEL_KEY_B                  66
    #define WEASEL_KEY_C                  67
    #define WEASEL_KEY_D                  68
    #define WEASEL_KEY_E                  69
    #define WEASEL_KEY_F                  70
    #define WEASEL_KEY_G                  71
    #define WEASEL_KEY_H                  72
    #define WEASEL_KEY_I                  73
    #define WEASEL_KEY_J                  74
    #define WEASEL_KEY_K                  75
    #define WEASEL_KEY_L                  76
    #define WEASEL_KEY_M                  77
    #define WEASEL_KEY_N                  78
    #define WEASEL_KEY_O                  79
    #define WEASEL_KEY_P                  80
    #define WEASEL_KEY_Q                  81
    #define WEASEL_KEY_R                  82
    #define WEASEL_KEY_S                  83
    #define WEASEL_KEY_T                  84
    #define WEASEL_KEY_U                  85
    #define WEASEL_KEY_V                  86
    #define WEASEL_KEY_W                  87
    #define WEASEL_KEY_X                  88
    #define WEASEL_KEY_Y                  89
    #define WEASEL_KEY_Z                  90
    #define WEASEL_KEY_LEFT_BRACKET       91  /* [ */
    #define WEASEL_KEY_BACKSLASH          92  /* \ */
    #define WEASEL_KEY_RIGHT_BRACKET      93  /* ] */
    #define WEASEL_KEY_GRAVE_ACCENT       96  /* ` */
    #define WEASEL_KEY_WORLD_1            161 /* non-US #1 */
    #define WEASEL_KEY_WORLD_2            162 /* non-US #2 */

    /* Function keys */
    #define WEASEL_KEY_ESCAPE             256
    #define WEASEL_KEY_ENTER              257
    #define WEASEL_KEY_TAB                258
    #define WEASEL_KEY_BACKSPACE          259
    #define WEASEL_KEY_INSERT             260
    #define WEASEL_KEY_DELETE             261
    #define WEASEL_KEY_RIGHT              262
    #define WEASEL_KEY_LEFT               263
    #define WEASEL_KEY_DOWN               264
    #define WEASEL_KEY_UP                 265
    #define WEASEL_KEY_PAGE_UP            266
    #define WEASEL_KEY_PAGE_DOWN          267
    #define WEASEL_KEY_HOME               268
    #define WEASEL_KEY_END                269
    #define WEASEL_KEY_CAPS_LOCK          280
    #define WEASEL_KEY_SCROLL_LOCK        281
    #define WEASEL_KEY_NUM_LOCK           282
    #define WEASEL_KEY_PRINT_SCREEN       283
    #define WEASEL_KEY_PAUSE              284
    #define WEASEL_KEY_F1                 290
    #define WEASEL_KEY_F2                 291
    #define WEASEL_KEY_F3                 292
    #define WEASEL_KEY_F4                 293
    #define WEASEL_KEY_F5                 294
    #define WEASEL_KEY_F6                 295
    #define WEASEL_KEY_F7                 296
    #define WEASEL_KEY_F8                 297
    #define WEASEL_KEY_F9                 298
    #define WEASEL_KEY_F10                299
    #define WEASEL_KEY_F11                300
    #define WEASEL_KEY_F12                301
    #define WEASEL_KEY_F13                302
    #define WEASEL_KEY_F14                303
    #define WEASEL_KEY_F15                304
    #define WEASEL_KEY_F16                305
    #define WEASEL_KEY_F17                306
    #define WEASEL_KEY_F18                307
    #define WEASEL_KEY_F19                308
    #define WEASEL_KEY_F20                309
    #define WEASEL_KEY_F21                310
    #define WEASEL_KEY_F22                311
    #define WEASEL_KEY_F23                312
    #define WEASEL_KEY_F24                313
    #define WEASEL_KEY_F25                314
    #define WEASEL_KEY_KP_0               320
    #define WEASEL_KEY_KP_1               321
    #define WEASEL_KEY_KP_2               322
    #define WEASEL_KEY_KP_3               323
    #define WEASEL_KEY_KP_4               324
    #define WEASEL_KEY_KP_5               325
    #define WEASEL_KEY_KP_6               326
    #define WEASEL_KEY_KP_7               327
    #define WEASEL_KEY_KP_8               328
    #define WEASEL_KEY_KP_9               329
    #define WEASEL_KEY_KP_DECIMAL         330
    #define WEASEL_KEY_KP_DIVIDE          331
    #define WEASEL_KEY_KP_MULTIPLY        332
    #define WEASEL_KEY_KP_SUBTRACT        333
    #define WEASEL_KEY_KP_ADD             334
    #define WEASEL_KEY_KP_ENTER           335
    #define WEASEL_KEY_KP_EQUAL           336
    #define WEASEL_KEY_LEFT_SHIFT         340
    #define WEASEL_KEY_LEFT_CONTROL       341
    #define WEASEL_KEY_LEFT_ALT           342
    #define WEASEL_KEY_LEFT_SUPER         343
    #define WEASEL_KEY_RIGHT_SHIFT        344
    #define WEASEL_KEY_RIGHT_CONTROL      345
    #define WEASEL_KEY_RIGHT_ALT          346
    #define WEASEL_KEY_RIGHT_SUPER        347
    #define WEASEL_KEY_MENU               348

    #define WEASEL_KEY_LAST               WEASEL_KEY_MENU
}