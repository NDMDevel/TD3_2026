#include <Arduino.h>
#include <WiFi.h>
#include "Timers.h"
#include <LinkedList.h>

LinkedList<WiFiClient> client_list;

uint16_t holding_registers[1000];
//holding_registers[0]  -> 40001
//holding_registers[1]  -> 40002

bool coils[256];
//coils[0]  -> 10001
//coils[1]  -> 10002

WiFiServer server(5000);
String sta_SSID = "Nodo Informatico IV";
String sta_PASS = "utn12345";

Tim32_ms timer;

void setup()
{
    Serial.begin(9600);
    timer.start();

    WiFi.begin( sta_SSID , sta_PASS );

    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\nConnected IP: "+WiFi.localIP().toString());

    server.begin();

}

void manage_clients(WiFiClient client)
{
    if( client )
        client_list.add(client);
    int idx = 0;
    while( idx < client_list.size() )
    {
        if( !client_list[idx].connected() )
            client_list.remove(idx);
        else
            idx++;
    }
}

void loop()
{
    WiFiClient client = server.available();
    manage_clients(client);

    for( int i=0 ; i<client_list.size() ; i++ )
    {
        if( client_list[i].available() )
            Serial.print(client_list[i].remoteIP().toString() + ": ");
        while( client_list[i].available() )
        {
            uint8_t b = client_list[i].read();
            Serial.printf("%c", b);
        }
    }

}