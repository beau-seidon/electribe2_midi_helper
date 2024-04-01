#include <Arduino.h>
#include <MIDI.h>

// This example shows how to create two instances of the library to create a merger.
// There are two MIDI couples of IO, A and B, each using thru and merging with the
// input from the other node. The result is the following:
// A out = A in + B in
// B out = B in + A in


// #include <SoftwareSerial.h>
// SoftwareSerial softSerial(2,3);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1,  midiA);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2,  midiB);


unsigned long blink_time;
int blink_delay = 20;  // [ms]


void setup() {
    // Initiate MIDI communications, listen to all channels
    midiA.begin(MIDI_CHANNEL_OMNI);
    midiB.begin(MIDI_CHANNEL_OMNI);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    if (midiA.read()) {
        // Thru on A has already pushed the input message to out A.
        // Forward the message to out B as well.
        midiB.send(midiA.getType(),
                   midiA.getData1(),
                   midiA.getData2(),
                   midiA.getChannel());
        digitalWrite(LED_BUILTIN, HIGH);
        blink_time = millis();
    }

    if (midiB.read()) {
        // Thru on B has already pushed the input message to out B.
        // Forward the message to out A as well.
        midiA.send(midiB.getType(),
                   midiB.getData1(),
                   midiB.getData2(),
                   midiB.getChannel());
        digitalWrite(LED_BUILTIN, HIGH);
        blink_time = millis();
    }

    if (millis() > blink_time + blink_delay) digitalWrite(LED_BUILTIN, LOW);
}
