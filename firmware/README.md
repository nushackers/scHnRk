# Firmware

## Hardware Setup

Here's our hardware setup to load 

```
Raspberry Pi
- GPIO pin to push NO (Normally Open) button, pulled up to high
- I2C
  - PCF8574 port expander
    -HD44780 LCD Controller
      -*LCD*
- SPI
  - Self made jig
    - ScHnRk SPI interface 
```

## Software Setup

Raspberry Pi runs Raspbian, with these packages installed

## Firmware

We used microneucleus bootloader for schnrk v0.1 - v0.5

## Downloading Firmware

*To be updated*