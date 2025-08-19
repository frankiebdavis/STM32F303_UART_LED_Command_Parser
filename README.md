# 💡 STM32F303RE UART LED Control via PuTTY

This project demonstrates how to control the onboard LED (**PA5 / D13**) of the STM32F303RE Nucleo board using **UART serial communication**. A user types commands into a PuTTY terminal, and the microcontroller responds by toggling the LED accordingly.

---

## ❓ Problem

How can a user **control a microcontroller’s hardware (LED)** from a PC using a **simple text interface** like PuTTY — without requiring extra peripherals, buttons, or GUIs?

---

## 🔨 Method

- **UART2 Peripheral:** Configured at 38400 baud, connected over USB via ST-Link Virtual COM port.  
- **Interrupt-Based Reception:** Incoming characters are appended into a buffer.  
- **Command Parsing:** When Enter (`\r`) is pressed, the buffer is compared against expected strings.  
- **Actions:** If input matches `LED ON` or `LED OFF`, the LED at **PA5 (D13)** is toggled. Any other input is ignored.  

Command → Action mapping:  
| Command   | Behavior               |
|-----------|------------------------|
| `LED ON`  | Turns LED **ON**       |
| `LED OFF` | Turns LED **OFF**      |
| Other     | No effect (ignored)    |

---

## ✅ Result

The system correctly interprets user commands typed into PuTTY:  

1. Typing `HELLO` → ignored.  
2. Typing `LED ON` → LED at PA5 turns **ON**.  
3. Typing `LED OFF` → LED at PA5 turns **OFF**.  
4. Typing `LED ON` again → LED turns **ON** again.  

🎥 Demo: [Watch Here](https://youtube.com/shorts/VSkRn4X--_U)  

[![Demo Video](https://img.youtube.com/vi/VSkRn4X--_U/0.jpg)](https://youtube.com/shorts/VSkRn4X--_U)

---

## 🔧 Hardware

- STM32F303RE Nucleo board  
- USB connection via ST-Link (provides power + virtual COM port)  
- PuTTY terminal on PC  

---

## 💻 Serial Setup

1. Plug in the Nucleo board via USB.  
2. Check the COM port in **Device Manager** (Windows).  
3. Open **PuTTY** → Connection type: Serial.  
   - Serial line: e.g., `COM7`  
   - Speed (baud): **38400**  
4. Send text commands to interact with the LED.  

---

## 🧠 Takeaways

- Implemented **interrupt-driven UART** reception with HAL.  
- Practiced **buffer handling** and `strcmp()` parsing in C.  
- Learned real-time debugging with **Live Expressions** in STM32CubeIDE to monitor input and LED state.  
- Reinforced the concept of **human-to-hardware interfacing** using nothing but serial text commands.  

---
