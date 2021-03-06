#ifndef DHT22_H
#define DHT22_H

#include <stdint.h>

typedef union {
    struct {
        uint8_t data[5];
    };
    struct {
        uint8_t cksum;
        int16_t temp;
        int16_t humidity;
    };
} dht22Dev;

void dht22Init(void);

void dht22Read(void);

int16_t dht22GetHumidity(void);

int16_t dht22GetTemp(void);

uint8_t dht22HaveSensor(void);

#endif // DHT22_H
