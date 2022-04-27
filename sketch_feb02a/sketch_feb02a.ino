
int redPin = 9;                // output pin number to Red pin of the LED
int greenPin = 10;              // output pin number to Green pin
int bluePin = 11;                // output pin number to Blue pin

int lightPin = A0;   // voltage input. Use any ADC pin (starts with A)
int hygrometerPin = A1;
int tempPin = A2;

int lightValue = 0;  // stores value from ADC
int hygrometerValue = 0;
int tempValue = 0;

int lightLow = 75;        // range for light, hygrometer, and temp
int lightHigh = 95;
int hygrometerLow = 10;
int hygrometerHigh = 25;
int tempLow = 65;
int tempHigh = 80;

String color = "green";
int blinkSpeed = 0;

const int inputLength = 30;
char inputValues[inputLength];
int index = 0;
int spaces = 0;
int readValue = 0;

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
  int lightMedian = (lightLow + lightHigh) / 2;
  int hygrometerMedian = (hygrometerLow + hygrometerHigh) / 2;
  int tempMedian = (tempLow + tempHigh) / 2;
  
  int lightRange = lightHigh - lightLow;
  int hygrometerRange = hygrometerHigh - hygrometerLow;
  int tempRange = tempHigh - tempLow;
  
  int lightValue = map(analogRead(lightPin), 0, 1023, 0, 100);   // reads the sensor
  int hygrometerValue = map(analogRead(hygrometerPin), 0, 1023, 0, 100);
  float tempValue = analogRead(tempPin) * 0.48828125;
  
  Serial.print(tempValue);   // Prints the value via the serial port
  Serial.print(" ");
  Serial.print(lightValue);
  Serial.print(" ");
  Serial.print(hygrometerValue);
  Serial.print(" ");

//    Serial.println(tempValue);
  
  float normalLightValue = ((float) (lightValue - lightMedian)) / lightRange;
  float normalHygrometerValue = ((float) (hygrometerValue - hygrometerMedian)) / hygrometerRange;
  float normalTempValue = ((float) (tempValue - tempMedian)) / tempRange;

 Serial.print(normalLightValue);   // Prints the value via the serial port
 Serial.print(" ");
 Serial.print(normalHygrometerValue);
 Serial.print(" ");
 Serial.println(normalTempValue);
  
  normalLightValue = abs(normalLightValue);
  normalHygrometerValue = abs(normalHygrometerValue);
  normalTempValue = abs(normalTempValue);
  

//  Serial.print(lightLow);   // Prints the value via the serial port
//  Serial.print(" ");
//  Serial.print(lightHigh);
//  Serial.print(" ");
//  Serial.print(hygrometerLow);
//  Serial.print(" ");
//  Serial.print(hygrometerHigh);
//  Serial.print(" ");
//  Serial.print(tempLow);
//  Serial.print(" ");
//  Serial.println(tempHigh);

//  Serial.println("------------------");

  if(normalLightValue > .5 && normalLightValue > normalHygrometerValue && normalLightValue > normalTempValue) {
    if (lightValue < lightLow) {
      color = "yellow";
      blinkSpeed = 1;
    } else {
      color = "yellow";
      blinkSpeed = 2;
    }
  } else if(normalHygrometerValue > .5 && normalHygrometerValue > normalLightValue && normalHygrometerValue > normalTempValue) {
    if (hygrometerValue < hygrometerLow) {
      color = "blue";
      blinkSpeed = 1;
    } else {
      color = "blue";
      blinkSpeed = 2;
    }
  } else if(normalTempValue > .5 && normalTempValue > normalHygrometerValue && normalTempValue > normalLightValue) {
    if (tempValue < tempLow) {
      color = "red";
      blinkSpeed = 1;
    } else {
      color = "red";
      blinkSpeed = 2;
    }
  } else {
    color = "green";
    blinkSpeed = 0;
  }
  setColor(color);
  doBlink(blinkSpeed);
}

void serialEvent()
{
  
  while(Serial.available()){
    char ch = Serial.read();
    if(ch == ' ')
      spaces++;
    if(index < inputLength && spaces < 6) {
      inputValues[index++] = ch;
    } else {
      index = 0;
      readValue = atoi(inputValues);
      tempLow = readValue;
      while(inputValues[index] != ' ')
        index++;
      index++;
      readValue = atoi(&inputValues[index]);
      tempHigh = readValue;
      while(inputValues[index] != ' ')
        index++;
      index++;
      readValue = atoi(&inputValues[index]);
      lightLow = readValue;
      while(inputValues[index] != ' ')
        index++;
      index++;
      readValue = atoi(&inputValues[index]);
      lightHigh = readValue;
      while(inputValues[index] != ' ')
        index++;
      index++;
      readValue = atoi(&inputValues[index]);
      hygrometerLow = readValue;
      while(inputValues[index] != ' ')
        index++;
      index++;
      readValue = atoi(&inputValues[index]);
      hygrometerHigh = readValue;
      index = 0;
      spaces = 0;
    }
  }
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
