---
title: "multi-tool"
author: "Limit6"
description: "A small pocket-size gadget that features clock or compass, with more features coming! It's built for hiking and is designed for ultra-low power."
created_at: "2025-07-12"
---

# July 12: Project outline and components
I've created this github repo and settled down on what the final projet should look like. I've had the project visioned for a some time, but i've started now building it. 

I want it to be a something like smart pocket watch. It should have clock, compass, also a gps for distance tracking. The watch would be built for use in nature, so it needs to be really power efficient, because charghing availability won't be big there. I'll be using it on trips that will be several days long, and I hope I could use this gadget for tracking my trip and general usage there. I imagine it would have a rotating wheel and a button. I think this would be sufficient for all ui navigation.

## Part selection

**Microcontroller**

I needed a very small one, that would also have a low power consumption and would be powerful enough to handle a desplay and several modules connected to it. After a quick search I chose the `arduino pro mini`, but later i've discovered the `Seeed Studio XIAO nRF52840`, which is way smaller than the arduino and has much better specs. It has 256 kB of ram (arduino has only 2kB!) and similar goes for flash storage. This microcontroller has 3 MB of flash memory in total, while arduino has 32kB. And it's only about 2x more expensive, just for $6. This is just the winner for me and I'll be comfortable knowing I have the specs for more intensive tasks. And as a bonus, it has a charging module built in! Maybe only problem that could occur is the number of gpio pins, which is 11, but i'll try to solve this by using i2c for sensor modules.

**Display**

I've initially wanted an e-ink display for it's readability on sun and also just cool looks, but i've found out that nobody is making small and square displays, which is what i need (and if there are, they are very expensive). After a bit of research, i know a small and grayscale oled would be perfect. It would be power efficient and also will have a cool retro look to it. But it took me a while to find the perfect one. First i've looked on `Waveshare 1.5inch OLED Display Module, 128×128 Resolution` for a while, but i've felt that it is just too big. But then i've found the `Waveshare 1.32" OLED (128×96, 16 grayscale)`. I will need to move a rezistor on the display to switch to the i2c communication, because the default SPI uses too many pins, as I've realized later when picking the gps and rotating wheel. It will have `0x3d` address by default.

**Magnetometer**

This module will be used by the compass feature. I've tried looking on aliexpress and eventually found two options: modules using the discontinued `HMC5883L` chip, or the newer `QMC5883L`. I eventually went with the newer chip which has a lower power draw. But i will need to keep in mind to use a dedicated code library. The i2c address is usually `0x0d`
The assembled module will be: https://www.aliexpress.com/item/1005007183006706.html

**Accelerometer + Gyro**

This wasn't too hard to find, but on aliexpress on large amount of products there were negative reviews, which was a bit surprising. I've eventually found https://www.aliexpress.com/item/1005008913624575.html and it has `0x68` i2c adress, which is not being used by other sensor.

**Real Time Clock**

This module is quite essential for my multi tool, and it wasn't hard to find. It will handle keeping track of current time and date. I did a quick google search and found a highly recommended `DS3231` module. It has default i2c adress `0x57`.
Aliexpress: https://www.aliexpress.com/item/1005007143596890.html 

**GPS Module**

I also want this gadget to have a gps inside it, mainly for trip tracking. I've found a popular gps module called `NEO-6M`, which I've found [on aliexpress](https://www.aliexpress.com/item/1005007175919889.html) shipped already with an antenna, which is perfect. However i will need to handle using the gps carefully, because the power draw is quite high. This gps module is communicating using UART protocol, which in practice uses TX and RX pins, which are P1.11 and P1.12 on the controller.

**Rotating wheel**

For this part, I've just gone to aliexpress and looked through generic wheels that had infinite rotation and had a button built-in. A minor challenge was finding one that operated on 3.3V. I've eventually found this one: https://www.aliexpress.com/item/1005001682499791.html with digital outputs. It will take up 3 gpio pins (2 for the wheel, 1 for button)

**Batterry**

This is surprisingly quite complicated part. I need high capacity for all the sensors and display to ideally last me days but also it needs to fit into a quite small case. After considering my space options and the needed capacity, I've picked this [550 mAh LiPo battery](https://www.aliexpress.com/item/1005006666958920.html). I have to hope that the capacity will be enough.

**Time spent this session: 5h15m**

**Total time spent: 5h15m**
