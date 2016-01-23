# scHnRk

The scHnRk (pronounced as snark) is a digispark/arduino compatible prototyping board developed for Hack&Roll'16.

The hardware design, firmware and software are derived from Galvant/usb_wrapper-pcb, digispark, micronucleus and arduino. Any derivative from their work is released under the Creative Commons License CC BY 4.0 wherever possible. (I'm no lawyer)

## Hardware

This design is adapted from the venerable DigiSpark Pro.

Here's the lowdown on the stats
- ATTINY85
  - 8KB Flash Memory
  - 512B EEPROM
  - 6 I/O Pins (SPI)
- Acessories
  - 5 WS2812B LEDs
  - 2 CR2032 Battery Holders
  - 2 LEDs (Status, Pwr)
  - USB Wrapper (In some circles its called USB Condom)
  - USB Connector

## Kits

### Green

- Resistor Information for green kits can be inferred from the following  
  - Galvant/usb_wrapper-pcb (Github)
    - Most basic configuration => R7 == 75K Ohm, R9 == 43.2K Ohm, R8 == R10 == 49.9K Ohm
    - R4 == 180 Ohm, LED == LED

### Orange

- Just solder on USB connector and you're set!

## Firmware

A jig will be provided on the day itself for firmware (bootloader) reprogramming using SPI. 

## Software

Feel free to program your arduino anyway you want during the competition using arduino IDE and the "on board" USB port!

## Designed by

```
NUSHackers and Pals

Chang Chu-Ming
Chinmay Pendharkar
Harish Venkatesan
Kenneth Lim
Vishnu Prem
Rahul Gokul
Sayanee Basu
Shanmugam Mpl
Yeo Kheng Meng
Jeremias Wong
```

## Secret Features

One has to be granted WOC REPUS Previleges before one accesses the secret features/puzzle.

There might be prizes for people who crack the puzzle during the hackathon! Maybe we forgot lol?

## Sponsors
 
### Platinum Sponsor
```
Zalora
```

### Gold Sponsors
```
Garena
Palantir
```

### Silver Sponsors
```
Titansoft
Google
Jane Street
Stripe
```

### Bronze Sponsors
```
Zopim
Carousell
NUS School of Computing
```

We thank the sponsors for making this happen.

Also we're looking out for sponsors for the next hackathon! Please contact us at coreteam@nushackers.org!
