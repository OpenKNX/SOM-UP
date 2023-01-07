#pragma once

// Parameter with single occurrence

#define LOG_NumChannels                0      // uint8_t
#define LOG_StartupDelayBase           1      // 2 Bits, Bit 7-6
#define     LOG_StartupDelayBaseMask 0xC0
#define     LOG_StartupDelayBaseShift 6
#define LOG_StartupDelayTime           1      // uint14_t
#define LOG_HeartbeatDelayBase         3      // 2 Bits, Bit 7-6
#define     LOG_HeartbeatDelayBaseMask 0xC0
#define     LOG_HeartbeatDelayBaseShift 6
#define LOG_HeartbeatDelayTime         3      // uint14_t
#define LOG_ReadTimeDate               5      // 1 Bit, Bit 7
#define     LOG_ReadTimeDateMask 0x80
#define     LOG_ReadTimeDateShift 7
#define LOG_BuzzerInstalled            5      // 1 Bit, Bit 6
#define     LOG_BuzzerInstalledMask 0x40
#define     LOG_BuzzerInstalledShift 6
#define LOG_LedInstalled               5      // 1 Bit, Bit 5
#define     LOG_LedInstalledMask 0x20
#define     LOG_LedInstalledShift 5
#define LOG_VacationKo                 5      // 1 Bit, Bit 2
#define     LOG_VacationKoMask 0x04
#define     LOG_VacationKoShift 2
#define LOG_HolidayKo                  5      // 1 Bit, Bit 1
#define     LOG_HolidayKoMask 0x02
#define     LOG_HolidayKoShift 1
#define LOG_VacationRead               5      // 1 Bit, Bit 0
#define     LOG_VacationReadMask 0x01
#define     LOG_VacationReadShift 0
#define LOG_HolidaySend                6      // 1 Bit, Bit 7
#define     LOG_HolidaySendMask 0x80
#define     LOG_HolidaySendShift 7
#define LOG_Timezone                   6      // 2 Bits, Bit 6-5
#define     LOG_TimezoneMask 0x60
#define     LOG_TimezoneShift 5
#define LOG_UseSummertime              6      // 1 Bit, Bit 4
#define     LOG_UseSummertimeMask 0x10
#define     LOG_UseSummertimeShift 4
#define LOG_Diagnose                   6      // 1 Bit, Bit 3
#define     LOG_DiagnoseMask 0x08
#define     LOG_DiagnoseShift 3
#define LOG_Watchdog                   6      // 1 Bit, Bit 2
#define     LOG_WatchdogMask 0x04
#define     LOG_WatchdogShift 2
#define LOG_Neujahr                    7      // 1 Bit, Bit 7
#define     LOG_NeujahrMask 0x80
#define     LOG_NeujahrShift 7
#define LOG_DreiKoenige                7      // 1 Bit, Bit 6
#define     LOG_DreiKoenigeMask 0x40
#define     LOG_DreiKoenigeShift 6
#define LOG_Weiberfastnacht            7      // 1 Bit, Bit 5
#define     LOG_WeiberfastnachtMask 0x20
#define     LOG_WeiberfastnachtShift 5
#define LOG_Rosenmontag                7      // 1 Bit, Bit 4
#define     LOG_RosenmontagMask 0x10
#define     LOG_RosenmontagShift 4
#define LOG_Fastnachtsdienstag         7      // 1 Bit, Bit 3
#define     LOG_FastnachtsdienstagMask 0x08
#define     LOG_FastnachtsdienstagShift 3
#define LOG_Aschermittwoch             7      // 1 Bit, Bit 2
#define     LOG_AschermittwochMask 0x04
#define     LOG_AschermittwochShift 2
#define LOG_Frauentag                  7      // 1 Bit, Bit 1
#define     LOG_FrauentagMask 0x02
#define     LOG_FrauentagShift 1
#define LOG_Gruendonnerstag            7      // 1 Bit, Bit 0
#define     LOG_GruendonnerstagMask 0x01
#define     LOG_GruendonnerstagShift 0
#define LOG_Karfreitag                 8      // 1 Bit, Bit 7
#define     LOG_KarfreitagMask 0x80
#define     LOG_KarfreitagShift 7
#define LOG_Ostersonntag               8      // 1 Bit, Bit 6
#define     LOG_OstersonntagMask 0x40
#define     LOG_OstersonntagShift 6
#define LOG_Ostermontag                8      // 1 Bit, Bit 5
#define     LOG_OstermontagMask 0x20
#define     LOG_OstermontagShift 5
#define LOG_TagDerArbeit               8      // 1 Bit, Bit 4
#define     LOG_TagDerArbeitMask 0x10
#define     LOG_TagDerArbeitShift 4
#define LOG_Himmelfahrt                8      // 1 Bit, Bit 3
#define     LOG_HimmelfahrtMask 0x08
#define     LOG_HimmelfahrtShift 3
#define LOG_Pfingstsonntag             8      // 1 Bit, Bit 2
#define     LOG_PfingstsonntagMask 0x04
#define     LOG_PfingstsonntagShift 2
#define LOG_Pfingstmontag              8      // 1 Bit, Bit 1
#define     LOG_PfingstmontagMask 0x02
#define     LOG_PfingstmontagShift 1
#define LOG_Fronleichnam               8      // 1 Bit, Bit 0
#define     LOG_FronleichnamMask 0x01
#define     LOG_FronleichnamShift 0
#define LOG_Friedensfest               9      // 1 Bit, Bit 7
#define     LOG_FriedensfestMask 0x80
#define     LOG_FriedensfestShift 7
#define LOG_MariaHimmelfahrt           9      // 1 Bit, Bit 6
#define     LOG_MariaHimmelfahrtMask 0x40
#define     LOG_MariaHimmelfahrtShift 6
#define LOG_DeutscheEinheit            9      // 1 Bit, Bit 5
#define     LOG_DeutscheEinheitMask 0x20
#define     LOG_DeutscheEinheitShift 5
#define LOG_Nationalfeiertag          10      // 1 Bit, Bit 1
#define     LOG_NationalfeiertagMask 0x02
#define     LOG_NationalfeiertagShift 1
#define LOG_Reformationstag            9      // 1 Bit, Bit 4
#define     LOG_ReformationstagMask 0x10
#define     LOG_ReformationstagShift 4
#define LOG_Allerheiligen              9      // 1 Bit, Bit 3
#define     LOG_AllerheiligenMask 0x08
#define     LOG_AllerheiligenShift 3
#define LOG_BussBettag                 9      // 1 Bit, Bit 2
#define     LOG_BussBettagMask 0x04
#define     LOG_BussBettagShift 2
#define LOG_MariaEmpfaengnis          10      // 1 Bit, Bit 0
#define     LOG_MariaEmpfaengnisMask 0x01
#define     LOG_MariaEmpfaengnisShift 0
#define LOG_Advent1                    9      // 1 Bit, Bit 1
#define     LOG_Advent1Mask 0x02
#define     LOG_Advent1Shift 1
#define LOG_Advent2                    9      // 1 Bit, Bit 0
#define     LOG_Advent2Mask 0x01
#define     LOG_Advent2Shift 0
#define LOG_Advent3                   10      // 1 Bit, Bit 7
#define     LOG_Advent3Mask 0x80
#define     LOG_Advent3Shift 7
#define LOG_Advent4                   10      // 1 Bit, Bit 6
#define     LOG_Advent4Mask 0x40
#define     LOG_Advent4Shift 6
#define LOG_Heiligabend               10      // 1 Bit, Bit 5
#define     LOG_HeiligabendMask 0x20
#define     LOG_HeiligabendShift 5
#define LOG_Weihnachtstag1            10      // 1 Bit, Bit 4
#define     LOG_Weihnachtstag1Mask 0x10
#define     LOG_Weihnachtstag1Shift 4
#define LOG_Weihnachtstag2            10      // 1 Bit, Bit 3
#define     LOG_Weihnachtstag2Mask 0x08
#define     LOG_Weihnachtstag2Shift 3
#define LOG_Silvester                 10      // 1 Bit, Bit 2
#define     LOG_SilvesterMask 0x04
#define     LOG_SilvesterShift 2
#define LOG_Latitude                  11      // float
#define LOG_Longitude                 15      // float
#define LOG_BuzzerSilent              19      // uint16_t
#define LOG_BuzzerNormal              21      // uint16_t
#define LOG_BuzzerLoud                23      // uint16_t
#define LOG_LedMapping                25      // 3 Bits, Bit 7-5
#define     LOG_LedMappingMask 0xE0
#define     LOG_LedMappingShift 5

#define LOG_KoHeartbeat 1
#define LOG_KoTime 2
#define LOG_KoDate 3
#define LOG_KoVacation 4
#define LOG_KoHoliday1 5
#define LOG_KoHoliday2 6
#define LOG_KoDiagnose 7
#define LOG_KoLedLock 8
#define LOG_KoBuzzerLock 9

#define SOM_External                  27      // 1 Bit, Bit 7
#define     SOM_ExternalMask 0x80
#define     SOM_ExternalShift 7
#define SOM_Scenes                    27      // 1 Bit, Bit 6
#define     SOM_ScenesMask 0x40
#define     SOM_ScenesShift 6
#define SOM_VolumeDay                 28      // uint8_t
#define SOM_VolumeNight               29      // uint8_t
#define SOM_Lock                      30      // 2 Bits, Bit 7-6
#define     SOM_LockMask 0xC0
#define     SOM_LockShift 6
#define SOM_DayNight                  30      // 2 Bits, Bit 5-4
#define     SOM_DayNightMask 0x30
#define     SOM_DayNightShift 4
#define SOM_Scene0                    31      // 8 Bits, Bit 7-0
#define SOM_Scene1                    32      // 8 Bits, Bit 7-0
#define SOM_Scene2                    33      // 8 Bits, Bit 7-0
#define SOM_Scene3                    34      // 8 Bits, Bit 7-0
#define SOM_Scene4                    35      // 8 Bits, Bit 7-0
#define SOM_Scene5                    36      // 8 Bits, Bit 7-0
#define SOM_Scene6                    37      // 8 Bits, Bit 7-0
#define SOM_Scene7                    38      // 8 Bits, Bit 7-0
#define SOM_Scene8                    39      // 8 Bits, Bit 7-0
#define SOM_Scene9                    40      // 8 Bits, Bit 7-0
#define SOM_Scene10                   41      // 8 Bits, Bit 7-0
#define SOM_Scene11                   42      // 8 Bits, Bit 7-0
#define SOM_Scene12                   43      // 8 Bits, Bit 7-0
#define SOM_Scene13                   44      // 8 Bits, Bit 7-0
#define SOM_Scene14                   45      // 8 Bits, Bit 7-0
#define SOM_Scene15                   46      // 8 Bits, Bit 7-0
#define SOM_Scene16                   47      // 8 Bits, Bit 7-0
#define SOM_Scene17                   48      // 8 Bits, Bit 7-0
#define SOM_Scene18                   49      // 8 Bits, Bit 7-0
#define SOM_Scene19                   50      // 8 Bits, Bit 7-0
#define SOM_SceneAction0              51      // 8 Bits, Bit 7-0
#define SOM_SceneAction1              52      // 8 Bits, Bit 7-0
#define SOM_SceneAction2              53      // 8 Bits, Bit 7-0
#define SOM_SceneAction3              54      // 8 Bits, Bit 7-0
#define SOM_SceneAction4              55      // 8 Bits, Bit 7-0
#define SOM_SceneAction5              56      // 8 Bits, Bit 7-0
#define SOM_SceneAction6              57      // 8 Bits, Bit 7-0
#define SOM_SceneAction7              58      // 8 Bits, Bit 7-0
#define SOM_SceneAction8              59      // 8 Bits, Bit 7-0
#define SOM_SceneAction9              60      // 8 Bits, Bit 7-0
#define SOM_SceneAction10             61      // 8 Bits, Bit 7-0
#define SOM_SceneAction11             62      // 8 Bits, Bit 7-0
#define SOM_SceneAction12             63      // 8 Bits, Bit 7-0
#define SOM_SceneAction13             64      // 8 Bits, Bit 7-0
#define SOM_SceneAction14             65      // 8 Bits, Bit 7-0
#define SOM_SceneAction15             66      // 8 Bits, Bit 7-0
#define SOM_SceneAction16             67      // 8 Bits, Bit 7-0
#define SOM_SceneAction17             68      // 8 Bits, Bit 7-0
#define SOM_SceneAction18             69      // 8 Bits, Bit 7-0
#define SOM_SceneAction19             70      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA0             71      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA1             72      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA2             73      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA3             74      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA4             75      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA5             76      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA6             77      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA7             78      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA8             79      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA9             80      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA10            81      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA11            82      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA12            83      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA13            84      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA14            85      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA15            86      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA16            87      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA17            88      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA18            89      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA19            90      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB0             71      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB1             72      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB2             73      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB3             74      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB4             75      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB5             76      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB6             77      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB7             78      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB8             79      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB9             80      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB10            81      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB11            82      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB12            83      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB13            84      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB14            85      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB15            86      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB16            87      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB17            88      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB18            89      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB19            90      // 8 Bits, Bit 7-0

#define SOM_KoStatus 20
#define SOM_KoFile 21
#define SOM_KoScene 28
#define SOM_KoLock 29
#define SOM_KoDayNight 27
#define SOM_KoExternalFile 30
#define SOM_KoExternalVolume 31
#define SOM_KoExternalPriority 32

#define BTN_ReactionTimeMultiClick    111      // 8 Bits, Bit 7-0
#define BTN_ReactionTimeLong          112      // 8 Bits, Bit 7-0
#define BTN_ReactionTimeExtraLong     113      // 8 Bits, Bit 7-0

#define LOG_ChannelCount 10

// Parameter per channel
#define LOG_ParamBlockOffset 115
#define LOG_ParamBlockSize 86
#define LOG_fChannelDelayBase          0      // 2 Bits, Bit 7-6
#define     LOG_fChannelDelayBaseMask 0xC0
#define     LOG_fChannelDelayBaseShift 6
#define LOG_fChannelDelayTime          0      // uint14_t
#define LOG_fLogic                     2      // 8 Bits, Bit 7-0
#define LOG_fCalculate                 3      // 2 Bits, Bit 1-0
#define     LOG_fCalculateMask 0x03
#define     LOG_fCalculateShift 0
#define LOG_fDisable                   3      // 1 Bit, Bit 2
#define     LOG_fDisableMask 0x04
#define     LOG_fDisableShift 2
#define LOG_fAlarm                     3      // 1 Bit, Bit 3
#define     LOG_fAlarmMask 0x08
#define     LOG_fAlarmShift 3
#define LOG_fTGate                     3      // 1 Bit, Bit 4
#define     LOG_fTGateMask 0x10
#define     LOG_fTGateShift 4
#define LOG_fOInternalOn               3      // 1 Bit, Bit 5
#define     LOG_fOInternalOnMask 0x20
#define     LOG_fOInternalOnShift 5
#define LOG_fOInternalOff              3      // 1 Bit, Bit 6
#define     LOG_fOInternalOffMask 0x40
#define     LOG_fOInternalOffShift 6
#define LOG_fTrigger                   4      // 8 Bits, Bit 7-0
#define LOG_fTriggerE1                 4      // 1 Bit, Bit 0
#define     LOG_fTriggerE1Mask 0x01
#define     LOG_fTriggerE1Shift 0
#define LOG_fTriggerE2                 4      // 1 Bit, Bit 1
#define     LOG_fTriggerE2Mask 0x02
#define     LOG_fTriggerE2Shift 1
#define LOG_fTriggerI1                 4      // 1 Bit, Bit 2
#define     LOG_fTriggerI1Mask 0x04
#define     LOG_fTriggerI1Shift 2
#define LOG_fTriggerI2                 4      // 1 Bit, Bit 3
#define     LOG_fTriggerI2Mask 0x08
#define     LOG_fTriggerI2Shift 3
#define LOG_fTriggerTime               4      // 8 Bits, Bit 7-0
#define LOG_fTriggerGateClose          5      // 2 Bits, Bit 7-6
#define     LOG_fTriggerGateCloseMask 0xC0
#define     LOG_fTriggerGateCloseShift 6
#define LOG_fTriggerGateOpen           5      // 2 Bits, Bit 5-4
#define     LOG_fTriggerGateOpenMask 0x30
#define     LOG_fTriggerGateOpenShift 4
#define LOG_fE1                        6      // 4 Bits, Bit 3-0
#define     LOG_fE1Mask 0x0F
#define     LOG_fE1Shift 0
#define LOG_fE1Convert                 6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertMask 0xF0
#define     LOG_fE1ConvertShift 4
#define LOG_fE1ConvertFloat            6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertFloatMask 0xF0
#define     LOG_fE1ConvertFloatShift 4
#define LOG_fE1ConvertSpecial          6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertSpecialMask 0xF0
#define     LOG_fE1ConvertSpecialShift 4
#define LOG_fE1Dpt                     7      // 8 Bits, Bit 7-0
#define LOG_fE1Default                 8      // 2 Bits, Bit 1-0
#define     LOG_fE1DefaultMask 0x03
#define     LOG_fE1DefaultShift 0
#define LOG_fE1DefaultExt              8      // 2 Bits, Bit 1-0
#define     LOG_fE1DefaultExtMask 0x03
#define     LOG_fE1DefaultExtShift 0
#define LOG_fE1DefaultEEPROM           8      // 1 Bit, Bit 2
#define     LOG_fE1DefaultEEPROMMask 0x04
#define     LOG_fE1DefaultEEPROMShift 2
#define LOG_fE1DefaultRepeat           8      // 1 Bit, Bit 3
#define     LOG_fE1DefaultRepeatMask 0x08
#define     LOG_fE1DefaultRepeatShift 3
#define LOG_fTYearDay                  8      // 1 Bit, Bit 4
#define     LOG_fTYearDayMask 0x10
#define     LOG_fTYearDayShift 4
#define LOG_fTRestoreState             8      // 2 Bits, Bit 6-5
#define     LOG_fTRestoreStateMask 0x60
#define     LOG_fTRestoreStateShift 5
#define LOG_fE1RepeatBase              9      // 2 Bits, Bit 7-6
#define     LOG_fE1RepeatBaseMask 0xC0
#define     LOG_fE1RepeatBaseShift 6
#define LOG_fE1RepeatTime              9      // uint14_t
#define LOG_fE2                       11      // 4 Bits, Bit 3-0
#define     LOG_fE2Mask 0x0F
#define     LOG_fE2Shift 0
#define LOG_fE2Convert                11      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertMask 0xF0
#define     LOG_fE2ConvertShift 4
#define LOG_fE2ConvertFloat           11      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertFloatMask 0xF0
#define     LOG_fE2ConvertFloatShift 4
#define LOG_fE2ConvertSpecial         11      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertSpecialMask 0xF0
#define     LOG_fE2ConvertSpecialShift 4
#define LOG_fE2Dpt                    12      // 8 Bits, Bit 7-0
#define LOG_fE2Default                13      // 2 Bits, Bit 1-0
#define     LOG_fE2DefaultMask 0x03
#define     LOG_fE2DefaultShift 0
#define LOG_fE2DefaultExt             13      // 2 Bits, Bit 1-0
#define     LOG_fE2DefaultExtMask 0x03
#define     LOG_fE2DefaultExtShift 0
#define LOG_fE2DefaultEEPROM          13      // 1 Bit, Bit 2
#define     LOG_fE2DefaultEEPROMMask 0x04
#define     LOG_fE2DefaultEEPROMShift 2
#define LOG_fE2DefaultRepeat          13      // 1 Bit, Bit 3
#define     LOG_fE2DefaultRepeatMask 0x08
#define     LOG_fE2DefaultRepeatShift 3
#define LOG_fTHoliday                 13      // 2 Bits, Bit 4-3
#define     LOG_fTHolidayMask 0x18
#define     LOG_fTHolidayShift 3
#define LOG_fTVacation                13      // 2 Bits, Bit 6-5
#define     LOG_fTVacationMask 0x60
#define     LOG_fTVacationShift 5
#define LOG_fE2RepeatBase             14      // 2 Bits, Bit 7-6
#define     LOG_fE2RepeatBaseMask 0xC0
#define     LOG_fE2RepeatBaseShift 6
#define LOG_fE2RepeatTime             14      // uint14_t
#define LOG_fTd1DuskDawn              14      // 4 Bits, Bit 7-4
#define     LOG_fTd1DuskDawnMask 0xF0
#define     LOG_fTd1DuskDawnShift 4
#define LOG_fTd2DuskDawn              14      // 4 Bits, Bit 3-0
#define     LOG_fTd2DuskDawnMask 0x0F
#define     LOG_fTd2DuskDawnShift 0
#define LOG_fTd3DuskDawn              15      // 4 Bits, Bit 7-4
#define     LOG_fTd3DuskDawnMask 0xF0
#define     LOG_fTd3DuskDawnShift 4
#define LOG_fTd4DuskDawn              15      // 4 Bits, Bit 3-0
#define     LOG_fTd4DuskDawnMask 0x0F
#define     LOG_fTd4DuskDawnShift 0
#define LOG_fTd5DuskDawn              16      // 4 Bits, Bit 7-4
#define     LOG_fTd5DuskDawnMask 0xF0
#define     LOG_fTd5DuskDawnShift 4
#define LOG_fTd6DuskDawn              16      // 4 Bits, Bit 3-0
#define     LOG_fTd6DuskDawnMask 0x0F
#define     LOG_fTd6DuskDawnShift 0
#define LOG_fTd7DuskDawn              17      // 4 Bits, Bit 7-4
#define     LOG_fTd7DuskDawnMask 0xF0
#define     LOG_fTd7DuskDawnShift 4
#define LOG_fTd8DuskDawn              17      // 4 Bits, Bit 3-0
#define     LOG_fTd8DuskDawnMask 0x0F
#define     LOG_fTd8DuskDawnShift 0
#define LOG_fE1LowDelta               18      // int32_t
#define LOG_fE1HighDelta              22      // int32_t
#define LOG_fE1LowDeltaFloat          18      // float
#define LOG_fE1HighDeltaFloat         22      // float
#define LOG_fE1Low0Valid              25      // 1 Bit, Bit 7
#define     LOG_fE1Low0ValidMask 0x80
#define     LOG_fE1Low0ValidShift 7
#define LOG_fE1Low1Valid              25      // 1 Bit, Bit 6
#define     LOG_fE1Low1ValidMask 0x40
#define     LOG_fE1Low1ValidShift 6
#define LOG_fE1Low2Valid              25      // 1 Bit, Bit 5
#define     LOG_fE1Low2ValidMask 0x20
#define     LOG_fE1Low2ValidShift 5
#define LOG_fE1Low3Valid              25      // 1 Bit, Bit 4
#define     LOG_fE1Low3ValidMask 0x10
#define     LOG_fE1Low3ValidShift 4
#define LOG_fE1Low4Valid              25      // 1 Bit, Bit 3
#define     LOG_fE1Low4ValidMask 0x08
#define     LOG_fE1Low4ValidShift 3
#define LOG_fE1Low5Valid              25      // 1 Bit, Bit 2
#define     LOG_fE1Low5ValidMask 0x04
#define     LOG_fE1Low5ValidShift 2
#define LOG_fE1Low6Valid              25      // 1 Bit, Bit 1
#define     LOG_fE1Low6ValidMask 0x02
#define     LOG_fE1Low6ValidShift 1
#define LOG_fE1Low7Valid              25      // 1 Bit, Bit 0
#define     LOG_fE1Low7ValidMask 0x01
#define     LOG_fE1Low7ValidShift 0
#define LOG_fE1LowDpt2                18      // 8 Bits, Bit 7-0
#define LOG_fE1Low1Dpt2               19      // 8 Bits, Bit 7-0
#define LOG_fE1Low2Dpt2               20      // 8 Bits, Bit 7-0
#define LOG_fE1Low3Dpt2               21      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt2Fix             18      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt5                18      // uint8_t
#define LOG_fE1HighDpt5               22      // uint8_t
#define LOG_fE1Low0Dpt5In             18      // uint8_t
#define LOG_fE1Low1Dpt5In             19      // uint8_t
#define LOG_fE1Low2Dpt5In             20      // uint8_t
#define LOG_fE1Low3Dpt5In             21      // uint8_t
#define LOG_fE1Low4Dpt5In             22      // uint8_t
#define LOG_fE1Low5Dpt5In             23      // uint8_t
#define LOG_fE1Low6Dpt5In             24      // uint8_t
#define LOG_fE1LowDpt5Fix             18      // uint8_t
#define LOG_fE1LowDpt5001             18      // uint8_t
#define LOG_fE1HighDpt5001            22      // uint8_t
#define LOG_fE1Low0Dpt5xIn            18      // uint8_t
#define LOG_fE1Low1Dpt5xIn            19      // uint8_t
#define LOG_fE1Low2Dpt5xIn            20      // uint8_t
#define LOG_fE1Low3Dpt5xIn            21      // uint8_t
#define LOG_fE1Low4Dpt5xIn            22      // uint8_t
#define LOG_fE1Low5Dpt5xIn            23      // uint8_t
#define LOG_fE1Low6Dpt5xIn            24      // uint8_t
#define LOG_fE1LowDpt5xFix            18      // uint8_t
#define LOG_fE1LowDpt6                18      // int8_t
#define LOG_fE1HighDpt6               22      // int8_t
#define LOG_fE1Low0Dpt6In             18      // int8_t
#define LOG_fE1Low1Dpt6In             19      // int8_t
#define LOG_fE1Low2Dpt6In             20      // int8_t
#define LOG_fE1Low3Dpt6In             21      // int8_t
#define LOG_fE1Low4Dpt6In             22      // int8_t
#define LOG_fE1Low5Dpt6In             23      // int8_t
#define LOG_fE1Low6Dpt6In             24      // int8_t
#define LOG_fE1LowDpt6Fix             18      // int8_t
#define LOG_fE1LowDpt7                18      // uint16_t
#define LOG_fE1HighDpt7               22      // uint16_t
#define LOG_fE1Low0Dpt7In             18      // uint16_t
#define LOG_fE1Low1Dpt7In             20      // uint16_t
#define LOG_fE1Low2Dpt7In             22      // uint16_t
#define LOG_fE1LowDpt7Fix             18      // uint16_t
#define LOG_fE1LowDpt8                18      // int16_t
#define LOG_fE1HighDpt8               22      // int16_t
#define LOG_fE1Low0Dpt8In             18      // int16_t
#define LOG_fE1Low1Dpt8In             20      // int16_t
#define LOG_fE1Low2Dpt8In             22      // int16_t
#define LOG_fE1LowDpt8Fix             18      // int16_t
#define LOG_fE1LowDpt9                18      // float
#define LOG_fE1HighDpt9               22      // float
#define LOG_fE1LowDpt9Fix             18      // float
#define LOG_fE1Low0Dpt17              18      // 8 Bits, Bit 7-0
#define LOG_fE1Low1Dpt17              19      // 8 Bits, Bit 7-0
#define LOG_fE1Low2Dpt17              20      // 8 Bits, Bit 7-0
#define LOG_fE1Low3Dpt17              21      // 8 Bits, Bit 7-0
#define LOG_fE1Low4Dpt17              22      // 8 Bits, Bit 7-0
#define LOG_fE1Low5Dpt17              23      // 8 Bits, Bit 7-0
#define LOG_fE1Low6Dpt17              24      // 8 Bits, Bit 7-0
#define LOG_fE1Low7Dpt17              25      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt17Fix            18      // 8 Bits, Bit 7-0
#define LOG_fE1LowDptRGB              18      // int32_t
#define LOG_fE1HighDptRGB             22      // int32_t
#define LOG_fE1LowDptRGBFix           18      // int32_t
#define LOG_fE2LowDelta               26      // int32_t
#define LOG_fE2HighDelta              30      // int32_t
#define LOG_fE2LowDeltaFloat          26      // float
#define LOG_fE2HighDeltaFloat         30      // float
#define LOG_fE2Low0Valid              33      // 1 Bit, Bit 7
#define     LOG_fE2Low0ValidMask 0x80
#define     LOG_fE2Low0ValidShift 7
#define LOG_fE2Low1Valid              33      // 1 Bit, Bit 6
#define     LOG_fE2Low1ValidMask 0x40
#define     LOG_fE2Low1ValidShift 6
#define LOG_fE2Low2Valid              33      // 1 Bit, Bit 5
#define     LOG_fE2Low2ValidMask 0x20
#define     LOG_fE2Low2ValidShift 5
#define LOG_fE2Low3Valid              33      // 1 Bit, Bit 4
#define     LOG_fE2Low3ValidMask 0x10
#define     LOG_fE2Low3ValidShift 4
#define LOG_fE2Low4Valid              33      // 1 Bit, Bit 3
#define     LOG_fE2Low4ValidMask 0x08
#define     LOG_fE2Low4ValidShift 3
#define LOG_fE2Low5Valid              33      // 1 Bit, Bit 2
#define     LOG_fE2Low5ValidMask 0x04
#define     LOG_fE2Low5ValidShift 2
#define LOG_fE2Low6Valid              33      // 1 Bit, Bit 1
#define     LOG_fE2Low6ValidMask 0x02
#define     LOG_fE2Low6ValidShift 1
#define LOG_fE2Low7Valid              33      // 1 Bit, Bit 0
#define     LOG_fE2Low7ValidMask 0x01
#define     LOG_fE2Low7ValidShift 0
#define LOG_fE2Low0Dpt2               26      // 8 Bits, Bit 7-0
#define LOG_fE2Low1Dpt2               27      // 8 Bits, Bit 7-0
#define LOG_fE2Low2Dpt2               28      // 8 Bits, Bit 7-0
#define LOG_fE2Low3Dpt2               29      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt2Fix             26      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt5                26      // uint8_t
#define LOG_fE2HighDpt5               30      // uint8_t
#define LOG_fE2Low0Dpt5In             26      // uint8_t
#define LOG_fE2Low1Dpt5In             27      // uint8_t
#define LOG_fE2Low2Dpt5In             28      // uint8_t
#define LOG_fE2Low3Dpt5In             29      // uint8_t
#define LOG_fE2Low4Dpt5In             30      // uint8_t
#define LOG_fE2Low5Dpt5In             31      // uint8_t
#define LOG_fE2Low6Dpt5In             32      // uint8_t
#define LOG_fE2LowDpt5Fix             26      // uint8_t
#define LOG_fE2LowDpt5001             26      // uint8_t
#define LOG_fE2HighDpt5001            30      // uint8_t
#define LOG_fE2Low0Dpt5xIn            26      // uint8_t
#define LOG_fE2Low1Dpt5xIn            27      // uint8_t
#define LOG_fE2Low2Dpt5xIn            28      // uint8_t
#define LOG_fE2Low3Dpt5xIn            29      // uint8_t
#define LOG_fE2Low4Dpt5xIn            30      // uint8_t
#define LOG_fE2Low5Dpt5xIn            31      // uint8_t
#define LOG_fE2Low6Dpt5xIn            32      // uint8_t
#define LOG_fE2LowDpt5xFix            26      // uint8_t
#define LOG_fE2LowDpt6                26      // int8_t
#define LOG_fE2HighDpt6               30      // int8_t
#define LOG_fE2Low0Dpt6In             26      // int8_t
#define LOG_fE2Low1Dpt6In             27      // int8_t
#define LOG_fE2Low2Dpt6In             28      // int8_t
#define LOG_fE2Low3Dpt6In             29      // int8_t
#define LOG_fE2Low4Dpt6In             30      // int8_t
#define LOG_fE2Low5Dpt6In             31      // int8_t
#define LOG_fE2Low6Dpt6In             32      // int8_t
#define LOG_fE2LowDpt6Fix             26      // int8_t
#define LOG_fE2LowDpt7                26      // uint16_t
#define LOG_fE2HighDpt7               30      // uint16_t
#define LOG_fE2Low0Dpt7In             26      // uint16_t
#define LOG_fE2Low1Dpt7In             28      // uint16_t
#define LOG_fE2Low2Dpt7In             30      // uint16_t
#define LOG_fE2LowDpt7Fix             26      // uint16_t
#define LOG_fE2LowDpt8                26      // int16_t
#define LOG_fE2HighDpt8               30      // int16_t
#define LOG_fE2Low0Dpt8In             26      // int16_t
#define LOG_fE2Low1Dpt8In             28      // int16_t
#define LOG_fE2Low2Dpt8In             30      // int16_t
#define LOG_fE2LowDpt8Fix             26      // int16_t
#define LOG_fE2LowDpt9                26      // float
#define LOG_fE2HighDpt9               30      // float
#define LOG_fE2LowDpt9Fix             26      // float
#define LOG_fE2Low0Dpt17              26      // 8 Bits, Bit 7-0
#define LOG_fE2Low1Dpt17              27      // 8 Bits, Bit 7-0
#define LOG_fE2Low2Dpt17              28      // 8 Bits, Bit 7-0
#define LOG_fE2Low3Dpt17              29      // 8 Bits, Bit 7-0
#define LOG_fE2Low4Dpt17              30      // 8 Bits, Bit 7-0
#define LOG_fE2Low5Dpt17              31      // 8 Bits, Bit 7-0
#define LOG_fE2Low6Dpt17              32      // 8 Bits, Bit 7-0
#define LOG_fE2Low7Dpt17              33      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt17Fix            26      // 8 Bits, Bit 7-0
#define LOG_fE2LowDptRGB              26      // int32_t
#define LOG_fE2HighDptRGB             30      // int32_t
#define LOG_fE2LowDptRGBFix           26      // int32_t
#define LOG_fTd1Value                 18      // 1 Bit, Bit 7
#define     LOG_fTd1ValueMask 0x80
#define     LOG_fTd1ValueShift 7
#define LOG_fTd1HourAbs               18      // 5 Bits, Bit 5-1
#define     LOG_fTd1HourAbsMask 0x3E
#define     LOG_fTd1HourAbsShift 1
#define LOG_fTd1HourRel               18      // 5 Bits, Bit 5-1
#define     LOG_fTd1HourRelMask 0x3E
#define     LOG_fTd1HourRelShift 1
#define LOG_fTd1MinuteAbs             18      // 6 Bits, Bit 0--5
#define LOG_fTd1MinuteRel             18      // 6 Bits, Bit 0--5
#define LOG_fTd1Weekday               19      // 3 Bits, Bit 2-0
#define     LOG_fTd1WeekdayMask 0x07
#define     LOG_fTd1WeekdayShift 0
#define LOG_fTd2Value                 20      // 1 Bit, Bit 7
#define     LOG_fTd2ValueMask 0x80
#define     LOG_fTd2ValueShift 7
#define LOG_fTd2HourAbs               20      // 5 Bits, Bit 5-1
#define     LOG_fTd2HourAbsMask 0x3E
#define     LOG_fTd2HourAbsShift 1
#define LOG_fTd2HourRel               20      // 5 Bits, Bit 5-1
#define     LOG_fTd2HourRelMask 0x3E
#define     LOG_fTd2HourRelShift 1
#define LOG_fTd2MinuteAbs             20      // 6 Bits, Bit 0--5
#define LOG_fTd2MinuteRel             20      // 6 Bits, Bit 0--5
#define LOG_fTd2Weekday               21      // 3 Bits, Bit 2-0
#define     LOG_fTd2WeekdayMask 0x07
#define     LOG_fTd2WeekdayShift 0
#define LOG_fTd3Value                 22      // 1 Bit, Bit 7
#define     LOG_fTd3ValueMask 0x80
#define     LOG_fTd3ValueShift 7
#define LOG_fTd3HourAbs               22      // 5 Bits, Bit 5-1
#define     LOG_fTd3HourAbsMask 0x3E
#define     LOG_fTd3HourAbsShift 1
#define LOG_fTd3HourRel               22      // 5 Bits, Bit 5-1
#define     LOG_fTd3HourRelMask 0x3E
#define     LOG_fTd3HourRelShift 1
#define LOG_fTd3MinuteAbs             22      // 6 Bits, Bit 0--5
#define LOG_fTd3MinuteRel             22      // 6 Bits, Bit 0--5
#define LOG_fTd3Weekday               23      // 3 Bits, Bit 2-0
#define     LOG_fTd3WeekdayMask 0x07
#define     LOG_fTd3WeekdayShift 0
#define LOG_fTd4Value                 24      // 1 Bit, Bit 7
#define     LOG_fTd4ValueMask 0x80
#define     LOG_fTd4ValueShift 7
#define LOG_fTd4HourAbs               24      // 5 Bits, Bit 5-1
#define     LOG_fTd4HourAbsMask 0x3E
#define     LOG_fTd4HourAbsShift 1
#define LOG_fTd4HourRel               24      // 5 Bits, Bit 5-1
#define     LOG_fTd4HourRelMask 0x3E
#define     LOG_fTd4HourRelShift 1
#define LOG_fTd4MinuteAbs             24      // 6 Bits, Bit 0--5
#define LOG_fTd4MinuteRel             24      // 6 Bits, Bit 0--5
#define LOG_fTd4Weekday               25      // 3 Bits, Bit 2-0
#define     LOG_fTd4WeekdayMask 0x07
#define     LOG_fTd4WeekdayShift 0
#define LOG_fTd5Value                 26      // 1 Bit, Bit 7
#define     LOG_fTd5ValueMask 0x80
#define     LOG_fTd5ValueShift 7
#define LOG_fTd5HourAbs               26      // 5 Bits, Bit 5-1
#define     LOG_fTd5HourAbsMask 0x3E
#define     LOG_fTd5HourAbsShift 1
#define LOG_fTd5HourRel               26      // 5 Bits, Bit 5-1
#define     LOG_fTd5HourRelMask 0x3E
#define     LOG_fTd5HourRelShift 1
#define LOG_fTd5MinuteAbs             26      // 6 Bits, Bit 0--5
#define LOG_fTd5MinuteRel             26      // 6 Bits, Bit 0--5
#define LOG_fTd5Weekday               27      // 3 Bits, Bit 2-0
#define     LOG_fTd5WeekdayMask 0x07
#define     LOG_fTd5WeekdayShift 0
#define LOG_fTd6Value                 28      // 1 Bit, Bit 7
#define     LOG_fTd6ValueMask 0x80
#define     LOG_fTd6ValueShift 7
#define LOG_fTd6HourAbs               28      // 5 Bits, Bit 5-1
#define     LOG_fTd6HourAbsMask 0x3E
#define     LOG_fTd6HourAbsShift 1
#define LOG_fTd6HourRel               28      // 5 Bits, Bit 5-1
#define     LOG_fTd6HourRelMask 0x3E
#define     LOG_fTd6HourRelShift 1
#define LOG_fTd6MinuteAbs             28      // 6 Bits, Bit 0--5
#define LOG_fTd6MinuteRel             28      // 6 Bits, Bit 0--5
#define LOG_fTd6Weekday               29      // 3 Bits, Bit 2-0
#define     LOG_fTd6WeekdayMask 0x07
#define     LOG_fTd6WeekdayShift 0
#define LOG_fTd7Value                 30      // 1 Bit, Bit 7
#define     LOG_fTd7ValueMask 0x80
#define     LOG_fTd7ValueShift 7
#define LOG_fTd7HourAbs               30      // 5 Bits, Bit 5-1
#define     LOG_fTd7HourAbsMask 0x3E
#define     LOG_fTd7HourAbsShift 1
#define LOG_fTd7HourRel               30      // 5 Bits, Bit 5-1
#define     LOG_fTd7HourRelMask 0x3E
#define     LOG_fTd7HourRelShift 1
#define LOG_fTd7MinuteAbs             30      // 6 Bits, Bit 0--5
#define LOG_fTd7MinuteRel             30      // 6 Bits, Bit 0--5
#define LOG_fTd7Weekday               31      // 3 Bits, Bit 2-0
#define     LOG_fTd7WeekdayMask 0x07
#define     LOG_fTd7WeekdayShift 0
#define LOG_fTd8Value                 32      // 1 Bit, Bit 7
#define     LOG_fTd8ValueMask 0x80
#define     LOG_fTd8ValueShift 7
#define LOG_fTd8HourAbs               32      // 5 Bits, Bit 5-1
#define     LOG_fTd8HourAbsMask 0x3E
#define     LOG_fTd8HourAbsShift 1
#define LOG_fTd8HourRel               32      // 5 Bits, Bit 5-1
#define     LOG_fTd8HourRelMask 0x3E
#define     LOG_fTd8HourRelShift 1
#define LOG_fTd8MinuteAbs             32      // 6 Bits, Bit 0--5
#define LOG_fTd8MinuteRel             32      // 6 Bits, Bit 0--5
#define LOG_fTd8Weekday               33      // 3 Bits, Bit 2-0
#define     LOG_fTd8WeekdayMask 0x07
#define     LOG_fTd8WeekdayShift 0
#define LOG_fTy1Weekday1              26      // 1 Bit, Bit 7
#define     LOG_fTy1Weekday1Mask 0x80
#define     LOG_fTy1Weekday1Shift 7
#define LOG_fTy1Weekday2              26      // 1 Bit, Bit 6
#define     LOG_fTy1Weekday2Mask 0x40
#define     LOG_fTy1Weekday2Shift 6
#define LOG_fTy1Weekday3              26      // 1 Bit, Bit 5
#define     LOG_fTy1Weekday3Mask 0x20
#define     LOG_fTy1Weekday3Shift 5
#define LOG_fTy1Weekday4              26      // 1 Bit, Bit 4
#define     LOG_fTy1Weekday4Mask 0x10
#define     LOG_fTy1Weekday4Shift 4
#define LOG_fTy1Weekday5              26      // 1 Bit, Bit 3
#define     LOG_fTy1Weekday5Mask 0x08
#define     LOG_fTy1Weekday5Shift 3
#define LOG_fTy1Weekday6              26      // 1 Bit, Bit 2
#define     LOG_fTy1Weekday6Mask 0x04
#define     LOG_fTy1Weekday6Shift 2
#define LOG_fTy1Weekday7              26      // 1 Bit, Bit 1
#define     LOG_fTy1Weekday7Mask 0x02
#define     LOG_fTy1Weekday7Shift 1
#define LOG_fTy1Day                   26      // 7 Bits, Bit 7-1
#define LOG_fTy1IsWeekday             26      // 1 Bit, Bit 0
#define     LOG_fTy1IsWeekdayMask 0x01
#define     LOG_fTy1IsWeekdayShift 0
#define LOG_fTy1Month                 27      // 4 Bits, Bit 7-4
#define     LOG_fTy1MonthMask 0xF0
#define     LOG_fTy1MonthShift 4
#define LOG_fTy2Weekday1              28      // 1 Bit, Bit 7
#define     LOG_fTy2Weekday1Mask 0x80
#define     LOG_fTy2Weekday1Shift 7
#define LOG_fTy2Weekday2              28      // 1 Bit, Bit 6
#define     LOG_fTy2Weekday2Mask 0x40
#define     LOG_fTy2Weekday2Shift 6
#define LOG_fTy2Weekday3              28      // 1 Bit, Bit 5
#define     LOG_fTy2Weekday3Mask 0x20
#define     LOG_fTy2Weekday3Shift 5
#define LOG_fTy2Weekday4              28      // 1 Bit, Bit 4
#define     LOG_fTy2Weekday4Mask 0x10
#define     LOG_fTy2Weekday4Shift 4
#define LOG_fTy2Weekday5              28      // 1 Bit, Bit 3
#define     LOG_fTy2Weekday5Mask 0x08
#define     LOG_fTy2Weekday5Shift 3
#define LOG_fTy2Weekday6              28      // 1 Bit, Bit 2
#define     LOG_fTy2Weekday6Mask 0x04
#define     LOG_fTy2Weekday6Shift 2
#define LOG_fTy2Weekday7              28      // 1 Bit, Bit 1
#define     LOG_fTy2Weekday7Mask 0x02
#define     LOG_fTy2Weekday7Shift 1
#define LOG_fTy2Day                   28      // 7 Bits, Bit 7-1
#define LOG_fTy2IsWeekday             28      // 1 Bit, Bit 0
#define     LOG_fTy2IsWeekdayMask 0x01
#define     LOG_fTy2IsWeekdayShift 0
#define LOG_fTy2Month                 29      // 4 Bits, Bit 7-4
#define     LOG_fTy2MonthMask 0xF0
#define     LOG_fTy2MonthShift 4
#define LOG_fTy3Weekday1              30      // 1 Bit, Bit 7
#define     LOG_fTy3Weekday1Mask 0x80
#define     LOG_fTy3Weekday1Shift 7
#define LOG_fTy3Weekday2              30      // 1 Bit, Bit 6
#define     LOG_fTy3Weekday2Mask 0x40
#define     LOG_fTy3Weekday2Shift 6
#define LOG_fTy3Weekday3              30      // 1 Bit, Bit 5
#define     LOG_fTy3Weekday3Mask 0x20
#define     LOG_fTy3Weekday3Shift 5
#define LOG_fTy3Weekday4              30      // 1 Bit, Bit 4
#define     LOG_fTy3Weekday4Mask 0x10
#define     LOG_fTy3Weekday4Shift 4
#define LOG_fTy3Weekday5              30      // 1 Bit, Bit 3
#define     LOG_fTy3Weekday5Mask 0x08
#define     LOG_fTy3Weekday5Shift 3
#define LOG_fTy3Weekday6              30      // 1 Bit, Bit 2
#define     LOG_fTy3Weekday6Mask 0x04
#define     LOG_fTy3Weekday6Shift 2
#define LOG_fTy3Weekday7              30      // 1 Bit, Bit 1
#define     LOG_fTy3Weekday7Mask 0x02
#define     LOG_fTy3Weekday7Shift 1
#define LOG_fTy3Day                   30      // 7 Bits, Bit 7-1
#define LOG_fTy3IsWeekday             30      // 1 Bit, Bit 0
#define     LOG_fTy3IsWeekdayMask 0x01
#define     LOG_fTy3IsWeekdayShift 0
#define LOG_fTy3Month                 31      // 4 Bits, Bit 7-4
#define     LOG_fTy3MonthMask 0xF0
#define     LOG_fTy3MonthShift 4
#define LOG_fTy4Weekday1              32      // 1 Bit, Bit 7
#define     LOG_fTy4Weekday1Mask 0x80
#define     LOG_fTy4Weekday1Shift 7
#define LOG_fTy4Weekday2              32      // 1 Bit, Bit 6
#define     LOG_fTy4Weekday2Mask 0x40
#define     LOG_fTy4Weekday2Shift 6
#define LOG_fTy4Weekday3              32      // 1 Bit, Bit 5
#define     LOG_fTy4Weekday3Mask 0x20
#define     LOG_fTy4Weekday3Shift 5
#define LOG_fTy4Weekday4              32      // 1 Bit, Bit 4
#define     LOG_fTy4Weekday4Mask 0x10
#define     LOG_fTy4Weekday4Shift 4
#define LOG_fTy4Weekday5              32      // 1 Bit, Bit 3
#define     LOG_fTy4Weekday5Mask 0x08
#define     LOG_fTy4Weekday5Shift 3
#define LOG_fTy4Weekday6              32      // 1 Bit, Bit 2
#define     LOG_fTy4Weekday6Mask 0x04
#define     LOG_fTy4Weekday6Shift 2
#define LOG_fTy4Weekday7              32      // 1 Bit, Bit 1
#define     LOG_fTy4Weekday7Mask 0x02
#define     LOG_fTy4Weekday7Shift 1
#define LOG_fTy4Day                   32      // 7 Bits, Bit 7-1
#define LOG_fTy4IsWeekday             32      // 1 Bit, Bit 0
#define     LOG_fTy4IsWeekdayMask 0x01
#define     LOG_fTy4IsWeekdayShift 0
#define LOG_fTy4Month                 33      // 4 Bits, Bit 7-4
#define     LOG_fTy4MonthMask 0xF0
#define     LOG_fTy4MonthShift 4
#define LOG_fI1                       34      // 4 Bits, Bit 7-4
#define     LOG_fI1Mask 0xF0
#define     LOG_fI1Shift 4
#define LOG_fI2                       34      // 4 Bits, Bit 3-0
#define     LOG_fI2Mask 0x0F
#define     LOG_fI2Shift 0
#define LOG_fI1Function               35      // uint8_t
#define LOG_fI2Function               36      // uint8_t
#define LOG_fOStairtimeBase           37      // 2 Bits, Bit 7-6
#define     LOG_fOStairtimeBaseMask 0xC0
#define     LOG_fOStairtimeBaseShift 6
#define LOG_fOStairtimeTime           37      // uint14_t
#define LOG_fOBlinkBase               39      // 2 Bits, Bit 7-6
#define     LOG_fOBlinkBaseMask 0xC0
#define     LOG_fOBlinkBaseShift 6
#define LOG_fOBlinkTime               39      // uint14_t
#define LOG_fODelay                   41      // 1 Bit, Bit 7
#define     LOG_fODelayMask 0x80
#define     LOG_fODelayShift 7
#define LOG_fODelayOnRepeat           41      // 2 Bits, Bit 6-5
#define     LOG_fODelayOnRepeatMask 0x60
#define     LOG_fODelayOnRepeatShift 5
#define LOG_fODelayOnReset            41      // 1 Bit, Bit 4
#define     LOG_fODelayOnResetMask 0x10
#define     LOG_fODelayOnResetShift 4
#define LOG_fODelayOffRepeat          41      // 2 Bits, Bit 3-2
#define     LOG_fODelayOffRepeatMask 0x0C
#define     LOG_fODelayOffRepeatShift 2
#define LOG_fODelayOffReset           41      // 1 Bit, Bit 1
#define     LOG_fODelayOffResetMask 0x02
#define     LOG_fODelayOffResetShift 1
#define LOG_fODelayOnBase             42      // 2 Bits, Bit 7-6
#define     LOG_fODelayOnBaseMask 0xC0
#define     LOG_fODelayOnBaseShift 6
#define LOG_fODelayOnTime             42      // uint14_t
#define LOG_fODelayOffBase            44      // 2 Bits, Bit 7-6
#define     LOG_fODelayOffBaseMask 0xC0
#define     LOG_fODelayOffBaseShift 6
#define LOG_fODelayOffTime            44      // uint14_t
#define LOG_fOStair                   46      // 1 Bit, Bit 7
#define     LOG_fOStairMask 0x80
#define     LOG_fOStairShift 7
#define LOG_fORetrigger               46      // 1 Bit, Bit 6
#define     LOG_fORetriggerMask 0x40
#define     LOG_fORetriggerShift 6
#define LOG_fOStairOff                46      // 1 Bit, Bit 5
#define     LOG_fOStairOffMask 0x20
#define     LOG_fOStairOffShift 5
#define LOG_fORepeat                  46      // 1 Bit, Bit 4
#define     LOG_fORepeatMask 0x10
#define     LOG_fORepeatShift 4
#define LOG_fOOutputFilter            46      // 2 Bits, Bit 3-2
#define     LOG_fOOutputFilterMask 0x0C
#define     LOG_fOOutputFilterShift 2
#define LOG_fORepeatOnBase            47      // 2 Bits, Bit 7-6
#define     LOG_fORepeatOnBaseMask 0xC0
#define     LOG_fORepeatOnBaseShift 6
#define LOG_fORepeatOnTime            47      // uint14_t
#define LOG_fORepeatOffBase           49      // 2 Bits, Bit 7-6
#define     LOG_fORepeatOffBaseMask 0xC0
#define     LOG_fORepeatOffBaseShift 6
#define LOG_fORepeatOffTime           49      // uint14_t
#define LOG_fODpt                     51      // 8 Bits, Bit 7-0
#define LOG_fOOn                      52      // 8 Bits, Bit 7-0
#define LOG_fOOnBuzzer                52      // 8 Bits, Bit 7-0
#define LOG_fOOnLed                   52      // 8 Bits, Bit 7-0
#define LOG_fOOnAll                   52      // 8 Bits, Bit 7-0
#define LOG_fOOnTone                  53      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt1                  53      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt2                  53      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt5                  53      // uint8_t
#define LOG_fOOnDpt5001               53      // uint8_t
#define LOG_fOOnDpt6                  53      // int8_t
#define LOG_fOOnDpt7                  53      // uint16_t
#define LOG_fOOnDpt8                  53      // int16_t
#define LOG_fOOnDpt9                  53      // float
#define LOG_fOOnDpt16                 53      // char*, 14 Byte
#define LOG_fOOnDpt17                 53      // 8 Bits, Bit 7-0
#define LOG_fOOnRGB                   53      // color, uint, 3 Byte
#define LOG_fOOnPAArea                53      // 4 Bits, Bit 7-4
#define     LOG_fOOnPAAreaMask 0xF0
#define     LOG_fOOnPAAreaShift 4
#define LOG_fOOnPALine                53      // 4 Bits, Bit 3-0
#define     LOG_fOOnPALineMask 0x0F
#define     LOG_fOOnPALineShift 0
#define LOG_fOOnPADevice              54      // uint8_t
#define LOG_fOOnFunction              53      // 8 Bits, Bit 7-0
#define LOG_fOOff                     67      // 8 Bits, Bit 7-0
#define LOG_fOOffBuzzer               67      // 8 Bits, Bit 7-0
#define LOG_fOOffLed                  67      // 8 Bits, Bit 7-0
#define LOG_fOOffAll                  67      // 8 Bits, Bit 7-0
#define LOG_fOOffTone                 68      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt1                 68      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt2                 68      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt5                 68      // uint8_t
#define LOG_fOOffDpt5001              68      // uint8_t
#define LOG_fOOffDpt6                 68      // int8_t
#define LOG_fOOffDpt7                 68      // uint16_t
#define LOG_fOOffDpt8                 68      // int16_t
#define LOG_fOOffDpt9                 68      // float
#define LOG_fOOffDpt16                68      // char*, 14 Byte
#define LOG_fOOffDpt17                68      // 8 Bits, Bit 7-0
#define LOG_fOOffRGB                  68      // color, uint, 3 Byte
#define LOG_fOOffPAArea               68      // 4 Bits, Bit 7-4
#define     LOG_fOOffPAAreaMask 0xF0
#define     LOG_fOOffPAAreaShift 4
#define LOG_fOOffPALine               68      // 4 Bits, Bit 3-0
#define     LOG_fOOffPALineMask 0x0F
#define     LOG_fOOffPALineShift 0
#define LOG_fOOffPADevice             69      // uint8_t
#define LOG_fOOffFunction             68      // 8 Bits, Bit 7-0
#define LOG_fE1UseOtherKO             82      // 1 Bit, Bit 7
#define     LOG_fE1UseOtherKOMask 0x80
#define     LOG_fE1UseOtherKOShift 7
#define LOG_fE1OtherKO                82      // uint15_t
#define LOG_fE2UseOtherKO             84      // 1 Bit, Bit 7
#define     LOG_fE2UseOtherKOMask 0x80
#define     LOG_fE2UseOtherKOShift 7
#define LOG_fE2OtherKO                84      // uint15_t

// Communication objects per channel (multiple occurrence)
#define LOG_KoOffset 400
#define LOG_KoBlockSize 3
#define LOG_KoKOfE1 0
#define LOG_KoKOfE2 1
#define LOG_KoKOfO 2

#define SOM_ChannelCount 10

// Parameter per channel
#define SOM_ParamBlockOffset 975
#define SOM_ParamBlockSize 10
#define SOM_TriState                   0      // 1 Bit, Bit 7
#define     SOM_TriStateMask 0x80
#define     SOM_TriStateShift 7
#define SOM_TriRepeat                  0      // 1 Bit, Bit 6
#define     SOM_TriRepeatMask 0x40
#define     SOM_TriRepeatShift 6
#define SOM_TriLock                    0      // 2 Bits, Bit 5-4
#define     SOM_TriLockMask 0x30
#define     SOM_TriLockShift 4
#define SOM_TriDayNight                0      // 2 Bits, Bit 3-2
#define     SOM_TriDayNightMask 0x0C
#define     SOM_TriDayNightShift 2
#define SOM_TriPriority                1      // 3 Bits, Bit 7-5
#define     SOM_TriPriorityMask 0xE0
#define     SOM_TriPriorityShift 5
#define SOM_TriDurationBase            2      // 2 Bits, Bit 7-6
#define     SOM_TriDurationBaseMask 0xC0
#define     SOM_TriDurationBaseShift 6
#define SOM_TriDurationTime            2      // uint14_t
#define SOM_TriFileDay                 4      // uint16_t
#define SOM_TriFileNight               6      // uint16_t
#define SOM_TriVolumeDay               8      // uint8_t
#define SOM_TriVolumeDayInactive       8      // uint8_t
#define SOM_TriVolumeNight             9      // uint8_t
#define SOM_TriVolumeNightInactive     9      // uint8_t

// Communication objects per channel (multiple occurrence)
#define SOM_KoOffset 50
#define SOM_KoBlockSize 4
#define SOM_KoTriTrigger 0
#define SOM_KoTriStatus 1
#define SOM_KoTriLock 2
#define SOM_KoTriDayNight 3

#define BTN_ChannelCount 20

// Parameter per channel
#define BTN_ParamBlockOffset 1075
#define BTN_ParamBlockSize 51
#define BTN_BTNMode                    0      // 4 Bits, Bit 7-4
#define     BTN_BTNModeMask 0xF0
#define     BTN_BTNModeShift 4
#define BTN_BTNLock                    0      // 2 Bits, Bit 3-2
#define     BTN_BTNLockMask 0x0C
#define     BTN_BTNLockShift 2
#define BTN_BTNMultiClickCount         0      // 1 Bit, Bit 3
#define     BTN_BTNMultiClickCountMask 0x08
#define     BTN_BTNMultiClickCountShift 3
#define BTN_BTNInputA                  1      // char*, 2 Byte
#define BTN_BTNInputB                  3      // char*, 2 Byte
#define BTN_BTNReactionTimeMultiClick  5      // 8 Bits, Bit 7-0
#define BTN_BTNReactionTimeLong        6      // 8 Bits, Bit 7-0
#define BTN_BTNReactionTimeExtraLong   7      // 8 Bits, Bit 7-0
#define BTN_BTNOutputShort_DPT         8      // 8 Bits, Bit 7-0
#define BTN_BTNOutputLong_DPT          9      // 8 Bits, Bit 7-0
#define BTN_BTNOutputExtraLong_DPT    10      // 8 Bits, Bit 7-0
#define BTN_BTNOutputMulti_DPT        11      // 8 Bits, Bit 7-0
#define BTN_BTNOutputMulti_Click1_Active 12      // 1 Bit, Bit 7
#define     BTN_BTNOutputMulti_Click1_ActiveMask 0x80
#define     BTN_BTNOutputMulti_Click1_ActiveShift 7
#define BTN_BTNOutputMulti_Click2_Active 12      // 1 Bit, Bit 6
#define     BTN_BTNOutputMulti_Click2_ActiveMask 0x40
#define     BTN_BTNOutputMulti_Click2_ActiveShift 6
#define BTN_BTNOutputMulti_Click3_Active 12      // 1 Bit, Bit 5
#define     BTN_BTNOutputMulti_Click3_ActiveMask 0x20
#define     BTN_BTNOutputMulti_Click3_ActiveShift 5
#define BTN_BTNOutputShort_Taster1_Active_Press 13      // 1 Bit, Bit 7
#define     BTN_BTNOutputShort_Taster1_Active_PressMask 0x80
#define     BTN_BTNOutputShort_Taster1_Active_PressShift 7
#define BTN_BTNOutputShort_Taster1_Active_Release 13      // 1 Bit, Bit 6
#define     BTN_BTNOutputShort_Taster1_Active_ReleaseMask 0x40
#define     BTN_BTNOutputShort_Taster1_Active_ReleaseShift 6
#define BTN_BTNOutputShort_Taster2_Active_Press 13      // 1 Bit, Bit 5
#define     BTN_BTNOutputShort_Taster2_Active_PressMask 0x20
#define     BTN_BTNOutputShort_Taster2_Active_PressShift 5
#define BTN_BTNOutputShort_Taster2_Active_Release 13      // 1 Bit, Bit 4
#define     BTN_BTNOutputShort_Taster2_Active_ReleaseMask 0x10
#define     BTN_BTNOutputShort_Taster2_Active_ReleaseShift 4
#define BTN_BTNOutputLong_Taster1_Active_Press 14      // 1 Bit, Bit 7
#define     BTN_BTNOutputLong_Taster1_Active_PressMask 0x80
#define     BTN_BTNOutputLong_Taster1_Active_PressShift 7
#define BTN_BTNOutputLong_Taster1_Active_Release 14      // 1 Bit, Bit 6
#define     BTN_BTNOutputLong_Taster1_Active_ReleaseMask 0x40
#define     BTN_BTNOutputLong_Taster1_Active_ReleaseShift 6
#define BTN_BTNOutputLong_Taster2_Active_Press 14      // 1 Bit, Bit 5
#define     BTN_BTNOutputLong_Taster2_Active_PressMask 0x20
#define     BTN_BTNOutputLong_Taster2_Active_PressShift 5
#define BTN_BTNOutputLong_Taster2_Active_Release 14      // 1 Bit, Bit 4
#define     BTN_BTNOutputLong_Taster2_Active_ReleaseMask 0x10
#define     BTN_BTNOutputLong_Taster2_Active_ReleaseShift 4
#define BTN_BTNOutputExtraLong_Taster1_Active_Press 15      // 1 Bit, Bit 7
#define     BTN_BTNOutputExtraLong_Taster1_Active_PressMask 0x80
#define     BTN_BTNOutputExtraLong_Taster1_Active_PressShift 7
#define BTN_BTNOutputExtraLong_Taster1_Active_Release 15      // 1 Bit, Bit 6
#define     BTN_BTNOutputExtraLong_Taster1_Active_ReleaseMask 0x40
#define     BTN_BTNOutputExtraLong_Taster1_Active_ReleaseShift 6
#define BTN_BTNOutputExtraLong_Taster2_Active_Press 15      // 1 Bit, Bit 5
#define     BTN_BTNOutputExtraLong_Taster2_Active_PressMask 0x20
#define     BTN_BTNOutputExtraLong_Taster2_Active_PressShift 5
#define BTN_BTNOutputExtraLong_Taster2_Active_Release 15      // 1 Bit, Bit 4
#define     BTN_BTNOutputExtraLong_Taster2_Active_ReleaseMask 0x10
#define     BTN_BTNOutputExtraLong_Taster2_Active_ReleaseShift 4
#define BTN_BTNOutputShort_Taster1_Dpt1_Press 16      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster1_Dpt1_Release 18      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster2_Dpt1_Press 20      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster2_Dpt1_Release 24      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster1_Dpt1_Press 26      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster1_Dpt1_Release 28      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster2_Dpt1_Press 30      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster2_Dpt1_Release 32      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster1_Dpt1_Press 34      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster1_Dpt1_Release 36      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster2_Dpt1_Press 38      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster2_Dpt1_Release 40      // char*, 2 Byte
#define BTN_BTNOutputMulti_Click1_Dpt1 42      // char*, 2 Byte
#define BTN_BTNOutputMulti_Click2_Dpt1 44      // char*, 2 Byte
#define BTN_BTNOutputMulti_Click3_Dpt1 46      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster1_Dpt2_Press 16      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster1_Dpt2_Release 18      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster2_Dpt2_Press 20      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster2_Dpt2_Release 24      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster1_Dpt2_Press 26      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster1_Dpt2_Release 28      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster2_Dpt2_Press 30      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster2_Dpt2_Release 32      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster1_Dpt2_Press 34      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster1_Dpt2_Release 36      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster2_Dpt2_Press 38      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster2_Dpt2_Release 40      // char*, 2 Byte
#define BTN_BTNOutputMulti_Click1_Dpt2 42      // char*, 2 Byte
#define BTN_BTNOutputMulti_Click2_Dpt2 44      // char*, 2 Byte
#define BTN_BTNOutputMulti_Click3_Dpt2 46      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster1_Dpt5_Press 16      // uint16_t
#define BTN_BTNOutputShort_Taster1_Dpt5_Release 18      // uint16_t
#define BTN_BTNOutputShort_Taster2_Dpt5_Press 20      // uint16_t
#define BTN_BTNOutputShort_Taster2_Dpt5_Release 24      // uint16_t
#define BTN_BTNOutputLong_Taster1_Dpt5_Press 26      // uint16_t
#define BTN_BTNOutputLong_Taster1_Dpt5_Release 28      // uint16_t
#define BTN_BTNOutputLong_Taster2_Dpt5_Press 30      // uint16_t
#define BTN_BTNOutputLong_Taster2_Dpt5_Release 32      // uint16_t
#define BTN_BTNOutputExtraLong_Taster1_Dpt5_Press 34      // uint16_t
#define BTN_BTNOutputExtraLong_Taster1_Dpt5_Release 36      // uint16_t
#define BTN_BTNOutputExtraLong_Taster2_Dpt5_Press 38      // uint16_t
#define BTN_BTNOutputExtraLong_Taster2_Dpt5_Release 40      // uint16_t
#define BTN_BTNOutputMulti_Click1_Dpt5 42      // uint16_t
#define BTN_BTNOutputMulti_Click2_Dpt5 44      // uint16_t
#define BTN_BTNOutputMulti_Click3_Dpt5 46      // uint16_t
#define BTN_BTNOutputShort_Taster1_Dpt5001_Press 16      // uint16_t
#define BTN_BTNOutputShort_Taster1_Dpt5001_Release 18      // uint16_t
#define BTN_BTNOutputShort_Taster2_Dpt5001_Press 20      // uint16_t
#define BTN_BTNOutputShort_Taster2_Dpt5001_Release 24      // uint16_t
#define BTN_BTNOutputLong_Taster1_Dpt5001_Press 26      // uint16_t
#define BTN_BTNOutputLong_Taster1_Dpt5001_Release 28      // uint16_t
#define BTN_BTNOutputLong_Taster2_Dpt5001_Press 30      // uint16_t
#define BTN_BTNOutputLong_Taster2_Dpt5001_Release 32      // uint16_t
#define BTN_BTNOutputExtraLong_Taster1_Dpt5001_Press 34      // uint16_t
#define BTN_BTNOutputExtraLong_Taster1_Dpt5001_Release 36      // uint16_t
#define BTN_BTNOutputExtraLong_Taster2_Dpt5001_Press 38      // uint16_t
#define BTN_BTNOutputExtraLong_Taster2_Dpt5001_Release 40      // uint16_t
#define BTN_BTNOutputMulti_Click1_Dpt5001 42      // uint16_t
#define BTN_BTNOutputMulti_Click2_Dpt5001 44      // uint16_t
#define BTN_BTNOutputMulti_Click3_Dpt5001 46      // uint16_t
#define BTN_BTNOutputShort_Taster1_Dpt7_Press 16      // uint16_t
#define BTN_BTNOutputShort_Taster1_Dpt7_Release 18      // uint16_t
#define BTN_BTNOutputShort_Taster2_Dpt7_Press 20      // uint16_t
#define BTN_BTNOutputShort_Taster2_Dpt7_Release 24      // uint16_t
#define BTN_BTNOutputLong_Taster1_Dpt7_Press 26      // uint16_t
#define BTN_BTNOutputLong_Taster1_Dpt7_Release 28      // uint16_t
#define BTN_BTNOutputLong_Taster2_Dpt7_Press 30      // uint16_t
#define BTN_BTNOutputLong_Taster2_Dpt7_Release 32      // uint16_t
#define BTN_BTNOutputExtraLong_Taster1_Dpt7_Press 34      // uint16_t
#define BTN_BTNOutputExtraLong_Taster1_Dpt7_Release 36      // uint16_t
#define BTN_BTNOutputExtraLong_Taster2_Dpt7_Press 38      // uint16_t
#define BTN_BTNOutputExtraLong_Taster2_Dpt7_Release 40      // uint16_t
#define BTN_BTNOutputMulti_Click1_Dpt7 42      // uint16_t
#define BTN_BTNOutputMulti_Click2_Dpt7 44      // uint16_t
#define BTN_BTNOutputMulti_Click3_Dpt7 46      // uint16_t
#define BTN_BTNOutputShort_Taster1_Dpt18_Press 16      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster1_Dpt18_Release 18      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster2_Dpt18_Press 20      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster2_Dpt18_Release 24      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster1_Dpt18_Press 26      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster1_Dpt18_Release 28      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster2_Dpt18_Press 30      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster2_Dpt18_Release 32      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster1_Dpt18_Press 34      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster1_Dpt18_Release 36      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster2_Dpt18_Press 38      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster2_Dpt18_Release 40      // char*, 2 Byte
#define BTN_BTNOutputMulti_Click1_Dpt18 42      // char*, 2 Byte
#define BTN_BTNOutputMulti_Click2_Dpt18 44      // char*, 2 Byte
#define BTN_BTNOutputMulti_Click3_Dpt18 46      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster1_Dpt3007_Press 16      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster1_Dpt3007_Release 18      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster2_Dpt3007_Press 20      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster2_Dpt3007_Release 24      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster1_Dpt3007_Press 26      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster1_Dpt3007_Release 28      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster2_Dpt3007_Press 30      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster2_Dpt3007_Release 32      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster1_Dpt3007_Press 34      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster1_Dpt3007_Release 36      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster2_Dpt3007_Press 38      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster2_Dpt3007_Release 40      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster1_Dpt3008_Press 16      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster1_Dpt3008_Release 18      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster2_Dpt3008_Press 20      // char*, 2 Byte
#define BTN_BTNOutputShort_Taster2_Dpt3008_Release 24      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster1_Dpt3008_Press 26      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster1_Dpt3008_Release 28      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster2_Dpt3008_Press 30      // char*, 2 Byte
#define BTN_BTNOutputLong_Taster2_Dpt3008_Release 32      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster1_Dpt3008_Press 34      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster1_Dpt3008_Release 36      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster2_Dpt3008_Press 38      // char*, 2 Byte
#define BTN_BTNOutputExtraLong_Taster2_Dpt3008_Release 40      // char*, 2 Byte
#define BTN_BTNOutput2Short_Taster1   46      // 2 Bits, Bit 7-6
#define     BTN_BTNOutput2Short_Taster1Mask 0xC0
#define     BTN_BTNOutput2Short_Taster1Shift 6
#define BTN_BTNOutput2Short_Taster2   46      // 2 Bits, Bit 5-4
#define     BTN_BTNOutput2Short_Taster2Mask 0x30
#define     BTN_BTNOutput2Short_Taster2Shift 4
#define BTN_BTNOutput2Long_Taster1    46      // 2 Bits, Bit 3-2
#define     BTN_BTNOutput2Long_Taster1Mask 0x0C
#define     BTN_BTNOutput2Long_Taster1Shift 2
#define BTN_BTNOutput2Long_Taster2    46      // 2 Bits, Bit 1-0
#define     BTN_BTNOutput2Long_Taster2Mask 0x03
#define     BTN_BTNOutput2Long_Taster2Shift 0
#define BTN_BTNOutput2ExtraLong_Taster1 47      // 2 Bits, Bit 7-6
#define     BTN_BTNOutput2ExtraLong_Taster1Mask 0xC0
#define     BTN_BTNOutput2ExtraLong_Taster1Shift 6
#define BTN_BTNOutput2ExtraLong_Taster2 47      // 2 Bits, Bit 5-4
#define     BTN_BTNOutput2ExtraLong_Taster2Mask 0x30
#define     BTN_BTNOutput2ExtraLong_Taster2Shift 4
#define BTN_BTNStatusThreshold        48      // uint8_t
#define BTN_BTNStatusFallbackBase     49      // 2 Bits, Bit 7-6
#define     BTN_BTNStatusFallbackBaseMask 0xC0
#define     BTN_BTNStatusFallbackBaseShift 6
#define BTN_BTNStatusFallbackTime     49      // uint14_t

// Communication objects per channel (multiple occurrence)
#define BTN_KoOffset 100
#define BTN_KoBlockSize 12
#define BTN_KoBTNLock 0
#define BTN_KoBTNInput1 1
#define BTN_KoBTNInput2 2
#define BTN_KoBTNOutput1Status 3
#define BTN_KoBTNOutput2Status 4
#define BTN_KoBTNOutput3Status 5
#define BTN_KoBTNOutput1 6
#define BTN_KoBTNOutput2 7
#define BTN_KoBTNOutput3 8
#define BTN_KoBTNOutput4 9
#define BTN_KoBTNOutput5 10
#define BTN_KoBTNOutput6 11

#define BI_ChannelCount 4

// Parameter per channel
#define BI_ParamBlockOffset 2095
#define BI_ParamBlockSize 4
#define BI_InputActive                0      // 1 Bit, Bit 7
#define     BI_InputActiveMask 0x80
#define     BI_InputActiveShift 7
#define BI_InputOpen                  0      // 2 Bits, Bit 5-4
#define     BI_InputOpenMask 0x30
#define     BI_InputOpenShift 4
#define BI_InputClose                 0      // 2 Bits, Bit 3-2
#define     BI_InputCloseMask 0x0C
#define     BI_InputCloseShift 2
#define BI_InputPeriodic              0      // 1 Bit, Bit 2
#define     BI_InputPeriodicMask 0x04
#define     BI_InputPeriodicShift 2
#define BI_InputDebouncing            1      // 8 Bits, Bit 7-0
#define BI_InputPeriodicBase          2      // 2 Bits, Bit 7-6
#define     BI_InputPeriodicBaseMask 0xC0
#define     BI_InputPeriodicBaseShift 6
#define BI_InputPeriodicTime          2      // uint14_t

// Communication objects per channel (multiple occurrence)
#define BI_KoOffset 41
#define BI_KoBlockSize 1
#define BI_KoInputOutput 0

#define MAIN_OpenKnxId 0xA3
#define MAIN_ApplicationNumber 0
#define MAIN_ApplicationVersion 2
#define MAIN_OrderNumber "SOM-UP"
