#include <WiFi.h>

const char* ssid = "Somesh’s iPhone 16 Pro Max";  
const char* password = "test1234";  
WiFiServer server(1234);  

#define VIBRATION_PIN 2  

int intensity = 0;
int duration = 0;
int frequency = 0;
bool customVibrationActive = false;
bool heartbeatActive = false;
bool relaxationActive = false;
unsigned long startTime = 0;

WiFiClient client;  

void setup() {
    Serial.begin(115200);
    pinMode(VIBRATION_PIN, OUTPUT);
    analogWrite(VIBRATION_PIN, 0);

    WiFi.begin(ssid, password);
    WiFi.setSleep(false);  // Prevent Wi-Fi from sleeping

    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected to WiFi!");
    Serial.print("ESP32 IP Address: ");
    Serial.println(WiFi.localIP());

    server.begin();
}

void loop() {
    // Check Wi-Fi connection & reconnect if needed
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Wi-Fi lost. Reconnecting...");
        WiFi.disconnect();
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("\nReconnected to Wi-Fi!");
    }

    // Check for incoming client connection
    if (!client || !client.connected()) {
        client = server.available();  
        if (client) {
            Serial.println("Client connected");
        }
    }

    // Read and process incoming command
    if (client && client.available()) {
        String command = client.readStringUntil('\n');  
        command.trim();
        Serial.println("Received: " + command);
        processCommand(command);
    }

    handleVibration();
}

void processCommand(String command) {
    if (command.startsWith("CUSTOM ")) {
        sscanf(command.c_str(), "CUSTOM %d %d %d", &intensity, &duration, &frequency);
        customVibrationActive = true;
        heartbeatActive = false;
        relaxationActive = false;
        startTime = millis();
    } else if (command.startsWith("HEARTBEAT ON")) {
        heartbeatActive = true;
        customVibrationActive = false;
        relaxationActive = false;
    } else if (command.startsWith("HEARTBEAT OFF")) {
        heartbeatActive = false;
        analogWrite(VIBRATION_PIN, 0);
    } else if (command.startsWith("RELAX ON")) {
        relaxationActive = true;
        customVibrationActive = false;
        heartbeatActive = false;
    } else if (command.startsWith("RELAX OFF")) {
        relaxationActive = false;
        analogWrite(VIBRATION_PIN, 0);
    } else if (command.startsWith("STOP")) {
        customVibrationActive = false;
        heartbeatActive = false;
        relaxationActive = false;
        analogWrite(VIBRATION_PIN, 0);
    }
}
void handleVibration() {
    if (customVibrationActive) {
        unsigned long elapsedTime = millis() - startTime;
        if (elapsedTime >= (duration * 1000)) {
            customVibrationActive = false;
            analogWrite(VIBRATION_PIN, 0);
            return;
        }

        if (frequency > 0) {
            if ((millis() / (1000 / frequency)) % 2 == 0) {
                analogWrite(VIBRATION_PIN, intensity);
            } else {
                analogWrite(VIBRATION_PIN, 0);
            }
        } else {
            analogWrite(VIBRATION_PIN, intensity);
        }
    } 
    else if (heartbeatActive) {
        static unsigned long lastBeatTime = 0;
        static int beatStage = 0;
        
        // Realistic Heartbeat Pattern: Lub-dub with pauses
        static int beatPattern[] = {255,0,175,0};  // Strong, pause, weak, pause
        static int beatDurations[] = {150,300,150,800};  // Strong beat, short pause, weak beat, long pause

        if (millis() - lastBeatTime > beatDurations[beatStage]) {
            lastBeatTime = millis();
            analogWrite(VIBRATION_PIN, beatPattern[beatStage]);
            beatStage = (beatStage + 1) % 4;  // Cycle through the 4 stages
        }
    } 
    else if (relaxationActive) {
        static unsigned long lastPulseTime = 0;
        static int relaxStage = 0;
        static int intensities[] = {125, 125, 180, 180, 180, 125, 125};  
        static int durations[] = {300, 300, 800, 800, 800, 300, 300}; 

        if (millis() - lastPulseTime > durations[relaxStage]) {
            lastPulseTime = millis();
            analogWrite(VIBRATION_PIN, intensities[relaxStage]);
            relaxStage = (relaxStage + 1) % 7;
        }
    } 
    else {
        analogWrite(VIBRATION_PIN, 0);
    }
}


/*void handleVibration() {
    if (customVibrationActive) {
        unsigned long elapsedTime = millis() - startTime;
        if (elapsedTime >= (duration * 1000)) {
            customVibrationActive = false;
            analogWrite(VIBRATION_PIN, 0);
            return;
        }

        if (frequency > 0) {
            if ((millis() / (1000 / frequency)) % 2 == 0) {
                analogWrite(VIBRATION_PIN, intensity);
            } else {
                analogWrite(VIBRATION_PIN, 0);
            }
        } else {
            analogWrite(VIBRATION_PIN, intensity);
        }
    } 
    else if (heartbeatActive) {
        static unsigned long lastBeatTime = 0;
        static int beatStage = 0;

        if (millis() - lastBeatTime > 100) {
            lastBeatTime = millis();
            switch (beatStage) {
                case 0: analogWrite(VIBRATION_PIN, 190); break;
                case 1: analogWrite(VIBRATION_PIN, 0); break;
                case 2: analogWrite(VIBRATION_PIN, 120); break;
                case 3: analogWrite(VIBRATION_PIN, 0); break;
            }
            beatStage = (beatStage + 1) % 4;
        }
    } 
    else if (relaxationActive) {
        static unsigned long lastPulseTime = 0;
        static int relaxStage = 0;
        static int intensities[] = {125, 125, 200, 200, 250, 125, 125};  
        static int durations[] = {300, 300, 800, 800, 800, 300, 300}; 

        if (millis() - lastPulseTime > durations[relaxStage]) {
            lastPulseTime = millis();
            analogWrite(VIBRATION_PIN, intensities[relaxStage]);
            relaxStage = (relaxStage + 1) % 7;
        }
    } 
    else {
        analogWrite(VIBRATION_PIN, 0);
    }
}*/
