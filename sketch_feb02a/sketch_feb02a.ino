
int redPin = 9;                // output pin number to Red pin of the LED
int greenPin = 10;              // output pin number to Green pin
int bluePin = 11;                // output pin number to Blue pin
int lightSensorPin = A0;   // voltage input. Use any ADC pin (starts with A)
int hygrometerPin = A1;
int lightSensorValue = 0;  // stores value from ADC
int hygrometerValue = 0;
String color = "green";
int blinkSpeed = 0;

void setup()                    // this runs once, when the sketch starts
{
  pinMode(redPin, OUTPUT);      // sets the pin as output pin
  pinMode(greenPin, OUTPUT);    // sets the pin as output pin
  pinMode(bluePin, OUTPUT);     // sets the pin as output pin
  Serial.begin(115200);    // Opens serial port, Baud Rate 115200 bps
}

void setColor(String color);
void doBlink(int blinkSpeed);

void loop()                     // this runs over and over again forever
{
  int lightSensorValue = analogRead (lightSensorPin);   // reads the sensor
  int hygrometerValue = analogRead (hygrometerPin);
  Serial.print(lightSensorValue);   // Prints the value via the serial port
  Serial.print(" ");
  Serial.println(hygrometerValue);

  
  if (lightSensorValue < 800) {
    color = "yellow";
    blinkSpeed = 1;
  } else if (lightSensorValue > 980) {
    color = "yellow";
    blinkSpeed = 2;
  } else if (hygrometerValue < 10) {
    color = "blue";
    blinkSpeed = 1;
  } else if (hygrometerValue > 25) {
    color = "blue";
    blinkSpeed = 2;
  } else {
    color = "green";
    blinkSpeed = 0;
  }
  setColor(color);
  doBlink(blinkSpeed);
}

void setColor(String color){
  if (color == "yellow") {
    analogWrite(redPin, 255);
    analogWrite(greenPin, 90);
    analogWrite(bluePin, 0);
  } else if (color == "blue") {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 255);
  } else if (color == "red") {
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  } else if (color == "green"){
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
  } else if (color == "off"){
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  }
}

void doBlink(int blinkSpeed){
  if (blinkSpeed == 1) {
    delay(700);
    setColor("off");
    delay(700);
  } else if (blinkSpeed == 2) {
    delay(300);
    setColor("off");
    delay(300);
  } else
    delay(500);
}
