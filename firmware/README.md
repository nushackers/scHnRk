# Firmware

## Hardware Setup

Here's our hardware setup to load the firmware into the ScHnRk.

- Windows Computer
  - AVRISP (USB)
    - AVRISP (SPI)
      - Self made jig
        - ScHnRk SPI interface 

We used microneucleus bootloader for schnrk v0.1 - v0.7

### Archived Setup

Raspberry Pi bit banging seems to fail, so we are using AVRISP instead.

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