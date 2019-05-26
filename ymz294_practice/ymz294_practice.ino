
const byte PWM_CLOCKOUT_PIN = 11;

const byte WRCS_PIN = 46;
const byte A0_PIN = 44;
const byte RESET_PIN = 42;

const int DATA_PIN[] = { 34, 35, 32, 33, 30, 31, 28, 29 };

void setup() {

  for (int i = 0; i < 8; i++) {
    pinMode(DATA_PIN[i], OUTPUT);
  }
  pinMode(WRCS_PIN, OUTPUT);
  pinMode(A0_PIN, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);

  pinMode(13, OUTPUT);

  reset(); 
  
  // mixer
  set_register(0x07, 0b00111000);
  // set channel volume to 0
  set_register(0x08, 0);
  set_register(0x09, 0);
  set_register(0x0a, 0);
  // set cahannel freq to 0
  SetFrequency(0, 0);
  SetFrequency(1, 0);
  SetFrequency(2, 0);

  delay(100);

  // set volume to channel a-c
  set_register(0x08, 15);
  set_register(0x09, 15);
  set_register(0x0a, 15);

}


void reset() {
  // freq (channel A)
  set_register(0x00, 0);
  set_register(0x01, 0);
  // freq (channel B)
  set_register(0x02, 0);
  set_register(0x03, 0);
  // freq (channel C)
  set_register(0x04, 0);
  set_register(0x05, 0);
  // freq (noise channel)
  set_register(0x06, 0);
  // mixer
  set_register(0x07, 0);
  // channel volumes
  set_register(0x08, 0);
  set_register(0x09, 0);
  set_register(0x0a, 0);
  // freq (envelop)
  set_register(0x0b, 0);
  set_register(0x0c, 0);
  // envelop control
  set_register(0x0d, 0);

  digitalWrite(WRCS_PIN, HIGH);
  digitalWrite(A0_PIN, LOW);
  digitalWrite(RESET_PIN, LOW);
  delay(10);
  digitalWrite(RESET_PIN, HIGH);
}

void set_register(byte addr, byte value)
{
  // addr
  digitalWrite(WRCS_PIN, LOW);
  digitalWrite(A0_PIN, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(DATA_PIN[i], bitRead(addr, i));
  }
  digitalWrite(WRCS_PIN, HIGH);

  // value
  digitalWrite(WRCS_PIN, LOW);
  digitalWrite(A0_PIN, HIGH);
  for (int i = 0; i < 8; i++) {
    digitalWrite(DATA_PIN[i], bitRead(value, i));
  }
  digitalWrite(WRCS_PIN, HIGH);
}

bool playState = false;
bool buttonPushed = false;
int beforeFrameState = HIGH;

// set freq to channel
void SetFrequency(int ch, word freq) {
  int buttonPinState = digitalRead(22);

   if (buttonPinState == LOW && beforeFrameState == HIGH) {
    buttonPushed = true;
   } else {
    buttonPushed = false;
   }
   if (buttonPushed) {
    playState = !playState;
   }
   if (playState) {
    digitalWrite(13, HIGH);
   } else {
    digitalWrite(13, LOW);
   }
   beforeFrameState = buttonPinState;
  word cal_freqency = 0;
  if (freq != 0) {
    cal_freqency = 125000 / freq;
  }
  if (playState == false) {
    cal_freqency = 0;
  }
  cal_freqency &= 0b0000111111111111;
  set_register(0x00 + (ch * 2), cal_freqency & 0xff);
  set_register(0x01 + (ch * 2), (cal_freqency >> 8) & 0xff);
}


void loop() {
 
  SetFrequency(0,1174);SetFrequency(1,493);SetFrequency(2,391);delay(250);SetFrequency(0,1046);delay(250);SetFrequency(0,987);SetFrequency(1,523);delay(250);SetFrequency(0,880);SetFrequency(1,587);SetFrequency(2,329);delay(250);SetFrequency(0,1567);delay(250);SetFrequency(0,1318);SetFrequency(1,783);delay(250);SetFrequency(0,1479);SetFrequency(1,587);SetFrequency(2,369);delay(250);SetFrequency(0,1318);SetFrequency(1,523);delay(250);SetFrequency(0,1174);SetFrequency(1,493);SetFrequency(2,391);delay(500);SetFrequency(1,391);delay(250);SetFrequency(0,987);SetFrequency(1,587);SetFrequency(2,440);delay(250);SetFrequency(0,783);delay(250);SetFrequency(0,783);SetFrequency(1,587);delay(250);SetFrequency(0,880);SetFrequency(1,523);SetFrequency(2,391);delay(250);SetFrequency(0,987);SetFrequency(1,493);delay(250);SetFrequency(0,1046);SetFrequency(2,329);delay(250);SetFrequency(1,493);delay(250);SetFrequency(1,523);delay(250);SetFrequency(1,493);SetFrequency(2,369);delay(250);SetFrequency(1,523);delay(250);SetFrequency(0,739);delay(250);SetFrequency(0,783);SetFrequency(2,329);delay(250);SetFrequency(0,880);delay(250);SetFrequency(0,987);SetFrequency(2,391);delay(250);SetFrequency(1,493);delay(250);SetFrequency(1,523);delay(250);SetFrequency(0,1046);SetFrequency(1,440);SetFrequency(2,329);delay(125);SetFrequency(0,987);delay(125);SetFrequency(0,880);SetFrequency(1,493);delay(250);SetFrequency(1,391);delay(250);SetFrequency(1,440);SetFrequency(2,293);delay(250);SetFrequency(1,369);delay(250);SetFrequency(0,1174);SetFrequency(1,493);SetFrequency(2,391);delay(250);SetFrequency(0,1046);delay(250);SetFrequency(0,987);SetFrequency(1,523);delay(250);SetFrequency(0,1174);SetFrequency(1,587);SetFrequency(2,329);delay(250);SetFrequency(0,1567);delay(250);SetFrequency(0,1479);SetFrequency(1,783);delay(250);SetFrequency(0,1479);SetFrequency(1,587);SetFrequency(2,369);delay(250);SetFrequency(0,1567);SetFrequency(1,523);delay(250);SetFrequency(0,1318);SetFrequency(1,493);SetFrequency(2,391);delay(500);SetFrequency(1,391);delay(250);SetFrequency(0,1174);SetFrequency(1,587);SetFrequency(2,440);delay(250);SetFrequency(0,1174);delay(250);SetFrequency(1,587);delay(250);SetFrequency(1,783);SetFrequency(2,391);delay(250);SetFrequency(1,739);delay(250);SetFrequency(0,1046);SetFrequency(1,659);SetFrequency(2,329);delay(250);SetFrequency(0,987);delay(250);SetFrequency(0,880);SetFrequency(1,587);delay(250);SetFrequency(0,783);SetFrequency(1,523);SetFrequency(2,369);delay(250);SetFrequency(0,1174);delay(250);SetFrequency(0,1046);SetFrequency(1,440);delay(250);SetFrequency(0,987);SetFrequency(1,493);SetFrequency(2,440);delay(250);SetFrequency(0,880);SetFrequency(1,523);SetFrequency(2,440);delay(250);SetFrequency(0,783);SetFrequency(1,587);SetFrequency(2,391);delay(250);SetFrequency(1,523);delay(250);SetFrequency(1,493);delay(250);SetFrequency(1,440);SetFrequency(2,329);delay(250);SetFrequency(1,391);delay(250);SetFrequency(0,783);delay(250);SetFrequency(0,880);SetFrequency(1,369);SetFrequency(2,293);delay(250);SetFrequency(0,987);delay(250);SetFrequency(0,1046);SetFrequency(1,523);SetFrequency(2,261);delay(250);SetFrequency(1,391);delay(250);SetFrequency(1,329);delay(250);SetFrequency(1,391);delay(250);SetFrequency(0,1174);SetFrequency(1,587);SetFrequency(2,293);delay(250);SetFrequency(1,440);delay(250);SetFrequency(1,369);delay(250);SetFrequency(0,1046);SetFrequency(1,440);delay(250);SetFrequency(0,987);SetFrequency(1,493);SetFrequency(2,391);delay(250);SetFrequency(1,391);delay(250);SetFrequency(1,293);delay(250);SetFrequency(1,391);delay(250);SetFrequency(1,493);SetFrequency(2,329);delay(250);SetFrequency(0,783);SetFrequency(1,391);delay(250);SetFrequency(0,880);SetFrequency(1,293);SetFrequency(2,293);delay(250);SetFrequency(0,987);SetFrequency(1,391);delay(250);SetFrequency(0,1046);SetFrequency(1,523);SetFrequency(2,261);delay(250);SetFrequency(1,391);delay(250);SetFrequency(0,1046);SetFrequency(1,329);delay(250);SetFrequency(1,391);delay(250);SetFrequency(0,1174);SetFrequency(1,587);SetFrequency(2,293);delay(250);SetFrequency(1,440);delay(250);SetFrequency(1,369);delay(250);SetFrequency(0,1046);SetFrequency(1,440);delay(125);SetFrequency(0,1174);delay(125);SetFrequency(0,987);SetFrequency(1,493);SetFrequency(2,391);delay(250);SetFrequency(1,391);delay(250);SetFrequency(1,293);delay(250);SetFrequency(1,391);delay(250);SetFrequency(1,493);SetFrequency(2,440);delay(250);SetFrequency(0,987);SetFrequency(1,391);delay(250);SetFrequency(0,880);SetFrequency(1,293);SetFrequency(2,391);delay(250);SetFrequency(0,783);SetFrequency(1,391);delay(250);SetFrequency(0,880);SetFrequency(1,440);SetFrequency(2,329);delay(250);SetFrequency(1,329);delay(250);SetFrequency(1,261);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,659);SetFrequency(1,440);SetFrequency(2,440);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,987);SetFrequency(1,261);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,880);SetFrequency(1,440);SetFrequency(2,329);delay(250);SetFrequency(1,329);delay(250);SetFrequency(1,261);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,783);SetFrequency(1,440);SetFrequency(2,391);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,659);SetFrequency(1,261);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,739);SetFrequency(1,369);SetFrequency(2,369);delay(250);SetFrequency(1,293);delay(250);SetFrequency(1,261);delay(250);SetFrequency(1,293);delay(250);SetFrequency(0,783);SetFrequency(1,391);SetFrequency(2,329);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,987);SetFrequency(1,261);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,987);SetFrequency(1,391);SetFrequency(2,329);delay(250);SetFrequency(1,329);delay(250);SetFrequency(1,261);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,880);SetFrequency(1,369);SetFrequency(2,369);delay(249);SetFrequency(1,293);delay(250);SetFrequency(1,261);delay(250);SetFrequency(1,293);delay(251);SetFrequency(0,1174);SetFrequency(1,493);SetFrequency(2,391);delay(250);SetFrequency(0,1046);delay(250);SetFrequency(0,987);SetFrequency(1,523);delay(250);SetFrequency(0,880);SetFrequency(1,587);SetFrequency(2,329);delay(250);SetFrequency(0,1567);delay(250);SetFrequency(0,1318);SetFrequency(1,783);delay(250);SetFrequency(0,1479);SetFrequency(1,587);SetFrequency(2,369);delay(250);SetFrequency(0,1318);SetFrequency(1,523);delay(250);SetFrequency(0,1174);SetFrequency(1,493);SetFrequency(2,391);delay(500);SetFrequency(1,391);delay(250);SetFrequency(0,987);SetFrequency(1,587);SetFrequency(2,440);delay(250);SetFrequency(0,783);delay(250);SetFrequency(0,783);SetFrequency(1,587);delay(250);SetFrequency(0,880);SetFrequency(1,523);SetFrequency(2,391);delay(250);SetFrequency(0,987);SetFrequency(1,493);delay(250);SetFrequency(0,1046);SetFrequency(2,329);delay(250);SetFrequency(1,493);delay(250);SetFrequency(1,523);delay(250);SetFrequency(1,493);SetFrequency(2,369);delay(250);SetFrequency(1,523);delay(250);SetFrequency(0,739);delay(250);SetFrequency(0,783);SetFrequency(2,329);delay(250);SetFrequency(0,880);delay(250);SetFrequency(0,987);SetFrequency(2,391);delay(250);SetFrequency(1,493);delay(250);SetFrequency(1,523);delay(250);SetFrequency(0,1046);SetFrequency(1,440);SetFrequency(2,329);delay(125);SetFrequency(0,987);delay(125);SetFrequency(0,880);SetFrequency(1,493);delay(250);SetFrequency(1,391);delay(250);SetFrequency(1,440);SetFrequency(2,293);delay(250);SetFrequency(1,369);delay(250);SetFrequency(0,1174);SetFrequency(1,493);SetFrequency(2,391);delay(250);SetFrequency(0,1046);delay(250);SetFrequency(0,987);SetFrequency(1,523);delay(250);SetFrequency(0,1174);SetFrequency(1,587);SetFrequency(2,329);delay(250);SetFrequency(0,1567);delay(250);SetFrequency(0,1479);SetFrequency(1,783);delay(250);SetFrequency(0,1479);SetFrequency(1,587);SetFrequency(2,369);delay(250);SetFrequency(0,1567);SetFrequency(1,523);delay(250);SetFrequency(0,1318);SetFrequency(1,493);SetFrequency(2,391);delay(500);SetFrequency(1,391);delay(250);SetFrequency(0,1174);SetFrequency(1,587);SetFrequency(2,440);delay(250);SetFrequency(0,1174);delay(250);SetFrequency(1,587);delay(250);SetFrequency(1,783);SetFrequency(2,391);delay(250);SetFrequency(1,739);delay(250);SetFrequency(0,1046);SetFrequency(1,659);SetFrequency(2,329);delay(250);SetFrequency(0,987);delay(250);SetFrequency(0,880);SetFrequency(1,587);delay(250);SetFrequency(0,783);SetFrequency(1,523);SetFrequency(2,369);delay(250);SetFrequency(0,1174);delay(250);SetFrequency(0,1046);SetFrequency(1,440);delay(250);SetFrequency(0,987);SetFrequency(1,493);SetFrequency(2,440);delay(250);SetFrequency(0,880);SetFrequency(1,523);SetFrequency(2,440);delay(250);SetFrequency(0,783);SetFrequency(1,587);SetFrequency(2,391);delay(250);SetFrequency(1,523);delay(250);SetFrequency(1,493);delay(250);SetFrequency(1,440);SetFrequency(2,329);delay(250);SetFrequency(1,391);delay(250);SetFrequency(0,783);delay(250);SetFrequency(0,880);SetFrequency(1,369);SetFrequency(2,293);delay(250);SetFrequency(0,987);delay(250);SetFrequency(0,1046);SetFrequency(1,523);SetFrequency(2,261);delay(250);SetFrequency(1,391);delay(250);SetFrequency(1,329);delay(250);SetFrequency(1,391);delay(250);SetFrequency(0,1174);SetFrequency(1,587);SetFrequency(2,293);delay(250);SetFrequency(1,440);delay(250);SetFrequency(1,369);delay(250);SetFrequency(0,1046);SetFrequency(1,440);delay(250);SetFrequency(0,987);SetFrequency(1,493);SetFrequency(2,391);delay(250);SetFrequency(1,391);delay(250);SetFrequency(1,293);delay(250);SetFrequency(1,391);delay(250);SetFrequency(1,493);SetFrequency(2,329);delay(250);SetFrequency(0,783);SetFrequency(1,391);delay(250);SetFrequency(0,880);SetFrequency(1,293);SetFrequency(2,293);delay(250);SetFrequency(0,987);SetFrequency(1,391);delay(250);SetFrequency(0,1046);SetFrequency(1,523);SetFrequency(2,261);delay(250);SetFrequency(1,391);delay(250);SetFrequency(0,1046);SetFrequency(1,329);delay(250);SetFrequency(1,391);delay(250);SetFrequency(0,1174);SetFrequency(1,587);SetFrequency(2,293);delay(250);SetFrequency(1,440);delay(250);SetFrequency(1,369);delay(250);SetFrequency(0,1046);SetFrequency(1,440);delay(125);SetFrequency(0,1174);delay(125);SetFrequency(0,987);SetFrequency(1,493);SetFrequency(2,391);delay(250);SetFrequency(1,391);delay(250);SetFrequency(1,293);delay(250);SetFrequency(1,391);delay(250);SetFrequency(1,493);SetFrequency(2,440);delay(250);SetFrequency(0,987);SetFrequency(1,391);delay(250);SetFrequency(0,880);SetFrequency(1,293);SetFrequency(2,391);delay(250);SetFrequency(0,783);SetFrequency(1,391);delay(250);SetFrequency(0,880);SetFrequency(1,440);SetFrequency(2,329);delay(250);SetFrequency(1,329);delay(250);SetFrequency(1,261);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,659);SetFrequency(1,440);SetFrequency(2,440);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,987);SetFrequency(1,261);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,880);SetFrequency(1,440);SetFrequency(2,329);delay(250);SetFrequency(1,329);delay(250);SetFrequency(1,261);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,783);SetFrequency(1,440);SetFrequency(2,391);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,659);SetFrequency(1,261);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,739);SetFrequency(1,369);SetFrequency(2,369);delay(250);SetFrequency(1,293);delay(250);SetFrequency(1,261);delay(250);SetFrequency(1,293);delay(250);SetFrequency(0,783);SetFrequency(1,391);SetFrequency(2,329);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,987);SetFrequency(1,261);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,987);SetFrequency(1,391);SetFrequency(2,329);delay(250);SetFrequency(1,329);delay(250);SetFrequency(1,261);delay(250);SetFrequency(1,329);delay(250);SetFrequency(0,880);SetFrequency(1,369);SetFrequency(2,369);delay(250);SetFrequency(1,293);delay(250);SetFrequency(1,261);delay(250);SetFrequency(1,293);delay(250);SetFrequency(0,1174);SetFrequency(1,493);SetFrequency(2,391);delay(250);SetFrequency(0,1046);delay(250);SetFrequency(0,987);SetFrequency(1,523);delay(250);SetFrequency(0,880);SetFrequency(1,587);SetFrequency(2,329);delay(250);SetFrequency(0,1567);delay(250);SetFrequency(0,1318);SetFrequency(1,783);delay(250);SetFrequency(0,1479);SetFrequency(1,587);SetFrequency(2,369);delay(250);SetFrequency(0,1318);SetFrequency(1,523);delay(250);SetFrequency(0,1174);SetFrequency(1,493);SetFrequency(2,391);delay(500);SetFrequency(1,391);delay(250);SetFrequency(0,987);SetFrequency(1,587);SetFrequency(2,440);delay(250);SetFrequency(0,783);delay(250);SetFrequency(0,783);SetFrequency(1,587);delay(250);SetFrequency(0,880);SetFrequency(1,523);SetFrequency(2,391);delay(250);SetFrequency(0,987);SetFrequency(1,493);delay(250);SetFrequency(0,1046);SetFrequency(2,329);delay(250);SetFrequency(1,493);delay(250);SetFrequency(1,523);delay(250);SetFrequency(1,493);SetFrequency(2,369);delay(250);SetFrequency(1,523);delay(250);SetFrequency(0,739);delay(250);SetFrequency(0,783);SetFrequency(2,329);delay(250);SetFrequency(0,880);delay(250);SetFrequency(0,987);SetFrequency(2,391);delay(250);SetFrequency(1,493);delay(250);SetFrequency(1,523);delay(250);SetFrequency(0,1046);SetFrequency(1,440);SetFrequency(2,329);delay(125);SetFrequency(0,987);delay(125);SetFrequency(0,880);SetFrequency(1,493);delay(250);SetFrequency(1,391);delay(250);SetFrequency(1,440);SetFrequency(2,293);delay(250);
}
