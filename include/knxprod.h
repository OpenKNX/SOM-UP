#pragma once


#define paramDelay(time) (uint32_t)( \
            (time & 0xC000) == 0xC000 ? (time & 0x3FFF) * 100 : \
            (time & 0xC000) == 0x0000 ? (time & 0x3FFF) * 1000 : \
            (time & 0xC000) == 0x4000 ? (time & 0x3FFF) * 60000 : \
            (time & 0xC000) == 0x8000 ? ((time & 0x3FFF) > 1000 ? 3600000 : \
                                         (time & 0x3FFF) * 3600000 ) : 0 )
                                             
#define MAIN_OpenKnxId 0xA2
#define MAIN_ApplicationNumber 41
#define MAIN_ApplicationVersion 3
#define MAIN_ParameterSize 3242
#define MAIN_MaxKoNumber 399
#define MAIN_OrderNumber "SOM-UP"
#define BTN_ModuleVersion 3
#define LOG_ModuleVersion 32
// Parameter with single occurrence


#define BASE_StartupDelayBase                     0      // 2 Bits, Bit 7-6
#define     BASE_StartupDelayBaseMask 0xC0
#define     BASE_StartupDelayBaseShift 6
#define BASE_StartupDelayTime                     0      // 14 Bits, Bit 13-0
#define     BASE_StartupDelayTimeMask 0x3FFF
#define     BASE_StartupDelayTimeShift 0
#define BASE_HeartbeatDelayBase                   2      // 2 Bits, Bit 7-6
#define     BASE_HeartbeatDelayBaseMask 0xC0
#define     BASE_HeartbeatDelayBaseShift 6
#define BASE_HeartbeatDelayTime                   2      // 14 Bits, Bit 13-0
#define     BASE_HeartbeatDelayTimeMask 0x3FFF
#define     BASE_HeartbeatDelayTimeShift 0
#define BASE_Timezone                             4      // 5 Bits, Bit 7-3
#define     BASE_TimezoneMask 0xF8
#define     BASE_TimezoneShift 3
#define BASE_TimezoneSign                         4      // 1 Bit, Bit 7
#define     BASE_TimezoneSignMask 0x80
#define     BASE_TimezoneSignShift 7
#define BASE_TimezoneValue                        4      // 4 Bits, Bit 6-3
#define     BASE_TimezoneValueMask 0x78
#define     BASE_TimezoneValueShift 3
#define BASE_CombinedTimeDate                     4      // 1 Bit, Bit 2
#define     BASE_CombinedTimeDateMask 0x04
#define     BASE_CombinedTimeDateShift 2
#define BASE_SummertimeAll                        4      // 2 Bits, Bit 1-0
#define     BASE_SummertimeAllMask 0x03
#define     BASE_SummertimeAllShift 0
#define BASE_SummertimeDE                         4      // 2 Bits, Bit 1-0
#define     BASE_SummertimeDEMask 0x03
#define     BASE_SummertimeDEShift 0
#define BASE_SummertimeWorld                      4      // 2 Bits, Bit 1-0
#define     BASE_SummertimeWorldMask 0x03
#define     BASE_SummertimeWorldShift 0
#define BASE_SummertimeKO                         4      // 2 Bits, Bit 1-0
#define     BASE_SummertimeKOMask 0x03
#define     BASE_SummertimeKOShift 0
#define BASE_Diagnose                             5      // 1 Bit, Bit 7
#define     BASE_DiagnoseMask 0x80
#define     BASE_DiagnoseShift 7
#define BASE_Watchdog                             5      // 1 Bit, Bit 6
#define     BASE_WatchdogMask 0x40
#define     BASE_WatchdogShift 6
#define BASE_ReadTimeDate                         5      // 1 Bit, Bit 5
#define     BASE_ReadTimeDateMask 0x20
#define     BASE_ReadTimeDateShift 5
#define BASE_Latitude                             6      // float
#define BASE_Longitude                           10      // float

// Zeitbasis
#define ParamBASE_StartupDelayBase                    ((knx.paramByte(BASE_StartupDelayBase) & BASE_StartupDelayBaseMask) >> BASE_StartupDelayBaseShift)
// Zeit
#define ParamBASE_StartupDelayTime                    (knx.paramWord(BASE_StartupDelayTime) & BASE_StartupDelayTimeMask)
// Zeit (in Millisekunden)
#define ParamBASE_StartupDelayTimeMS                  (paramDelay(knx.paramWord(BASE_StartupDelayTime)))
// Zeitbasis
#define ParamBASE_HeartbeatDelayBase                  ((knx.paramByte(BASE_HeartbeatDelayBase) & BASE_HeartbeatDelayBaseMask) >> BASE_HeartbeatDelayBaseShift)
// Zeit
#define ParamBASE_HeartbeatDelayTime                  (knx.paramWord(BASE_HeartbeatDelayTime) & BASE_HeartbeatDelayTimeMask)
// Zeit (in Millisekunden)
#define ParamBASE_HeartbeatDelayTimeMS                (paramDelay(knx.paramWord(BASE_HeartbeatDelayTime)))
// Zeitzone
#define ParamBASE_Timezone                            ((knx.paramByte(BASE_Timezone) & BASE_TimezoneMask) >> BASE_TimezoneShift)
// Zeitzone-Vorzeichen
#define ParamBASE_TimezoneSign                        ((bool)(knx.paramByte(BASE_TimezoneSign) & BASE_TimezoneSignMask))
// Zeitzone-Wert
#define ParamBASE_TimezoneValue                       ((knx.paramByte(BASE_TimezoneValue) & BASE_TimezoneValueMask) >> BASE_TimezoneValueShift)
// Empfangen über
#define ParamBASE_CombinedTimeDate                    ((bool)(knx.paramByte(BASE_CombinedTimeDate) & BASE_CombinedTimeDateMask))
// Sommerzeit ermitteln durch
#define ParamBASE_SummertimeAll                       (knx.paramByte(BASE_SummertimeAll) & BASE_SummertimeAllMask)
// Sommerzeit ermitteln durch
#define ParamBASE_SummertimeDE                        (knx.paramByte(BASE_SummertimeDE) & BASE_SummertimeDEMask)
// Sommerzeit ermitteln durch
#define ParamBASE_SummertimeWorld                     (knx.paramByte(BASE_SummertimeWorld) & BASE_SummertimeWorldMask)
// Sommerzeit ermitteln durch
#define ParamBASE_SummertimeKO                        (knx.paramByte(BASE_SummertimeKO) & BASE_SummertimeKOMask)
// Diagnoseobjekt anzeigen
#define ParamBASE_Diagnose                            ((bool)(knx.paramByte(BASE_Diagnose) & BASE_DiagnoseMask))
// Watchdog aktivieren
#define ParamBASE_Watchdog                            ((bool)(knx.paramByte(BASE_Watchdog) & BASE_WatchdogMask))
// Bei Neustart vom Bus lesen
#define ParamBASE_ReadTimeDate                        ((bool)(knx.paramByte(BASE_ReadTimeDate) & BASE_ReadTimeDateMask))
// Breitengrad
#define ParamBASE_Latitude                            (knx.paramFloat(BASE_Latitude, Float_Enc_IEEE754Single))
// Längengrad
#define ParamBASE_Longitude                           (knx.paramFloat(BASE_Longitude, Float_Enc_IEEE754Single))

#define BASE_KoHeartbeat 1
#define BASE_KoTime 2
#define BASE_KoDate 3
#define BASE_KoDiagnose 7
#define BASE_KoIsSummertime 10

// In Betrieb
#define KoBASE_Heartbeat                           (knx.getGroupObject(BASE_KoHeartbeat))
// Uhrzeit/Datum
#define KoBASE_Time                                (knx.getGroupObject(BASE_KoTime))
// Datum
#define KoBASE_Date                                (knx.getGroupObject(BASE_KoDate))
// Diagnose
#define KoBASE_Diagnose                            (knx.getGroupObject(BASE_KoDiagnose))
// Sommerzeit aktiv
#define KoBASE_IsSummertime                        (knx.getGroupObject(BASE_KoIsSummertime))

#define SOM_External                            15      // 1 Bit, Bit 7
#define     SOM_ExternalMask 0x80
#define     SOM_ExternalShift 7
#define SOM_Scenes                              15      // 1 Bit, Bit 6
#define     SOM_ScenesMask 0x40
#define     SOM_ScenesShift 6
#define SOM_VolumeDay                           16      // uint8_t
#define SOM_VolumeNight                         17      // uint8_t
#define SOM_Lock                                18      // 2 Bits, Bit 7-6
#define     SOM_LockMask 0xC0
#define     SOM_LockShift 6
#define SOM_DayNight                            18      // 2 Bits, Bit 5-4
#define     SOM_DayNightMask 0x30
#define     SOM_DayNightShift 4
#define SOM_Scene0                              19      // 8 Bits, Bit 7-0
#define SOM_Scene1                              20      // 8 Bits, Bit 7-0
#define SOM_Scene2                              21      // 8 Bits, Bit 7-0
#define SOM_Scene3                              22      // 8 Bits, Bit 7-0
#define SOM_Scene4                              23      // 8 Bits, Bit 7-0
#define SOM_Scene5                              24      // 8 Bits, Bit 7-0
#define SOM_Scene6                              25      // 8 Bits, Bit 7-0
#define SOM_Scene7                              26      // 8 Bits, Bit 7-0
#define SOM_Scene8                              27      // 8 Bits, Bit 7-0
#define SOM_Scene9                              28      // 8 Bits, Bit 7-0
#define SOM_Scene10                             29      // 8 Bits, Bit 7-0
#define SOM_Scene11                             30      // 8 Bits, Bit 7-0
#define SOM_Scene12                             31      // 8 Bits, Bit 7-0
#define SOM_Scene13                             32      // 8 Bits, Bit 7-0
#define SOM_Scene14                             33      // 8 Bits, Bit 7-0
#define SOM_Scene15                             34      // 8 Bits, Bit 7-0
#define SOM_Scene16                             35      // 8 Bits, Bit 7-0
#define SOM_Scene17                             36      // 8 Bits, Bit 7-0
#define SOM_Scene18                             37      // 8 Bits, Bit 7-0
#define SOM_Scene19                             38      // 8 Bits, Bit 7-0
#define SOM_SceneAction0                        39      // 8 Bits, Bit 7-0
#define SOM_SceneAction1                        40      // 8 Bits, Bit 7-0
#define SOM_SceneAction2                        41      // 8 Bits, Bit 7-0
#define SOM_SceneAction3                        42      // 8 Bits, Bit 7-0
#define SOM_SceneAction4                        43      // 8 Bits, Bit 7-0
#define SOM_SceneAction5                        44      // 8 Bits, Bit 7-0
#define SOM_SceneAction6                        45      // 8 Bits, Bit 7-0
#define SOM_SceneAction7                        46      // 8 Bits, Bit 7-0
#define SOM_SceneAction8                        47      // 8 Bits, Bit 7-0
#define SOM_SceneAction9                        48      // 8 Bits, Bit 7-0
#define SOM_SceneAction10                       49      // 8 Bits, Bit 7-0
#define SOM_SceneAction11                       50      // 8 Bits, Bit 7-0
#define SOM_SceneAction12                       51      // 8 Bits, Bit 7-0
#define SOM_SceneAction13                       52      // 8 Bits, Bit 7-0
#define SOM_SceneAction14                       53      // 8 Bits, Bit 7-0
#define SOM_SceneAction15                       54      // 8 Bits, Bit 7-0
#define SOM_SceneAction16                       55      // 8 Bits, Bit 7-0
#define SOM_SceneAction17                       56      // 8 Bits, Bit 7-0
#define SOM_SceneAction18                       57      // 8 Bits, Bit 7-0
#define SOM_SceneAction19                       58      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA0                       59      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA1                       60      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA2                       61      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA3                       62      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA4                       63      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA5                       64      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA6                       65      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA7                       66      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA8                       67      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA9                       68      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA10                      69      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA11                      70      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA12                      71      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA13                      72      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA14                      73      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA15                      74      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA16                      75      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA17                      76      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA18                      77      // 8 Bits, Bit 7-0
#define SOM_SceneTargetA19                      78      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB0                       59      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB1                       60      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB2                       61      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB3                       62      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB4                       63      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB5                       64      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB6                       65      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB7                       66      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB8                       67      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB9                       68      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB10                      69      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB11                      70      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB12                      71      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB13                      72      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB14                      73      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB15                      74      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB16                      75      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB17                      76      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB18                      77      // 8 Bits, Bit 7-0
#define SOM_SceneTargetB19                      78      // 8 Bits, Bit 7-0

// Externe Logik
#define ParamSOM_External                            ((bool)(knx.paramByte(SOM_External) & SOM_ExternalMask))
// Szenen
#define ParamSOM_Scenes                              ((bool)(knx.paramByte(SOM_Scenes) & SOM_ScenesMask))
// 
#define ParamSOM_VolumeDay                           (knx.paramByte(SOM_VolumeDay))
// 
#define ParamSOM_VolumeNight                         (knx.paramByte(SOM_VolumeNight))
// Zentrale Sperre
#define ParamSOM_Lock                                ((knx.paramByte(SOM_Lock) & SOM_LockMask) >> SOM_LockShift)
// Tag/Nacht-Objekt
#define ParamSOM_DayNight                            ((knx.paramByte(SOM_DayNight) & SOM_DayNightMask) >> SOM_DayNightShift)
// Scene0
#define ParamSOM_Scene0                              (knx.paramByte(SOM_Scene0))
// Scene1
#define ParamSOM_Scene1                              (knx.paramByte(SOM_Scene1))
// Scene2
#define ParamSOM_Scene2                              (knx.paramByte(SOM_Scene2))
// Scene3
#define ParamSOM_Scene3                              (knx.paramByte(SOM_Scene3))
// Scene4
#define ParamSOM_Scene4                              (knx.paramByte(SOM_Scene4))
// Scene5
#define ParamSOM_Scene5                              (knx.paramByte(SOM_Scene5))
// Scene6
#define ParamSOM_Scene6                              (knx.paramByte(SOM_Scene6))
// Scene7
#define ParamSOM_Scene7                              (knx.paramByte(SOM_Scene7))
// Scene8
#define ParamSOM_Scene8                              (knx.paramByte(SOM_Scene8))
// Scene9
#define ParamSOM_Scene9                              (knx.paramByte(SOM_Scene9))
// Scene10
#define ParamSOM_Scene10                             (knx.paramByte(SOM_Scene10))
// Scene11
#define ParamSOM_Scene11                             (knx.paramByte(SOM_Scene11))
// Scene12
#define ParamSOM_Scene12                             (knx.paramByte(SOM_Scene12))
// Scene13
#define ParamSOM_Scene13                             (knx.paramByte(SOM_Scene13))
// Scene14
#define ParamSOM_Scene14                             (knx.paramByte(SOM_Scene14))
// Scene15
#define ParamSOM_Scene15                             (knx.paramByte(SOM_Scene15))
// Scene16
#define ParamSOM_Scene16                             (knx.paramByte(SOM_Scene16))
// Scene17
#define ParamSOM_Scene17                             (knx.paramByte(SOM_Scene17))
// Scene18
#define ParamSOM_Scene18                             (knx.paramByte(SOM_Scene18))
// Scene19
#define ParamSOM_Scene19                             (knx.paramByte(SOM_Scene19))
// SceneAction0
#define ParamSOM_SceneAction0                        (knx.paramByte(SOM_SceneAction0))
// SceneAction1
#define ParamSOM_SceneAction1                        (knx.paramByte(SOM_SceneAction1))
// SceneAction2
#define ParamSOM_SceneAction2                        (knx.paramByte(SOM_SceneAction2))
// SceneAction3
#define ParamSOM_SceneAction3                        (knx.paramByte(SOM_SceneAction3))
// SceneAction4
#define ParamSOM_SceneAction4                        (knx.paramByte(SOM_SceneAction4))
// SceneAction5
#define ParamSOM_SceneAction5                        (knx.paramByte(SOM_SceneAction5))
// SceneAction6
#define ParamSOM_SceneAction6                        (knx.paramByte(SOM_SceneAction6))
// SceneAction7
#define ParamSOM_SceneAction7                        (knx.paramByte(SOM_SceneAction7))
// SceneAction8
#define ParamSOM_SceneAction8                        (knx.paramByte(SOM_SceneAction8))
// SceneAction9
#define ParamSOM_SceneAction9                        (knx.paramByte(SOM_SceneAction9))
// SceneAction10
#define ParamSOM_SceneAction10                       (knx.paramByte(SOM_SceneAction10))
// SceneAction11
#define ParamSOM_SceneAction11                       (knx.paramByte(SOM_SceneAction11))
// SceneAction12
#define ParamSOM_SceneAction12                       (knx.paramByte(SOM_SceneAction12))
// SceneAction13
#define ParamSOM_SceneAction13                       (knx.paramByte(SOM_SceneAction13))
// SceneAction14
#define ParamSOM_SceneAction14                       (knx.paramByte(SOM_SceneAction14))
// SceneAction15
#define ParamSOM_SceneAction15                       (knx.paramByte(SOM_SceneAction15))
// SceneAction16
#define ParamSOM_SceneAction16                       (knx.paramByte(SOM_SceneAction16))
// SceneAction17
#define ParamSOM_SceneAction17                       (knx.paramByte(SOM_SceneAction17))
// SceneAction18
#define ParamSOM_SceneAction18                       (knx.paramByte(SOM_SceneAction18))
// SceneAction19
#define ParamSOM_SceneAction19                       (knx.paramByte(SOM_SceneAction19))
// SceneTargetA0
#define ParamSOM_SceneTargetA0                       (knx.paramByte(SOM_SceneTargetA0))
// SceneTargetA1
#define ParamSOM_SceneTargetA1                       (knx.paramByte(SOM_SceneTargetA1))
// SceneTargetA2
#define ParamSOM_SceneTargetA2                       (knx.paramByte(SOM_SceneTargetA2))
// SceneTargetA3
#define ParamSOM_SceneTargetA3                       (knx.paramByte(SOM_SceneTargetA3))
// SceneTargetA4
#define ParamSOM_SceneTargetA4                       (knx.paramByte(SOM_SceneTargetA4))
// SceneTargetA5
#define ParamSOM_SceneTargetA5                       (knx.paramByte(SOM_SceneTargetA5))
// SceneTargetA6
#define ParamSOM_SceneTargetA6                       (knx.paramByte(SOM_SceneTargetA6))
// SceneTargetA7
#define ParamSOM_SceneTargetA7                       (knx.paramByte(SOM_SceneTargetA7))
// SceneTargetA8
#define ParamSOM_SceneTargetA8                       (knx.paramByte(SOM_SceneTargetA8))
// SceneTargetA9
#define ParamSOM_SceneTargetA9                       (knx.paramByte(SOM_SceneTargetA9))
// SceneTargetA10
#define ParamSOM_SceneTargetA10                      (knx.paramByte(SOM_SceneTargetA10))
// SceneTargetA11
#define ParamSOM_SceneTargetA11                      (knx.paramByte(SOM_SceneTargetA11))
// SceneTargetA12
#define ParamSOM_SceneTargetA12                      (knx.paramByte(SOM_SceneTargetA12))
// SceneTargetA13
#define ParamSOM_SceneTargetA13                      (knx.paramByte(SOM_SceneTargetA13))
// SceneTargetA14
#define ParamSOM_SceneTargetA14                      (knx.paramByte(SOM_SceneTargetA14))
// SceneTargetA15
#define ParamSOM_SceneTargetA15                      (knx.paramByte(SOM_SceneTargetA15))
// SceneTargetA16
#define ParamSOM_SceneTargetA16                      (knx.paramByte(SOM_SceneTargetA16))
// SceneTargetA17
#define ParamSOM_SceneTargetA17                      (knx.paramByte(SOM_SceneTargetA17))
// SceneTargetA18
#define ParamSOM_SceneTargetA18                      (knx.paramByte(SOM_SceneTargetA18))
// SceneTargetA19
#define ParamSOM_SceneTargetA19                      (knx.paramByte(SOM_SceneTargetA19))
// SceneTargetB0
#define ParamSOM_SceneTargetB0                       (knx.paramByte(SOM_SceneTargetB0))
// SceneTargetB1
#define ParamSOM_SceneTargetB1                       (knx.paramByte(SOM_SceneTargetB1))
// SceneTargetB2
#define ParamSOM_SceneTargetB2                       (knx.paramByte(SOM_SceneTargetB2))
// SceneTargetB3
#define ParamSOM_SceneTargetB3                       (knx.paramByte(SOM_SceneTargetB3))
// SceneTargetB4
#define ParamSOM_SceneTargetB4                       (knx.paramByte(SOM_SceneTargetB4))
// SceneTargetB5
#define ParamSOM_SceneTargetB5                       (knx.paramByte(SOM_SceneTargetB5))
// SceneTargetB6
#define ParamSOM_SceneTargetB6                       (knx.paramByte(SOM_SceneTargetB6))
// SceneTargetB7
#define ParamSOM_SceneTargetB7                       (knx.paramByte(SOM_SceneTargetB7))
// SceneTargetB8
#define ParamSOM_SceneTargetB8                       (knx.paramByte(SOM_SceneTargetB8))
// SceneTargetB9
#define ParamSOM_SceneTargetB9                       (knx.paramByte(SOM_SceneTargetB9))
// SceneTargetB0
#define ParamSOM_SceneTargetB10                      (knx.paramByte(SOM_SceneTargetB10))
// SceneTargetB1
#define ParamSOM_SceneTargetB11                      (knx.paramByte(SOM_SceneTargetB11))
// SceneTargetB2
#define ParamSOM_SceneTargetB12                      (knx.paramByte(SOM_SceneTargetB12))
// SceneTargetB3
#define ParamSOM_SceneTargetB13                      (knx.paramByte(SOM_SceneTargetB13))
// SceneTargetB4
#define ParamSOM_SceneTargetB14                      (knx.paramByte(SOM_SceneTargetB14))
// SceneTargetB5
#define ParamSOM_SceneTargetB15                      (knx.paramByte(SOM_SceneTargetB15))
// SceneTargetB6
#define ParamSOM_SceneTargetB16                      (knx.paramByte(SOM_SceneTargetB16))
// SceneTargetB7
#define ParamSOM_SceneTargetB17                      (knx.paramByte(SOM_SceneTargetB17))
// SceneTargetB8
#define ParamSOM_SceneTargetB18                      (knx.paramByte(SOM_SceneTargetB18))
// SceneTargetB9
#define ParamSOM_SceneTargetB19                      (knx.paramByte(SOM_SceneTargetB19))

#define SOM_KoStatus 20
#define SOM_KoFile 21
#define SOM_KoScene 28
#define SOM_KoLock 29
#define SOM_KoDayNight 27
#define SOM_KoExternalFile 30
#define SOM_KoExternalVolume 31
#define SOM_KoExternalPriority 32

// Zentral
#define KoSOM_Status                              (knx.getGroupObject(SOM_KoStatus))
// Zentral
#define KoSOM_File                                (knx.getGroupObject(SOM_KoFile))
// Zentral
#define KoSOM_Scene                               (knx.getGroupObject(SOM_KoScene))
// Zentral
#define KoSOM_Lock                                (knx.getGroupObject(SOM_KoLock))
// Zentral
#define KoSOM_DayNight                            (knx.getGroupObject(SOM_KoDayNight))
// Externe Logik
#define KoSOM_ExternalFile                        (knx.getGroupObject(SOM_KoExternalFile))
// Externe Logik
#define KoSOM_ExternalVolume                      (knx.getGroupObject(SOM_KoExternalVolume))
// Externe Logik
#define KoSOM_ExternalPriority                    (knx.getGroupObject(SOM_KoExternalPriority))

#define SOM_ChannelCount 10

// Parameter per channel
#define SOM_ParamBlockOffset 99
#define SOM_ParamBlockSize 11
#define SOM_ParamCalcIndex(index) (index + SOM_ParamBlockOffset + _channelIndex * SOM_ParamBlockSize)

#define SOM_TriggerState                         0      // 1 Bit, Bit 7
#define     SOM_TriggerStateMask 0x80
#define     SOM_TriggerStateShift 7
#define SOM_TriggerLock                          0      // 2 Bits, Bit 5-4
#define     SOM_TriggerLockMask 0x30
#define     SOM_TriggerLockShift 4
#define SOM_TriggerDayNight                      0      // 2 Bits, Bit 3-2
#define     SOM_TriggerDayNightMask 0x0C
#define     SOM_TriggerDayNightShift 2
#define SOM_TriggerPriority                      1      // 3 Bits, Bit 7-5
#define     SOM_TriggerPriorityMask 0xE0
#define     SOM_TriggerPriorityShift 5
#define SOM_TriggerControl                       1      // 2 Bits, Bit 4-3
#define     SOM_TriggerControlMask 0x18
#define     SOM_TriggerControlShift 3
#define SOM_TriggerReTrigger                     1      // 1 Bit, Bit 2
#define     SOM_TriggerReTriggerMask 0x04
#define     SOM_TriggerReTriggerShift 2
#define SOM_TriggerDurationBase                  2      // 2 Bits, Bit 7-6
#define     SOM_TriggerDurationBaseMask 0xC0
#define     SOM_TriggerDurationBaseShift 6
#define SOM_TriggerDurationTime                  2      // 14 Bits, Bit 13-0
#define     SOM_TriggerDurationTimeMask 0x3FFF
#define     SOM_TriggerDurationTimeShift 0
#define SOM_TriggerFileDay                       4      // uint16_t
#define SOM_TriggerFileNight                     6      // uint16_t
#define SOM_TriggerVolumeDay                     8      // uint8_t
#define SOM_TriggerVolumeDayInactive             8      // uint8_t
#define SOM_TriggerVolumeNight                   9      // uint8_t
#define SOM_TriggerVolumeNightInactive           9      // uint8_t
#define SOM_TriggerRepeats                      10      // uint8_t
#define SOM_TriggerRepeatsInactive              10      // uint16_t

// Trigger aktiv
#define ParamSOM_TriggerState                        ((bool)(knx.paramByte(SOM_ParamCalcIndex(SOM_TriggerState)) & SOM_TriggerStateMask))
// Sperrobjekt
#define ParamSOM_TriggerLock                         ((knx.paramByte(SOM_ParamCalcIndex(SOM_TriggerLock)) & SOM_TriggerLockMask) >> SOM_TriggerLockShift)
// Tag/Nacht-Objekt
#define ParamSOM_TriggerDayNight                     ((knx.paramByte(SOM_ParamCalcIndex(SOM_TriggerDayNight)) & SOM_TriggerDayNightMask) >> SOM_TriggerDayNightShift)
// Priorität
#define ParamSOM_TriggerPriority                     ((knx.paramByte(SOM_ParamCalcIndex(SOM_TriggerPriority)) & SOM_TriggerPriorityMask) >> SOM_TriggerPriorityShift)
// Steuerung
#define ParamSOM_TriggerControl                      ((knx.paramByte(SOM_ParamCalcIndex(SOM_TriggerControl)) & SOM_TriggerControlMask) >> SOM_TriggerControlShift)
// Retrigger-Schutz
#define ParamSOM_TriggerReTrigger                    ((bool)(knx.paramByte(SOM_ParamCalcIndex(SOM_TriggerReTrigger)) & SOM_TriggerReTriggerMask))
// Zeitbasis
#define ParamSOM_TriggerDurationBase                 ((knx.paramByte(SOM_ParamCalcIndex(SOM_TriggerDurationBase)) & SOM_TriggerDurationBaseMask) >> SOM_TriggerDurationBaseShift)
// Zeit
#define ParamSOM_TriggerDurationTime                 (knx.paramWord(SOM_ParamCalcIndex(SOM_TriggerDurationTime)) & SOM_TriggerDurationTimeMask)
// Zeit (in Millisekunden)
#define ParamSOM_TriggerDurationTimeMS               (paramDelay(knx.paramWord(SOM_ParamCalcIndex(SOM_TriggerDurationTime))))
// Datei
#define ParamSOM_TriggerFileDay                      (knx.paramWord(SOM_ParamCalcIndex(SOM_TriggerFileDay)))
// Datei
#define ParamSOM_TriggerFileNight                    (knx.paramWord(SOM_ParamCalcIndex(SOM_TriggerFileNight)))
// Lautstärke
#define ParamSOM_TriggerVolumeDay                    (knx.paramByte(SOM_ParamCalcIndex(SOM_TriggerVolumeDay)))
// Lautstärke
#define ParamSOM_TriggerVolumeDayInactive            (knx.paramByte(SOM_ParamCalcIndex(SOM_TriggerVolumeDayInactive)))
// Lautstärke
#define ParamSOM_TriggerVolumeNight                  (knx.paramByte(SOM_ParamCalcIndex(SOM_TriggerVolumeNight)))
// Lautstärke
#define ParamSOM_TriggerVolumeNightInactive          (knx.paramByte(SOM_ParamCalcIndex(SOM_TriggerVolumeNightInactive)))
// 
#define ParamSOM_TriggerRepeats                      (knx.paramByte(SOM_ParamCalcIndex(SOM_TriggerRepeats)))
// 
#define ParamSOM_TriggerRepeatsInactive              (knx.paramWord(SOM_ParamCalcIndex(SOM_TriggerRepeatsInactive)))

// deprecated
#define SOM_KoOffset 50

// Communication objects per channel (multiple occurrence)
#define SOM_KoBlockOffset 50
#define SOM_KoBlockSize 4

#define SOM_KoCalcNumber(index) (index + SOM_KoBlockOffset + _channelIndex * SOM_KoBlockSize)
#define SOM_KoCalcIndex(number) ((number >= SOM_KoCalcNumber(0) && number < SOM_KoCalcNumber(SOM_KoBlockSize)) ? (number - SOM_KoOffset) % SOM_KoBlockSize : -1)

#define SOM_KoTriggerTrigger 0
#define SOM_KoTriggerStatus 1
#define SOM_KoTriggerLock 2
#define SOM_KoTriggerDayNight 3

// 
#define KoSOM_TriggerTrigger                      (knx.getGroupObject(SOM_KoCalcNumber(SOM_KoTriggerTrigger)))
// 
#define KoSOM_TriggerStatus                       (knx.getGroupObject(SOM_KoCalcNumber(SOM_KoTriggerStatus)))
// 
#define KoSOM_TriggerLock                         (knx.getGroupObject(SOM_KoCalcNumber(SOM_KoTriggerLock)))
// 
#define KoSOM_TriggerDayNight                     (knx.getGroupObject(SOM_KoCalcNumber(SOM_KoTriggerDayNight)))

#define TONE_ChannelCount 9

// Parameter per channel
#define TONE_ParamBlockOffset 209
#define TONE_ParamBlockSize 29
#define TONE_ParamCalcIndex(index) (index + TONE_ParamBlockOffset + _channelIndex * TONE_ParamBlockSize)

#define TONE_ToneGeneratorMode                    0      // 2 Bits, Bit 7-6
#define     TONE_ToneGeneratorModeMask 0xC0
#define     TONE_ToneGeneratorModeShift 6
#define TONE_ToneGeneratorRepeats                 1      // uint8_t
#define TONE_ToneGeneratorRepeatsInactive         1      // uint16_t
#define TONE_ToneGeneratorRepeatPause             2      // uint8_t
#define TONE_ToneGeneratorDuration1               4      // uint8_t
#define TONE_ToneGeneratorDuration2               5      // uint8_t
#define TONE_ToneGeneratorDuration3               6      // uint8_t
#define TONE_ToneGeneratorDuration4               7      // uint8_t
#define TONE_ToneGeneratorDuration5               8      // uint8_t
#define TONE_ToneGeneratorDuration6               9      // uint8_t
#define TONE_ToneGeneratorDuration7              10      // uint8_t
#define TONE_ToneGeneratorDuration8              11      // uint8_t
#define TONE_ToneGeneratorDuration9              12      // uint8_t
#define TONE_ToneGeneratorFrequency1             13      // uint16_t
#define TONE_ToneGeneratorFrequency2             15      // uint16_t
#define TONE_ToneGeneratorFrequency3             17      // uint16_t
#define TONE_ToneGeneratorFrequency4             19      // uint16_t
#define TONE_ToneGeneratorFrequency5             21      // uint16_t
#define TONE_ToneGeneratorFrequency6             23      // uint16_t
#define TONE_ToneGeneratorFrequency7             25      // uint16_t
#define TONE_ToneGeneratorFrequency8             27      // uint16_t
#define TONE_ToneGeneratorFrequency9             29      // uint16_t

// Modus
#define ParamTONE_ToneGeneratorMode                   ((knx.paramByte(TONE_ParamCalcIndex(TONE_ToneGeneratorMode)) & TONE_ToneGeneratorModeMask) >> TONE_ToneGeneratorModeShift)
// 
#define ParamTONE_ToneGeneratorRepeats                (knx.paramByte(TONE_ParamCalcIndex(TONE_ToneGeneratorRepeats)))
// 
#define ParamTONE_ToneGeneratorRepeatsInactive        (knx.paramWord(TONE_ParamCalcIndex(TONE_ToneGeneratorRepeatsInactive)))
// Pause zwischen der Wiederholung
#define ParamTONE_ToneGeneratorRepeatPause            (knx.paramByte(TONE_ParamCalcIndex(TONE_ToneGeneratorRepeatPause)))
// Dauer
#define ParamTONE_ToneGeneratorDuration1              (knx.paramByte(TONE_ParamCalcIndex(TONE_ToneGeneratorDuration1)))
// 
#define ParamTONE_ToneGeneratorDuration2              (knx.paramByte(TONE_ParamCalcIndex(TONE_ToneGeneratorDuration2)))
// 
#define ParamTONE_ToneGeneratorDuration3              (knx.paramByte(TONE_ParamCalcIndex(TONE_ToneGeneratorDuration3)))
// 
#define ParamTONE_ToneGeneratorDuration4              (knx.paramByte(TONE_ParamCalcIndex(TONE_ToneGeneratorDuration4)))
// 
#define ParamTONE_ToneGeneratorDuration5              (knx.paramByte(TONE_ParamCalcIndex(TONE_ToneGeneratorDuration5)))
// 
#define ParamTONE_ToneGeneratorDuration6              (knx.paramByte(TONE_ParamCalcIndex(TONE_ToneGeneratorDuration6)))
// 
#define ParamTONE_ToneGeneratorDuration7              (knx.paramByte(TONE_ParamCalcIndex(TONE_ToneGeneratorDuration7)))
// 
#define ParamTONE_ToneGeneratorDuration8              (knx.paramByte(TONE_ParamCalcIndex(TONE_ToneGeneratorDuration8)))
// 
#define ParamTONE_ToneGeneratorDuration9              (knx.paramByte(TONE_ParamCalcIndex(TONE_ToneGeneratorDuration9)))
// Frequenz
#define ParamTONE_ToneGeneratorFrequency1             (knx.paramWord(TONE_ParamCalcIndex(TONE_ToneGeneratorFrequency1)))
// 
#define ParamTONE_ToneGeneratorFrequency2             (knx.paramWord(TONE_ParamCalcIndex(TONE_ToneGeneratorFrequency2)))
// 
#define ParamTONE_ToneGeneratorFrequency3             (knx.paramWord(TONE_ParamCalcIndex(TONE_ToneGeneratorFrequency3)))
// 
#define ParamTONE_ToneGeneratorFrequency4             (knx.paramWord(TONE_ParamCalcIndex(TONE_ToneGeneratorFrequency4)))
// 
#define ParamTONE_ToneGeneratorFrequency5             (knx.paramWord(TONE_ParamCalcIndex(TONE_ToneGeneratorFrequency5)))
// 
#define ParamTONE_ToneGeneratorFrequency6             (knx.paramWord(TONE_ParamCalcIndex(TONE_ToneGeneratorFrequency6)))
// 
#define ParamTONE_ToneGeneratorFrequency7             (knx.paramWord(TONE_ParamCalcIndex(TONE_ToneGeneratorFrequency7)))
// 
#define ParamTONE_ToneGeneratorFrequency8             (knx.paramWord(TONE_ParamCalcIndex(TONE_ToneGeneratorFrequency8)))
// 
#define ParamTONE_ToneGeneratorFrequency9             (knx.paramWord(TONE_ParamCalcIndex(TONE_ToneGeneratorFrequency9)))

#define BI_ChannelCount 4

// Parameter per channel
#define BI_ParamBlockOffset 470
#define BI_ParamBlockSize 4
#define BI_ParamCalcIndex(index) (index + BI_ParamBlockOffset + _channelIndex * BI_ParamBlockSize)

#define BI_ChannelActive                        0      // 1 Bit, Bit 7
#define     BI_ChannelActiveMask 0x80
#define     BI_ChannelActiveShift 7
#define BI_ChannelOpen                          0      // 2 Bits, Bit 5-4
#define     BI_ChannelOpenMask 0x30
#define     BI_ChannelOpenShift 4
#define BI_ChannelClose                         0      // 2 Bits, Bit 3-2
#define     BI_ChannelCloseMask 0x0C
#define     BI_ChannelCloseShift 2
#define BI_ChannelPeriodic                      0      // 1 Bit, Bit 2
#define     BI_ChannelPeriodicMask 0x04
#define     BI_ChannelPeriodicShift 2
#define BI_ChannelDebouncing                    1      // 8 Bits, Bit 7-0
#define BI_ChannelPeriodicBase                  2      // 2 Bits, Bit 7-6
#define     BI_ChannelPeriodicBaseMask 0xC0
#define     BI_ChannelPeriodicBaseShift 6
#define BI_ChannelPeriodicTime                  2      // 14 Bits, Bit 13-0
#define     BI_ChannelPeriodicTimeMask 0x3FFF
#define     BI_ChannelPeriodicTimeShift 0

// Aktiv
#define ParamBI_ChannelActive                       ((bool)(knx.paramByte(BI_ParamCalcIndex(BI_ChannelActive)) & BI_ChannelActiveMask))
// Geöffnet
#define ParamBI_ChannelOpen                         ((knx.paramByte(BI_ParamCalcIndex(BI_ChannelOpen)) & BI_ChannelOpenMask) >> BI_ChannelOpenShift)
// Geschlossen
#define ParamBI_ChannelClose                        ((knx.paramByte(BI_ParamCalcIndex(BI_ChannelClose)) & BI_ChannelCloseMask) >> BI_ChannelCloseShift)
// Zyklisch senden
#define ParamBI_ChannelPeriodic                     ((bool)(knx.paramByte(BI_ParamCalcIndex(BI_ChannelPeriodic)) & BI_ChannelPeriodicMask))
// Entprellung
#define ParamBI_ChannelDebouncing                   (knx.paramByte(BI_ParamCalcIndex(BI_ChannelDebouncing)))
// Zeitbasis
#define ParamBI_ChannelPeriodicBase                 ((knx.paramByte(BI_ParamCalcIndex(BI_ChannelPeriodicBase)) & BI_ChannelPeriodicBaseMask) >> BI_ChannelPeriodicBaseShift)
// Zeit
#define ParamBI_ChannelPeriodicTime                 (knx.paramWord(BI_ParamCalcIndex(BI_ChannelPeriodicTime)) & BI_ChannelPeriodicTimeMask)
// Zeit (in Millisekunden)
#define ParamBI_ChannelPeriodicTimeMS               (paramDelay(knx.paramWord(BI_ParamCalcIndex(BI_ChannelPeriodicTime))))

// deprecated
#define BI_KoOffset 41

// Communication objects per channel (multiple occurrence)
#define BI_KoBlockOffset 41
#define BI_KoBlockSize 1

#define BI_KoCalcNumber(index) (index + BI_KoBlockOffset + _channelIndex * BI_KoBlockSize)
#define BI_KoCalcIndex(number) ((number >= BI_KoCalcNumber(0) && number < BI_KoCalcNumber(BI_KoBlockSize)) ? (number - BI_KoOffset) % BI_KoBlockSize : -1)

#define BI_KoChannelOutput 0

// 
#define KoBI_ChannelOutput                       (knx.getGroupObject(BI_KoCalcNumber(BI_KoChannelOutput)))

#define BTN_ReactionTimeMultiClick              486      // 8 Bits, Bit 7-0
#define BTN_ReactionTimeLong                    487      // 8 Bits, Bit 7-0
#define BTN_ReactionTimeExtraLong               488      // 8 Bits, Bit 7-0

//   Mehrfach-Klick
#define ParamBTN_ReactionTimeMultiClick              (knx.paramByte(BTN_ReactionTimeMultiClick))
//   Langer Tasterdruck
#define ParamBTN_ReactionTimeLong                    (knx.paramByte(BTN_ReactionTimeLong))
//   Extra langer Tastedruck
#define ParamBTN_ReactionTimeExtraLong               (knx.paramByte(BTN_ReactionTimeExtraLong))

#define BTN_ChannelCount 20

// Parameter per channel
#define BTN_ParamBlockOffset 490
#define BTN_ParamBlockSize 51
#define BTN_ParamCalcIndex(index) (index + BTN_ParamBlockOffset + _channelIndex * BTN_ParamBlockSize)

#define BTN_ChannelMode                          0      // 4 Bits, Bit 7-4
#define     BTN_ChannelModeMask 0xF0
#define     BTN_ChannelModeShift 4
#define BTN_ChannelLock                          0      // 2 Bits, Bit 3-2
#define     BTN_ChannelLockMask 0x0C
#define     BTN_ChannelLockShift 2
#define BTN_ChannelMultiClickCount               0      // 1 Bit, Bit 3
#define     BTN_ChannelMultiClickCountMask 0x08
#define     BTN_ChannelMultiClickCountShift 3
#define BTN_ChannelInputA                        1      // 16 Bits, Bit 15-0
#define BTN_ChannelInputB                        3      // 16 Bits, Bit 15-0
#define BTN_ChannelReactionTimeMultiClick        5      // 8 Bits, Bit 7-0
#define BTN_ChannelReactionTimeLong              6      // 8 Bits, Bit 7-0
#define BTN_ChannelReactionTimeExtraLong         7      // 8 Bits, Bit 7-0
#define BTN_ChannelOutputShort_DPT               8      // 8 Bits, Bit 7-0
#define BTN_ChannelOutputLong_DPT                9      // 8 Bits, Bit 7-0
#define BTN_ChannelOutputExtraLong_DPT          10      // 8 Bits, Bit 7-0
#define BTN_ChannelOutputMulti_DPT              11      // 8 Bits, Bit 7-0
#define BTN_ChannelOutputMulti_Click1_Active    12      // 1 Bit, Bit 7
#define     BTN_ChannelOutputMulti_Click1_ActiveMask 0x80
#define     BTN_ChannelOutputMulti_Click1_ActiveShift 7
#define BTN_ChannelOutputMulti_Click2_Active    12      // 1 Bit, Bit 6
#define     BTN_ChannelOutputMulti_Click2_ActiveMask 0x40
#define     BTN_ChannelOutputMulti_Click2_ActiveShift 6
#define BTN_ChannelOutputMulti_Click3_Active    12      // 1 Bit, Bit 5
#define     BTN_ChannelOutputMulti_Click3_ActiveMask 0x20
#define     BTN_ChannelOutputMulti_Click3_ActiveShift 5
#define BTN_ChannelOutputShort_Taster1_Active_Press 13      // 1 Bit, Bit 7
#define     BTN_ChannelOutputShort_Taster1_Active_PressMask 0x80
#define     BTN_ChannelOutputShort_Taster1_Active_PressShift 7
#define BTN_ChannelOutputShort_Taster1_Active_Release 13      // 1 Bit, Bit 6
#define     BTN_ChannelOutputShort_Taster1_Active_ReleaseMask 0x40
#define     BTN_ChannelOutputShort_Taster1_Active_ReleaseShift 6
#define BTN_ChannelOutputShort_Taster2_Active_Press 13      // 1 Bit, Bit 5
#define     BTN_ChannelOutputShort_Taster2_Active_PressMask 0x20
#define     BTN_ChannelOutputShort_Taster2_Active_PressShift 5
#define BTN_ChannelOutputShort_Taster2_Active_Release 13      // 1 Bit, Bit 4
#define     BTN_ChannelOutputShort_Taster2_Active_ReleaseMask 0x10
#define     BTN_ChannelOutputShort_Taster2_Active_ReleaseShift 4
#define BTN_ChannelOutputLong_Taster1_Active_Press 14      // 1 Bit, Bit 7
#define     BTN_ChannelOutputLong_Taster1_Active_PressMask 0x80
#define     BTN_ChannelOutputLong_Taster1_Active_PressShift 7
#define BTN_ChannelOutputLong_Taster1_Active_Release 14      // 1 Bit, Bit 6
#define     BTN_ChannelOutputLong_Taster1_Active_ReleaseMask 0x40
#define     BTN_ChannelOutputLong_Taster1_Active_ReleaseShift 6
#define BTN_ChannelOutputLong_Taster2_Active_Press 14      // 1 Bit, Bit 5
#define     BTN_ChannelOutputLong_Taster2_Active_PressMask 0x20
#define     BTN_ChannelOutputLong_Taster2_Active_PressShift 5
#define BTN_ChannelOutputLong_Taster2_Active_Release 14      // 1 Bit, Bit 4
#define     BTN_ChannelOutputLong_Taster2_Active_ReleaseMask 0x10
#define     BTN_ChannelOutputLong_Taster2_Active_ReleaseShift 4
#define BTN_ChannelOutputExtraLong_Taster1_Active_Press 15      // 1 Bit, Bit 7
#define     BTN_ChannelOutputExtraLong_Taster1_Active_PressMask 0x80
#define     BTN_ChannelOutputExtraLong_Taster1_Active_PressShift 7
#define BTN_ChannelOutputExtraLong_Taster1_Active_Release 15      // 1 Bit, Bit 6
#define     BTN_ChannelOutputExtraLong_Taster1_Active_ReleaseMask 0x40
#define     BTN_ChannelOutputExtraLong_Taster1_Active_ReleaseShift 6
#define BTN_ChannelOutputExtraLong_Taster2_Active_Press 15      // 1 Bit, Bit 5
#define     BTN_ChannelOutputExtraLong_Taster2_Active_PressMask 0x20
#define     BTN_ChannelOutputExtraLong_Taster2_Active_PressShift 5
#define BTN_ChannelOutputExtraLong_Taster2_Active_Release 15      // 1 Bit, Bit 4
#define     BTN_ChannelOutputExtraLong_Taster2_Active_ReleaseMask 0x10
#define     BTN_ChannelOutputExtraLong_Taster2_Active_ReleaseShift 4
#define BTN_ChannelOutputShort_Taster1_Dpt1_Press 16      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster1_Dpt1_Release 18      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster2_Dpt1_Press 20      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster2_Dpt1_Release 24      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster1_Dpt1_Press 26      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster1_Dpt1_Release 28      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster2_Dpt1_Press 30      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster2_Dpt1_Release 32      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster1_Dpt1_Press 34      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster1_Dpt1_Release 36      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster2_Dpt1_Press 38      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster2_Dpt1_Release 40      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputMulti_Click1_Dpt1      42      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputMulti_Click2_Dpt1      44      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputMulti_Click3_Dpt1      46      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster1_Dpt2_Press 16      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster1_Dpt2_Release 18      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster2_Dpt2_Press 20      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster2_Dpt2_Release 24      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster1_Dpt2_Press 26      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster1_Dpt2_Release 28      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster2_Dpt2_Press 30      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster2_Dpt2_Release 32      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster1_Dpt2_Press 34      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster1_Dpt2_Release 36      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster2_Dpt2_Press 38      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster2_Dpt2_Release 40      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputMulti_Click1_Dpt2      42      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputMulti_Click2_Dpt2      44      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputMulti_Click3_Dpt2      46      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster1_Dpt5_Press 16      // uint16_t
#define BTN_ChannelOutputShort_Taster1_Dpt5_Release 18      // uint16_t
#define BTN_ChannelOutputShort_Taster2_Dpt5_Press 20      // uint16_t
#define BTN_ChannelOutputShort_Taster2_Dpt5_Release 24      // uint16_t
#define BTN_ChannelOutputLong_Taster1_Dpt5_Press 26      // uint16_t
#define BTN_ChannelOutputLong_Taster1_Dpt5_Release 28      // uint16_t
#define BTN_ChannelOutputLong_Taster2_Dpt5_Press 30      // uint16_t
#define BTN_ChannelOutputLong_Taster2_Dpt5_Release 32      // uint16_t
#define BTN_ChannelOutputExtraLong_Taster1_Dpt5_Press 34      // uint16_t
#define BTN_ChannelOutputExtraLong_Taster1_Dpt5_Release 36      // uint16_t
#define BTN_ChannelOutputExtraLong_Taster2_Dpt5_Press 38      // uint16_t
#define BTN_ChannelOutputExtraLong_Taster2_Dpt5_Release 40      // uint16_t
#define BTN_ChannelOutputMulti_Click1_Dpt5      42      // uint16_t
#define BTN_ChannelOutputMulti_Click2_Dpt5      44      // uint16_t
#define BTN_ChannelOutputMulti_Click3_Dpt5      46      // uint16_t
#define BTN_ChannelOutputShort_Taster1_Dpt5001_Press 16      // uint16_t
#define BTN_ChannelOutputShort_Taster1_Dpt5001_Release 18      // uint16_t
#define BTN_ChannelOutputShort_Taster2_Dpt5001_Press 20      // uint16_t
#define BTN_ChannelOutputShort_Taster2_Dpt5001_Release 24      // uint16_t
#define BTN_ChannelOutputLong_Taster1_Dpt5001_Press 26      // uint16_t
#define BTN_ChannelOutputLong_Taster1_Dpt5001_Release 28      // uint16_t
#define BTN_ChannelOutputLong_Taster2_Dpt5001_Press 30      // uint16_t
#define BTN_ChannelOutputLong_Taster2_Dpt5001_Release 32      // uint16_t
#define BTN_ChannelOutputExtraLong_Taster1_Dpt5001_Press 34      // uint16_t
#define BTN_ChannelOutputExtraLong_Taster1_Dpt5001_Release 36      // uint16_t
#define BTN_ChannelOutputExtraLong_Taster2_Dpt5001_Press 38      // uint16_t
#define BTN_ChannelOutputExtraLong_Taster2_Dpt5001_Release 40      // uint16_t
#define BTN_ChannelOutputMulti_Click1_Dpt5001   42      // uint16_t
#define BTN_ChannelOutputMulti_Click2_Dpt5001   44      // uint16_t
#define BTN_ChannelOutputMulti_Click3_Dpt5001   46      // uint16_t
#define BTN_ChannelOutputShort_Taster1_Dpt7_Press 16      // uint16_t
#define BTN_ChannelOutputShort_Taster1_Dpt7_Release 18      // uint16_t
#define BTN_ChannelOutputShort_Taster2_Dpt7_Press 20      // uint16_t
#define BTN_ChannelOutputShort_Taster2_Dpt7_Release 24      // uint16_t
#define BTN_ChannelOutputLong_Taster1_Dpt7_Press 26      // uint16_t
#define BTN_ChannelOutputLong_Taster1_Dpt7_Release 28      // uint16_t
#define BTN_ChannelOutputLong_Taster2_Dpt7_Press 30      // uint16_t
#define BTN_ChannelOutputLong_Taster2_Dpt7_Release 32      // uint16_t
#define BTN_ChannelOutputExtraLong_Taster1_Dpt7_Press 34      // uint16_t
#define BTN_ChannelOutputExtraLong_Taster1_Dpt7_Release 36      // uint16_t
#define BTN_ChannelOutputExtraLong_Taster2_Dpt7_Press 38      // uint16_t
#define BTN_ChannelOutputExtraLong_Taster2_Dpt7_Release 40      // uint16_t
#define BTN_ChannelOutputMulti_Click1_Dpt7      42      // uint16_t
#define BTN_ChannelOutputMulti_Click2_Dpt7      44      // uint16_t
#define BTN_ChannelOutputMulti_Click3_Dpt7      46      // uint16_t
#define BTN_ChannelOutputShort_Taster1_Dpt18_Press 16      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster1_Dpt18_Release 18      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster2_Dpt18_Press 20      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster2_Dpt18_Release 24      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster1_Dpt18_Press 26      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster1_Dpt18_Release 28      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster2_Dpt18_Press 30      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster2_Dpt18_Release 32      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster1_Dpt18_Press 34      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster1_Dpt18_Release 36      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster2_Dpt18_Press 38      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster2_Dpt18_Release 40      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputMulti_Click1_Dpt18     42      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputMulti_Click2_Dpt18     44      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputMulti_Click3_Dpt18     46      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster1_Dpt3007_Press 16      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster1_Dpt3007_Release 18      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster2_Dpt3007_Press 20      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster2_Dpt3007_Release 24      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster1_Dpt3007_Press 26      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster1_Dpt3007_Release 28      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster2_Dpt3007_Press 30      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster2_Dpt3007_Release 32      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster1_Dpt3007_Press 34      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster1_Dpt3007_Release 36      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster2_Dpt3007_Press 38      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster2_Dpt3007_Release 40      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster1_Dpt3008_Press 16      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster1_Dpt3008_Release 18      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster2_Dpt3008_Press 20      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputShort_Taster2_Dpt3008_Release 24      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster1_Dpt3008_Press 26      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster1_Dpt3008_Release 28      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster2_Dpt3008_Press 30      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputLong_Taster2_Dpt3008_Release 32      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster1_Dpt3008_Press 34      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster1_Dpt3008_Release 36      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster2_Dpt3008_Press 38      // 16 Bits, Bit 15-0
#define BTN_ChannelOutputExtraLong_Taster2_Dpt3008_Release 40      // 16 Bits, Bit 15-0
#define BTN_ChannelOutput2Short_Taster1         46      // 2 Bits, Bit 7-6
#define     BTN_ChannelOutput2Short_Taster1Mask 0xC0
#define     BTN_ChannelOutput2Short_Taster1Shift 6
#define BTN_ChannelOutput2Short_Taster2         46      // 2 Bits, Bit 5-4
#define     BTN_ChannelOutput2Short_Taster2Mask 0x30
#define     BTN_ChannelOutput2Short_Taster2Shift 4
#define BTN_ChannelOutput2Long_Taster1          46      // 2 Bits, Bit 3-2
#define     BTN_ChannelOutput2Long_Taster1Mask 0x0C
#define     BTN_ChannelOutput2Long_Taster1Shift 2
#define BTN_ChannelOutput2Long_Taster2          46      // 2 Bits, Bit 1-0
#define     BTN_ChannelOutput2Long_Taster2Mask 0x03
#define     BTN_ChannelOutput2Long_Taster2Shift 0
#define BTN_ChannelOutput2ExtraLong_Taster1     47      // 2 Bits, Bit 7-6
#define     BTN_ChannelOutput2ExtraLong_Taster1Mask 0xC0
#define     BTN_ChannelOutput2ExtraLong_Taster1Shift 6
#define BTN_ChannelOutput2ExtraLong_Taster2     47      // 2 Bits, Bit 5-4
#define     BTN_ChannelOutput2ExtraLong_Taster2Mask 0x30
#define     BTN_ChannelOutput2ExtraLong_Taster2Shift 4
#define BTN_ChannelStatusThreshold              48      // uint8_t
#define BTN_ChannelStatusFallbackBase           49      // 2 Bits, Bit 7-6
#define     BTN_ChannelStatusFallbackBaseMask 0xC0
#define     BTN_ChannelStatusFallbackBaseShift 6
#define BTN_ChannelStatusFallbackTime           49      // 14 Bits, Bit 13-0
#define     BTN_ChannelStatusFallbackTimeMask 0x3FFF
#define     BTN_ChannelStatusFallbackTimeShift 0

// Modus
#define ParamBTN_ChannelMode                         ((knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelMode)) & BTN_ChannelModeMask) >> BTN_ChannelModeShift)
// Sperre
#define ParamBTN_ChannelLock                         ((knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelLock)) & BTN_ChannelLockMask) >> BTN_ChannelLockShift)
// Ausgabe der Klickanzahl
#define ParamBTN_ChannelMultiClickCount              ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelMultiClickCount)) & BTN_ChannelMultiClickCountMask))
// 1. Taster
#define ParamBTN_ChannelInputA                       (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelInputA)))
// 2. Taster
#define ParamBTN_ChannelInputB                       (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelInputB)))
//   Mehrfach-Klick
#define ParamBTN_ChannelReactionTimeMultiClick       (knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelReactionTimeMultiClick)))
//   Langer Tasterdruck
#define ParamBTN_ChannelReactionTimeLong             (knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelReactionTimeLong)))
//   Extra langer Tasterdruck
#define ParamBTN_ChannelReactionTimeExtraLong        (knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelReactionTimeExtraLong)))
// Datentyp
#define ParamBTN_ChannelOutputShort_DPT              (knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputShort_DPT)))
// Datentyp
#define ParamBTN_ChannelOutputLong_DPT               (knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputLong_DPT)))
// Datentyp
#define ParamBTN_ChannelOutputExtraLong_DPT          (knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_DPT)))
// Datentyp
#define ParamBTN_ChannelOutputMulti_DPT              (knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_DPT)))
// 1. Klick
#define ParamBTN_ChannelOutputMulti_Click1_Active    ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click1_Active)) & BTN_ChannelOutputMulti_Click1_ActiveMask))
// 2. Klick
#define ParamBTN_ChannelOutputMulti_Click2_Active    ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click2_Active)) & BTN_ChannelOutputMulti_Click2_ActiveMask))
// 3. Klick
#define ParamBTN_ChannelOutputMulti_Click3_Active    ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click3_Active)) & BTN_ChannelOutputMulti_Click3_ActiveMask))
//   Wert beim Drücken
#define ParamBTN_ChannelOutputShort_Taster1_Active_Press ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Active_Press)) & BTN_ChannelOutputShort_Taster1_Active_PressMask))
//   Wert beim Loslassen
#define ParamBTN_ChannelOutputShort_Taster1_Active_Release ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Active_Release)) & BTN_ChannelOutputShort_Taster1_Active_ReleaseMask))
//   Wert beim Drücken
#define ParamBTN_ChannelOutputShort_Taster2_Active_Press ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Active_Press)) & BTN_ChannelOutputShort_Taster2_Active_PressMask))
//   Wert beim Loslassen
#define ParamBTN_ChannelOutputShort_Taster2_Active_Release ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Active_Release)) & BTN_ChannelOutputShort_Taster2_Active_ReleaseMask))
//   Wert beim Drücken
#define ParamBTN_ChannelOutputLong_Taster1_Active_Press ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Active_Press)) & BTN_ChannelOutputLong_Taster1_Active_PressMask))
//   Wert beim Loslassen
#define ParamBTN_ChannelOutputLong_Taster1_Active_Release ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Active_Release)) & BTN_ChannelOutputLong_Taster1_Active_ReleaseMask))
//   Wert beim Drücken
#define ParamBTN_ChannelOutputLong_Taster2_Active_Press ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Active_Press)) & BTN_ChannelOutputLong_Taster2_Active_PressMask))
//   Wert beim Loslassen
#define ParamBTN_ChannelOutputLong_Taster2_Active_Release ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Active_Release)) & BTN_ChannelOutputLong_Taster2_Active_ReleaseMask))
//   Wert beim Drücken
#define ParamBTN_ChannelOutputExtraLong_Taster1_Active_Press ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Active_Press)) & BTN_ChannelOutputExtraLong_Taster1_Active_PressMask))
//   Wert beim Loslassen
#define ParamBTN_ChannelOutputExtraLong_Taster1_Active_Release ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Active_Release)) & BTN_ChannelOutputExtraLong_Taster1_Active_ReleaseMask))
//   Wert beim Drücken
#define ParamBTN_ChannelOutputExtraLong_Taster2_Active_Press ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Active_Press)) & BTN_ChannelOutputExtraLong_Taster2_Active_PressMask))
//   Wert beim Loslassen
#define ParamBTN_ChannelOutputExtraLong_Taster2_Active_Release ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Active_Release)) & BTN_ChannelOutputExtraLong_Taster2_Active_ReleaseMask))
// 
#define ParamBTN_ChannelOutputShort_Taster1_Dpt1_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Dpt1_Press)))
// 
#define ParamBTN_ChannelOutputShort_Taster1_Dpt1_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Dpt1_Release)))
// 
#define ParamBTN_ChannelOutputShort_Taster2_Dpt1_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Dpt1_Press)))
// 
#define ParamBTN_ChannelOutputShort_Taster2_Dpt1_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Dpt1_Release)))
// 
#define ParamBTN_ChannelOutputLong_Taster1_Dpt1_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Dpt1_Press)))
// 
#define ParamBTN_ChannelOutputLong_Taster1_Dpt1_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Dpt1_Release)))
// 
#define ParamBTN_ChannelOutputLong_Taster2_Dpt1_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Dpt1_Press)))
// 
#define ParamBTN_ChannelOutputLong_Taster2_Dpt1_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Dpt1_Release)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster1_Dpt1_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Dpt1_Press)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster1_Dpt1_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Dpt1_Release)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster2_Dpt1_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Dpt1_Press)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster2_Dpt1_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Dpt1_Release)))
// 
#define ParamBTN_ChannelOutputMulti_Click1_Dpt1      (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click1_Dpt1)))
// 
#define ParamBTN_ChannelOutputMulti_Click2_Dpt1      (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click2_Dpt1)))
// 
#define ParamBTN_ChannelOutputMulti_Click3_Dpt1      (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click3_Dpt1)))
// 
#define ParamBTN_ChannelOutputShort_Taster1_Dpt2_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Dpt2_Press)))
// 
#define ParamBTN_ChannelOutputShort_Taster1_Dpt2_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Dpt2_Release)))
// 
#define ParamBTN_ChannelOutputShort_Taster2_Dpt2_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Dpt2_Press)))
// 
#define ParamBTN_ChannelOutputShort_Taster2_Dpt2_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Dpt2_Release)))
// 
#define ParamBTN_ChannelOutputLong_Taster1_Dpt2_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Dpt2_Press)))
// 
#define ParamBTN_ChannelOutputLong_Taster1_Dpt2_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Dpt2_Release)))
// 
#define ParamBTN_ChannelOutputLong_Taster2_Dpt2_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Dpt2_Press)))
// 
#define ParamBTN_ChannelOutputLong_Taster2_Dpt2_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Dpt2_Release)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster1_Dpt2_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Dpt2_Press)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster1_Dpt2_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Dpt2_Release)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster2_Dpt2_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Dpt2_Press)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster2_Dpt2_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Dpt2_Release)))
// 
#define ParamBTN_ChannelOutputMulti_Click1_Dpt2      (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click1_Dpt2)))
// 
#define ParamBTN_ChannelOutputMulti_Click2_Dpt2      (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click2_Dpt2)))
// 
#define ParamBTN_ChannelOutputMulti_Click3_Dpt2      (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click3_Dpt2)))
// 
#define ParamBTN_ChannelOutputShort_Taster1_Dpt5_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Dpt5_Press)))
// 
#define ParamBTN_ChannelOutputShort_Taster1_Dpt5_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Dpt5_Release)))
// 
#define ParamBTN_ChannelOutputShort_Taster2_Dpt5_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Dpt5_Press)))
// 
#define ParamBTN_ChannelOutputShort_Taster2_Dpt5_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Dpt5_Release)))
// 
#define ParamBTN_ChannelOutputLong_Taster1_Dpt5_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Dpt5_Press)))
// 
#define ParamBTN_ChannelOutputLong_Taster1_Dpt5_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Dpt5_Release)))
// 
#define ParamBTN_ChannelOutputLong_Taster2_Dpt5_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Dpt5_Press)))
// 
#define ParamBTN_ChannelOutputLong_Taster2_Dpt5_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Dpt5_Release)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster1_Dpt5_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Dpt5_Press)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster1_Dpt5_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Dpt5_Release)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster2_Dpt5_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Dpt5_Press)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster2_Dpt5_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Dpt5_Release)))
// 
#define ParamBTN_ChannelOutputMulti_Click1_Dpt5      (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click1_Dpt5)))
// 
#define ParamBTN_ChannelOutputMulti_Click2_Dpt5      (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click2_Dpt5)))
// 
#define ParamBTN_ChannelOutputMulti_Click3_Dpt5      (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click3_Dpt5)))
// 
#define ParamBTN_ChannelOutputShort_Taster1_Dpt5001_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Dpt5001_Press)))
// 
#define ParamBTN_ChannelOutputShort_Taster1_Dpt5001_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Dpt5001_Release)))
// 
#define ParamBTN_ChannelOutputShort_Taster2_Dpt5001_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Dpt5001_Press)))
// 
#define ParamBTN_ChannelOutputShort_Taster2_Dpt5001_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Dpt5001_Release)))
// 
#define ParamBTN_ChannelOutputLong_Taster1_Dpt5001_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Dpt5001_Press)))
// 
#define ParamBTN_ChannelOutputLong_Taster1_Dpt5001_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Dpt5001_Release)))
// 
#define ParamBTN_ChannelOutputLong_Taster2_Dpt5001_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Dpt5001_Press)))
// 
#define ParamBTN_ChannelOutputLong_Taster2_Dpt5001_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Dpt5001_Release)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster1_Dpt5001_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Dpt5001_Press)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster1_Dpt5001_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Dpt5001_Release)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster2_Dpt5001_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Dpt5001_Press)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster2_Dpt5001_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Dpt5001_Release)))
// 
#define ParamBTN_ChannelOutputMulti_Click1_Dpt5001   (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click1_Dpt5001)))
// 
#define ParamBTN_ChannelOutputMulti_Click2_Dpt5001   (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click2_Dpt5001)))
// 
#define ParamBTN_ChannelOutputMulti_Click3_Dpt5001   (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click3_Dpt5001)))
// 
#define ParamBTN_ChannelOutputShort_Taster1_Dpt7_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Dpt7_Press)))
// 
#define ParamBTN_ChannelOutputShort_Taster1_Dpt7_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Dpt7_Release)))
// 
#define ParamBTN_ChannelOutputShort_Taster2_Dpt7_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Dpt7_Press)))
// 
#define ParamBTN_ChannelOutputShort_Taster2_Dpt7_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Dpt7_Release)))
// 
#define ParamBTN_ChannelOutputLong_Taster1_Dpt7_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Dpt7_Press)))
// 
#define ParamBTN_ChannelOutputLong_Taster1_Dpt7_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Dpt7_Release)))
// 
#define ParamBTN_ChannelOutputLong_Taster2_Dpt7_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Dpt7_Press)))
// 
#define ParamBTN_ChannelOutputLong_Taster2_Dpt7_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Dpt7_Release)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster1_Dpt7_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Dpt7_Press)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster1_Dpt7_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Dpt7_Release)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster2_Dpt7_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Dpt7_Press)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster2_Dpt7_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Dpt7_Release)))
// 
#define ParamBTN_ChannelOutputMulti_Click1_Dpt7      (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click1_Dpt7)))
// 
#define ParamBTN_ChannelOutputMulti_Click2_Dpt7      (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click2_Dpt7)))
// 
#define ParamBTN_ChannelOutputMulti_Click3_Dpt7      (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click3_Dpt7)))
// 
#define ParamBTN_ChannelOutputShort_Taster1_Dpt18_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Dpt18_Press)))
// 
#define ParamBTN_ChannelOutputShort_Taster1_Dpt18_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Dpt18_Release)))
// 
#define ParamBTN_ChannelOutputShort_Taster2_Dpt18_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Dpt18_Press)))
// 
#define ParamBTN_ChannelOutputShort_Taster2_Dpt18_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Dpt18_Release)))
// 
#define ParamBTN_ChannelOutputLong_Taster1_Dpt18_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Dpt18_Press)))
// 
#define ParamBTN_ChannelOutputLong_Taster1_Dpt18_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Dpt18_Release)))
// 
#define ParamBTN_ChannelOutputLong_Taster2_Dpt18_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Dpt18_Press)))
// 
#define ParamBTN_ChannelOutputLong_Taster2_Dpt18_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Dpt18_Release)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster1_Dpt18_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Dpt18_Press)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster1_Dpt18_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Dpt18_Release)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster2_Dpt18_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Dpt18_Press)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster2_Dpt18_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Dpt18_Release)))
// 
#define ParamBTN_ChannelOutputMulti_Click1_Dpt18     (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click1_Dpt18)))
// 
#define ParamBTN_ChannelOutputMulti_Click2_Dpt18     (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click2_Dpt18)))
// 
#define ParamBTN_ChannelOutputMulti_Click3_Dpt18     (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputMulti_Click3_Dpt18)))
// 
#define ParamBTN_ChannelOutputShort_Taster1_Dpt3007_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Dpt3007_Press)))
// 
#define ParamBTN_ChannelOutputShort_Taster1_Dpt3007_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Dpt3007_Release)))
// 
#define ParamBTN_ChannelOutputShort_Taster2_Dpt3007_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Dpt3007_Press)))
// 
#define ParamBTN_ChannelOutputShort_Taster2_Dpt3007_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Dpt3007_Release)))
// 
#define ParamBTN_ChannelOutputLong_Taster1_Dpt3007_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Dpt3007_Press)))
// 
#define ParamBTN_ChannelOutputLong_Taster1_Dpt3007_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Dpt3007_Release)))
// 
#define ParamBTN_ChannelOutputLong_Taster2_Dpt3007_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Dpt3007_Press)))
// 
#define ParamBTN_ChannelOutputLong_Taster2_Dpt3007_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Dpt3007_Release)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster1_Dpt3007_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Dpt3007_Press)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster1_Dpt3007_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Dpt3007_Release)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster2_Dpt3007_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Dpt3007_Press)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster2_Dpt3007_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Dpt3007_Release)))
// 
#define ParamBTN_ChannelOutputShort_Taster1_Dpt3008_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Dpt3008_Press)))
// 
#define ParamBTN_ChannelOutputShort_Taster1_Dpt3008_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster1_Dpt3008_Release)))
// 
#define ParamBTN_ChannelOutputShort_Taster2_Dpt3008_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Dpt3008_Press)))
// 
#define ParamBTN_ChannelOutputShort_Taster2_Dpt3008_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputShort_Taster2_Dpt3008_Release)))
// 
#define ParamBTN_ChannelOutputLong_Taster1_Dpt3008_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Dpt3008_Press)))
// 
#define ParamBTN_ChannelOutputLong_Taster1_Dpt3008_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster1_Dpt3008_Release)))
// 
#define ParamBTN_ChannelOutputLong_Taster2_Dpt3008_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Dpt3008_Press)))
// 
#define ParamBTN_ChannelOutputLong_Taster2_Dpt3008_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputLong_Taster2_Dpt3008_Release)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster1_Dpt3008_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Dpt3008_Press)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster1_Dpt3008_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster1_Dpt3008_Release)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster2_Dpt3008_Press (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Dpt3008_Press)))
// 
#define ParamBTN_ChannelOutputExtraLong_Taster2_Dpt3008_Release (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelOutputExtraLong_Taster2_Dpt3008_Release)))
//   Zusatzausgang (DPT1 beim Loslassen)
#define ParamBTN_ChannelOutput2Short_Taster1         ((knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutput2Short_Taster1)) & BTN_ChannelOutput2Short_Taster1Mask) >> BTN_ChannelOutput2Short_Taster1Shift)
//   Zusatzausgang (DPT1 beim Loslassen)
#define ParamBTN_ChannelOutput2Short_Taster2         ((knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutput2Short_Taster2)) & BTN_ChannelOutput2Short_Taster2Mask) >> BTN_ChannelOutput2Short_Taster2Shift)
//   Zusatzausgang (DPT1 beim Loslassen)
#define ParamBTN_ChannelOutput2Long_Taster1          ((knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutput2Long_Taster1)) & BTN_ChannelOutput2Long_Taster1Mask) >> BTN_ChannelOutput2Long_Taster1Shift)
//   Zusatzausgang (DPT1 beim Loslassen)
#define ParamBTN_ChannelOutput2Long_Taster2          (knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutput2Long_Taster2)) & BTN_ChannelOutput2Long_Taster2Mask)
//   Zusatzausgang (DPT1 beim Loslassen)
#define ParamBTN_ChannelOutput2ExtraLong_Taster1     ((knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutput2ExtraLong_Taster1)) & BTN_ChannelOutput2ExtraLong_Taster1Mask) >> BTN_ChannelOutput2ExtraLong_Taster1Shift)
//   Zusatzausgang (DPT1 beim Loslassen)
#define ParamBTN_ChannelOutput2ExtraLong_Taster2     ((knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelOutput2ExtraLong_Taster2)) & BTN_ChannelOutput2ExtraLong_Taster2Mask) >> BTN_ChannelOutput2ExtraLong_Taster2Shift)
// Schwellwert
#define ParamBTN_ChannelStatusThreshold              (knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelStatusThreshold)))
// Zeitbasis
#define ParamBTN_ChannelStatusFallbackBase           ((knx.paramByte(BTN_ParamCalcIndex(BTN_ChannelStatusFallbackBase)) & BTN_ChannelStatusFallbackBaseMask) >> BTN_ChannelStatusFallbackBaseShift)
// Zeit
#define ParamBTN_ChannelStatusFallbackTime           (knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelStatusFallbackTime)) & BTN_ChannelStatusFallbackTimeMask)
// Zeit (in Millisekunden)
#define ParamBTN_ChannelStatusFallbackTimeMS         (paramDelay(knx.paramWord(BTN_ParamCalcIndex(BTN_ChannelStatusFallbackTime))))

// deprecated
#define BTN_KoOffset 100

// Communication objects per channel (multiple occurrence)
#define BTN_KoBlockOffset 100
#define BTN_KoBlockSize 12

#define BTN_KoCalcNumber(index) (index + BTN_KoBlockOffset + _channelIndex * BTN_KoBlockSize)
#define BTN_KoCalcIndex(number) ((number >= BTN_KoCalcNumber(0) && number < BTN_KoCalcNumber(BTN_KoBlockSize)) ? (number - BTN_KoOffset) % BTN_KoBlockSize : -1)

#define BTN_KoChannelLock 0
#define BTN_KoChannelInput1 1
#define BTN_KoChannelInput2 2
#define BTN_KoChannelOutput1Status 3
#define BTN_KoChannelOutput2Status 4
#define BTN_KoChannelOutput3Status 5
#define BTN_KoChannelOutput1 6
#define BTN_KoChannelOutput2 7
#define BTN_KoChannelOutput3 8
#define BTN_KoChannelOutput4 9
#define BTN_KoChannelOutput5 10
#define BTN_KoChannelOutput6 11

// 
#define KoBTN_ChannelLock                         (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoChannelLock)))
// 
#define KoBTN_ChannelInput1                       (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoChannelInput1)))
// 
#define KoBTN_ChannelInput2                       (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoChannelInput2)))
// 
#define KoBTN_ChannelOutput1Status                (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoChannelOutput1Status)))
// 
#define KoBTN_ChannelOutput2Status                (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoChannelOutput2Status)))
// 
#define KoBTN_ChannelOutput3Status                (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoChannelOutput3Status)))
// 
#define KoBTN_ChannelOutput1                      (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoChannelOutput1)))
// 
#define KoBTN_ChannelOutput2                      (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoChannelOutput2)))
// 
#define KoBTN_ChannelOutput3                      (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoChannelOutput3)))
// 
#define KoBTN_ChannelOutput4                      (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoChannelOutput4)))
// 
#define KoBTN_ChannelOutput5                      (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoChannelOutput5)))
// 
#define KoBTN_ChannelOutput6                      (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoChannelOutput6)))

#define LOG_BuzzerInstalled                     1510      // 1 Bit, Bit 7
#define     LOG_BuzzerInstalledMask 0x80
#define     LOG_BuzzerInstalledShift 7
#define LOG_LedInstalled                        1510      // 1 Bit, Bit 6
#define     LOG_LedInstalledMask 0x40
#define     LOG_LedInstalledShift 6
#define LOG_VacationKo                          1510      // 1 Bit, Bit 5
#define     LOG_VacationKoMask 0x20
#define     LOG_VacationKoShift 5
#define LOG_HolidayKo                           1510      // 1 Bit, Bit 4
#define     LOG_HolidayKoMask 0x10
#define     LOG_HolidayKoShift 4
#define LOG_VacationRead                        1510      // 1 Bit, Bit 3
#define     LOG_VacationReadMask 0x08
#define     LOG_VacationReadShift 3
#define LOG_HolidaySend                         1510      // 1 Bit, Bit 2
#define     LOG_HolidaySendMask 0x04
#define     LOG_HolidaySendShift 2
#define LOG_Neujahr                             1511      // 1 Bit, Bit 7
#define     LOG_NeujahrMask 0x80
#define     LOG_NeujahrShift 7
#define LOG_DreiKoenige                         1511      // 1 Bit, Bit 6
#define     LOG_DreiKoenigeMask 0x40
#define     LOG_DreiKoenigeShift 6
#define LOG_Weiberfastnacht                     1511      // 1 Bit, Bit 5
#define     LOG_WeiberfastnachtMask 0x20
#define     LOG_WeiberfastnachtShift 5
#define LOG_Rosenmontag                         1511      // 1 Bit, Bit 4
#define     LOG_RosenmontagMask 0x10
#define     LOG_RosenmontagShift 4
#define LOG_Fastnachtsdienstag                  1511      // 1 Bit, Bit 3
#define     LOG_FastnachtsdienstagMask 0x08
#define     LOG_FastnachtsdienstagShift 3
#define LOG_Aschermittwoch                      1511      // 1 Bit, Bit 2
#define     LOG_AschermittwochMask 0x04
#define     LOG_AschermittwochShift 2
#define LOG_Frauentag                           1511      // 1 Bit, Bit 1
#define     LOG_FrauentagMask 0x02
#define     LOG_FrauentagShift 1
#define LOG_Gruendonnerstag                     1511      // 1 Bit, Bit 0
#define     LOG_GruendonnerstagMask 0x01
#define     LOG_GruendonnerstagShift 0
#define LOG_Karfreitag                          1512      // 1 Bit, Bit 7
#define     LOG_KarfreitagMask 0x80
#define     LOG_KarfreitagShift 7
#define LOG_Ostersonntag                        1512      // 1 Bit, Bit 6
#define     LOG_OstersonntagMask 0x40
#define     LOG_OstersonntagShift 6
#define LOG_Ostermontag                         1512      // 1 Bit, Bit 5
#define     LOG_OstermontagMask 0x20
#define     LOG_OstermontagShift 5
#define LOG_TagDerArbeit                        1512      // 1 Bit, Bit 4
#define     LOG_TagDerArbeitMask 0x10
#define     LOG_TagDerArbeitShift 4
#define LOG_Himmelfahrt                         1512      // 1 Bit, Bit 3
#define     LOG_HimmelfahrtMask 0x08
#define     LOG_HimmelfahrtShift 3
#define LOG_Pfingstsonntag                      1512      // 1 Bit, Bit 2
#define     LOG_PfingstsonntagMask 0x04
#define     LOG_PfingstsonntagShift 2
#define LOG_Pfingstmontag                       1512      // 1 Bit, Bit 1
#define     LOG_PfingstmontagMask 0x02
#define     LOG_PfingstmontagShift 1
#define LOG_Fronleichnam                        1512      // 1 Bit, Bit 0
#define     LOG_FronleichnamMask 0x01
#define     LOG_FronleichnamShift 0
#define LOG_Friedensfest                        1513      // 1 Bit, Bit 7
#define     LOG_FriedensfestMask 0x80
#define     LOG_FriedensfestShift 7
#define LOG_MariaHimmelfahrt                    1513      // 1 Bit, Bit 6
#define     LOG_MariaHimmelfahrtMask 0x40
#define     LOG_MariaHimmelfahrtShift 6
#define LOG_DeutscheEinheit                     1513      // 1 Bit, Bit 5
#define     LOG_DeutscheEinheitMask 0x20
#define     LOG_DeutscheEinheitShift 5
#define LOG_Nationalfeiertag                    1514      // 1 Bit, Bit 1
#define     LOG_NationalfeiertagMask 0x02
#define     LOG_NationalfeiertagShift 1
#define LOG_Reformationstag                     1513      // 1 Bit, Bit 4
#define     LOG_ReformationstagMask 0x10
#define     LOG_ReformationstagShift 4
#define LOG_Allerheiligen                       1513      // 1 Bit, Bit 3
#define     LOG_AllerheiligenMask 0x08
#define     LOG_AllerheiligenShift 3
#define LOG_BussBettag                          1513      // 1 Bit, Bit 2
#define     LOG_BussBettagMask 0x04
#define     LOG_BussBettagShift 2
#define LOG_MariaEmpfaengnis                    1514      // 1 Bit, Bit 0
#define     LOG_MariaEmpfaengnisMask 0x01
#define     LOG_MariaEmpfaengnisShift 0
#define LOG_Advent1                             1513      // 1 Bit, Bit 1
#define     LOG_Advent1Mask 0x02
#define     LOG_Advent1Shift 1
#define LOG_Advent2                             1513      // 1 Bit, Bit 0
#define     LOG_Advent2Mask 0x01
#define     LOG_Advent2Shift 0
#define LOG_Advent3                             1514      // 1 Bit, Bit 7
#define     LOG_Advent3Mask 0x80
#define     LOG_Advent3Shift 7
#define LOG_Advent4                             1514      // 1 Bit, Bit 6
#define     LOG_Advent4Mask 0x40
#define     LOG_Advent4Shift 6
#define LOG_Heiligabend                         1514      // 1 Bit, Bit 5
#define     LOG_HeiligabendMask 0x20
#define     LOG_HeiligabendShift 5
#define LOG_Weihnachtstag1                      1514      // 1 Bit, Bit 4
#define     LOG_Weihnachtstag1Mask 0x10
#define     LOG_Weihnachtstag1Shift 4
#define LOG_Weihnachtstag2                      1514      // 1 Bit, Bit 3
#define     LOG_Weihnachtstag2Mask 0x08
#define     LOG_Weihnachtstag2Shift 3
#define LOG_Silvester                           1514      // 1 Bit, Bit 2
#define     LOG_SilvesterMask 0x04
#define     LOG_SilvesterShift 2
#define LOG_BuzzerSilent                        1515      // uint16_t
#define LOG_BuzzerNormal                        1517      // uint16_t
#define LOG_BuzzerLoud                          1519      // uint16_t
#define LOG_LedMapping                          1521      // 3 Bits, Bit 7-5
#define     LOG_LedMappingMask 0xE0
#define     LOG_LedMappingShift 5

// Akustischer Signalgeber vorhanden (Buzzer)?
#define ParamLOG_BuzzerInstalled                     ((bool)(knx.paramByte(LOG_BuzzerInstalled) & LOG_BuzzerInstalledMask))
// Optischer Signalgeber vorhanden (RGB-LED)?
#define ParamLOG_LedInstalled                        ((bool)(knx.paramByte(LOG_LedInstalled) & LOG_LedInstalledMask))
// Urlaubsbehandlung aktivieren?
#define ParamLOG_VacationKo                          ((bool)(knx.paramByte(LOG_VacationKo) & LOG_VacationKoMask))
// Feiertage auf dem Bus verfügbar machen?
#define ParamLOG_HolidayKo                           ((bool)(knx.paramByte(LOG_HolidayKo) & LOG_HolidayKoMask))
// Nach Neustart Urlaubsinfo lesen?
#define ParamLOG_VacationRead                        ((bool)(knx.paramByte(LOG_VacationRead) & LOG_VacationReadMask))
// Nach Neuberechnung Feiertagsinfo senden?
#define ParamLOG_HolidaySend                         ((bool)(knx.paramByte(LOG_HolidaySend) & LOG_HolidaySendMask))
// 1. Neujahr
#define ParamLOG_Neujahr                             ((bool)(knx.paramByte(LOG_Neujahr) & LOG_NeujahrMask))
// 2. Heilige Drei Könige
#define ParamLOG_DreiKoenige                         ((bool)(knx.paramByte(LOG_DreiKoenige) & LOG_DreiKoenigeMask))
// 3. Weiberfastnacht
#define ParamLOG_Weiberfastnacht                     ((bool)(knx.paramByte(LOG_Weiberfastnacht) & LOG_WeiberfastnachtMask))
// 4. Rosenmontag
#define ParamLOG_Rosenmontag                         ((bool)(knx.paramByte(LOG_Rosenmontag) & LOG_RosenmontagMask))
// 5. Fastnachtsdienstag
#define ParamLOG_Fastnachtsdienstag                  ((bool)(knx.paramByte(LOG_Fastnachtsdienstag) & LOG_FastnachtsdienstagMask))
// 6. Aschermittwoch
#define ParamLOG_Aschermittwoch                      ((bool)(knx.paramByte(LOG_Aschermittwoch) & LOG_AschermittwochMask))
// 7. Frauentag
#define ParamLOG_Frauentag                           ((bool)(knx.paramByte(LOG_Frauentag) & LOG_FrauentagMask))
// 8. Gründonnerstag
#define ParamLOG_Gruendonnerstag                     ((bool)(knx.paramByte(LOG_Gruendonnerstag) & LOG_GruendonnerstagMask))
// 9. Karfreitag
#define ParamLOG_Karfreitag                          ((bool)(knx.paramByte(LOG_Karfreitag) & LOG_KarfreitagMask))
// 10. Ostersonntag
#define ParamLOG_Ostersonntag                        ((bool)(knx.paramByte(LOG_Ostersonntag) & LOG_OstersonntagMask))
// 11. Ostermontag
#define ParamLOG_Ostermontag                         ((bool)(knx.paramByte(LOG_Ostermontag) & LOG_OstermontagMask))
// 12. Tag der Arbeit
#define ParamLOG_TagDerArbeit                        ((bool)(knx.paramByte(LOG_TagDerArbeit) & LOG_TagDerArbeitMask))
// 13. Christi Himmelfahrt
#define ParamLOG_Himmelfahrt                         ((bool)(knx.paramByte(LOG_Himmelfahrt) & LOG_HimmelfahrtMask))
// 14. Pfingstsonntag
#define ParamLOG_Pfingstsonntag                      ((bool)(knx.paramByte(LOG_Pfingstsonntag) & LOG_PfingstsonntagMask))
// 15. Pfingstmontag
#define ParamLOG_Pfingstmontag                       ((bool)(knx.paramByte(LOG_Pfingstmontag) & LOG_PfingstmontagMask))
// 16. Fronleichnam
#define ParamLOG_Fronleichnam                        ((bool)(knx.paramByte(LOG_Fronleichnam) & LOG_FronleichnamMask))
// 17. Hohes Friedensfest
#define ParamLOG_Friedensfest                        ((bool)(knx.paramByte(LOG_Friedensfest) & LOG_FriedensfestMask))
// 18. Mariä Himmelfahrt
#define ParamLOG_MariaHimmelfahrt                    ((bool)(knx.paramByte(LOG_MariaHimmelfahrt) & LOG_MariaHimmelfahrtMask))
// 19. Tag der Deutschen Einheit
#define ParamLOG_DeutscheEinheit                     ((bool)(knx.paramByte(LOG_DeutscheEinheit) & LOG_DeutscheEinheitMask))
// 31. Nationalfeiertag (AT)
#define ParamLOG_Nationalfeiertag                    ((bool)(knx.paramByte(LOG_Nationalfeiertag) & LOG_NationalfeiertagMask))
// 20. Reformationstag
#define ParamLOG_Reformationstag                     ((bool)(knx.paramByte(LOG_Reformationstag) & LOG_ReformationstagMask))
// 21. Allerheiligen
#define ParamLOG_Allerheiligen                       ((bool)(knx.paramByte(LOG_Allerheiligen) & LOG_AllerheiligenMask))
// 22. Buß- und Bettag
#define ParamLOG_BussBettag                          ((bool)(knx.paramByte(LOG_BussBettag) & LOG_BussBettagMask))
// 32. Maria Empfängnis (AT)
#define ParamLOG_MariaEmpfaengnis                    ((bool)(knx.paramByte(LOG_MariaEmpfaengnis) & LOG_MariaEmpfaengnisMask))
// 23. Erster Advent
#define ParamLOG_Advent1                             ((bool)(knx.paramByte(LOG_Advent1) & LOG_Advent1Mask))
// 24. Zweiter Advent
#define ParamLOG_Advent2                             ((bool)(knx.paramByte(LOG_Advent2) & LOG_Advent2Mask))
// 25. Dritter Advent
#define ParamLOG_Advent3                             ((bool)(knx.paramByte(LOG_Advent3) & LOG_Advent3Mask))
// 26. Vierter Advent
#define ParamLOG_Advent4                             ((bool)(knx.paramByte(LOG_Advent4) & LOG_Advent4Mask))
// 27. Heiligabend
#define ParamLOG_Heiligabend                         ((bool)(knx.paramByte(LOG_Heiligabend) & LOG_HeiligabendMask))
// 28. Erster Weihnachtstag
#define ParamLOG_Weihnachtstag1                      ((bool)(knx.paramByte(LOG_Weihnachtstag1) & LOG_Weihnachtstag1Mask))
// 29. Zweiter Weihnachtstag
#define ParamLOG_Weihnachtstag2                      ((bool)(knx.paramByte(LOG_Weihnachtstag2) & LOG_Weihnachtstag2Mask))
// 30. Silvester
#define ParamLOG_Silvester                           ((bool)(knx.paramByte(LOG_Silvester) & LOG_SilvesterMask))
// Frequenz für Buzzer (leise)
#define ParamLOG_BuzzerSilent                        (knx.paramWord(LOG_BuzzerSilent))
// Frequenz für Buzzer (normal)
#define ParamLOG_BuzzerNormal                        (knx.paramWord(LOG_BuzzerNormal))
// Frequenz für Buzzer (laut)
#define ParamLOG_BuzzerLoud                          (knx.paramWord(LOG_BuzzerLoud))
// Lötpad A / B / C entspricht
#define ParamLOG_LedMapping                          ((knx.paramByte(LOG_LedMapping) & LOG_LedMappingMask) >> LOG_LedMappingShift)

#define LOG_KoVacation 4
#define LOG_KoHoliday1 5
#define LOG_KoHoliday2 6
#define LOG_KoLedLock 8
#define LOG_KoBuzzerLock 9

// Urlaub
#define KoLOG_Vacation                            (knx.getGroupObject(LOG_KoVacation))
// Welcher Feiertag ist heute?
#define KoLOG_Holiday1                            (knx.getGroupObject(LOG_KoHoliday1))
// Welcher Feiertag ist morgen?
#define KoLOG_Holiday2                            (knx.getGroupObject(LOG_KoHoliday2))
// LED sperren
#define KoLOG_LedLock                             (knx.getGroupObject(LOG_KoLedLock))
// Buzzer sperren
#define KoLOG_BuzzerLock                          (knx.getGroupObject(LOG_KoBuzzerLock))

#define LOG_ChannelCount 20

// Parameter per channel
#define LOG_ParamBlockOffset 1522
#define LOG_ParamBlockSize 86
#define LOG_ParamCalcIndex(index) (index + LOG_ParamBlockOffset + _channelIndex * LOG_ParamBlockSize)

#define LOG_fChannelDelayBase                    0      // 2 Bits, Bit 7-6
#define     LOG_fChannelDelayBaseMask 0xC0
#define     LOG_fChannelDelayBaseShift 6
#define LOG_fChannelDelayTime                    0      // 14 Bits, Bit 13-0
#define     LOG_fChannelDelayTimeMask 0x3FFF
#define     LOG_fChannelDelayTimeShift 0
#define LOG_fLogic                               2      // 8 Bits, Bit 7-0
#define LOG_fCalculate                           3      // 2 Bits, Bit 1-0
#define     LOG_fCalculateMask 0x03
#define     LOG_fCalculateShift 0
#define LOG_fDisable                             3      // 1 Bit, Bit 2
#define     LOG_fDisableMask 0x04
#define     LOG_fDisableShift 2
#define LOG_fAlarm                               3      // 1 Bit, Bit 3
#define     LOG_fAlarmMask 0x08
#define     LOG_fAlarmShift 3
#define LOG_fTGate                               3      // 1 Bit, Bit 4
#define     LOG_fTGateMask 0x10
#define     LOG_fTGateShift 4
#define LOG_fOInternalOn                         3      // 1 Bit, Bit 5
#define     LOG_fOInternalOnMask 0x20
#define     LOG_fOInternalOnShift 5
#define LOG_fOInternalOff                        3      // 1 Bit, Bit 6
#define     LOG_fOInternalOffMask 0x40
#define     LOG_fOInternalOffShift 6
#define LOG_fTrigger                             4      // 8 Bits, Bit 7-0
#define LOG_fTriggerE1                           4      // 1 Bit, Bit 0
#define     LOG_fTriggerE1Mask 0x01
#define     LOG_fTriggerE1Shift 0
#define LOG_fTriggerE2                           4      // 1 Bit, Bit 1
#define     LOG_fTriggerE2Mask 0x02
#define     LOG_fTriggerE2Shift 1
#define LOG_fTriggerI1                           4      // 1 Bit, Bit 2
#define     LOG_fTriggerI1Mask 0x04
#define     LOG_fTriggerI1Shift 2
#define LOG_fTriggerI2                           4      // 1 Bit, Bit 3
#define     LOG_fTriggerI2Mask 0x08
#define     LOG_fTriggerI2Shift 3
#define LOG_fTriggerTime                         4      // 8 Bits, Bit 7-0
#define LOG_fTriggerGateClose                    5      // 2 Bits, Bit 7-6
#define     LOG_fTriggerGateCloseMask 0xC0
#define     LOG_fTriggerGateCloseShift 6
#define LOG_fTriggerGateOpen                     5      // 2 Bits, Bit 5-4
#define     LOG_fTriggerGateOpenMask 0x30
#define     LOG_fTriggerGateOpenShift 4
#define LOG_fE1                                  6      // 4 Bits, Bit 3-0
#define     LOG_fE1Mask 0x0F
#define     LOG_fE1Shift 0
#define LOG_fE1Convert                           6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertMask 0xF0
#define     LOG_fE1ConvertShift 4
#define LOG_fE1ConvertFloat                      6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertFloatMask 0xF0
#define     LOG_fE1ConvertFloatShift 4
#define LOG_fE1ConvertSpecial                    6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertSpecialMask 0xF0
#define     LOG_fE1ConvertSpecialShift 4
#define LOG_fE1Dpt                               7      // 8 Bits, Bit 7-0
#define LOG_fE1Default                           8      // 2 Bits, Bit 1-0
#define     LOG_fE1DefaultMask 0x03
#define     LOG_fE1DefaultShift 0
#define LOG_fE1DefaultExt                        8      // 2 Bits, Bit 1-0
#define     LOG_fE1DefaultExtMask 0x03
#define     LOG_fE1DefaultExtShift 0
#define LOG_fE1DefaultEEPROM                     8      // 1 Bit, Bit 2
#define     LOG_fE1DefaultEEPROMMask 0x04
#define     LOG_fE1DefaultEEPROMShift 2
#define LOG_fE1DefaultRepeat                     8      // 1 Bit, Bit 3
#define     LOG_fE1DefaultRepeatMask 0x08
#define     LOG_fE1DefaultRepeatShift 3
#define LOG_fTYearDay                            8      // 1 Bit, Bit 4
#define     LOG_fTYearDayMask 0x10
#define     LOG_fTYearDayShift 4
#define LOG_fTRestoreState                       8      // 2 Bits, Bit 6-5
#define     LOG_fTRestoreStateMask 0x60
#define     LOG_fTRestoreStateShift 5
#define LOG_fE1RepeatBase                        9      // 2 Bits, Bit 7-6
#define     LOG_fE1RepeatBaseMask 0xC0
#define     LOG_fE1RepeatBaseShift 6
#define LOG_fE1RepeatTime                        9      // 14 Bits, Bit 13-0
#define     LOG_fE1RepeatTimeMask 0x3FFF
#define     LOG_fE1RepeatTimeShift 0
#define LOG_fE2                                 11      // 4 Bits, Bit 3-0
#define     LOG_fE2Mask 0x0F
#define     LOG_fE2Shift 0
#define LOG_fE2Convert                          11      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertMask 0xF0
#define     LOG_fE2ConvertShift 4
#define LOG_fE2ConvertFloat                     11      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertFloatMask 0xF0
#define     LOG_fE2ConvertFloatShift 4
#define LOG_fE2ConvertSpecial                   11      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertSpecialMask 0xF0
#define     LOG_fE2ConvertSpecialShift 4
#define LOG_fE2Dpt                              12      // 8 Bits, Bit 7-0
#define LOG_fE2Default                          13      // 2 Bits, Bit 1-0
#define     LOG_fE2DefaultMask 0x03
#define     LOG_fE2DefaultShift 0
#define LOG_fE2DefaultExt                       13      // 2 Bits, Bit 1-0
#define     LOG_fE2DefaultExtMask 0x03
#define     LOG_fE2DefaultExtShift 0
#define LOG_fE2DefaultEEPROM                    13      // 1 Bit, Bit 2
#define     LOG_fE2DefaultEEPROMMask 0x04
#define     LOG_fE2DefaultEEPROMShift 2
#define LOG_fE2DefaultRepeat                    13      // 1 Bit, Bit 3
#define     LOG_fE2DefaultRepeatMask 0x08
#define     LOG_fE2DefaultRepeatShift 3
#define LOG_fTHoliday                           13      // 2 Bits, Bit 4-3
#define     LOG_fTHolidayMask 0x18
#define     LOG_fTHolidayShift 3
#define LOG_fTVacation                          13      // 2 Bits, Bit 6-5
#define     LOG_fTVacationMask 0x60
#define     LOG_fTVacationShift 5
#define LOG_fE2RepeatBase                       14      // 2 Bits, Bit 7-6
#define     LOG_fE2RepeatBaseMask 0xC0
#define     LOG_fE2RepeatBaseShift 6
#define LOG_fE2RepeatTime                       14      // 14 Bits, Bit 13-0
#define     LOG_fE2RepeatTimeMask 0x3FFF
#define     LOG_fE2RepeatTimeShift 0
#define LOG_fTd1DuskDawn                        14      // 4 Bits, Bit 7-4
#define     LOG_fTd1DuskDawnMask 0xF0
#define     LOG_fTd1DuskDawnShift 4
#define LOG_fTd2DuskDawn                        14      // 4 Bits, Bit 3-0
#define     LOG_fTd2DuskDawnMask 0x0F
#define     LOG_fTd2DuskDawnShift 0
#define LOG_fTd3DuskDawn                        15      // 4 Bits, Bit 7-4
#define     LOG_fTd3DuskDawnMask 0xF0
#define     LOG_fTd3DuskDawnShift 4
#define LOG_fTd4DuskDawn                        15      // 4 Bits, Bit 3-0
#define     LOG_fTd4DuskDawnMask 0x0F
#define     LOG_fTd4DuskDawnShift 0
#define LOG_fTd5DuskDawn                        16      // 4 Bits, Bit 7-4
#define     LOG_fTd5DuskDawnMask 0xF0
#define     LOG_fTd5DuskDawnShift 4
#define LOG_fTd6DuskDawn                        16      // 4 Bits, Bit 3-0
#define     LOG_fTd6DuskDawnMask 0x0F
#define     LOG_fTd6DuskDawnShift 0
#define LOG_fTd7DuskDawn                        17      // 4 Bits, Bit 7-4
#define     LOG_fTd7DuskDawnMask 0xF0
#define     LOG_fTd7DuskDawnShift 4
#define LOG_fTd8DuskDawn                        17      // 4 Bits, Bit 3-0
#define     LOG_fTd8DuskDawnMask 0x0F
#define     LOG_fTd8DuskDawnShift 0
#define LOG_fE1LowDelta                         18      // int32_t
#define LOG_fE1HighDelta                        22      // int32_t
#define LOG_fE1LowDeltaFloat                    18      // float
#define LOG_fE1HighDeltaFloat                   22      // float
#define LOG_fE1LowDeltaDouble                   18      // float
#define LOG_fE1HighDeltaDouble                  22      // float
#define LOG_fE1Low0Valid                        25      // 1 Bit, Bit 7
#define     LOG_fE1Low0ValidMask 0x80
#define     LOG_fE1Low0ValidShift 7
#define LOG_fE1Low1Valid                        25      // 1 Bit, Bit 6
#define     LOG_fE1Low1ValidMask 0x40
#define     LOG_fE1Low1ValidShift 6
#define LOG_fE1Low2Valid                        25      // 1 Bit, Bit 5
#define     LOG_fE1Low2ValidMask 0x20
#define     LOG_fE1Low2ValidShift 5
#define LOG_fE1Low3Valid                        25      // 1 Bit, Bit 4
#define     LOG_fE1Low3ValidMask 0x10
#define     LOG_fE1Low3ValidShift 4
#define LOG_fE1Low4Valid                        25      // 1 Bit, Bit 3
#define     LOG_fE1Low4ValidMask 0x08
#define     LOG_fE1Low4ValidShift 3
#define LOG_fE1Low5Valid                        25      // 1 Bit, Bit 2
#define     LOG_fE1Low5ValidMask 0x04
#define     LOG_fE1Low5ValidShift 2
#define LOG_fE1Low6Valid                        25      // 1 Bit, Bit 1
#define     LOG_fE1Low6ValidMask 0x02
#define     LOG_fE1Low6ValidShift 1
#define LOG_fE1Low7Valid                        25      // 1 Bit, Bit 0
#define     LOG_fE1Low7ValidMask 0x01
#define     LOG_fE1Low7ValidShift 0
#define LOG_fE1LowDpt2                          18      // 8 Bits, Bit 7-0
#define LOG_fE1Low1Dpt2                         19      // 8 Bits, Bit 7-0
#define LOG_fE1Low2Dpt2                         20      // 8 Bits, Bit 7-0
#define LOG_fE1Low3Dpt2                         21      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt2Fix                       18      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt5                          18      // uint8_t
#define LOG_fE1HighDpt5                         22      // uint8_t
#define LOG_fE1Low0Dpt5In                       18      // uint8_t
#define LOG_fE1Low1Dpt5In                       19      // uint8_t
#define LOG_fE1Low2Dpt5In                       20      // uint8_t
#define LOG_fE1Low3Dpt5In                       21      // uint8_t
#define LOG_fE1Low4Dpt5In                       22      // uint8_t
#define LOG_fE1Low5Dpt5In                       23      // uint8_t
#define LOG_fE1Low6Dpt5In                       24      // uint8_t
#define LOG_fE1LowDpt5Fix                       18      // uint8_t
#define LOG_fE1LowDpt5001                       18      // uint8_t
#define LOG_fE1HighDpt5001                      22      // uint8_t
#define LOG_fE1Low0Dpt5xIn                      18      // uint8_t
#define LOG_fE1Low1Dpt5xIn                      19      // uint8_t
#define LOG_fE1Low2Dpt5xIn                      20      // uint8_t
#define LOG_fE1Low3Dpt5xIn                      21      // uint8_t
#define LOG_fE1Low4Dpt5xIn                      22      // uint8_t
#define LOG_fE1Low5Dpt5xIn                      23      // uint8_t
#define LOG_fE1Low6Dpt5xIn                      24      // uint8_t
#define LOG_fE1LowDpt5xFix                      18      // uint8_t
#define LOG_fE1LowDpt6                          18      // int8_t
#define LOG_fE1HighDpt6                         22      // int8_t
#define LOG_fE1Low0Dpt6In                       18      // int8_t
#define LOG_fE1Low1Dpt6In                       19      // int8_t
#define LOG_fE1Low2Dpt6In                       20      // int8_t
#define LOG_fE1Low3Dpt6In                       21      // int8_t
#define LOG_fE1Low4Dpt6In                       22      // int8_t
#define LOG_fE1Low5Dpt6In                       23      // int8_t
#define LOG_fE1Low6Dpt6In                       24      // int8_t
#define LOG_fE1LowDpt6Fix                       18      // int8_t
#define LOG_fE1LowDpt7                          18      // uint16_t
#define LOG_fE1HighDpt7                         22      // uint16_t
#define LOG_fE1Low0Dpt7In                       18      // uint16_t
#define LOG_fE1Low1Dpt7In                       20      // uint16_t
#define LOG_fE1Low2Dpt7In                       22      // uint16_t
#define LOG_fE1LowDpt7Fix                       18      // uint16_t
#define LOG_fE1LowDpt8                          18      // int16_t
#define LOG_fE1HighDpt8                         22      // int16_t
#define LOG_fE1Low0Dpt8In                       18      // int16_t
#define LOG_fE1Low1Dpt8In                       20      // int16_t
#define LOG_fE1Low2Dpt8In                       22      // int16_t
#define LOG_fE1LowDpt8Fix                       18      // int16_t
#define LOG_fE1LowDpt9                          18      // float
#define LOG_fE1HighDpt9                         22      // float
#define LOG_fE1LowDpt9Fix                       18      // float
#define LOG_fE1LowDpt12                         18      // uint32_t
#define LOG_fE1HighDpt12                        22      // uint32_t
#define LOG_fE1LowDpt12Fix                      18      // uint32_t
#define LOG_fE1LowDpt13                         18      // int32_t
#define LOG_fE1HighDpt13                        22      // int32_t
#define LOG_fE1LowDpt13Fix                      18      // int32_t
#define LOG_fE1LowDpt14                         18      // float
#define LOG_fE1HighDpt14                        22      // float
#define LOG_fE1LowDpt14Fix                      18      // float
#define LOG_fE1Low0Dpt17                        18      // 8 Bits, Bit 7-0
#define LOG_fE1Low1Dpt17                        19      // 8 Bits, Bit 7-0
#define LOG_fE1Low2Dpt17                        20      // 8 Bits, Bit 7-0
#define LOG_fE1Low3Dpt17                        21      // 8 Bits, Bit 7-0
#define LOG_fE1Low4Dpt17                        22      // 8 Bits, Bit 7-0
#define LOG_fE1Low5Dpt17                        23      // 8 Bits, Bit 7-0
#define LOG_fE1Low6Dpt17                        24      // 8 Bits, Bit 7-0
#define LOG_fE1Low7Dpt17                        25      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt17Fix                      18      // 8 Bits, Bit 7-0
#define LOG_fE1LowDptRGB                        18      // int32_t
#define LOG_fE1HighDptRGB                       22      // int32_t
#define LOG_fE1LowDptRGBFix                     18      // int32_t
#define LOG_fE2LowDelta                         26      // int32_t
#define LOG_fE2HighDelta                        30      // int32_t
#define LOG_fE2LowDeltaFloat                    26      // float
#define LOG_fE2HighDeltaFloat                   30      // float
#define LOG_fE2LowDeltaDouble                   26      // float
#define LOG_fE2HighDeltaDouble                  30      // float
#define LOG_fE2Low0Valid                        33      // 1 Bit, Bit 7
#define     LOG_fE2Low0ValidMask 0x80
#define     LOG_fE2Low0ValidShift 7
#define LOG_fE2Low1Valid                        33      // 1 Bit, Bit 6
#define     LOG_fE2Low1ValidMask 0x40
#define     LOG_fE2Low1ValidShift 6
#define LOG_fE2Low2Valid                        33      // 1 Bit, Bit 5
#define     LOG_fE2Low2ValidMask 0x20
#define     LOG_fE2Low2ValidShift 5
#define LOG_fE2Low3Valid                        33      // 1 Bit, Bit 4
#define     LOG_fE2Low3ValidMask 0x10
#define     LOG_fE2Low3ValidShift 4
#define LOG_fE2Low4Valid                        33      // 1 Bit, Bit 3
#define     LOG_fE2Low4ValidMask 0x08
#define     LOG_fE2Low4ValidShift 3
#define LOG_fE2Low5Valid                        33      // 1 Bit, Bit 2
#define     LOG_fE2Low5ValidMask 0x04
#define     LOG_fE2Low5ValidShift 2
#define LOG_fE2Low6Valid                        33      // 1 Bit, Bit 1
#define     LOG_fE2Low6ValidMask 0x02
#define     LOG_fE2Low6ValidShift 1
#define LOG_fE2Low7Valid                        33      // 1 Bit, Bit 0
#define     LOG_fE2Low7ValidMask 0x01
#define     LOG_fE2Low7ValidShift 0
#define LOG_fE2Low0Dpt2                         26      // 8 Bits, Bit 7-0
#define LOG_fE2Low1Dpt2                         27      // 8 Bits, Bit 7-0
#define LOG_fE2Low2Dpt2                         28      // 8 Bits, Bit 7-0
#define LOG_fE2Low3Dpt2                         29      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt2Fix                       26      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt5                          26      // uint8_t
#define LOG_fE2HighDpt5                         30      // uint8_t
#define LOG_fE2Low0Dpt5In                       26      // uint8_t
#define LOG_fE2Low1Dpt5In                       27      // uint8_t
#define LOG_fE2Low2Dpt5In                       28      // uint8_t
#define LOG_fE2Low3Dpt5In                       29      // uint8_t
#define LOG_fE2Low4Dpt5In                       30      // uint8_t
#define LOG_fE2Low5Dpt5In                       31      // uint8_t
#define LOG_fE2Low6Dpt5In                       32      // uint8_t
#define LOG_fE2LowDpt5Fix                       26      // uint8_t
#define LOG_fE2LowDpt5001                       26      // uint8_t
#define LOG_fE2HighDpt5001                      30      // uint8_t
#define LOG_fE2Low0Dpt5xIn                      26      // uint8_t
#define LOG_fE2Low1Dpt5xIn                      27      // uint8_t
#define LOG_fE2Low2Dpt5xIn                      28      // uint8_t
#define LOG_fE2Low3Dpt5xIn                      29      // uint8_t
#define LOG_fE2Low4Dpt5xIn                      30      // uint8_t
#define LOG_fE2Low5Dpt5xIn                      31      // uint8_t
#define LOG_fE2Low6Dpt5xIn                      32      // uint8_t
#define LOG_fE2LowDpt5xFix                      26      // uint8_t
#define LOG_fE2LowDpt6                          26      // int8_t
#define LOG_fE2HighDpt6                         30      // int8_t
#define LOG_fE2Low0Dpt6In                       26      // int8_t
#define LOG_fE2Low1Dpt6In                       27      // int8_t
#define LOG_fE2Low2Dpt6In                       28      // int8_t
#define LOG_fE2Low3Dpt6In                       29      // int8_t
#define LOG_fE2Low4Dpt6In                       30      // int8_t
#define LOG_fE2Low5Dpt6In                       31      // int8_t
#define LOG_fE2Low6Dpt6In                       32      // int8_t
#define LOG_fE2LowDpt6Fix                       26      // int8_t
#define LOG_fE2LowDpt7                          26      // uint16_t
#define LOG_fE2HighDpt7                         30      // uint16_t
#define LOG_fE2Low0Dpt7In                       26      // uint16_t
#define LOG_fE2Low1Dpt7In                       28      // uint16_t
#define LOG_fE2Low2Dpt7In                       30      // uint16_t
#define LOG_fE2LowDpt7Fix                       26      // uint16_t
#define LOG_fE2LowDpt8                          26      // int16_t
#define LOG_fE2HighDpt8                         30      // int16_t
#define LOG_fE2Low0Dpt8In                       26      // int16_t
#define LOG_fE2Low1Dpt8In                       28      // int16_t
#define LOG_fE2Low2Dpt8In                       30      // int16_t
#define LOG_fE2LowDpt8Fix                       26      // int16_t
#define LOG_fE2LowDpt9                          26      // float
#define LOG_fE2HighDpt9                         30      // float
#define LOG_fE2LowDpt9Fix                       26      // float
#define LOG_fE2LowDpt12                         26      // uint32_t
#define LOG_fE2HighDpt12                        30      // uint32_t
#define LOG_fE2LowDpt12Fix                      26      // uint32_t
#define LOG_fE2LowDpt13                         26      // int32_t
#define LOG_fE2HighDpt13                        30      // int32_t
#define LOG_fE2LowDpt13Fix                      26      // int32_t
#define LOG_fE2LowDpt14                         26      // float
#define LOG_fE2HighDpt14                        30      // float
#define LOG_fE2LowDpt14Fix                      26      // float
#define LOG_fE2Low0Dpt17                        26      // 8 Bits, Bit 7-0
#define LOG_fE2Low1Dpt17                        27      // 8 Bits, Bit 7-0
#define LOG_fE2Low2Dpt17                        28      // 8 Bits, Bit 7-0
#define LOG_fE2Low3Dpt17                        29      // 8 Bits, Bit 7-0
#define LOG_fE2Low4Dpt17                        30      // 8 Bits, Bit 7-0
#define LOG_fE2Low5Dpt17                        31      // 8 Bits, Bit 7-0
#define LOG_fE2Low6Dpt17                        32      // 8 Bits, Bit 7-0
#define LOG_fE2Low7Dpt17                        33      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt17Fix                      26      // 8 Bits, Bit 7-0
#define LOG_fE2LowDptRGB                        26      // int32_t
#define LOG_fE2HighDptRGB                       30      // int32_t
#define LOG_fE2LowDptRGBFix                     26      // int32_t
#define LOG_fTd1Value                           18      // 1 Bit, Bit 7
#define     LOG_fTd1ValueMask 0x80
#define     LOG_fTd1ValueShift 7
#define LOG_fTd1Degree                          18      // 6 Bits, Bit 6-1
#define     LOG_fTd1DegreeMask 0x7E
#define     LOG_fTd1DegreeShift 1
#define LOG_fTd1HourAbs                         18      // 5 Bits, Bit 5-1
#define     LOG_fTd1HourAbsMask 0x3E
#define     LOG_fTd1HourAbsShift 1
#define LOG_fTd1HourRel                         18      // 5 Bits, Bit 5-1
#define     LOG_fTd1HourRelMask 0x3E
#define     LOG_fTd1HourRelShift 1
#define LOG_fTd1MinuteAbs                       18      // 6 Bits, Bit 0--5
#define LOG_fTd1MinuteRel                       18      // 6 Bits, Bit 0--5
#define LOG_fTd1Weekday                         19      // 3 Bits, Bit 2-0
#define     LOG_fTd1WeekdayMask 0x07
#define     LOG_fTd1WeekdayShift 0
#define LOG_fTd2Value                           20      // 1 Bit, Bit 7
#define     LOG_fTd2ValueMask 0x80
#define     LOG_fTd2ValueShift 7
#define LOG_fTd2Degree                          20      // 6 Bits, Bit 6-1
#define     LOG_fTd2DegreeMask 0x7E
#define     LOG_fTd2DegreeShift 1
#define LOG_fTd2HourAbs                         20      // 5 Bits, Bit 5-1
#define     LOG_fTd2HourAbsMask 0x3E
#define     LOG_fTd2HourAbsShift 1
#define LOG_fTd2HourRel                         20      // 5 Bits, Bit 5-1
#define     LOG_fTd2HourRelMask 0x3E
#define     LOG_fTd2HourRelShift 1
#define LOG_fTd2MinuteAbs                       20      // 6 Bits, Bit 0--5
#define LOG_fTd2MinuteRel                       20      // 6 Bits, Bit 0--5
#define LOG_fTd2Weekday                         21      // 3 Bits, Bit 2-0
#define     LOG_fTd2WeekdayMask 0x07
#define     LOG_fTd2WeekdayShift 0
#define LOG_fTd3Value                           22      // 1 Bit, Bit 7
#define     LOG_fTd3ValueMask 0x80
#define     LOG_fTd3ValueShift 7
#define LOG_fTd3Degree                          22      // 6 Bits, Bit 6-1
#define     LOG_fTd3DegreeMask 0x7E
#define     LOG_fTd3DegreeShift 1
#define LOG_fTd3HourAbs                         22      // 5 Bits, Bit 5-1
#define     LOG_fTd3HourAbsMask 0x3E
#define     LOG_fTd3HourAbsShift 1
#define LOG_fTd3HourRel                         22      // 5 Bits, Bit 5-1
#define     LOG_fTd3HourRelMask 0x3E
#define     LOG_fTd3HourRelShift 1
#define LOG_fTd3MinuteAbs                       22      // 6 Bits, Bit 0--5
#define LOG_fTd3MinuteRel                       22      // 6 Bits, Bit 0--5
#define LOG_fTd3Weekday                         23      // 3 Bits, Bit 2-0
#define     LOG_fTd3WeekdayMask 0x07
#define     LOG_fTd3WeekdayShift 0
#define LOG_fTd4Value                           24      // 1 Bit, Bit 7
#define     LOG_fTd4ValueMask 0x80
#define     LOG_fTd4ValueShift 7
#define LOG_fTd4Degree                          24      // 6 Bits, Bit 6-1
#define     LOG_fTd4DegreeMask 0x7E
#define     LOG_fTd4DegreeShift 1
#define LOG_fTd4HourAbs                         24      // 5 Bits, Bit 5-1
#define     LOG_fTd4HourAbsMask 0x3E
#define     LOG_fTd4HourAbsShift 1
#define LOG_fTd4HourRel                         24      // 5 Bits, Bit 5-1
#define     LOG_fTd4HourRelMask 0x3E
#define     LOG_fTd4HourRelShift 1
#define LOG_fTd4MinuteAbs                       24      // 6 Bits, Bit 0--5
#define LOG_fTd4MinuteRel                       24      // 6 Bits, Bit 0--5
#define LOG_fTd4Weekday                         25      // 3 Bits, Bit 2-0
#define     LOG_fTd4WeekdayMask 0x07
#define     LOG_fTd4WeekdayShift 0
#define LOG_fTd5Value                           26      // 1 Bit, Bit 7
#define     LOG_fTd5ValueMask 0x80
#define     LOG_fTd5ValueShift 7
#define LOG_fTd5Degree                          26      // 6 Bits, Bit 6-1
#define     LOG_fTd5DegreeMask 0x7E
#define     LOG_fTd5DegreeShift 1
#define LOG_fTd5HourAbs                         26      // 5 Bits, Bit 5-1
#define     LOG_fTd5HourAbsMask 0x3E
#define     LOG_fTd5HourAbsShift 1
#define LOG_fTd5HourRel                         26      // 5 Bits, Bit 5-1
#define     LOG_fTd5HourRelMask 0x3E
#define     LOG_fTd5HourRelShift 1
#define LOG_fTd5MinuteAbs                       26      // 6 Bits, Bit 0--5
#define LOG_fTd5MinuteRel                       26      // 6 Bits, Bit 0--5
#define LOG_fTd5Weekday                         27      // 3 Bits, Bit 2-0
#define     LOG_fTd5WeekdayMask 0x07
#define     LOG_fTd5WeekdayShift 0
#define LOG_fTd6Value                           28      // 1 Bit, Bit 7
#define     LOG_fTd6ValueMask 0x80
#define     LOG_fTd6ValueShift 7
#define LOG_fTd6Degree                          28      // 6 Bits, Bit 6-1
#define     LOG_fTd6DegreeMask 0x7E
#define     LOG_fTd6DegreeShift 1
#define LOG_fTd6HourAbs                         28      // 5 Bits, Bit 5-1
#define     LOG_fTd6HourAbsMask 0x3E
#define     LOG_fTd6HourAbsShift 1
#define LOG_fTd6HourRel                         28      // 5 Bits, Bit 5-1
#define     LOG_fTd6HourRelMask 0x3E
#define     LOG_fTd6HourRelShift 1
#define LOG_fTd6MinuteAbs                       28      // 6 Bits, Bit 0--5
#define LOG_fTd6MinuteRel                       28      // 6 Bits, Bit 0--5
#define LOG_fTd6Weekday                         29      // 3 Bits, Bit 2-0
#define     LOG_fTd6WeekdayMask 0x07
#define     LOG_fTd6WeekdayShift 0
#define LOG_fTd7Value                           30      // 1 Bit, Bit 7
#define     LOG_fTd7ValueMask 0x80
#define     LOG_fTd7ValueShift 7
#define LOG_fTd7Degree                          30      // 6 Bits, Bit 6-1
#define     LOG_fTd7DegreeMask 0x7E
#define     LOG_fTd7DegreeShift 1
#define LOG_fTd7HourAbs                         30      // 5 Bits, Bit 5-1
#define     LOG_fTd7HourAbsMask 0x3E
#define     LOG_fTd7HourAbsShift 1
#define LOG_fTd7HourRel                         30      // 5 Bits, Bit 5-1
#define     LOG_fTd7HourRelMask 0x3E
#define     LOG_fTd7HourRelShift 1
#define LOG_fTd7MinuteAbs                       30      // 6 Bits, Bit 0--5
#define LOG_fTd7MinuteRel                       30      // 6 Bits, Bit 0--5
#define LOG_fTd7Weekday                         31      // 3 Bits, Bit 2-0
#define     LOG_fTd7WeekdayMask 0x07
#define     LOG_fTd7WeekdayShift 0
#define LOG_fTd8Value                           32      // 1 Bit, Bit 7
#define     LOG_fTd8ValueMask 0x80
#define     LOG_fTd8ValueShift 7
#define LOG_fTd8Degree                          32      // 6 Bits, Bit 6-1
#define     LOG_fTd8DegreeMask 0x7E
#define     LOG_fTd8DegreeShift 1
#define LOG_fTd8HourAbs                         32      // 5 Bits, Bit 5-1
#define     LOG_fTd8HourAbsMask 0x3E
#define     LOG_fTd8HourAbsShift 1
#define LOG_fTd8HourRel                         32      // 5 Bits, Bit 5-1
#define     LOG_fTd8HourRelMask 0x3E
#define     LOG_fTd8HourRelShift 1
#define LOG_fTd8MinuteAbs                       32      // 6 Bits, Bit 0--5
#define LOG_fTd8MinuteRel                       32      // 6 Bits, Bit 0--5
#define LOG_fTd8Weekday                         33      // 3 Bits, Bit 2-0
#define     LOG_fTd8WeekdayMask 0x07
#define     LOG_fTd8WeekdayShift 0
#define LOG_fTy1Weekday1                        26      // 1 Bit, Bit 7
#define     LOG_fTy1Weekday1Mask 0x80
#define     LOG_fTy1Weekday1Shift 7
#define LOG_fTy1Weekday2                        26      // 1 Bit, Bit 6
#define     LOG_fTy1Weekday2Mask 0x40
#define     LOG_fTy1Weekday2Shift 6
#define LOG_fTy1Weekday3                        26      // 1 Bit, Bit 5
#define     LOG_fTy1Weekday3Mask 0x20
#define     LOG_fTy1Weekday3Shift 5
#define LOG_fTy1Weekday4                        26      // 1 Bit, Bit 4
#define     LOG_fTy1Weekday4Mask 0x10
#define     LOG_fTy1Weekday4Shift 4
#define LOG_fTy1Weekday5                        26      // 1 Bit, Bit 3
#define     LOG_fTy1Weekday5Mask 0x08
#define     LOG_fTy1Weekday5Shift 3
#define LOG_fTy1Weekday6                        26      // 1 Bit, Bit 2
#define     LOG_fTy1Weekday6Mask 0x04
#define     LOG_fTy1Weekday6Shift 2
#define LOG_fTy1Weekday7                        26      // 1 Bit, Bit 1
#define     LOG_fTy1Weekday7Mask 0x02
#define     LOG_fTy1Weekday7Shift 1
#define LOG_fTy1Day                             26      // 7 Bits, Bit 7-1
#define     LOG_fTy1DayMask 0xFE
#define     LOG_fTy1DayShift 1
#define LOG_fTy1IsWeekday                       26      // 1 Bit, Bit 0
#define     LOG_fTy1IsWeekdayMask 0x01
#define     LOG_fTy1IsWeekdayShift 0
#define LOG_fTy1Month                           27      // 4 Bits, Bit 7-4
#define     LOG_fTy1MonthMask 0xF0
#define     LOG_fTy1MonthShift 4
#define LOG_fTy2Weekday1                        28      // 1 Bit, Bit 7
#define     LOG_fTy2Weekday1Mask 0x80
#define     LOG_fTy2Weekday1Shift 7
#define LOG_fTy2Weekday2                        28      // 1 Bit, Bit 6
#define     LOG_fTy2Weekday2Mask 0x40
#define     LOG_fTy2Weekday2Shift 6
#define LOG_fTy2Weekday3                        28      // 1 Bit, Bit 5
#define     LOG_fTy2Weekday3Mask 0x20
#define     LOG_fTy2Weekday3Shift 5
#define LOG_fTy2Weekday4                        28      // 1 Bit, Bit 4
#define     LOG_fTy2Weekday4Mask 0x10
#define     LOG_fTy2Weekday4Shift 4
#define LOG_fTy2Weekday5                        28      // 1 Bit, Bit 3
#define     LOG_fTy2Weekday5Mask 0x08
#define     LOG_fTy2Weekday5Shift 3
#define LOG_fTy2Weekday6                        28      // 1 Bit, Bit 2
#define     LOG_fTy2Weekday6Mask 0x04
#define     LOG_fTy2Weekday6Shift 2
#define LOG_fTy2Weekday7                        28      // 1 Bit, Bit 1
#define     LOG_fTy2Weekday7Mask 0x02
#define     LOG_fTy2Weekday7Shift 1
#define LOG_fTy2Day                             28      // 7 Bits, Bit 7-1
#define     LOG_fTy2DayMask 0xFE
#define     LOG_fTy2DayShift 1
#define LOG_fTy2IsWeekday                       28      // 1 Bit, Bit 0
#define     LOG_fTy2IsWeekdayMask 0x01
#define     LOG_fTy2IsWeekdayShift 0
#define LOG_fTy2Month                           29      // 4 Bits, Bit 7-4
#define     LOG_fTy2MonthMask 0xF0
#define     LOG_fTy2MonthShift 4
#define LOG_fTy3Weekday1                        30      // 1 Bit, Bit 7
#define     LOG_fTy3Weekday1Mask 0x80
#define     LOG_fTy3Weekday1Shift 7
#define LOG_fTy3Weekday2                        30      // 1 Bit, Bit 6
#define     LOG_fTy3Weekday2Mask 0x40
#define     LOG_fTy3Weekday2Shift 6
#define LOG_fTy3Weekday3                        30      // 1 Bit, Bit 5
#define     LOG_fTy3Weekday3Mask 0x20
#define     LOG_fTy3Weekday3Shift 5
#define LOG_fTy3Weekday4                        30      // 1 Bit, Bit 4
#define     LOG_fTy3Weekday4Mask 0x10
#define     LOG_fTy3Weekday4Shift 4
#define LOG_fTy3Weekday5                        30      // 1 Bit, Bit 3
#define     LOG_fTy3Weekday5Mask 0x08
#define     LOG_fTy3Weekday5Shift 3
#define LOG_fTy3Weekday6                        30      // 1 Bit, Bit 2
#define     LOG_fTy3Weekday6Mask 0x04
#define     LOG_fTy3Weekday6Shift 2
#define LOG_fTy3Weekday7                        30      // 1 Bit, Bit 1
#define     LOG_fTy3Weekday7Mask 0x02
#define     LOG_fTy3Weekday7Shift 1
#define LOG_fTy3Day                             30      // 7 Bits, Bit 7-1
#define     LOG_fTy3DayMask 0xFE
#define     LOG_fTy3DayShift 1
#define LOG_fTy3IsWeekday                       30      // 1 Bit, Bit 0
#define     LOG_fTy3IsWeekdayMask 0x01
#define     LOG_fTy3IsWeekdayShift 0
#define LOG_fTy3Month                           31      // 4 Bits, Bit 7-4
#define     LOG_fTy3MonthMask 0xF0
#define     LOG_fTy3MonthShift 4
#define LOG_fTy4Weekday1                        32      // 1 Bit, Bit 7
#define     LOG_fTy4Weekday1Mask 0x80
#define     LOG_fTy4Weekday1Shift 7
#define LOG_fTy4Weekday2                        32      // 1 Bit, Bit 6
#define     LOG_fTy4Weekday2Mask 0x40
#define     LOG_fTy4Weekday2Shift 6
#define LOG_fTy4Weekday3                        32      // 1 Bit, Bit 5
#define     LOG_fTy4Weekday3Mask 0x20
#define     LOG_fTy4Weekday3Shift 5
#define LOG_fTy4Weekday4                        32      // 1 Bit, Bit 4
#define     LOG_fTy4Weekday4Mask 0x10
#define     LOG_fTy4Weekday4Shift 4
#define LOG_fTy4Weekday5                        32      // 1 Bit, Bit 3
#define     LOG_fTy4Weekday5Mask 0x08
#define     LOG_fTy4Weekday5Shift 3
#define LOG_fTy4Weekday6                        32      // 1 Bit, Bit 2
#define     LOG_fTy4Weekday6Mask 0x04
#define     LOG_fTy4Weekday6Shift 2
#define LOG_fTy4Weekday7                        32      // 1 Bit, Bit 1
#define     LOG_fTy4Weekday7Mask 0x02
#define     LOG_fTy4Weekday7Shift 1
#define LOG_fTy4Day                             32      // 7 Bits, Bit 7-1
#define     LOG_fTy4DayMask 0xFE
#define     LOG_fTy4DayShift 1
#define LOG_fTy4IsWeekday                       32      // 1 Bit, Bit 0
#define     LOG_fTy4IsWeekdayMask 0x01
#define     LOG_fTy4IsWeekdayShift 0
#define LOG_fTy4Month                           33      // 4 Bits, Bit 7-4
#define     LOG_fTy4MonthMask 0xF0
#define     LOG_fTy4MonthShift 4
#define LOG_fI1                                 34      // 4 Bits, Bit 7-4
#define     LOG_fI1Mask 0xF0
#define     LOG_fI1Shift 4
#define LOG_fI2                                 34      // 4 Bits, Bit 3-0
#define     LOG_fI2Mask 0x0F
#define     LOG_fI2Shift 0
#define LOG_fI1Function                         35      // uint8_t
#define LOG_fI2Function                         36      // uint8_t
#define LOG_fOStairtimeBase                     37      // 2 Bits, Bit 7-6
#define     LOG_fOStairtimeBaseMask 0xC0
#define     LOG_fOStairtimeBaseShift 6
#define LOG_fOStairtimeTime                     37      // 14 Bits, Bit 13-0
#define     LOG_fOStairtimeTimeMask 0x3FFF
#define     LOG_fOStairtimeTimeShift 0
#define LOG_fOBlinkBase                         39      // 2 Bits, Bit 7-6
#define     LOG_fOBlinkBaseMask 0xC0
#define     LOG_fOBlinkBaseShift 6
#define LOG_fOBlinkTime                         39      // 14 Bits, Bit 13-0
#define     LOG_fOBlinkTimeMask 0x3FFF
#define     LOG_fOBlinkTimeShift 0
#define LOG_fODelay                             41      // 1 Bit, Bit 7
#define     LOG_fODelayMask 0x80
#define     LOG_fODelayShift 7
#define LOG_fODelayOnRepeat                     41      // 2 Bits, Bit 6-5
#define     LOG_fODelayOnRepeatMask 0x60
#define     LOG_fODelayOnRepeatShift 5
#define LOG_fODelayOnReset                      41      // 1 Bit, Bit 4
#define     LOG_fODelayOnResetMask 0x10
#define     LOG_fODelayOnResetShift 4
#define LOG_fODelayOffRepeat                    41      // 2 Bits, Bit 3-2
#define     LOG_fODelayOffRepeatMask 0x0C
#define     LOG_fODelayOffRepeatShift 2
#define LOG_fODelayOffReset                     41      // 1 Bit, Bit 1
#define     LOG_fODelayOffResetMask 0x02
#define     LOG_fODelayOffResetShift 1
#define LOG_fODelayOnBase                       42      // 2 Bits, Bit 7-6
#define     LOG_fODelayOnBaseMask 0xC0
#define     LOG_fODelayOnBaseShift 6
#define LOG_fODelayOnTime                       42      // 14 Bits, Bit 13-0
#define     LOG_fODelayOnTimeMask 0x3FFF
#define     LOG_fODelayOnTimeShift 0
#define LOG_fODelayOffBase                      44      // 2 Bits, Bit 7-6
#define     LOG_fODelayOffBaseMask 0xC0
#define     LOG_fODelayOffBaseShift 6
#define LOG_fODelayOffTime                      44      // 14 Bits, Bit 13-0
#define     LOG_fODelayOffTimeMask 0x3FFF
#define     LOG_fODelayOffTimeShift 0
#define LOG_fOStair                             46      // 1 Bit, Bit 7
#define     LOG_fOStairMask 0x80
#define     LOG_fOStairShift 7
#define LOG_fORetrigger                         46      // 1 Bit, Bit 6
#define     LOG_fORetriggerMask 0x40
#define     LOG_fORetriggerShift 6
#define LOG_fOStairOff                          46      // 1 Bit, Bit 5
#define     LOG_fOStairOffMask 0x20
#define     LOG_fOStairOffShift 5
#define LOG_fORepeat                            46      // 1 Bit, Bit 4
#define     LOG_fORepeatMask 0x10
#define     LOG_fORepeatShift 4
#define LOG_fOOutputFilter                      46      // 2 Bits, Bit 3-2
#define     LOG_fOOutputFilterMask 0x0C
#define     LOG_fOOutputFilterShift 2
#define LOG_fORepeatOnBase                      47      // 2 Bits, Bit 7-6
#define     LOG_fORepeatOnBaseMask 0xC0
#define     LOG_fORepeatOnBaseShift 6
#define LOG_fORepeatOnTime                      47      // 14 Bits, Bit 13-0
#define     LOG_fORepeatOnTimeMask 0x3FFF
#define     LOG_fORepeatOnTimeShift 0
#define LOG_fORepeatOffBase                     49      // 2 Bits, Bit 7-6
#define     LOG_fORepeatOffBaseMask 0xC0
#define     LOG_fORepeatOffBaseShift 6
#define LOG_fORepeatOffTime                     49      // 14 Bits, Bit 13-0
#define     LOG_fORepeatOffTimeMask 0x3FFF
#define     LOG_fORepeatOffTimeShift 0
#define LOG_fODpt                               51      // 8 Bits, Bit 7-0
#define LOG_fOOn                                52      // 8 Bits, Bit 7-0
#define LOG_fOOnBuzzer                          52      // 8 Bits, Bit 7-0
#define LOG_fOOnLed                             52      // 8 Bits, Bit 7-0
#define LOG_fOOnAll                             52      // 8 Bits, Bit 7-0
#define LOG_fOOnTone                            53      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt1                            53      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt2                            53      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt5                            53      // uint8_t
#define LOG_fOOnDpt5001                         53      // uint8_t
#define LOG_fOOnDpt6                            53      // int8_t
#define LOG_fOOnDpt7                            53      // uint16_t
#define LOG_fOOnDpt8                            53      // int16_t
#define LOG_fOOnDpt9                            53      // float
#define LOG_fOOnDpt12                           53      // uint32_t
#define LOG_fOOnDpt13                           53      // int32_t
#define LOG_fOOnDpt14                           53      // float
#define LOG_fOOnDpt16                           53      // char*, 14 Byte
#define LOG_fOOnDpt17                           53      // 8 Bits, Bit 7-0
#define LOG_fOOnRGB                             53      // 24 Bits, Bit 31-8
#define     LOG_fOOnRGBMask 0xFFFFFF00
#define     LOG_fOOnRGBShift 8
#define LOG_fOOnPAArea                          53      // 4 Bits, Bit 7-4
#define     LOG_fOOnPAAreaMask 0xF0
#define     LOG_fOOnPAAreaShift 4
#define LOG_fOOnPALine                          53      // 4 Bits, Bit 3-0
#define     LOG_fOOnPALineMask 0x0F
#define     LOG_fOOnPALineShift 0
#define LOG_fOOnPADevice                        54      // uint8_t
#define LOG_fOOnFunction                        53      // 8 Bits, Bit 7-0
#define LOG_fOOnKONumber                        53      // 15 Bits, Bit 15-1
#define     LOG_fOOnKONumberMask 0xFFFE
#define     LOG_fOOnKONumberShift 1
#define LOG_fOOnKODpt                           55      // 8 Bits, Bit 7-0
#define LOG_fOOff                               67      // 8 Bits, Bit 7-0
#define LOG_fOOffBuzzer                         67      // 8 Bits, Bit 7-0
#define LOG_fOOffLed                            67      // 8 Bits, Bit 7-0
#define LOG_fOOffAll                            67      // 8 Bits, Bit 7-0
#define LOG_fOOffTone                           68      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt1                           68      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt2                           68      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt5                           68      // uint8_t
#define LOG_fOOffDpt5001                        68      // uint8_t
#define LOG_fOOffDpt6                           68      // int8_t
#define LOG_fOOffDpt7                           68      // uint16_t
#define LOG_fOOffDpt8                           68      // int16_t
#define LOG_fOOffDpt9                           68      // float
#define LOG_fOOffDpt12                          68      // uint32_t
#define LOG_fOOffDpt13                          68      // int32_t
#define LOG_fOOffDpt14                          68      // float
#define LOG_fOOffDpt16                          68      // char*, 14 Byte
#define LOG_fOOffDpt17                          68      // 8 Bits, Bit 7-0
#define LOG_fOOffRGB                            68      // 24 Bits, Bit 31-8
#define     LOG_fOOffRGBMask 0xFFFFFF00
#define     LOG_fOOffRGBShift 8
#define LOG_fOOffPAArea                         68      // 4 Bits, Bit 7-4
#define     LOG_fOOffPAAreaMask 0xF0
#define     LOG_fOOffPAAreaShift 4
#define LOG_fOOffPALine                         68      // 4 Bits, Bit 3-0
#define     LOG_fOOffPALineMask 0x0F
#define     LOG_fOOffPALineShift 0
#define LOG_fOOffPADevice                       69      // uint8_t
#define LOG_fOOffFunction                       68      // 8 Bits, Bit 7-0
#define LOG_fOOffKONumber                       68      // 15 Bits, Bit 15-1
#define     LOG_fOOffKONumberMask 0xFFFE
#define     LOG_fOOffKONumberShift 1
#define LOG_fOOffKODpt                          70      // 8 Bits, Bit 7-0
#define LOG_fE1UseOtherKO                       82      // 1 Bit, Bit 7
#define     LOG_fE1UseOtherKOMask 0x80
#define     LOG_fE1UseOtherKOShift 7
#define LOG_fE1OtherKO                          82      // 15 Bits, Bit 14-0
#define     LOG_fE1OtherKOMask 0x7FFF
#define     LOG_fE1OtherKOShift 0
#define LOG_fE2UseOtherKO                       84      // 1 Bit, Bit 7
#define     LOG_fE2UseOtherKOMask 0x80
#define     LOG_fE2UseOtherKOShift 7
#define LOG_fE2OtherKO                          84      // 15 Bits, Bit 14-0
#define     LOG_fE2OtherKOMask 0x7FFF
#define     LOG_fE2OtherKOShift 0

// Zeit bis der Kanal nach einem Neustart aktiv wird
#define ParamLOG_fChannelDelayBase                   ((knx.paramByte(LOG_ParamCalcIndex(LOG_fChannelDelayBase)) & LOG_fChannelDelayBaseMask) >> LOG_fChannelDelayBaseShift)
// Zeit bis der Kanal nach einem Neustart aktiv wird
#define ParamLOG_fChannelDelayTime                   (knx.paramWord(LOG_ParamCalcIndex(LOG_fChannelDelayTime)) & LOG_fChannelDelayTimeMask)
// Zeit bis der Kanal nach einem Neustart aktiv wird (in Millisekunden)
#define ParamLOG_fChannelDelayTimeMS                 (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fChannelDelayTime))))
// Logik-Operation
#define ParamLOG_fLogic                              (knx.paramByte(LOG_ParamCalcIndex(LOG_fLogic)))
// Logik auswerten
#define ParamLOG_fCalculate                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fCalculate)) & LOG_fCalculateMask)
// Kanal deaktivieren (zu Testzwecken)
#define ParamLOG_fDisable                            ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fDisable)) & LOG_fDisableMask))
// Alarmausgabe (Buzzer oder LED trotz Sperre schalten)?
#define ParamLOG_fAlarm                              ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fAlarm)) & LOG_fAlarmMask))
// Tor geht sofort wieder zu
#define ParamLOG_fTGate                              ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTGate)) & LOG_fTGateMask))
// Wert EIN intern weiterleiten
#define ParamLOG_fOInternalOn                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fOInternalOn)) & LOG_fOInternalOnMask))
// Wert AUS intern weiterleiten
#define ParamLOG_fOInternalOff                       ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fOInternalOff)) & LOG_fOInternalOffMask))
// Logik sendet ihren Wert weiter
#define ParamLOG_fTrigger                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fTrigger)))
//           Eingang 1
#define ParamLOG_fTriggerE1                          ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerE1)) & LOG_fTriggerE1Mask))
//           Eingang 2
#define ParamLOG_fTriggerE2                          ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerE2)) & LOG_fTriggerE2Mask))
//           Interner Eingang 3
#define ParamLOG_fTriggerI1                          ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerI1)) & LOG_fTriggerI1Mask))
//           Interner Eingang 4
#define ParamLOG_fTriggerI2                          ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerI2)) & LOG_fTriggerI2Mask))
// Logik sendet ihren Wert weiter
#define ParamLOG_fTriggerTime                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerTime)))
// Beim schließen vom Tor wird
#define ParamLOG_fTriggerGateClose                   ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerGateClose)) & LOG_fTriggerGateCloseMask) >> LOG_fTriggerGateCloseShift)
// Beim öffnen vom Tor wird
#define ParamLOG_fTriggerGateOpen                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerGateOpen)) & LOG_fTriggerGateOpenMask) >> LOG_fTriggerGateOpenShift)
// Eingang 1
#define ParamLOG_fE1                                 (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1)) & LOG_fE1Mask)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE1Convert                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Convert)) & LOG_fE1ConvertMask) >> LOG_fE1ConvertShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE1ConvertFloat                     ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1ConvertFloat)) & LOG_fE1ConvertFloatMask) >> LOG_fE1ConvertFloatShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE1ConvertSpecial                   ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1ConvertSpecial)) & LOG_fE1ConvertSpecialMask) >> LOG_fE1ConvertSpecialShift)
// DPT für Eingang
#define ParamLOG_fE1Dpt                              (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Dpt)))
// Falls Vorbelegung aus dem Speicher nicht möglich oder nicht gewünscht, dann vorbelegen mit
#define ParamLOG_fE1Default                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Default)) & LOG_fE1DefaultMask)
// Eingang vorbelegen mit
#define ParamLOG_fE1DefaultExt                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1DefaultExt)) & LOG_fE1DefaultExtMask)
// Eingangswert speichern und beim nächsten Neustart als Vorbelegung nutzen?
#define ParamLOG_fE1DefaultEEPROM                    ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1DefaultEEPROM)) & LOG_fE1DefaultEEPROMMask))
// Nur so lange zyklisch lesen, bis erstes Telegramm eingeht
#define ParamLOG_fE1DefaultRepeat                    ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1DefaultRepeat)) & LOG_fE1DefaultRepeatMask))
// Typ der Zeitschaltuhr
#define ParamLOG_fTYearDay                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTYearDay)) & LOG_fTYearDayMask))
// Bei Neustart letzte Schaltzeit nachholen
#define ParamLOG_fTRestoreState                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTRestoreState)) & LOG_fTRestoreStateMask) >> LOG_fTRestoreStateShift)
// Eingang wird gelesen alle
#define ParamLOG_fE1RepeatBase                       ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1RepeatBase)) & LOG_fE1RepeatBaseMask) >> LOG_fE1RepeatBaseShift)
// Eingang wird gelesen alle
#define ParamLOG_fE1RepeatTime                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1RepeatTime)) & LOG_fE1RepeatTimeMask)
// Eingang wird gelesen alle (in Millisekunden)
#define ParamLOG_fE1RepeatTimeMS                     (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fE1RepeatTime))))
// Eingang 2
#define ParamLOG_fE2                                 (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2)) & LOG_fE2Mask)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE2Convert                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Convert)) & LOG_fE2ConvertMask) >> LOG_fE2ConvertShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE2ConvertFloat                     ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2ConvertFloat)) & LOG_fE2ConvertFloatMask) >> LOG_fE2ConvertFloatShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE2ConvertSpecial                   ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2ConvertSpecial)) & LOG_fE2ConvertSpecialMask) >> LOG_fE2ConvertSpecialShift)
// DPT für Eingang
#define ParamLOG_fE2Dpt                              (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Dpt)))
// Falls Vorbelegung aus dem Speicher nicht möglich oder nicht gewünscht, dann vorbelegen mit
#define ParamLOG_fE2Default                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Default)) & LOG_fE2DefaultMask)
// Eingang vorbelegen mit
#define ParamLOG_fE2DefaultExt                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2DefaultExt)) & LOG_fE2DefaultExtMask)
// Eingangswert speichern und beim nächsten Neustart als Vorbelegung nutzen?
#define ParamLOG_fE2DefaultEEPROM                    ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2DefaultEEPROM)) & LOG_fE2DefaultEEPROMMask))
// Nur so lange zyklisch lesen, bis erstes Telegramm eingeht
#define ParamLOG_fE2DefaultRepeat                    ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2DefaultRepeat)) & LOG_fE2DefaultRepeatMask))
// Feiertagsbehandlung
#define ParamLOG_fTHoliday                           ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTHoliday)) & LOG_fTHolidayMask) >> LOG_fTHolidayShift)
// Urlaubsbehandlung
#define ParamLOG_fTVacation                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTVacation)) & LOG_fTVacationMask) >> LOG_fTVacationShift)
// Eingang wird gelesen alle
#define ParamLOG_fE2RepeatBase                       ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2RepeatBase)) & LOG_fE2RepeatBaseMask) >> LOG_fE2RepeatBaseShift)
// Eingang wird gelesen alle
#define ParamLOG_fE2RepeatTime                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2RepeatTime)) & LOG_fE2RepeatTimeMask)
// Eingang wird gelesen alle (in Millisekunden)
#define ParamLOG_fE2RepeatTimeMS                     (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fE2RepeatTime))))
// Zeitbezug
#define ParamLOG_fTd1DuskDawn                        ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1DuskDawn)) & LOG_fTd1DuskDawnMask) >> LOG_fTd1DuskDawnShift)
// Zeitbezug
#define ParamLOG_fTd2DuskDawn                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2DuskDawn)) & LOG_fTd2DuskDawnMask)
// Zeitbezug
#define ParamLOG_fTd3DuskDawn                        ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3DuskDawn)) & LOG_fTd3DuskDawnMask) >> LOG_fTd3DuskDawnShift)
// Zeitbezug
#define ParamLOG_fTd4DuskDawn                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4DuskDawn)) & LOG_fTd4DuskDawnMask)
// Zeitbezug
#define ParamLOG_fTd5DuskDawn                        ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5DuskDawn)) & LOG_fTd5DuskDawnMask) >> LOG_fTd5DuskDawnShift)
// Zeitbezug
#define ParamLOG_fTd6DuskDawn                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6DuskDawn)) & LOG_fTd6DuskDawnMask)
// Zeitbezug
#define ParamLOG_fTd7DuskDawn                        ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7DuskDawn)) & LOG_fTd7DuskDawnMask) >> LOG_fTd7DuskDawnShift)
// Zeitbezug
#define ParamLOG_fTd8DuskDawn                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8DuskDawn)) & LOG_fTd8DuskDawnMask)
// Von-Wert
#define ParamLOG_fE1LowDelta                         ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDelta)))
// Bis-Wert
#define ParamLOG_fE1HighDelta                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1HighDelta)))
// Von-Wert
#define ParamLOG_fE1LowDeltaFloat                    (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDeltaFloat), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE1HighDeltaFloat                   (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1HighDeltaFloat), Float_Enc_IEEE754Single))
// Von-Wert
#define ParamLOG_fE1LowDeltaDouble                   (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDeltaDouble), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE1HighDeltaDouble                  (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1HighDeltaDouble), Float_Enc_IEEE754Single))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low0Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Valid)) & LOG_fE1Low0ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low1Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Valid)) & LOG_fE1Low1ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low2Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Valid)) & LOG_fE1Low2ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low3Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Valid)) & LOG_fE1Low3ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low4Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low4Valid)) & LOG_fE1Low4ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low5Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low5Valid)) & LOG_fE1Low5ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low6Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low6Valid)) & LOG_fE1Low6ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low7Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low7Valid)) & LOG_fE1Low7ValidMask))
// Eingang ist EIN, wenn Wert gleich
#define ParamLOG_fE1LowDpt2                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE1Low1Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Dpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE1Low2Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Dpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE1Low3Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Dpt2)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt2Fix                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt2Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt5                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt5)))
// Bis-Wert
#define ParamLOG_fE1HighDpt5                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1HighDpt5)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE1Low0Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low1Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low2Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low3Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low4Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low4Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low5Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low5Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low6Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low6Dpt5In)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt5Fix                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt5Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt5001                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt5001)))
// Bis-Wert
#define ParamLOG_fE1HighDpt5001                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1HighDpt5001)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE1Low0Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low1Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low2Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low3Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low4Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low4Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low5Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low5Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low6Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low6Dpt5xIn)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt5xFix                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt5xFix)))
// Von-Wert
#define ParamLOG_fE1LowDpt6                          ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt6)))
// Bis-Wert
#define ParamLOG_fE1HighDpt6                         ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1HighDpt6)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE1Low0Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low1Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low2Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low3Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low4Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low4Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low5Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low5Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low6Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low6Dpt6In)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt6Fix                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt6Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt7                          (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1LowDpt7)))
// Bis-Wert
#define ParamLOG_fE1HighDpt7                         (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1HighDpt7)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE1Low0Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low0Dpt7In)))
// ... oder bei Wert
#define ParamLOG_fE1Low1Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low1Dpt7In)))
// ... oder bei Wert
#define ParamLOG_fE1Low2Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low2Dpt7In)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt7Fix                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1LowDpt7Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt8                          ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1LowDpt8)))
// Bis-Wert
#define ParamLOG_fE1HighDpt8                         ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1HighDpt8)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE1Low0Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low0Dpt8In)))
// ... oder bei Wert
#define ParamLOG_fE1Low1Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low1Dpt8In)))
// ... oder bei Wert
#define ParamLOG_fE1Low2Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low2Dpt8In)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt8Fix                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1LowDpt8Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt9                          (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDpt9), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE1HighDpt9                         (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1HighDpt9), Float_Enc_IEEE754Single))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt9Fix                       (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDpt9Fix), Float_Enc_IEEE754Single))
// Von-Wert
#define ParamLOG_fE1LowDpt12                         (knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDpt12)))
// Bis-Wert
#define ParamLOG_fE1HighDpt12                        (knx.paramInt(LOG_ParamCalcIndex(LOG_fE1HighDpt12)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt12Fix                      (knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDpt12Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt13                         ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDpt13)))
// Bis-Wert
#define ParamLOG_fE1HighDpt13                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1HighDpt13)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt13Fix                      ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDpt13Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt14                         (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDpt14), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE1HighDpt14                        (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1HighDpt14), Float_Enc_IEEE754Single))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt14Fix                      (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDpt14Fix), Float_Enc_IEEE754Single))
// Eingang ist EIN bei Szene
#define ParamLOG_fE1Low0Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low1Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low2Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low3Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low4Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low4Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low5Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low5Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low6Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low6Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low7Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low7Dpt17)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt17Fix                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt17Fix)))
// Von-Wert
#define ParamLOG_fE1LowDptRGB                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDptRGB)))
// Bis-Wert
#define ParamLOG_fE1HighDptRGB                       ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1HighDptRGB)))
// Eingang ist konstant
#define ParamLOG_fE1LowDptRGBFix                     ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDptRGBFix)))
// Von-Wert
#define ParamLOG_fE2LowDelta                         ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDelta)))
// Bis-Wert
#define ParamLOG_fE2HighDelta                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2HighDelta)))
// Von-Wert
#define ParamLOG_fE2LowDeltaFloat                    (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDeltaFloat), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE2HighDeltaFloat                   (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2HighDeltaFloat), Float_Enc_IEEE754Single))
// Von-Wert
#define ParamLOG_fE2LowDeltaDouble                   (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDeltaDouble), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE2HighDeltaDouble                  (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2HighDeltaDouble), Float_Enc_IEEE754Single))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low0Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Valid)) & LOG_fE2Low0ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low1Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Valid)) & LOG_fE2Low1ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low2Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Valid)) & LOG_fE2Low2ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low3Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Valid)) & LOG_fE2Low3ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low4Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low4Valid)) & LOG_fE2Low4ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low5Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low5Valid)) & LOG_fE2Low5ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low6Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low6Valid)) & LOG_fE2Low6ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low7Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low7Valid)) & LOG_fE2Low7ValidMask))
// Eingang ist EIN, wenn Wert gleich 
#define ParamLOG_fE2Low0Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Dpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE2Low1Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Dpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE2Low2Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Dpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE2Low3Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Dpt2)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt2Fix                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt2Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt5                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt5)))
// Bis-Wert
#define ParamLOG_fE2HighDpt5                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2HighDpt5)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE2Low0Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low1Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low2Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low3Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low4Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low4Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low5Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low5Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low6Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low6Dpt5In)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt5Fix                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt5Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt5001                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt5001)))
// Bis-Wert
#define ParamLOG_fE2HighDpt5001                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2HighDpt5001)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE2Low0Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low1Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low2Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low3Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low4Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low4Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low5Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low5Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low6Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low6Dpt5xIn)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt5xFix                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt5xFix)))
// Von-Wert
#define ParamLOG_fE2LowDpt6                          ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt6)))
// Bis-Wert
#define ParamLOG_fE2HighDpt6                         ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2HighDpt6)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE2Low0Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low1Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low2Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low3Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low4Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low4Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low5Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low5Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low6Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low6Dpt6In)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt6Fix                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt6Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt7                          (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2LowDpt7)))
// Bis-Wert
#define ParamLOG_fE2HighDpt7                         (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2HighDpt7)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE2Low0Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low0Dpt7In)))
// ... oder bei Wert
#define ParamLOG_fE2Low1Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low1Dpt7In)))
// ... oder bei Wert
#define ParamLOG_fE2Low2Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low2Dpt7In)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt7Fix                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2LowDpt7Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt8                          ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2LowDpt8)))
// Bis-Wert
#define ParamLOG_fE2HighDpt8                         ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2HighDpt8)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE2Low0Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low0Dpt8In)))
// ... oder bei Wert
#define ParamLOG_fE2Low1Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low1Dpt8In)))
// ... oder bei Wert
#define ParamLOG_fE2Low2Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low2Dpt8In)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt8Fix                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2LowDpt8Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt9                          (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDpt9), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE2HighDpt9                         (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2HighDpt9), Float_Enc_IEEE754Single))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt9Fix                       (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDpt9Fix), Float_Enc_IEEE754Single))
// Von-Wert
#define ParamLOG_fE2LowDpt12                         (knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDpt12)))
// Bis-Wert
#define ParamLOG_fE2HighDpt12                        (knx.paramInt(LOG_ParamCalcIndex(LOG_fE2HighDpt12)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt12Fix                      (knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDpt12Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt13                         ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDpt13)))
// Bis-Wert
#define ParamLOG_fE2HighDpt13                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2HighDpt13)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt13Fix                      ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDpt13Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt14                         (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDpt14), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE2HighDpt14                        (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2HighDpt14), Float_Enc_IEEE754Single))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt14Fix                      (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDpt14Fix), Float_Enc_IEEE754Single))
// Eingang ist EIN bei Szene
#define ParamLOG_fE2Low0Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low1Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low2Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low3Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low4Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low4Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low5Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low5Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low6Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low6Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low7Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low7Dpt17)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt17Fix                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt17Fix)))
// Von-Wert
#define ParamLOG_fE2LowDptRGB                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDptRGB)))
// Bis-Wert
#define ParamLOG_fE2HighDptRGB                       ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2HighDptRGB)))
// Eingang ist konstant
#define ParamLOG_fE2LowDptRGBFix                     ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDptRGBFix)))
// Schaltwert
#define ParamLOG_fTd1Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1Value)) & LOG_fTd1ValueMask))
// Grad
#define ParamLOG_fTd1Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1Degree)) & LOG_fTd1DegreeMask) >> LOG_fTd1DegreeShift)
// Stunde
#define ParamLOG_fTd1HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1HourAbs)) & LOG_fTd1HourAbsMask) >> LOG_fTd1HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd1HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1HourRel)) & LOG_fTd1HourRelMask) >> LOG_fTd1HourRelShift)
// Minute
#define ParamLOG_fTd1MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1MinuteAbs)))
// Minute
#define ParamLOG_fTd1MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1MinuteRel)))
// Wochentag
#define ParamLOG_fTd1Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1Weekday)) & LOG_fTd1WeekdayMask)
// Schaltwert
#define ParamLOG_fTd2Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2Value)) & LOG_fTd2ValueMask))
// Grad
#define ParamLOG_fTd2Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2Degree)) & LOG_fTd2DegreeMask) >> LOG_fTd2DegreeShift)
// Stunde
#define ParamLOG_fTd2HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2HourAbs)) & LOG_fTd2HourAbsMask) >> LOG_fTd2HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd2HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2HourRel)) & LOG_fTd2HourRelMask) >> LOG_fTd2HourRelShift)
// Minute
#define ParamLOG_fTd2MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2MinuteAbs)))
// Minute
#define ParamLOG_fTd2MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2MinuteRel)))
// Wochentag
#define ParamLOG_fTd2Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2Weekday)) & LOG_fTd2WeekdayMask)
// Schaltwert
#define ParamLOG_fTd3Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3Value)) & LOG_fTd3ValueMask))
// Grad
#define ParamLOG_fTd3Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3Degree)) & LOG_fTd3DegreeMask) >> LOG_fTd3DegreeShift)
// Stunde
#define ParamLOG_fTd3HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3HourAbs)) & LOG_fTd3HourAbsMask) >> LOG_fTd3HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd3HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3HourRel)) & LOG_fTd3HourRelMask) >> LOG_fTd3HourRelShift)
// Minute
#define ParamLOG_fTd3MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3MinuteAbs)))
// Minute
#define ParamLOG_fTd3MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3MinuteRel)))
// Wochentag
#define ParamLOG_fTd3Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3Weekday)) & LOG_fTd3WeekdayMask)
// Schaltwert
#define ParamLOG_fTd4Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4Value)) & LOG_fTd4ValueMask))
// Grad
#define ParamLOG_fTd4Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4Degree)) & LOG_fTd4DegreeMask) >> LOG_fTd4DegreeShift)
// Stunde
#define ParamLOG_fTd4HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4HourAbs)) & LOG_fTd4HourAbsMask) >> LOG_fTd4HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd4HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4HourRel)) & LOG_fTd4HourRelMask) >> LOG_fTd4HourRelShift)
// Minute
#define ParamLOG_fTd4MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4MinuteAbs)))
// Minute
#define ParamLOG_fTd4MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4MinuteRel)))
// Wochentag
#define ParamLOG_fTd4Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4Weekday)) & LOG_fTd4WeekdayMask)
// Schaltwert
#define ParamLOG_fTd5Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5Value)) & LOG_fTd5ValueMask))
// Grad
#define ParamLOG_fTd5Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5Degree)) & LOG_fTd5DegreeMask) >> LOG_fTd5DegreeShift)
// Stunde
#define ParamLOG_fTd5HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5HourAbs)) & LOG_fTd5HourAbsMask) >> LOG_fTd5HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd5HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5HourRel)) & LOG_fTd5HourRelMask) >> LOG_fTd5HourRelShift)
// Minute
#define ParamLOG_fTd5MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5MinuteAbs)))
// Minute
#define ParamLOG_fTd5MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5MinuteRel)))
// Wochentag
#define ParamLOG_fTd5Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5Weekday)) & LOG_fTd5WeekdayMask)
// Schaltwert
#define ParamLOG_fTd6Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6Value)) & LOG_fTd6ValueMask))
// Grad
#define ParamLOG_fTd6Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6Degree)) & LOG_fTd6DegreeMask) >> LOG_fTd6DegreeShift)
// Stunde
#define ParamLOG_fTd6HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6HourAbs)) & LOG_fTd6HourAbsMask) >> LOG_fTd6HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd6HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6HourRel)) & LOG_fTd6HourRelMask) >> LOG_fTd6HourRelShift)
// Minute
#define ParamLOG_fTd6MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6MinuteAbs)))
// Minute
#define ParamLOG_fTd6MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6MinuteRel)))
// Wochentag
#define ParamLOG_fTd6Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6Weekday)) & LOG_fTd6WeekdayMask)
// Schaltwert
#define ParamLOG_fTd7Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7Value)) & LOG_fTd7ValueMask))
// Grad
#define ParamLOG_fTd7Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7Degree)) & LOG_fTd7DegreeMask) >> LOG_fTd7DegreeShift)
// Stunde
#define ParamLOG_fTd7HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7HourAbs)) & LOG_fTd7HourAbsMask) >> LOG_fTd7HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd7HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7HourRel)) & LOG_fTd7HourRelMask) >> LOG_fTd7HourRelShift)
// Minute
#define ParamLOG_fTd7MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7MinuteAbs)))
// Minute
#define ParamLOG_fTd7MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7MinuteRel)))
// Wochentag
#define ParamLOG_fTd7Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7Weekday)) & LOG_fTd7WeekdayMask)
// Schaltwert
#define ParamLOG_fTd8Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8Value)) & LOG_fTd8ValueMask))
// Grad
#define ParamLOG_fTd8Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8Degree)) & LOG_fTd8DegreeMask) >> LOG_fTd8DegreeShift)
// Stunde
#define ParamLOG_fTd8HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8HourAbs)) & LOG_fTd8HourAbsMask) >> LOG_fTd8HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd8HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8HourRel)) & LOG_fTd8HourRelMask) >> LOG_fTd8HourRelShift)
// Minute
#define ParamLOG_fTd8MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8MinuteAbs)))
// Minute
#define ParamLOG_fTd8MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8MinuteRel)))
// Wochentag
#define ParamLOG_fTd8Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8Weekday)) & LOG_fTd8WeekdayMask)
// Mo
#define ParamLOG_fTy1Weekday1                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday1)) & LOG_fTy1Weekday1Mask))
// Di
#define ParamLOG_fTy1Weekday2                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday2)) & LOG_fTy1Weekday2Mask))
// Mi
#define ParamLOG_fTy1Weekday3                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday3)) & LOG_fTy1Weekday3Mask))
// Do
#define ParamLOG_fTy1Weekday4                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday4)) & LOG_fTy1Weekday4Mask))
// Fr
#define ParamLOG_fTy1Weekday5                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday5)) & LOG_fTy1Weekday5Mask))
// Sa
#define ParamLOG_fTy1Weekday6                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday6)) & LOG_fTy1Weekday6Mask))
// So
#define ParamLOG_fTy1Weekday7                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday7)) & LOG_fTy1Weekday7Mask))
// Tag
#define ParamLOG_fTy1Day                             ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Day)) & LOG_fTy1DayMask) >> LOG_fTy1DayShift)
// Wochentag
#define ParamLOG_fTy1IsWeekday                       ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1IsWeekday)) & LOG_fTy1IsWeekdayMask))
// Monat
#define ParamLOG_fTy1Month                           ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Month)) & LOG_fTy1MonthMask) >> LOG_fTy1MonthShift)
// Mo
#define ParamLOG_fTy2Weekday1                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday1)) & LOG_fTy2Weekday1Mask))
// Di
#define ParamLOG_fTy2Weekday2                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday2)) & LOG_fTy2Weekday2Mask))
// Mi
#define ParamLOG_fTy2Weekday3                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday3)) & LOG_fTy2Weekday3Mask))
// Do
#define ParamLOG_fTy2Weekday4                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday4)) & LOG_fTy2Weekday4Mask))
// Fr
#define ParamLOG_fTy2Weekday5                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday5)) & LOG_fTy2Weekday5Mask))
// Sa
#define ParamLOG_fTy2Weekday6                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday6)) & LOG_fTy2Weekday6Mask))
// So
#define ParamLOG_fTy2Weekday7                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday7)) & LOG_fTy2Weekday7Mask))
// Tag
#define ParamLOG_fTy2Day                             ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Day)) & LOG_fTy2DayMask) >> LOG_fTy2DayShift)
// Wochentag
#define ParamLOG_fTy2IsWeekday                       ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2IsWeekday)) & LOG_fTy2IsWeekdayMask))
// Monat
#define ParamLOG_fTy2Month                           ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Month)) & LOG_fTy2MonthMask) >> LOG_fTy2MonthShift)
// Mo
#define ParamLOG_fTy3Weekday1                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday1)) & LOG_fTy3Weekday1Mask))
// Di
#define ParamLOG_fTy3Weekday2                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday2)) & LOG_fTy3Weekday2Mask))
// Mi
#define ParamLOG_fTy3Weekday3                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday3)) & LOG_fTy3Weekday3Mask))
// Do
#define ParamLOG_fTy3Weekday4                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday4)) & LOG_fTy3Weekday4Mask))
// Fr
#define ParamLOG_fTy3Weekday5                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday5)) & LOG_fTy3Weekday5Mask))
// Sa
#define ParamLOG_fTy3Weekday6                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday6)) & LOG_fTy3Weekday6Mask))
// So
#define ParamLOG_fTy3Weekday7                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday7)) & LOG_fTy3Weekday7Mask))
// Tag
#define ParamLOG_fTy3Day                             ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Day)) & LOG_fTy3DayMask) >> LOG_fTy3DayShift)
// Wochentag
#define ParamLOG_fTy3IsWeekday                       ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3IsWeekday)) & LOG_fTy3IsWeekdayMask))
// Monat
#define ParamLOG_fTy3Month                           ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Month)) & LOG_fTy3MonthMask) >> LOG_fTy3MonthShift)
// Mo
#define ParamLOG_fTy4Weekday1                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday1)) & LOG_fTy4Weekday1Mask))
// Di
#define ParamLOG_fTy4Weekday2                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday2)) & LOG_fTy4Weekday2Mask))
// Mi
#define ParamLOG_fTy4Weekday3                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday3)) & LOG_fTy4Weekday3Mask))
// Do
#define ParamLOG_fTy4Weekday4                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday4)) & LOG_fTy4Weekday4Mask))
// Fr
#define ParamLOG_fTy4Weekday5                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday5)) & LOG_fTy4Weekday5Mask))
// Sa
#define ParamLOG_fTy4Weekday6                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday6)) & LOG_fTy4Weekday6Mask))
// So
#define ParamLOG_fTy4Weekday7                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday7)) & LOG_fTy4Weekday7Mask))
// Tag
#define ParamLOG_fTy4Day                             ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Day)) & LOG_fTy4DayMask) >> LOG_fTy4DayShift)
// Wochentag
#define ParamLOG_fTy4IsWeekday                       ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4IsWeekday)) & LOG_fTy4IsWeekdayMask))
// Monat
#define ParamLOG_fTy4Month                           ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Month)) & LOG_fTy4MonthMask) >> LOG_fTy4MonthShift)
// Interner Eingang 3
#define ParamLOG_fI1                                 ((knx.paramByte(LOG_ParamCalcIndex(LOG_fI1)) & LOG_fI1Mask) >> LOG_fI1Shift)
// Interner Eingang 4
#define ParamLOG_fI2                                 (knx.paramByte(LOG_ParamCalcIndex(LOG_fI2)) & LOG_fI2Mask)
// Internen Eingang verbinden mit Kanalausgang Nr.:
#define ParamLOG_fI1Function                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fI1Function)))
// Internen Eingang verbinden mit Kanalausgang Nr.:
#define ParamLOG_fI2Function                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fI2Function)))
// Zeit für Treppenlicht
#define ParamLOG_fOStairtimeBase                     ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOStairtimeBase)) & LOG_fOStairtimeBaseMask) >> LOG_fOStairtimeBaseShift)
// Zeit für Treppenlicht
#define ParamLOG_fOStairtimeTime                     (knx.paramWord(LOG_ParamCalcIndex(LOG_fOStairtimeTime)) & LOG_fOStairtimeTimeMask)
// Zeit für Treppenlicht (in Millisekunden)
#define ParamLOG_fOStairtimeTimeMS                   (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fOStairtimeTime))))
// Treppenlicht blinkt im Rhythmus
#define ParamLOG_fOBlinkBase                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOBlinkBase)) & LOG_fOBlinkBaseMask) >> LOG_fOBlinkBaseShift)
// Treppenlicht blinkt im Rhythmus
#define ParamLOG_fOBlinkTime                         (knx.paramWord(LOG_ParamCalcIndex(LOG_fOBlinkTime)) & LOG_fOBlinkTimeMask)
// Treppenlicht blinkt im Rhythmus (in Millisekunden)
#define ParamLOG_fOBlinkTimeMS                       (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fOBlinkTime))))
// Ausgang schaltet zeitverzögert
#define ParamLOG_fODelay                             ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fODelay)) & LOG_fODelayMask))
// Erneutes EIN führt zu
#define ParamLOG_fODelayOnRepeat                     ((knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOnRepeat)) & LOG_fODelayOnRepeatMask) >> LOG_fODelayOnRepeatShift)
// Darauffolgendes AUS führt zu
#define ParamLOG_fODelayOnReset                      ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOnReset)) & LOG_fODelayOnResetMask))
// Erneutes AUS führt zu
#define ParamLOG_fODelayOffRepeat                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOffRepeat)) & LOG_fODelayOffRepeatMask) >> LOG_fODelayOffRepeatShift)
// Darauffolgendes EIN führt zu
#define ParamLOG_fODelayOffReset                     ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOffReset)) & LOG_fODelayOffResetMask))
// EINschalten wird verzögert um
#define ParamLOG_fODelayOnBase                       ((knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOnBase)) & LOG_fODelayOnBaseMask) >> LOG_fODelayOnBaseShift)
// EINschalten wird verzögert um
#define ParamLOG_fODelayOnTime                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fODelayOnTime)) & LOG_fODelayOnTimeMask)
// EINschalten wird verzögert um (in Millisekunden)
#define ParamLOG_fODelayOnTimeMS                     (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fODelayOnTime))))
// AUSschalten wird verzögert um
#define ParamLOG_fODelayOffBase                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOffBase)) & LOG_fODelayOffBaseMask) >> LOG_fODelayOffBaseShift)
// AUSschalten wird verzögert um
#define ParamLOG_fODelayOffTime                      (knx.paramWord(LOG_ParamCalcIndex(LOG_fODelayOffTime)) & LOG_fODelayOffTimeMask)
// AUSschalten wird verzögert um (in Millisekunden)
#define ParamLOG_fODelayOffTimeMS                    (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fODelayOffTime))))
// Ausgang hat eine Treppenlichtfunktion
#define ParamLOG_fOStair                             ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fOStair)) & LOG_fOStairMask))
// Treppenlicht kann verlängert werden
#define ParamLOG_fORetrigger                         ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fORetrigger)) & LOG_fORetriggerMask))
// Treppenlicht kann ausgeschaltet werden
#define ParamLOG_fOStairOff                          ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fOStairOff)) & LOG_fOStairOffMask))
// Ausgang wiederholt zyklisch
#define ParamLOG_fORepeat                            ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fORepeat)) & LOG_fORepeatMask))
// Wiederholungsfilter
#define ParamLOG_fOOutputFilter                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOutputFilter)) & LOG_fOOutputFilterMask) >> LOG_fOOutputFilterShift)
// EIN-Telegramm wird wiederholt alle
#define ParamLOG_fORepeatOnBase                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fORepeatOnBase)) & LOG_fORepeatOnBaseMask) >> LOG_fORepeatOnBaseShift)
// EIN-Telegramm wird wiederholt alle
#define ParamLOG_fORepeatOnTime                      (knx.paramWord(LOG_ParamCalcIndex(LOG_fORepeatOnTime)) & LOG_fORepeatOnTimeMask)
// EIN-Telegramm wird wiederholt alle (in Millisekunden)
#define ParamLOG_fORepeatOnTimeMS                    (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fORepeatOnTime))))
// AUS-Telegramm wird wiederholt alle
#define ParamLOG_fORepeatOffBase                     ((knx.paramByte(LOG_ParamCalcIndex(LOG_fORepeatOffBase)) & LOG_fORepeatOffBaseMask) >> LOG_fORepeatOffBaseShift)
// AUS-Telegramm wird wiederholt alle
#define ParamLOG_fORepeatOffTime                     (knx.paramWord(LOG_ParamCalcIndex(LOG_fORepeatOffTime)) & LOG_fORepeatOffTimeMask)
// AUS-Telegramm wird wiederholt alle (in Millisekunden)
#define ParamLOG_fORepeatOffTimeMS                   (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fORepeatOffTime))))
// DPT für Ausgang
#define ParamLOG_fODpt                               (knx.paramByte(LOG_ParamCalcIndex(LOG_fODpt)))
// Wert für EIN senden?
#define ParamLOG_fOOn                                (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOn)))
// Wert für EIN senden?
#define ParamLOG_fOOnBuzzer                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnBuzzer)))
// Wert für EIN senden?
#define ParamLOG_fOOnLed                             (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnLed)))
// Wert für EIN senden?
#define ParamLOG_fOOnAll                             (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnAll)))
//     Wert für EIN senden als
#define ParamLOG_fOOnTone                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnTone)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt1                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt1)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt2                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt2)))
//     Wert für EIN senden als 
#define ParamLOG_fOOnDpt5                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt5)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt5001                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt5001)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt6                            ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt6)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt7                            (knx.paramWord(LOG_ParamCalcIndex(LOG_fOOnDpt7)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt8                            ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fOOnDpt8)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt9                            (knx.paramFloat(LOG_ParamCalcIndex(LOG_fOOnDpt9), Float_Enc_IEEE754Single))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt12                           (knx.paramInt(LOG_ParamCalcIndex(LOG_fOOnDpt12)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt13                           ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fOOnDpt13)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt14                           (knx.paramFloat(LOG_ParamCalcIndex(LOG_fOOnDpt14), Float_Enc_IEEE754Single))
//     Wert für EIN senden als 
#define ParamLOG_fOOnDpt16                           (knx.paramData(LOG_ParamCalcIndex(LOG_fOOnDpt16)))
//     Wert für EIN senden als 
#define ParamLOG_fOOnDpt17                           (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt17)))
//     Wert für EIN senden als (3-Byte-RGB)
#define ParamLOG_fOOnRGB                             ((knx.paramInt(LOG_ParamCalcIndex(LOG_fOOnRGB)) & LOG_fOOnRGBMask) >> LOG_fOOnRGBShift)
// 
#define ParamLOG_fOOnPAArea                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnPAArea)) & LOG_fOOnPAAreaMask) >> LOG_fOOnPAAreaShift)
// 
#define ParamLOG_fOOnPALine                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnPALine)) & LOG_fOOnPALineMask)
// 
#define ParamLOG_fOOnPADevice                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnPADevice)))
//     Wert für EIN ermitteln als
#define ParamLOG_fOOnFunction                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnFunction)))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fOOnKONumber                        ((knx.paramWord(LOG_ParamCalcIndex(LOG_fOOnKONumber)) & LOG_fOOnKONumberMask) >> LOG_fOOnKONumberShift)
//     DPT des Kommunikationsobjekts
#define ParamLOG_fOOnKODpt                           (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnKODpt)))
// Wert für AUS senden?
#define ParamLOG_fOOff                               (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOff)))
// Wert für AUS senden?
#define ParamLOG_fOOffBuzzer                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffBuzzer)))
// Wert für AUS senden?
#define ParamLOG_fOOffLed                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffLed)))
// Wert für AUS senden?
#define ParamLOG_fOOffAll                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffAll)))
//     Wert für AUS senden als
#define ParamLOG_fOOffTone                           (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffTone)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt1                           (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt1)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt2                           (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt2)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt5                           (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt5)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt5001                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt5001)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt6                           ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt6)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt7                           (knx.paramWord(LOG_ParamCalcIndex(LOG_fOOffDpt7)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt8                           ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fOOffDpt8)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt9                           (knx.paramFloat(LOG_ParamCalcIndex(LOG_fOOffDpt9), Float_Enc_IEEE754Single))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt12                          (knx.paramInt(LOG_ParamCalcIndex(LOG_fOOffDpt12)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt13                          ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fOOffDpt13)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt14                          (knx.paramFloat(LOG_ParamCalcIndex(LOG_fOOffDpt14), Float_Enc_IEEE754Single))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt16                          (knx.paramData(LOG_ParamCalcIndex(LOG_fOOffDpt16)))
//     Wert für AUS senden als 
#define ParamLOG_fOOffDpt17                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt17)))
//     Wert für AUS senden als (3-Byte-RGB)
#define ParamLOG_fOOffRGB                            ((knx.paramInt(LOG_ParamCalcIndex(LOG_fOOffRGB)) & LOG_fOOffRGBMask) >> LOG_fOOffRGBShift)
// 
#define ParamLOG_fOOffPAArea                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffPAArea)) & LOG_fOOffPAAreaMask) >> LOG_fOOffPAAreaShift)
// 
#define ParamLOG_fOOffPALine                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffPALine)) & LOG_fOOffPALineMask)
// 
#define ParamLOG_fOOffPADevice                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffPADevice)))
//     Wert für AUS ermitteln als
#define ParamLOG_fOOffFunction                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffFunction)))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fOOffKONumber                       ((knx.paramWord(LOG_ParamCalcIndex(LOG_fOOffKONumber)) & LOG_fOOffKONumberMask) >> LOG_fOOffKONumberShift)
//     DPT des Kommunikationsobjekts
#define ParamLOG_fOOffKODpt                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffKODpt)))
// Kommunikationsobjekt für Eingang
#define ParamLOG_fE1UseOtherKO                       ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1UseOtherKO)) & LOG_fE1UseOtherKOMask))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fE1OtherKO                          (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1OtherKO)) & LOG_fE1OtherKOMask)
// Kommunikationsobjekt für Eingang
#define ParamLOG_fE2UseOtherKO                       ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2UseOtherKO)) & LOG_fE2UseOtherKOMask))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fE2OtherKO                          (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2OtherKO)) & LOG_fE2OtherKOMask)

// deprecated
#define LOG_KoOffset 340

// Communication objects per channel (multiple occurrence)
#define LOG_KoBlockOffset 340
#define LOG_KoBlockSize 3

#define LOG_KoCalcNumber(index) (index + LOG_KoBlockOffset + _channelIndex * LOG_KoBlockSize)
#define LOG_KoCalcIndex(number) ((number >= LOG_KoCalcNumber(0) && number < LOG_KoCalcNumber(LOG_KoBlockSize)) ? (number - LOG_KoOffset) % LOG_KoBlockSize : -1)

#define LOG_KoKOfE1 0
#define LOG_KoKOfE2 1
#define LOG_KoKOfO 2

// Eingang 1
#define KoLOG_KOfE1                               (knx.getGroupObject(LOG_KoCalcNumber(LOG_KoKOfE1)))
// Eingang 2
#define KoLOG_KOfE2                               (knx.getGroupObject(LOG_KoCalcNumber(LOG_KoKOfE2)))
// Ausgang
#define KoLOG_KOfO                                (knx.getGroupObject(LOG_KoCalcNumber(LOG_KoKOfO)))



// Header generation for Module 'BASE_KommentarModule'

#define BASE_KommentarModuleCount 20
#define BASE_KommentarModuleModuleParamSize 0
#define BASE_KommentarModuleSubmodulesParamSize 0
#define BASE_KommentarModuleParamSize 0
#define BASE_KommentarModuleParamOffset 3242
#define BASE_KommentarModuleCalcIndex(index, m1) (index + BASE_KommentarModuleParamOffset + _channelIndex * BASE_KommentarModuleCount * BASE_KommentarModuleParamSize + m1 * BASE_KommentarModuleParamSize)



