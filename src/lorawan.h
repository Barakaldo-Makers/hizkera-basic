#pragma once
#ifndef _LORAWAN_H
#define _LORAWAN_H

#include <Arduino.h>
#include <lmic.h>
#include "lora_credentials.h"

// This EUI must be in little-endian format, so least-significant-byte
// first. When copying an EUI from ttnctl output, this means to reverse
// the bytes. For TTN issued EUIs the last bytes should be 0xD5, 0xB3,
// 0x70.
static const u1_t PROGMEM APPEUI[8] = {0xc7, 0x00, 0x73, 0xa2, 0xe1, 0x85, 0x2f, 0x59};

// This should also be in little endian format, see above.
static const u1_t PROGMEM DEVEUI[8] = TTN_DEVEUI;

// This key should be in big endian format (or, since it is not really a
// number but a block of memory, endianness does not really apply). In
// practice, a key taken from ttnctl can be copied as-is.
static const u1_t PROGMEM APPKEY[16] = {0x25, 0xf9,0x3c, 0x13, 0x50, 0x96, 0x4b, 0xd2, 0xa8, 0xa2, 0x2f, 0x5b, 0xad, 0xa7, 0x9a, ox27};

static osjob_t sendjob;

// LMIC State save for reboot
extern RTC_DATA_ATTR lmic_t RTC_LMIC;

void os_getArtEui(u1_t *buf);
void os_getDevEui(u1_t *buf);
void os_getDevKey(u1_t *buf);

void LoRaWANSetup(void);
void LoraWANDo_send(osjob_t *j);
void LoraWANDo(void);
void LoraWANGetData(void);
void LoraWANSaveLMICToRTC(int deepsleep_sec);
void LoraWANLoadLMICFromRTC(void);
void LoraWANPrintVersion(void);
void LoraWANPrintLMICOpmode(void);
void LoraWANDebug(lmic_t lmic_to_check);

#endif
