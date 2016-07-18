#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#include "config.h"

DHT dht(DHT_PIN, DHT_TYPE);
WiFiClient espClient;
PubSubClient mqtt(espClient);

void setup()
{
    Serial.begin(115200);
    setup_wifi();
    mqtt.setServer(MQTT_SERVER, MQTT_PORT);
    dht.begin();
}

void setup_wifi()
{
    delay(10);

    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PSK);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    if (!mqtt.connected()) {
        reconnect();
    }

    char b[6];
    char message[BUFSIZ];
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    dtostrf(t, 4, 2, b);
    sprintf(message, "{\"room_id\": %d, \"temperature\": %s }", ROOM_ID, b);
    mqtt.publish("domotic/temperature", message);

    dtostrf(h, 4, 2, b);
    sprintf(message, "{\"room_id\": %d, \"humidity\": %s }", ROOM_ID, b);
    mqtt.publish("domotic/humidity", message);

    delay(60000);
}

void reconnect()
{
    while (!mqtt.connected()) {
        Serial.print("Attempting MQTT connection... ");

        if (mqtt.connect("esp8266", MQTT_USER, MQTT_PASSWORD)) {
            Serial.println("connected");
        }
        else {
            Serial.print("failed, rc=");
            Serial.println(mqtt.state());

            delay(5000);
        }
    }
}
