# STM32F446Re_USART_Baremetal

A tribute to Juice Wrld. 
999 Forever <3.

## About the project.

A building Controller using STM32 USART and GPIO for Building/Apartment Light, Temperature, Water Supply, and Humidity Control.

## Temperature Control

The controller can obtain the actual temperature value by employing a temperature sensor. However, for this lab, we use two jumper wires or toggle switches where 00 (both grounded/off) indicate the temperature is within the range of 23oC C to 27oC C. 10 or 01 (one jumper cable connected to VCC or switch-on) indicates the temperature is below 23oC and 11 indicates the temperature is above 27oC. In this case, the operation or expected temperature is 25oC, and the tolerance level is ± 2oC. The tolerance level defines that if the operating temperature is ToC, then heating is switched-on when the temperature is less than ToC − 2 and the cooling system switch-on when the temperature is above ToC + 2. We can replace the air conditioner or heating system by connecting two LEDs (two GPIO ports). We assume that the cooling/heating system can adjust the temperature within 30 seconds, and therefore, any of the two LEDs will switch on for 30 seconds. In the existing (real) system, the input temperature of the controller will change, and the controller will switch on/off the heating and cooling system. Also, the controller output will trigger an electronic switch on/off instead of directly controlling the A/C switch.

## Humidity/Water Level Control

Similar to the temperature control, we take two inputs to indicate current humidity below 40% and higher than 50%. The controller will switch off the pump for the water level above 55 liters and switch on the pump if the water level is below 45 liters (here, a LED).

## Room Light Control

Here we have three inputs (Jumper cables or switches), one of the inputs indicates the night or daytime. At night the input is 1, and day time it is 0. The other two inputs control the light bulb in the four rooms (Living (00), Dining (01), Bedroom (10), and office room (11))—the light bulb-switch on/off based on the input. However, the controller (terminal program) must send a light bulb configuration to set on for the control. All light bulbs are on at nighttime, depending on the configuration. The terminal program sends the configuration using USART2.

## Control Command – Design

The computer terminal program must send the initial configuration to the MCU, and the MCU controller program will store it to a variable known as ‘config.’ You must use the USART interrupt in the MCU to send or receive any configuration. (Using Interrupt handler)

### Config Init temp 25 water 50 hum 45 light 1111

The above initial configuration command instruct controller to set and store the initial configuration unless otherwise changed. To change the configuration to the light bulbs or any other devices, the command sample is as follows: Initial configuration must be sent to the MCU from your computer and will be stored to a variable known as ‘config’

### Config temp 27

The temperature set to 27oC. Similarly, for light blub

### Config light 1010

Living and Office rooms lights will respond for the day and night. To read the current configuration
use the following command from the terminal program:

### Read Config

For all configuration. To read the current configuration of the light bulb use the following command

### Read Config light

References : STM32F446Re Datasheet, Reference Manual STM32F446Re, UM1724 User manual.
