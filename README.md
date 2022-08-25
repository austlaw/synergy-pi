# HID Synergy

This is a fork of the open source core component of Synergy, a keyboard
and mouse sharing tool.
For compilation and configuration, check
[the main repo](https://github.com/symless/synergy-core).

Many corporate environments require the use of a VPN that prevents network connectivity
between the synergy server and client. Furthermore, administrative permissions are
required to install the synergy client. By using a programmable USB device no network
connectivity is required and no client needs to be installed on the remote computer.

Standard HID mouse drivers support absolute position but only on a single display.
Therefore, two HID mice are emulated, one with absolute positioning and one with
relative positioning.

The original hid-synergy fork found here (https://github.com/alexvanyo/hid-synergy) 
was intended to work on mobile devices. This branch is intended to work on desk

## Raspberry Pi Zero W Setup

To setup the Raspberry Pi Zero W to act as a USB device, follow the
guide found at https://www.aidanwoods.com/blog/building-a-wifi-enabled-usb-rubber-ducky/,
with its [corresponding repo](https://github.com/aidantwoods/RPi0w-keyboard).
In particular, [this issue](https://github.com/aidantwoods/RPi0w-keyboard/issues/1)
contains a necessary workaround.

HID Synergy requires three USB devices, a mouse, a keyboard, and a
digitzer (for absolute mouse functionality), so use
[this hid.sh](https://gist.github.com/alexvanyo/408870730c5337111ef07b23d48ed742)
instead of the one from the tutorial.

Ensure that the Raspberry Pi Zero W is being picked up as a USB device
by running `hid-gadget-test.c` with the mouse and keyboard.

## Usage

After compiling Synergy on the Raspberry Pi Zero W, there is a single
new option for use with the client:

```[--hid <keyboard> <mouse> <mouse2> <width> height> <x> <y>]```

The keyboard and mouse and mouse2 arguments correspond to the HID dev
path for each. For the `hid.sh` included, these should be `/dev/hidg0`,
`/dev/hidg1` and `/dev/hidg2` in order.


## Known Issues/Limitations
- The mouse wheel functionality isn't implemented yet
- The clipboard is not shared with the client device. This could potentially
be done with a companion app, or in a limited auto-type fashion for just text.
