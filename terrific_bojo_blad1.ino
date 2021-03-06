
const int potInPin = A0;  // Analog input pin that the potentiometer is attached to
const int leftDisplayPins = 13; // 4 Output pins corresponding to the left display, descending from 13 (13, 12, 11, 10)
const int rightDisplayPins = 5; // 4 Output pins corresponding to the right display, descending from 5 (5, 4, 3, 2)

int binaryNum[4]; // an array to hold a 4 digit binary representation of one of the decimal digits of the potentiometer's output

int sensorValue = 0; // value read from the potentiometer
int outputValue = 0; // output value to be displayed

void setup()
{
  // Setting all of these pins as outputs
  pinMode(leftDisplayPins, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  
  pinMode(rightDisplayPins, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
}

// Takes one 1-digit decimal number in, converts it to 4-digit binary
// Modifies the array "binaryNum" to hold this value
void decimalToBinary(int num)
{
  if ((num / 8) == 1) { // if the number is larger than or equal to 8, place a 1 in the 2^3 spot of the 4-digit binary number
    binaryNum[0] = 1;   // uses the remainder of this division to find rest of binary digits
    num %= 8;
  } 
  else {
    binaryNum[0] = 0;   // if number is smaller than 8, place a 0 in the 2^3 spot of the 4-digit binary number
  }						// move to next step of algorithm
  
  if ((num / 4) == 1) {
    binaryNum[1] = 1;
    num %= 4;
  }
  else {
    binaryNum[1] = 0;
  }
  
  if ((num / 2) == 1) {
    binaryNum[2] = 1;
    num %= 2;
  }
  else {
    binaryNum[2] = 0;
  }
  
  if ((num / 1) == 1) {
    binaryNum[3] = 1;
    num %= 1;
  }
  else {
    binaryNum[3] = 0;
  }
}

// Takes in a 4-digit binary number and sets the corresponding output according to the CD4511 decoder.
//    The display will show this output
// eg. if the decimal digit is 5, then the binary representation is 0101.
//    Output pins will be set such that the input to the CD4511 is as follows: D3=0; D2=1; D1=0; D0=1;
// Also takes in "display", which represents the left or right display
void assignPins(int binaryNum[], int display)
{
    for (int i = 0; i < 4; i++)
  	  {
        digitalWrite(display-i, binaryNum[i]);
  	  }
}


void loop()
{
  // reads in the analog value from the potentiometer
  sensorValue = analogRead(potInPin);
  // maps it to the range of the analog out (the 7-segment displays)
  outputValue = map(sensorValue, 0, 1023, 0, 99);
  
  // Sets the left display (the 10's digit of the output value)
  decimalToBinary(outputValue / 10); // floor division so that the 10's digit of outputValue is obtained
  assignPins(binaryNum, leftDisplayPins); // assigns output pins so the display shows the appropriate digit
  
  // Sets the right display (the 1's digit of the output value)
  decimalToBinary(outputValue % 10); // remainder division so that the 1's digit of outputValue is obtained
  assignPins(binaryNum, rightDisplayPins); // assigns output pins so the display shows the appropriate digit
}