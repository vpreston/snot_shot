SnotShot Data Logger

This is a repo created by Victoria Preston on behalf of the Olin College and Ocean Alliance SnotBot development team.  SnotBot is an autonomous drone with the capabililty to track and collect blow samples from whales.  

SnotShot is a whale analogue used for testing.  Attached to this analogue is a sensor suite which detects whether or not a SnotBot is over the analoque, and records the height of the system via a link to a XBee radio on a computer ground station.

Hardware required:
- Arbotix Board
- XBee Radio
- Small Lithium Battery for Power
- Long Range Sonar
- Indicator Light

To set-up your computer hardware to use an Arbotix Board and related systems, follow the steps below, courtest of Garland O'Connell:

To program the Arbotix-M board a number of software routines must be loaded onto a PC.  Below is a link which provides great detail in the process, some of which works and some of which is iffy.

http://learn.trossenrobotics.com/arbotix/7-arbotix-quick-start-guide

The following is a list in order:
•	First download and install Arduino  IDE 1.0.5 from this site  http://arduino.cc/en/Main/Software
•	Then download and install the FTDI drivers 2.08.30 from http://www.ftdichip.com/Drivers/VCP.htm
•	Next download the library files for the Arbotix-M board, Arbotix-Master.zip, from https://codeload.github.com/trossenrobotics/arbotix/zip/master  Place these files in the Arduino working directory.
•	Next you need to download and install “USB AVR Programmer Windows Drivers and Software”, pololu-usb-avr-programmer-win-121114 (1).exe, from the site http://www.pololu.com/docs/0J36/3.a 
•	If you wish to use the Arbotix-M with Dynamixel servos, follow this link http://learn.trossenrobotics.com/arbotix/1-using-the-tr-dynamixel-servo-tool#&panel1-1 which first has you install JAVA from this site https://java.com/en/download/index.jsp  and then install the DynaManager Software from here https://github.com/trossenrobotics/dynaManager/releases   This will allow you to program the servos themselves and give each servo an ID number.
•	If you wish to program the XBEE radios follow the link http://learn.trossenrobotics.com/arbotix/10-configuring-xbees-for-the-arbotix#&panel1-1  which has you download the program X-CTU from http://www.digi.com/support/productdetail?pid=3352&osvid=57&type=utilities  and then download the file ” xbeeProfilesInterbotiX-master (1).zip” which contains file to load onto the XBEE radios.

Once all of this is done you might do the following:
•	Plug the AVR Programming board into a USB port on the PC.  It should find the drivers and install them.  Check the installation at “Control Panel”…”Device Manager”.  Assuming all went well record the lowest com port number used by the device.
•	Next plug in the USB to XBEE board, it goes by several names, and again check the Device Manager for the installed com port number.
•	Then start the Arduino IDE and select “Tools” “Board” and choose “Arbotix”.
•	The go to “Serial Port” and select the com port for the AVR Programmer board.
•	When you write the serial communication software in LabVIEW use the com port number which has been assigned to the USB to XBEE device.
