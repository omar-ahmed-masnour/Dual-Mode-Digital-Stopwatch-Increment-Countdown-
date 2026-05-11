# Dual-Mode-Digital-Stopwatch-Increment-Countdown-

A versatile digital stopwatch implemented on an ATmega32 microcontroller, featuring six multiplexed seven-segment displays and two distinct operational modes: precise increment counting and user-defined countdown timing. 
Key Features
	• Dual Mode Operation: Default Increment Mode for upward counting and a toggleable Countdown Mode for timer functionality. 
	• Dynamic Time Adjustment: Dedicated buttons for incrementing and decrementing hours, minutes, and seconds independently. 
	• Control Interface: Hardware-level Reset, Pause, and Resume functions utilizing external interrupts. 
	• Alert System: Integrated buzzer alarm that triggers when the countdown reaches zero. 
	• Status Indicators: Red LED for Increment mode and Yellow LED for Countdown mode. 
Technical Specifications
	• Microcontroller: ATmega32 (16 MHz). 
	• Timer Configuration: Timer1 configured in CTC Mode (Clear Timer on Compare Match) for high-precision timekeeping. 
	• External Interrupts:
		○ INT0: Reset function (Falling edge, internal pull-up). 
		○ INT1: Pause function (Rising edge, external pull-down). 
		○ INT2: Resume function (Falling edge, internal pull-up). 
	• Display Logic:
		○ Six common-anode seven-segment displays. 
		○ Multiplexing Technique: Utilizes Persistence of Vision (POV) by switching displays via NPN BJT transistors at high speed. 
		○ BCD Decoding: Driven by a 7447 BCD to 7-segment decoder to minimize MCU pin usage. 
Hardware Components
	• ATmega32 Microcontroller. 
	• 6x Seven-Segment Displays. 
	• 7447 Decoder IC. 
	• 10x Push Buttons. 
	• NPN BJT Transistors (BC547/BC548). 
	• Buzzer and LED indicators. 
A versatile digital stopwatch implemented on an **ATmega32** microcontroller, featuring six multiplexed seven-segment displays and two distinct operational modes: precise increment counting and user-defined countdown timing.

## Key Features
* **Dual Mode Operation**: Default **Increment Mode** for upward counting and a toggleable **Countdown Mode** for timer functionality.
* **Dynamic Time Adjustment**: Dedicated buttons for incrementing and decrementing hours, minutes, and seconds independently.
* **Control Interface**: Hardware-level **Reset**, **Pause**, and **Resume** functions utilizing external interrupts.
* **Alert System**: Integrated buzzer alarm that triggers when the countdown reaches zero.
* **Status Indicators**: Red LED for Increment mode and Yellow LED for Countdown mode.

## Technical Specifications
* **Microcontroller**: ATmega32 (16 MHz).
* **Timer Configuration**: **Timer1** configured in **CTC Mode** (Clear Timer on Compare Match) for high-precision timekeeping.
* **External Interrupts**:
  * **INT0**: Reset function (Falling edge, internal pull-up).
  * **INT1**: Pause function (Rising edge, external pull-down).
  * **INT2**: Resume function (Falling edge, internal pull-up).
* **Display Logic**:
  * Six common-anode seven-segment displays.
  * **Multiplexing Technique**: Utilizes Persistence of Vision (POV) by switching displays via NPN BJT transistors at high speed.
  * **BCD Decoding**: Driven by a **7447 BCD to 7-segment decoder** to minimize MCU pin usage.

## Hardware Components
* **ATmega32 Microcontroller**.
* **6x Seven-Segment Displays**.
* **7447 Decoder IC**.
* **10x Push Buttons**.
* **NPN BJT Transistors (BC547/BC548)**.
* **Buzzer and LED indicators**.
