Morse Code Joystick Input System

A custom Arduino-based Morse code input device using a joystick and a 20×4 I2C LCD.
The system converts joystick movements into Morse code, decodes it into text, and displays it in real time.

⭐ Features
🎮 Joystick-Based Input
Joystick Direction	Action
Up	Dot (.)
Right	Dash (-)
Down	Space between letters → Immediate decode
Left	Backspace (single delete)
Hold Left (1 sec)	Clear all text

All inputs use edge detection, meaning holding the joystick won’t cause repeated inputs.

🔠 Supported Characters
Letters (A–Z)

Standard Morse code.

Numbers

0–9

Punctuation

. , ? ' ! / ( ) & : ; = + - _ " $ @

🤖 Smart Behavior
⏳ Idle Auto-Clear

If no input occurs for 5 seconds, the next joystick movement will:

Clear the screen

Reset buffers

Then process that new movement normally

🔄 Real-Time Decoding

Morse is decoded automatically when pressing Down (space).

📟 LCD Automatic Wrapping

Text wraps across 4 lines (20 characters per line).

🛑 Hold Protection

Holding a direction does not repeatedly trigger dot/dash/backspace.

HOLD is used only for clearing the screen.

🛠 Hardware Requirements

Arduino Uno / Nano

Joystick module

I2C LCD 20×4 (address: 0x27)

Jumper wires

🔌 Wiring Guide
Joystick to Arduino
Joystick Pin	Arduino Pin
VRX	A0
VRY	A1
VCC	5V
GND	GND
LCD to Arduino
LCD Pin	Arduino Pin
SDA	A4
SCL	A5
VCC	5V
GND	GND
🚀 How to Use

Power the Arduino.

Move joystick Up → dot

Move joystick Right → dash

Move joystick Down → space (decode letter)

Move joystick Left → backspace

Hold Left for 1 second → clear screen
