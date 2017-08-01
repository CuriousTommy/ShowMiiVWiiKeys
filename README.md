# ShowMiiVWiiKeys
An Application That Analyzes A Wii U OTP File For vWii Information. It can generate a text file that can hold the vWii key and a BootMii keys.bin file that can be used with Dolphin (read the disclaimer).

**Please do NOT share the otp.bin, generated keys.bin, or generated text file as they not only contain copyrighted keys but also personal information about you Wii U** (Note: If you are doing a recording of this application, be sure to censor what is shown on the cmd/terminal window).

## Why create this program when we can run Dump Mii Nand, XYZZY, etc.
When you try to run those programs on a vWii, they do not, for some reason, provide the entire information needed to run the Wii Shop Channel on Dolphin. 

## How to obtain the otp.bin file
You will need a Wii U with the ability run the [Homebrew Launcher](https://github.com/dimok789/homebrew_launcher/releases) and run the IOSU exploit. Download dimok's [OTP2SD application](https://github.com/dimok789/otp2sd_dumper/releases) and place the .elf file on your SD card like so:

```
[root of SD card]/wiiu/apps/otp2sd/otp2sd.elf
```
If the program ran successfully on you Wii U, you should see an otp.bin file in the root of your SD card. Copy that file and paste it next to the ShowMiiVWiiKeys application.

## How to use the program
Currently, the program is hard-coded to check if the otp.bin file in the same folder as the executable/application. If the file is there, the program will generate both a keys.bin and keys.txt file.

To run the program, just double click on the executable/application (or run it on a cmd/terminal interface).

## How to access the vWii Shop Account on Dolphin.
**Disclaimer: This is considered unofficial since the vWii is not a real Wii. There may be features on Dolphin that are impossible to do with the generated keys.bin. Please do not bother the Dolphin team if you have any issues with accessing the Wii Shop Channel or using any of the Wii NAND features**

Keep in mind that vWii NAND dumps are not compatible to with Dolphin, so you will need a manually create a Wii filesystem. You will need the latest development version of Dolphin or at least the version of Dolphin that [supports doing Wii update without needing a Wii NAND](https://github.com/dolphin-emu/dolphin/pull/5610).

If you haven't already, dump the otp.bin file and use my program to generate a keys.bin file. Before we start with Dolphin, we will also need to go to the Wii U's `System Settings` app.
1. On the top-right corner, you will see the current version of your Wii U. Make a note of the letter that is next to the number. You will need this to download the correct Wii OS files.
2. Go to `Console Information` (it has a picture of the Wii U with the tablet), then select `Set Country of Residence`. Make a note of the country that is selected on the Wii U. This is needed to access the Wii Shop on Dolphin.


Now let open up Dolphin! Click on the `Tools` tab and hover over `Perform Online System Update`. Select the region that corresponds to the letter you saw next to the version number. For example, my console's version is `5.5.1 U`. Therefore, I need to pick `United States`. If you are unsure what option to pick refer to the table below.

Letter Region | Region Option on Dolphin
--- | ---
U | United States
E | Europe
J | Japan

Once that is done, we are going to close Dolphin. We will need to paste the generated keys.bin file into the Wii folder. By default, Dolphin has the Wii folder located in these locations:

Operating System | Folder Location
--- | ---
Windows | `%userprofile%\My Documents\Dolphin Emulator\Wii`
Mac | `~/Library/Application Support/Dolphin/Wii`
Linux | `~/.local/share/dolphin-emu/Wii/`

After doing that, reopen Dolphin. Click on `Tools` again and click on `Load Wii System...`. go through the setup procedure, as you would on a real Wii until you get to the `Select your country of residence` section. Once you are in this section, put the country that you set on your Wii U. Then finish the rest of the setup.

Before we can actually use the Wii Shop Channel, we need to agree to the user agreements. On the Wii menu, click on the `Wii` circle button. We then traverse to `Wii Settings` --> `Internet` --> `User Agreements`. Once you agreed to the terms of condition, you will be returned to the Wii Menu.

Now you can finally use the Wii Shop Channel! Go ahead and launch the Wii Shop Channel! If you see a 205906 error code, don't worry about it. It is normal, just click `OK`. If everything worked fine, you should now have access to the Wii Shop Channel!

## Current Bugs

Sometimes Dolphin gives an error when trying to access the Wii Shop Channel as if you never supplied a keys.bin file. 

I don't have a proper solution for this problem. One method I tried that worked was to use my normal Wii's keys.bin and then swap it with my Wii u version. This bug seems to happen randomly, but once you get access to the shop channel, it seems to go away.