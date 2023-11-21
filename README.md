# Blackies-Bubbles-Cat-SFMLgame
A simple game in C++ SFML in which you have to control a cat. Left/Right - A/B, Jump - Space.

Using a jump, you can jump to the top of the bubbles, but not above the upper border of the screen.

Blackheads appear in a random place on the game screen near one of the sides. Their generation and movement are determined randomly using random timers.

If the cat collides with a blackie, the blackie will disappear.
If the cat was above the blackie at the same time, you will hear a faint crunch and the cat will heal from 1 to 4 hp and get from 1 to 4 points accordingly. 
In all other cases, you will hear "meow" and the cat will receive from 5 to 20 damage.

This project also implemented a health bar and animation of a cat.
The game has a "Game over" and "Pause" function (press the P key).

The project is suitable for beginners, it has a minimum of OOP, and the code uses the most basic features of the C++ language and the SFML library.

To build the game, you will need to connect the SFML 2.6.0 library. You can do this by viewing the manual on the official website: https://www.sfml-dev.org/tutorials/2.6 / Or, if you use Visual Studio, use the easiest way to install SFML via NuGet: https://www.youtube.com/watch ?v=on7U-90gfrI (SFML-audio is installed separately!)
