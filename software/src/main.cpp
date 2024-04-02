#include <Arduino.h>
#include <MIDI.h>



MIDI_CREATE_INSTANCE(HardwareSerial, Serial1,  midiA);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2,  midiB);


unsigned long blink_time;
int blink_delay = 20;  // [ms]


void setup() {
    midiA.begin(MIDI_CHANNEL_OMNI);
    midiB.begin(MIDI_CHANNEL_OMNI);
    pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
    if (midiA.read()) {
        midiB.send(midiA.getType(),
                    midiA.getData1(),
                    midiA.getData2(),
                    midiA.getChannel());
        digitalWrite(LED_BUILTIN, HIGH);
        blink_time = millis();
    }

    if (midiB.read()) {
        midiA.send(midiB.getType(),
                    midiB.getData1(),
                    midiB.getData2(),
                    midiB.getChannel());
        digitalWrite(LED_BUILTIN, HIGH);
        blink_time = millis();
    }

    if (millis() > blink_time + blink_delay) digitalWrite(LED_BUILTIN, LOW);
}
