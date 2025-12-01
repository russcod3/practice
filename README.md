<h1 align="center">Arduino Morse Code Joystick ⬆️⬇️⬅️➡️</h1>
<h3 align="center">A Morse-to-Text interface using a joystick and 20x4 LCD for disabled and elderly-friendly input</h3>
<p align="center">
</p>

## 📝 ┊ Overview
This Arduino project allows users to input text using a joystick as a Morse code interface. The system is designed for accessibility, ensuring that **holding the joystick does not register multiple inputs** for dots, dashes, spaces, or backspace. A 20x4 LCD displays the translated text in real-time.

Features:
- Single-input per joystick movement (no repeated inputs on hold)
- Backspace deletes one character; long-hold clears all text
- Space, dots, and dashes follow the same single-input rule
- 5-second idle reset: if no input occurs for 5 seconds, the next input clears the screen first

---

## 📚 ┊ Project Structure
📂 MorseJoystick/
├── MorseJoystick.ino
├── README.md
└── libraries/
└── LiquidCrystal_I2C/

- `MorseJoystick.ino` - Main Arduino sketch containing joystick input, Morse code translation, and LCD output.
- `libraries/LiquidCrystal_I2C` - Required library for controlling the 20x4 LCD.

---

## ⚙️ ┊ Hardware Requirements
- Arduino Uno or compatible board  
- 20x4 I2C LCD (LiquidCrystal_I2C)  
- Analog joystick module  
- Jumper wires and breadboard  

---

## 🎮 ┊ How It Works
1. **Joystick Up (Y-axis < 300)** → Registers a **dot (.)**  
2. **Joystick Right (X-axis > 700)** → Registers a **dash (-)**  
3. **Joystick Down (Y-axis > 700)** → Registers a **space**  
4. **Joystick Left (X-axis < 300)** → **Backspace**, deletes one character; hold for 1 second → clears all text  

**Notes:**
- Each input is only registered once per joystick movement, preventing accidental repeats for elderly or disabled users.
- The 5-second idle reset ensures that if no activity occurs for 5 seconds, the next input will first clear the screen before adding the new character.

---

## 🔧 ┊ Installation & Usage
1. Install the `LiquidCrystal_I2C` library via Arduino IDE Library Manager.
2. Connect the joystick module:
   - VRx → A0  
   - VRy → A1  
   - GND → GND  
   - VCC → 5V
3. Connect the 20x4 I2C LCD to SDA/SCL pins.
4. Upload `MorseJoystick.ino` to your Arduino.
5. Move the joystick to input Morse code; text appears on the LCD.

---

## 💡 ┊ Design Considerations
- **Accessibility:** Edge detection prevents repeated character input when the joystick is held.
- **Safety:** Backspace removes one character at a time; full clear requires a deliberate long hold.
- **Feedback:** 20x4 LCD displays the current buffer and updates in real-time.
- **Idle Reset:** Ensures accidental or forgotten inputs do not confuse the user; clears old text after inactivity.

---

## 🚀 ┊ Future Enhancements
- **SMS Feature:** Send the translated Morse code as a text message using a GSM module.  
- **Text-to-Speech Feature:** Convert the final text to audio output for visually impaired users.

---

## 📄 ┊ Example LCD Output
HELLO WORLD

yaml
Copy code
- Moving the joystick up once: adds `.`
- Moving the joystick right once: adds `-`
- Moving down: adds a space
- Moving left once: deletes one character
- Hold left for 1 second: clears entire LCD

---

## 🎨 ┊ Visual Joystick Mapping
markdown
Copy code
    UP
    ⬆️
    DOT (.)
LEFT ⬅️ BACKSPACE DASH (-) ➡️ RIGHT
⬇️
DOWN
SPACE


This diagram shows how each joystick movement maps to a Morse code action.

---

## 📝 ┊ Notes for Users
- Move joystick **back to the center** before entering the next dot, dash, space, or backspace.
- The system is optimized for elderly and disabled users to **avoid repeated accidental inputs**.
- The LCD displays the last 80 characters (20x4). Older text scrolls off as new input is added.

---
