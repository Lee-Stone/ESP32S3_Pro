#ifndef __ALL_EXTERN_H__
#define __ALL_EXTERN_H__

#include <Arduino.h>

extern bool init_flag;

extern bool wifi_scan_flag;
extern bool wifi_connect_flag;
extern bool wifi_button_flag;
extern bool isconnect;
extern bool time_flag;
extern char wifi_name[64];
extern const char * wifi_password;
extern struct tm timeinfo;
extern bool weather_flag;

extern const char * songoptions;
extern char songname[64];
extern bool start_flag;
extern bool play_flag;
extern int voice;

extern bool mic_flag;
extern bool serial_flag;

extern char * rate_buf;

#endif
