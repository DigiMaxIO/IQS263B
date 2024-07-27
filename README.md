# IQS263B-CapWheel2-Click-Arduino
Arduino Library for the MikroE CapWheel2 Click, using the IQS263B I2C Capacitive Chip from Azoteq
This Library was ported via the MikroSDK Example Project & Library.

Note: I believe MikroE made some mistakes on this design:

1. The Capacitive Sensors have no inline resistors for noise reduction.
2. The design of the Wheel Sensors is wrong
3. VDDHI Capacitor Missing

Unfortunately, because of these issues, the resolution of the wheel is completely broken.
