# NightLite
Implements a Nightlight with configurable lighting and sound controls using the ATxmega128A1U on an Out of the Box (OOTB) uPAD 2.0 as well as the Analog Backpack and an external power block (needed to power the speaker).

See https://ootbrobotics.com/products/upad-2/ for a description of the uPAD 2.0 for information and availability.

To interface with the uPAD 2.0, this project uses PuTTY.
Windows download links:
* 64-bit PuTTY: https://the.earth.li/~sgtatham/putty/latest/w64/putty.exe
* 32-bit PuTTY: https://the.earth.li/~sgtatham/putty/latest/w32/putty.exe
* To use PuTTY, select SSH connection type and in the Serial settings (under SSH), configure the baudrate as 2,000,000. Also configure the frame to have 8 data bits, even parity, 1 stop bit, and turn Flow control to None. Finally, select the serial line to connect to (COMXX). Determine what COM to use from the device manager list.


To write the program and data to the microcontroller, install Atmel Studio 7 following the guide linked below:
http://atmel-studio-doc.s3-website-us-east-1.amazonaws.com/webhelp/GUID-54E8AE06-C4C4-430C-B316-1C19714D122B-en-US-1/index.html?GUID-8F63ECC8-08B9-4CCD-85EF-88D30AC06499

To run NightLite, create a GCC C Executable Project.
Then, move the downloaded source files into the project.
Then, right-click project > Add > Add Existing > Select the source files and press OK / Apply.
Then, navigate to Project > AVR/GNU C Compiler > Optimization > Set the optimization to None
NOTE: For NightLite to run properly, the optimization of the GCC compiler MUST be set to (-O0) NONE.
<How to setup programmer>

Finally, some documentation about the ATxmega128A1U is linked below:

https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8331-8-and-16-bit-AVR-Microcontroller-XMEGA-AU_Manual.pdf
https://ww1.microchip.com/downloads/en/DeviceDoc/ATxmega128A1U-64A1U-Data-Sheet-DS40002058A.pdf
