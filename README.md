TilePuzzle

Latest update 201015

Blending SFML with the interactive functionality of SFGUI - a preliminary attempt.

You should be able to run this after downloading and extracting the zip file on your computer or otherwise run the exe - but make sure the Data/ dir and its files is appended to your working dir as it contains the images, fonts and themes.

Once it's compiled and linked you should see a screen with a picture. Look carefully at the bottom RH corner. The tile is slightly greyed out. That is your 'blank tile'.Click on an adjacent tile to the blank and the blank will move. Why you would want to do this I don't know but it's kind of fun. Once you get bored with that press RESET and the tiles will reset themselves to the intial configuration. 
If you press SCRAMBLE the tiles will move themselves around meaninglessly deconstructing the painting. You can SCRAMBLE after moving around manually. SCRAMBLE is a toggle - click to stop randomizing. The number at the bottom is  a running tally of moves. Further developments include choice of picture, varying tile sizes, speeds etc. You can scramble stop, reconstruct the picture. The rows and cols variables are set to 4 - I havent tried past 16X16
RESET now works after any combination of manual tile moves and SCRAMBLE. I am not sure what will happen if you leave SCRAMBLE running - I suppose you will run out of memory for the vector after some time! I will place a limit on the number of moves eventually. Or a cycle with a display during the reconstruction of the original image.

The only way to control the speed at the moment is by changing the framerate. On my machine with no framrate setting it runs at about 150 frames per second.

The only way to change the picture at the moment is to edit Puzzle.hpp and set the #define to TPIC.

Here's a question - is every random set of moves unique? - no because there is a small chance of repetition.
But is there only one way back through the pattern created? 
In the program Moves are added sequentially to a vector and played back in reverse order to reset (which is fast because there is no display).

See To_Do.md for more notes.
