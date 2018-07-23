# powerModule Control Board Firmware

Developed for HKUST Robomaster team Enterprize by Alex Wong.

Uses ChibiOS for HAL and RTOS. 

The controller is a STM32F103C6T8 on custom PCB. Read Power Module V1.pdf for schematics and layout snapshot.

## The powerModule feature 3 operation modes:

Mode 0 (DIODE) : Whichever path with high voltage is connected to the powerModule output, reserved for emergency only.

Mode 1 (JUDGE) : The judgement system chassis power output is connected to the powerModule output. When operating in this mode, the powerModule has no control of the chassis power draw and the chassis controller should limit the chassis power draw. If the chassis is not drawing power at the power limit, the surplus power is stored into the super capacitor.

Mode 2 (BOOST) : The super capacitor is connected to the powerModule output through a boost regulator. The chassis should not draw more than 1.2kW. The judgement system power output is connected to the super capacitor charger and charged at the power limit.

## powerModule control

Send a 2-byte CAN packet to the powerModule with ID 0x055, data definition as follows:
    byte 0, uint8_t : pathType, 1 = judge power, 2 = cap power
    byte 1, uint8_t : robotType, 1 = 80W limit, 2 = 120W limit

##powerModule feedback

The powerModule sends a 8-byte CAN packet to the chassis conroller at 1000Hz, data definition as follows:
    byte 0, uint8_t : Battery Voltege, in volts
    byte 1, uint8_t : pathType, 1 = judge power, 2 = cap power
    byte 2-3 int16_t : capacitor energy available, in joules
    byte 4-5 uint16_t : power draw from judgement system, in watts
    byte 6-7 uint16_t : power draw of chassis, in watts
