This project is a port to Qt of the recreation I'm making of Kirby's Dreamland (GB) on the PIC18F45K22.
The PIC18F45K22 is a microprocessor with a clock speed of 8 MHz, 32 Kb of rom size, 1.5 Kb of ram size and no hardware acceleration so the entire recreation was made from the ground up (from the graphics engine to all the gameplay system) on C, having to be carefull so the entire game fits on the limited space and runs at around 30 fps.
The original project is uploaded on my repository "KirbyPIC" inside a Proteus project that emulates the PIC and GLCD's (used to output video) behaviour.
This port takes the recreation and rewires it's input and output so it works as a standalone Qt 6.7.3 app on Windows.
Neither project is fully finished so both have some visual bugs and errors.
