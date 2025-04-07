#pragma once

// #define M5Stack_Core 1
#define M5Stack_CoreS3 1

#ifdef M5Stack_Core

#define PORT_NUM I2C_NUM_0
#define PORT_SCL 22
#define PORT_SDA 21
#define PORT_FREQ 400000

#else   // M5Stack_CoreS3

#define PORT_NUM I2C_NUM_0
#define PORT_SCL 1
#define PORT_SDA 2
#define PORT_FREQ 400000

#endif

