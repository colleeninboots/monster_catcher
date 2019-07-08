# The Monster Catcher

The Monster Catcher is a nightlight that keeps monsters at bay. This repo holds the Arduino firmware needed to make your own. Check out the [Monster Catcher instructable](https://www.google.com "Instructable") for the full set of steps.

## Project Description

This nightlight doubles as a trap to catch monsters under the bed! Before you go to sleep at night, place it under your bed and it will catch any monster under there. It even keeps a light on all night to make sure new monsters stay away.

This instructable makes a great project for parents with a kid who’s afraid of monsters under the bed. The trap can help them sleep easy knowing that any monsters are locked away in the trap and can’t get them.

## Files
<dl>
  <dt>monster_catcher.ino</dt>
  <dd>The main Arduino firmware file for this project. Uploaded to an Uno or Leonardo.</dd>
  
  <dt>monster_catcher_schematic.png</dt>
  <dd>The schematic for the electronics portion of the project.</dd>
</dl>

## Functionality
The firmware is designed to open the trap (move the servos) when the board is turned on, showing the user that it is ready to catch a monster. As the user turns the trimmer potentiometer (or trimpot), it changes the color of the light. Once a color is chosen, the trap snaps shut after 4 seconds, capturing any nearby monster. If the knob is turned all the way to 0, then the LED shuts off and the trap opens back up.

## Note on Polarity
The program is coded for a Common Anode RGB LED. If you have a Common Cathode RGB LED, just remove the “255 - “ from each of the digitalWrite lines in the setColorRGB method. If you aren’t sure, then check the data sheet for the LED that you have.

## Further Work
There are several possible modifications we can make to this program. We can change the timing of when the trap shuts or incorporate other sensors like a motion sensor to snap shut when someone walks by or an accelerometer so it opens back up when you shake it.

We can also incorporate more color options into the design, or create different interesting light effects (fading, blinking, etc) with the RGB LED depending on the trimpot rotation. We can also turn the trimpot into a monster selector, so different color settings can catch different monsters! 

Let me know if you have a cool idea or would like to contribute!
