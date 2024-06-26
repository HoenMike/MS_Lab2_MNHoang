/* USER CODE BEGIN Header */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4]; // LED Status

int hour = 15, minute = 8, second = 50;

// DOT_COUNTER = 1 times per second, LED_SWITCH_COUNTER = 500 * 4 (7Seg) = 0.5Hz, CLOCK_COUNTER = 1 second counter;
const int DOT_COUNTER = 100, LED_SWITCH_COUNTER = 25, CLOCK_COUNTER = 100;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);

/* USER CODE BEGIN PFP */
void display7SEG(int displayNumber);
void update7SEG(int index);
void updateClockBuffer();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  // Initialize 7-segment display & timer
  setTimer0(DOT_COUNTER);
  setTimer1(LED_SWITCH_COUNTER);
  setTimer2(CLOCK_COUNTER);
  updateClockBuffer();

  while (1)
  {

    if (timer0_flag == 1)
    {
      HAL_GPIO_TogglePin(GPIOA, DOT_Pin);
      HAL_GPIO_TogglePin(GPIOA, LED_RED_Pin);
      setTimer0(DOT_COUNTER);
    } // end of timer0_flag

    if (timer1_flag == 1)
    {
      update7SEG(index_led++);
      if (index_led >= MAX_LED)
      {
        index_led = 0;
      }
      setTimer1(LED_SWITCH_COUNTER);
    } // end of timer1_flag

    if (timer2_flag == 1)
    {
      second++;
      if (second >= 60)
      {
        second = 0;
        minute++;
      }
      if (minute >= 60)
      {
        minute = 0;
        hour++;
      }
      if (hour >= 24)
      {
        hour = 0;
      }
      updateClockBuffer();
      setTimer2(CLOCK_COUNTER);
    } // end of timer2_flag
  }
}
/* USER CODE END WHILE */

/* USER CODE BEGIN 3 */
void display7SEG(int displayNumber)
{
  switch (displayNumber)
  {
  case 1:
    HAL_GPIO_WritePin(GPIOB, B_Pin | C_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, A_Pin | D_Pin | E_Pin | F_Pin | G_Pin, GPIO_PIN_SET);
    break;
  case 2:
    HAL_GPIO_WritePin(GPIOB, A_Pin | B_Pin | G_Pin | E_Pin | D_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, C_Pin | F_Pin, GPIO_PIN_SET);
    break;
  case 3:
    HAL_GPIO_WritePin(GPIOB, A_Pin | B_Pin | G_Pin | C_Pin | D_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, E_Pin | F_Pin, GPIO_PIN_SET);
    break;
  case 4:
    HAL_GPIO_WritePin(GPIOB, F_Pin | G_Pin | B_Pin | C_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, A_Pin | D_Pin | E_Pin, GPIO_PIN_SET);
    break;
  case 5:
    HAL_GPIO_WritePin(GPIOB, A_Pin | F_Pin | G_Pin | C_Pin | D_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, B_Pin | E_Pin, GPIO_PIN_SET);
    break;
  case 6:
    HAL_GPIO_WritePin(GPIOB, A_Pin | F_Pin | G_Pin | C_Pin | D_Pin | E_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_SET);
    break;
  case 7:
    HAL_GPIO_WritePin(GPIOB, A_Pin | B_Pin | C_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, D_Pin | E_Pin | F_Pin | G_Pin, GPIO_PIN_SET);
    break;
  case 8:
    HAL_GPIO_WritePin(GPIOB, A_Pin | B_Pin | C_Pin | D_Pin | E_Pin | F_Pin | G_Pin, GPIO_PIN_RESET);
    break;
  case 9:
    HAL_GPIO_WritePin(GPIOB, A_Pin | B_Pin | C_Pin | D_Pin | F_Pin | G_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_SET);
    break;
  case 0:
    HAL_GPIO_WritePin(GPIOB, A_Pin | B_Pin | C_Pin | D_Pin | E_Pin | F_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_SET);
    break;

  default:
    break;
  }
  return;
}

void update7SEG(int index)
{
  if (index >= MAX_LED)
  {
    index = 0;
  }
  switch (index)
  {
  case 0:
    HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, EN2_Pin | EN3_Pin | EN1_Pin, GPIO_PIN_SET);
    display7SEG(led_buffer[0]);
    break;
  case 1:
    HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN2_Pin | EN3_Pin, GPIO_PIN_SET);
    display7SEG(led_buffer[1]);
    break;
  case 2:
    HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN1_Pin | EN3_Pin, GPIO_PIN_SET);
    display7SEG(led_buffer[2]);
    break;
  case 3:
    HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, EN2_Pin | EN0_Pin | EN1_Pin, GPIO_PIN_SET);
    display7SEG(led_buffer[3]);
    break;
  default:
    break;
  }
}

void updateClockBuffer()
{
  led_buffer[0] = hour / 10;
  led_buffer[1] = hour % 10;
  led_buffer[2] = minute / 10;
  led_buffer[3] = minute % 10;

  // if (hour < 10)
  // {
  //   led_buffer[0] = 0;
  //   led_buffer[1] = hour;
  // }
  // if (minute < 10)
  // {
  //   led_buffer[2] = 0;
  //   led_buffer[3] = minute;
  // }
}
/* USER CODE END 3 */

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */
  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */
  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */
  /* USER CODE END TIM2_Init 2 */
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DOT_Pin | LED_RED_Pin | EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, A_Pin | B_Pin | C_Pin | D_Pin | E_Pin | F_Pin | G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : DOT_Pin LED_RED_Pin EN0_Pin EN1_Pin
                           EN2_Pin EN3_Pin */
  GPIO_InitStruct.Pin = DOT_Pin | LED_RED_Pin | EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : A_Pin B_Pin C_Pin D_Pin
                           E_Pin F_Pin G_Pin */
  GPIO_InitStruct.Pin = A_Pin | B_Pin | C_Pin | D_Pin | E_Pin | F_Pin | G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  timerRun();
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
