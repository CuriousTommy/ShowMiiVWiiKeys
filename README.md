# ShowMiiVWiiKeys
An Application That Analyzes A Wii U OTP File For vWii Information. It can generate a text file that can hold the vWii key and a BootMii keys.bin file that can be used with Dolphin (read the disclaimer).

## How to obtain the otp.bin file
You will need a Wii U with the ability run the [Homebrew Launcher](https://github.com/dimok789/homebrew_launcher/releases) and run an IOSU exploit. Download dimok's [OTP2SD application](https://github.com/dimok789/otp2sd_dumper/releases). Place the .elf file in your SD card like so:

```
[root of SD card]/wiiu/apps/otp2sd/otp2sd.elf
```
If the program ran sucessfully on you Wii U, you should see a otp.bin file in the root of your SD card. Copy that file and paste it next to the ShowMiiVWiiKeys application.

## How to use the program
(Add later)

## How to access the vWii Shop Account on Dolphin.
**Disclaimer: This is consider unoffical since the vWii is not a real Wii. There may be features on dolphin that are impossible to do with the generated keys.bin. Please do not bother the Dolphin team if you have any issues with accessing the Wii Shop Channel or using any Wii NAND features when using this method**
(instructions are incomplete)

vWii NAND dumps are not compatiable to with Dolphin, so you will need a manually create a Wii filesystem. To make our lives eaiser, we will focus on downloading the essentials needed to perform a Wii update on Dolphin to download the rest of the Operating System.

We are going to need to generate three wad files for Dolphin. These are IOS13, IOS80, and the System Menu. We will be using [NUS Downloader](http://wiibrew.org/wiki/NUS_Downloader). For Mac/Linux users, you can use [Wine](https://www.winehq.org/) to run the program.

When you open the application, tick the box next to `Pack Wad` and click on `Database`. IOS13 and IOS80 are both located under the `IOS` sections, and the System Menu under `System`. For both IOS, make sure you pick `Latest Version`. For System Menu, look for the latest version **that corresponds to the region your Wii U is in** (For example, I have a US Wii U, so I would pick 4.3U). To start the download, press `Start NUS Download!`. You should see title folder with three additional folders inside. Keep click on each folder until you find a file that had a .wad. Store these files somewhere for easy access.

If you haven't already, use my program to generate a keys.bin file. We will now open up Dolphin. Under `Tools`, click on `Install WAD...`. Open each wad file. When you are done doing that, go back to the `Tools` menu and click on `Extract Certificates from NAND`. Before we start the emulator, we are going to need to go to the Wii folder. This folder depends on the Operating System you are currently using:

```
Windows : %userprofile%\My Documents\Dolphin Emulator\
Mac     : 
Linux   : ~/.local/share/dolphin-emu/Wii/
```