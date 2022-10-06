[![MCHP](images/microchip.png)](https://www.microchip.com)

 # Core Independent Quadrature Decoder using the AVR64DD32 Microcontroller with MCC Melody

Quadrature signals are the standard output waveforms of incremental encoders that come with motors. They provide information about motor direction and shaft position. There are two types of encoders - linear and rotary - and each can have two types of measurement: Absolute and incremental. There are also different technologies used for encoders: Magnetic, optical, inductive, capacitive, and laser. 

The main categories of encoders are absolute and incremental. A **rotary absolute encoder** outputs a unique code for each position of the motor's shaft. If the power of this encoder is lost and the shaft is rotated, the encoder can return the correct position of the shaft. The **rotary incremental encoder** generates pulses while the shaft is rotated. If any pulse is missed, then the shaft position cannot be determined correctly anymore.
This application will use a rotary incremental encoder to show how to decode quadrature signals.

The following image highlights the Clockwise (CW) and Counterclockwise (CCW) conditions on the quadrature signals A and B. When signal A leads signal B (on rising or falling edge), it will be a clockwise detection, otherwise, when signal B leads signal A (on rising or falling edge), it will be a counterclockwise detection.

<br><img src="images/cw_ccw.png" width="800">

The quadrature decoder uses the Configurable Custom Logic (CCL) on the AVR64DD32 to detect CW and CCW pulses. The following picture shows the output signals of the CCL implementation, CW and CCW, based on the quadrature signals A and B.

<br><img src="images/wavedrom.png" width="800">

Using the Event System (EVSYS) peripheral, the CW and CCW signals are linked to two TCB instances: One counts the CW pulses, the other one counts the CCW pulses.

##  Related Documentation

More details and code examples on the AVR64DD32 can be found at the following links:
- [Interfacing Quadrature Encoder using CCL with TCA and TCB](http://ww1.microchip.com/downloads/en/AppNotes/00002434A.pdf)
- [Getting Started with CCL](http://ww1.microchip.com/downloads/en/AppNotes/TB3218-Getting-Started-with-CCL-90003218A.pdf)
- [AVR64DD32 Product Page](https://www.microchip.com/wwwproducts/en/AVR64DD32)
- [AVR64DD32 Code Examples on GitHub](https://github.com/microchip-pic-avr-examples?q=AVR64DD32)

##  Software Used

- [MPLAB® X IDE 6.00 or newer](http://www.microchip.com/mplab/mplab-x-ide)
- [MPLAB® XC8 2.36 or a newer compiler](http://www.microchip.com/mplab/compilers)
- [AVR-Dx Series Device Pack v2.1.152 or newer](https://packs.download.microchip.com)
- [MPLAB® Code Configurator Melody core 2.1.13 or newer](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator/melody)
- [MPLAB® Code Configurator Melody Drivers](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator/melody)
- [MPLAB® Data Visualizer v1.2.1160 or newer](https://www.microchip.com/en-us/tools-resources/debug/mplab-data-visualizer)
- Logic analyzer software


##  Hardware Used

- AVR64DD32 Curiosity Nano Development Board is used as a test platform.<br>

<br><img src="images/AVR64DD32.PNG" width="640"><br>
<br>
- Oscilloscope/Logic Analyzer

- Rotary encoder <br>
    <img src="images/rotor.jpg" width="300"><br>

*Note*: The setup can be made using **rotary encoder** or **motor with encoder**. In this example we use the **rotary encoder**.

- Motor with encoder
    
    <img src="images/motor.jpg" width="300"><br>


## Operation

To program the Curiosity Nano board with this MPLAB® X project, follow the steps provided in the [How to Program the Curiosity Nano Board](#how-to-program-the-curiosity-nano-board) chapter.<br><br>


## 1. Setup

The following peripheral and clock configurations are set up using MCC Melody for the AVR64DD32:

- System Clock - 4 MHz (default)
- TCA0:
  - System Clock/64
  - Timer Mode 16 bit
  - Count Direction - UP
  - Overflow Interrupt Enable - every 1 second
  - Waveform Generation Mode - Normal Mode
- TCB0:
  - Clock Select - Event
  - Timer Mode: INT
  - Enable Asynchronous
  - Overflow Interrupt Enable
- TCB1:
  - Clock Select - Event
  - Timer Mode: INT
  - Enable Asynchronous
  - Overflow Interrupt Enable
- UART0:
  - Baudrate: 115200
  - Parity: None
  - Enable USART Transmit and Receive
  - Printf Support Enable
- EVSYS:
  - Configuration described in the below schematic
- CCL:
  - Configuration described in the below schematic

The following pin configurations must be made for this project:


|  Pin  |    Configuration    |      Function       |
| :---: | :-----------------: | :-----------------: |
|  PA4  | Input               | Phase A             |
|  PA5  | Input               | Phase B             |
|  PC0  | Output              | USART TX            |
|  PC1  | Input               | USART RX            |
|  PA6  | Output              | CW detection        |
|  PD3  | Output              | CCW detection       |


The internal connections and signals are presented in the following pictures:

<br><img src="images/quad_internal_connections.png" width="1200">

<br><img src="images/cases.png" width="1000">

 ## 2. Demo

In this demo, the function `QEI_GetVelocity` is called every second and the returned value is printed on the serial terminal. The hardware setup is presented in the image below:

<br><img src="images/portconn.jpg" width="1000">
<br>

Every second, the device prints a message with the counter value through the USART interface: 
<br>
<br><img src="images/serial-terminal.jpg" width="1000">

**Note:** Follow the steps in the **How to use MPLAB® Data Visualizer** section to set up the Data Visualizer so that it can correctly show the text messages through USART0.

A snapshot of the different signals from the logic analyzer can be seen below. The CW and CCW pulses correspond to the counter values **8** and **-8**.
<br>
<br><img src="images/Signals_Capture.jpg" width="1000">


 ## 3. Summary

The quadrature decoder can detect and count clockwise and counterclockwise pulses on rising and falling edges of the quadrature signals. Read more about the implementation at https://www.microchip.com/en-us/about/blog/design-corner/quadrature-decoder.


## How to use MPLAB® Data Visualizer

This section illustrates how to use the MPLAB® X Data Visualizer to send commands and receive information, but prior to programming the AVR64DD32 Curiosity Nano Board. This can be applied to any other projects.

### Operation

1. Open the software terminal in MPLAB® X IDE. Left click on the **Data Visualizer** button.
  <br><img src="./images/data_visualizer_button.png" width="1000"><br>

2. Select the **Input Source** corresponding to the AVR64DD32 in the right side.<br>

3. Identify the coresponding COMx that is represented by the AVR64DD32 Curiosity Nano Board and select it in the **Connections** tab in the left side.<br>

4. Set the specific **Baud Rate**, in this case **115200**.<br>

5. Press **Start streaming COMx button**. The text messages will appear in the **Terminal** tab.
<br><img src="./images/data_visualizer_config.png" width="1000">

##  How to Program the Curiosity Nano board

This chapter shows how to use the MPLAB® X IDE to program an AVR® device with an Example_Project.X. This can be applied for any other projects. 

- Connect the board to the PC.

- Open the Example_Project.X project in MPLAB X IDE.

- Set the Example_Project.X project as main project.

  - Right click on the project in the **Projects** tab and click **Set as Main Project**.
    <br><img src="images/Program_Set_as_Main_Project.PNG" width="600">

- Clean and build the Example_Project.X project.

  - Right click on the **Example_Project.X** project and select **Clean and Build**.
    <br><img src="images/Program_Clean_and_Build.PNG" width="600">

- Select the **AVRxxxxx Curiosity Nano** in the Connected Hardware Tool section of the project settings:

  - Right click on the project and click **Properties**
  - Click on the arrow under the Connected Hardware Tool
  - Select the **AVRxxxxx Curiosity Nano** (click on the **SN**), click **Apply** and then click **OK**:
    <br><img src="images/Program_Tool_Selection.PNG" width="600">

- Program the project to the board.
  - Right click on the project and click **Make and Program Device**.
    <br><img src="images/Program_Make_and_Program_Device.PNG" width="600">

<br>

- [Back to  Setup](#1-setup)
- [Back to  Demo](#2-demo)
- [Back to  Summary](#3-summary) 
- [Back to Top](#core-independent-quadrature-decoder-using-the-avr64dd32-microcontroller-with-mcc-melody)

