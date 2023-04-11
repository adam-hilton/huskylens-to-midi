
#include "MIDIUSB.h"
#include "HUSKYLENS.h"

HUSKYLENS huskylens;

int xChan = 9; // 0-15 for MIDI channels 1 - 16
int xControl = 93; // 0 - 127

int yChan = 9; // 0-15 for MIDI channels 1 - 16
int yControl = 94; // 0 - 127

int wChan = 9; // 0-15 for MIDI channels 1 - 16
int wControl = 95; // 0 - 127

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Wire.begin();
    while (!huskylens.begin(Wire))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
    
  huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING);

}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void loop() {
  // put your main code here, to run repeatedly:

 if (!huskylens.request()) Serial.println(F("Fail to request objects from HUSKYLENS!"));
    else if(!huskylens.available()) Serial.println(F("Object disappeared!"));
    else
    {

  HUSKYLENSResult result = huskylens.read();
  controlChange(xChan, xControl, result.xCenter);
  controlChange(yChan, yControl, result.yCenter);
  controlChange(wChan, wControl, result.width);
  MidiUSB.flush();
//  Serial.println(String()+F("X=")+result.xCenter);
//  Serial.println(String()+F("Y=")+result.yCenter);
//  Serial.println(String()+F("Width=")+result.width);
  delay(100);
  
}
}

//void printResult(HUSKYLENSResult result){
//  
//  }
