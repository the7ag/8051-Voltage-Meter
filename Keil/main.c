/*
 * Copyright 2024 mohamed ali <the7ag22477@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * STC8H1K08
 *   AVref   -> VCC 
 *   Vcc     -> VCC
 *   Gnd     -> GND
 *   ADC1    -> Test voltage
*/

#include "fw_hal.h"

uint16_t adc_result;
uint8_t flag=0;
uint8_t level=0;
// Define GPIO pins for LEDs and Buzzer
#define LED_PIN_BASE GPIO_Pin_2 // Assume LEDs are connected to P1.2 - P1.5
#define BUZZER_PIN GPIO_Pin_6   // Assume buzzer is connected to P1.6

// Interrupt Service Routine for ADC
INTERRUPT(ADC_Routine, EXTI_VectADC)
{
    ADC_ClearInterrupt();
    adc_result = ADC_RESL;
    adc_result |= (ADC_RES & 0x0F) << 8;
    flag=1;
    // Restart ADC for continuous sampling
    ADC_Start();
}
/**
 * @brief Initializes the GPIO pins for LEDs and Buzzer.
 *
 * This function configures GPIO pins P1.2 to P1.5 as output pins for LEDs,
 * and P1.6 as an output pin for the buzzer. It also sets P1.1 as an input pin.
 */
void GPIO_Init(void)
{
    // Configure P1.2 to P1.5 as output for LEDs and P1.6 for Buzzer
    GPIO_P1_SetMode(GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | BUZZER_PIN, GPIO_Mode_Output_PP);
    
    // Configure P1.1 as an input pin
    GPIO_P1_SetMode(GPIO_Pin_1, GPIO_Mode_Input_HIP);
}
/**
 * @brief Initializes the ADC module.
 *
 * This function sets up the ADC module by selecting the
 * first channel (GPIO P1.1), setting the clock prescaler
 * to 15, aligning the result to the right, and enabling
 * the ADC interrupt. It also starts the ADC conversion.
 */
void ADC_Init(void)
{
    // Select the first channel (GPIO P1.1)
    ADC_SetChannel(0x01);
    // Set the clock prescaler to 15
    ADC_SetClockPrescaler(0x0F);
    // Align the result to the right
    ADC_SetResultAlignmentRight();
    // Enable the ADC interrupt
    EXTI_Global_SetIntState(HAL_State_ON);
    EXTI_ADC_SetIntState(HAL_State_ON);
    // Turn on the ADC power
    ADC_SetPowerState(HAL_State_ON);
    // Start the ADC conversion
    ADC_Start();
}

/**
 * @brief Updates the LEDs and buzzer based on the ADC result.
 *
 * This function takes the ADC result and maps it to a level between 0 and 10.
 * It then turns off all LEDs, and turns on the LEDs up to the current level.
 * If the level is 10, it also activates the buzzer.
 *
 * @param adc_value The ADC result value
 */
void UpdateOutputs(uint16_t adc_value)
{
    if (flag)
    {
        flag = 0;
        // Map ADC result to voltage levels (example: 0-1023 mapped to 10 levels)
        level = adc_value / 102; // Each level covers ~102 ADC units (10-bit ADC)

        // Turn off all LEDs
        P12 = RESET;
        P13 = RESET;
        P14 = RESET;
        P15 = RESET;
        P16 = RESET;

        // Turn on LEDs up to the current level
        if (level >= 1) P12 = SET;
        if (level >= 4) P13 = SET;
        if (level >= 7) P14 = SET;
        if (level >= 10) P15 = SET;

        // Activate buzzer if at the highest level
        P16 = (level >= 10) ? SET : RESET;
    }
}
/**
 * @brief The main entry point of the program.
 *
 * This function initializes the system clock, GPIO, and ADC,
 * and enters an infinite loop to continuously read ADC values
 * and update the LEDs and buzzer accordingly.
 */
void main(void)
{
    // Initialize the system clock
    SYS_SetClock();

    // Initialize the GPIO
    GPIO_Init();

    // Initialize the ADC
    ADC_Init();

    while (1)
    {
        // Check for errors
        if (adc_result == 0 || adc_result == 0xFFFF)
        {
            // Handle error, e.g. reset ADC
            ADC_SetPowerState(HAL_State_OFF);
            ADC_SetPowerState(HAL_State_ON);
        }
        else
        {
            // Update LEDs and buzzer based on ADC result
            UpdateOutputs(adc_result);
        }

        // Delay for 100ms
        SYS_Delay(100);
    }
}
