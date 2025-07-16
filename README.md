# STM32F303RE UART LED Control via PuTTY

This project demonstrates how to control an onboard LED connected to pin **D13 (PA5)** on the STM32F303RE Nucleo board using **UART serial communication**. Through a PuTTY serial terminal, specific string commands are sent from a computer to the microcontroller. Based on the received command, the LED is either turned ON, turned OFF, or left unchanged.

## Overview

- **Board:** STM32F303RE Nucleo
- **Communication:** UART2 over USB (via PuTTY)
- **Interface:** Serial terminal input (ASCII command strings)
- **Functionality:** Interprets user input to control onboard LED
- **Baud Rate:** 38400
- **LED Pin:** PA5 (labeled as D13 on the Nucleo board)

## How It Works

The microcontroller continuously listens for input from the UART2 peripheral using interrupt-based reception. When a complete message is received (terminated by a carriage return), the input is checked against expected command strings:

| Command      | Behavior                   |
|--------------|----------------------------|
| `LED ON`     | Turns on the LED (PA5)     |
| `LED OFF`    | Turns off the LED (PA5)    |
| Any other input | No effect (ignored)     |

Internally, an interrupt service routine appends received characters to a buffer until the carriage return is detected (`\r`), at which point the command is parsed and executed.

## Serial Communication Setup

To communicate with the STM32F303RE board:

1. Connect the Nucleo board via USB to your PC.
2. Identify the **COM port** using Device Manager (Windows).
3. Open **PuTTY** and configure:
   - **Connection type:** Serial
   - **Serial line:** (e.g., `COM7`)
   - **Speed (baud):** `38400`
4. Open the terminal and send the command strings.

## Demo Video 🎥

[![Demo Video](https://img.youtube.com/vi/VSkRn4X--_U/0.jpg)](https://youtube.com/shorts/VSkRn4X--_U)

🔗 **Watch the demo**: [https://youtube.com/shorts/VSkRn4X--_U](https://youtube.com/shorts/VSkRn4X--_U)

### What the video shows:
1. User first types `HELLO` – no response (invalid command).
2. Then types `LED ON` – LED turns **on**.
3. Then types `LED OFF` – LED turns **off**.
4. Finally types `LED ON` again – LED turns **on** again to confirm toggle functionality.

## Learning Highlights

During this project, I became comfortable with:
- Using **interrupt-based UART communication** in STM32CubeIDE.
- Handling character buffers and string comparison in C.
- Debugging UART behavior via the **Live Expressions** tab in STM32CubeIDE, which allowed real-time tracking of character reception, buffer content, and LED state during runtime.
- Creating a clean `main.c` with properly encapsulated logic in the `HAL_UART_RxCpltCallback()`.

## License

This project is released under the [MIT License](LICENSE).
