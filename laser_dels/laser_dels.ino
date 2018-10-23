#define     GAME_WON_DIGITAL_TRESHOLD_LOW         980
#define     GAME_WON_DIGITAL_TRESHOLD_HIGH        1008

enum game_state_type {
  GAME_IDLE,
  GAME_IN_PROGRESS,
  GAME_WON,
};


int red_led_1 = 2;
int red_led_2 = 3;
int green_led_1 = 4;
int green_led_2 = 5;
int photodiode_digital_value = 0;
int analog_pin = 3;
bool first_iteration_red_led = false;
bool first_iteration_green_led = false;




game_state_type actual_game_state = GAME_IDLE;

void setup() {
  // put your setup code here, to run once:
  pinMode(red_led_1, OUTPUT);
  pinMode(red_led_2, OUTPUT);
  pinMode(green_led_1, OUTPUT);
  pinMode(green_led_2, OUTPUT);    
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (actual_game_state) {
      case GAME_IDLE:
          digitalWrite(red_led_1, HIGH);
          delay(10);
          digitalWrite(red_led_2, HIGH);
          delay(10);
          digitalWrite(green_led_1, HIGH);
          delay(10);
          digitalWrite(green_led_2, HIGH);
          delay(10);
          digitalWrite(red_led_1, LOW);
          digitalWrite(red_led_2, LOW);
          digitalWrite(green_led_1, LOW);
          digitalWrite(green_led_2, LOW);
          actual_game_state = GAME_IN_PROGRESS;
          break;
      case GAME_IN_PROGRESS:
          if (!first_iteration_red_led) {
              digitalWrite(red_led_1, HIGH);
              digitalWrite(red_led_2, HIGH);
              first_iteration_red_led = true;
          }
          photodiode_digital_value = analogRead(analog_pin);
          if (photodiode_digital_value > GAME_WON_DIGITAL_TRESHOLD_LOW && photodiode_digital_value < GAME_WON_DIGITAL_TRESHOLD_HIGH) {
              actual_game_state = GAME_WON;
          }
          break;
      case GAME_WON:
          if (!first_iteration_green_led) {
              digitalWrite(red_led_1, LOW);
              digitalWrite(red_led_2, LOW);
              digitalWrite(green_led_1, HIGH);
              digitalWrite(green_led_2, HIGH);
              first_iteration_green_led = true;
          }
          break;   
  }
  Serial.println(photodiode_digital_value);             // debug value
}
