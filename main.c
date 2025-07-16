/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : UART-controlled LED via PuTTY on STM32F303RE
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>  // For string handling functions like strcmp

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

// UART transmission buffer
uint8_t tx_buffer[] = "Welcome!\n\r";

// UART reception
uint8_t rx_indx = 0;           // Current index in rx_buffer
uint8_t rx_data[2];            // Temporary byte storage during RX interrupt
uint8_t rx_buffer[100];        // Full buffer to store user command
uint8_t transfer_cplt = 0;     // Flag indicating full command received

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{
  HAL_Init();                 // Reset all peripherals and initialize HAL
  SystemClock_Config();      // Configure system clocks
  MX_GPIO_Init();            // Initialize onboard LED GPIO
  MX_USART2_UART_Init();     // Initialize UART2

  // Start receiving UART data in interrupt mode
  HAL_UART_Receive_IT(&huart2, rx_data, 1);

  while (1)
  {
    // Idle loop — logic handled in UART callback
  }
}

/**
  * @brief UART receive complete callback
  * This is called after each received byte.
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART2)
  {
    // First byte in command: clear buffer
    if (rx_indx == 0)
      memset(rx_buffer, 0, sizeof(rx_buffer));

    // If not carriage return (Enter key)
    if (rx_data[0] != 13)
    {
      rx_buffer[rx_indx++] = rx_data[0];
      rx_buffer[rx_indx] = '\0';  // Keep buffer null-terminated
    }
    else
    {
      // Full command received
      rx_indx = 0;
      transfer_cplt = 1;

      HAL_UART_Transmit(&huart2, (uint8_t*)"\n\r", 2, 100);

      // Compare full string and take action
      if (!strcmp((char*)rx_buffer, "LED ON"))
      {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
      }
      else if (!strcmp((char*)rx_buffer, "LED OFF"))
      {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
      }
      // Else: do nothing for unrecognized commands
    }

    // Re-arm UART RX interrupt for next byte
    HAL_UART_Receive_IT(&huart2, rx_data, 1);

    // Echo received character back (optional)
    HAL_UART_Transmit(&huart2, rx_data, strlen((char*)rx_data), 100);
  }
}
