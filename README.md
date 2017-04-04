GCW0 port

This uses Bitbox's emulator in order to run Alter Ego for the Bitbox.
In actual reality, the bitbox emulator isn't one : it's an extremely simple simulator compiled to native code.
Since the bitbox is just a pretty simple machine with a framebuffere and a DAC, the results are close enough to the hardware.

I had to modify main_sdl.c in order to support the GCW Zero properly. (buttons were not mapped correctly)

===============

#Alter Ego port to Bitbox !

*Alter Ego* is a unique platformer based on the fact that you control an alter ego with which you wan swap position
to solve puzzle levels ! Look at video to understand gameplay.

 - Controls : Press button A to swap, D-pad to move !
 - Original game by retro souls [Homepage](http://www.retrosouls.net/?page_id=614)
 - NES port by [Shiru](http://shiru.untergrund.net/software.shtml#nes)
 - Port by Makapuf for bitbox micro, 2016

![Animated screenshot](screencast.gif)

[A Video of the gameplay](https://www.youtube.com/watch?v=OLNn7vlYZLc)


