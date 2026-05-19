#include <Arduino.h>
#include <WiFi.h>
#include "Timers.h"
#include "checksum.h"

WiFiServer server(5000);
String sta_SSID = "LAB_ELECTRONICA";
String sta_PASS = "LabElec2022";

Tim32_ms timer;

uint16_t crc_16(uint8_t *buffer, uint16_t length)
{
    uint16_t i, j, temp_bit, temp_int, crc;
    crc = 0xFFFF;
    for (i = 0; i < length; i++)
    {
        temp_int = (unsigned char)*buffer++;
        crc ^= temp_int;
        for (j = 0; j < 8; j++)
        {
            temp_bit = crc & 0x0001;
            crc >>= 1;
            if (temp_bit != 0)
                crc ^= 0xA001;
        }
    }
    return crc;
}

void setup()
{
    Serial.begin(9600);
    timer.start();

    WiFi.begin( sta_SSID , sta_PASS );

    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
    }
    Serial.println("\nConnected IP: "+WiFi.localIP().toString());

    server.begin();

}

void loop()
{
    if( timer > 1s )    
    {
        uint16_t mb_address = 40030;

        uint8_t mb_frame[64];
        mb_frame[0] = 0x01;
        mb_frame[1] = 0x03;
        mb_frame[2] = mb_address >> 8;
        mb_frame[3] = mb_address & 0x00FF;
        mb_frame[4] = 0x00;
        mb_frame[5] = 0x01;
        uint16_t crc = crc_modbus( mb_frame , 6 );
        mb_frame[6] = crc >> 8;
        mb_frame[7] = crc & 0x00FF;

        //Serial.write( mb_frame , 8);

        timer.start();
    }
    WiFiClient client = server.available();

    if( client )
    {
        while (client.connected())
        {
            while (client.available())
            {
                uint8_t b = client.read();
                Serial.printf("%02X ", b);
            }
        }
        client.stop();
    }
}