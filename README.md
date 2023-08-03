# RP2040-Zero GameCube Controller

This software project aims to transform the RP2040-Zero into a functional GameCube controller. It allows you to use the RP2040-Zero as a game controller with support for analog controls (except for triggers).

- [Legal information and license](#legalInformationAndLicense)
- [Features](#features) 
- [RP2040 Perks](#rp2040perks)
- [Pin Mapping](#pinMapping)
- [Getting Started](#gettingStarted)

<a name="legalInformationAndLicense"/>

This project is free to use for personal use; i.e for use with controllers you build and use yourself, usually referred to as "DIY controllers".

You may not sell devices with this firmware uploaded or suggest to people to use this firmware with a device you sell, past the first 50 devices sold.
You may not upload this firmware onto a device you've bought that didn't come with a license for it.

You may not use parts of this firmware in another firmware used for anything but personal use, and may not redistribute parts of this firmware under a license that waives this requirement.
Should you want to use this firmware or parts of this firmware commercially, contact me.

### LEGAL INFORMATION

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

<a name="features"/>

### Features
- Turn your RP2040-Zero into a GameCube controller
- Full support for analog controls (except triggers)
- Easy to use and configure


<a name="rp2040perks"/>

### RP2040 Perks

- 29 × multi-function GPIO pins (20× via edge pinout, others via solder points).

- No 5V input required (Voltage regulator accepts 3.3V)

- No logic level shifter required (3.3V GPIO by default)

- Extremely simple programming (USB drag and drop)
  
- 2 × SPI, 2 × I2C, 2 × UART, 4 × 12-bit ADC, 16 × controllable PWM channels.
  
- Very cheap ($4~5) and widely available

<a name="pinMapping"/>

### Pin Mapping
Here's the pin mapping for the RP2040-Zero GameCube Controller:

- Start: GPIO 0
- DpadUP: GPIO 1
- DpadDown: GPIO 2
- DpadLeft: GPIO 3
- DpadRight: GPIO 4
- A: GPIO 5
- B: GPIO 6
- X: GPIO 7
- Y: GPIO 8
- L: GPIO 9
- R: GPIO 10
- Z: GPIO 11
- C-stick X-axis: GPIO 26
- C-stick Y-axis: GPIO 27
- StickX Analog Stick X-axis: GPIO 28
- StickY Analog Stick Y-axis: GPIO 29

<a name="gettingStarted"/>

### Getting Started
To get started with the RP2040-Zero GameCube Controller, follow these steps:

##### Hardware Requirements: 
-Make sure you have an RP2040-Zero board and the necessary connections to set it up as a GameCube controller.

#### Installation:
- Download the latest release from the Releases page.

#### Upload Firmware:
- Upload the firmware to your RP2040-Zero board.

#### Connect and Play:
- Connect your RP2040-Zero to a GameCube console and start playing!


### Acknowledgments
Thanks to JulienBernard3383279 for the core of this project.

