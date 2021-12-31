# R3-SoftwareTask1-JasonQuantrill

Link to TinkerCAD project:  https://www.tinkercad.com/things/4CSwvqEoNfi 

The potentiometer is hooked up to ground and 5V. There is a third wire coming out of it which is the output of the potentiometer. When dial is fully counterclockwise, resistance is high and no current/voltage is output. When the dial is fully clockwise, resistance is negligible and approximately 5V is the output. If the dial is halfway, voltage will be 2.5V.

This output is wired into the Arduino UNO's A0 input port. The input is read into the microcontroller using command "sensorValue = analogRead(potInPin);". When the Arduino reads in the voltage, 0V is represented as 0 and 5V is represented as 1023, and it scales linearly in between.

Since we have 2 7-segment displays, we are able to represent this 0-1023 from 0-99. To do this, we use the command "outputValue = map(sensorValue, 0, 1023, 0, 99);". The output value to be shown on the 7-segment displys is now scaled to the output of the potentiometer, where 0V is 00 and 5V is 99.

Next, this output value must be fed into the CD4511 module. This has (among other things) 4 input ports. Each of these input ports essentially represents 1 digit of a 4-digit binary number. These inputs then dictate which of its output ports are set to HIGH or LOW. The output ports are labelled from A-G which each correspond to one segment on the 7 segment display. For example, if the input ports are set: D0=0; D1=1; D2=0; D3=1; (which is 5 in binary), the outputs a, f, g, c, d will cause the corresponding segments on the 7-segment display to light up, displaying the number 5.

Since the outputValue that we currently have is in decimal, it must first be converted to binary so that the data is compatible with the CD4511 module. Additionally, since each 7-segment display can only display 1 digit the 2-digit decimal number must be handled as individual digits. The first digit can be obtained from ( outputValue / 10) , since Arduino uses floor division for integers. The second digit can be obtained from ( outputValue % 10). Each of these values is the fed into  the function "void decimalToBinary(int num)". This function is an algorithm to convert the digit from decimal to a 4-digit binary number. These 4 binary digits are then stored in the array binaryNum.

This array is then fed into the function void assignPins(int binaryNum[], int display), along with an output pin number from either the left or right 7-segment display. This function uses the 4-digit binary array to set the corresponding output pins to either HIGH or LOW. These outputs are then wired into the CD4511, and the correct decimal digit is displayed on the 7-segment display (as explained above).
