Project Name
-----------------------------

  Tetris


Authors
-----------------------------

  Peter Zhang (tzhangam@ust.hk)
  Thomas Zhou (szhouan@ust.hk)


Description
-----------------------------

  A simple tetris game with ordinary operation and simple functionalities such as preview and score/level/combo display.


Download
-----------------------------

  https://github.com/tzhangam/Project_2


Contents
-----------------------------

  tetris/
    .gitignore
    Makefile
    README.txt
    images/
      background.bmp
    inc/
      *.h
      misc.h
    src/
      *.cpp
      main.cpp
    tetris.pro
    tetris.qrc

  NOTE: In the above list, * stands for the following:
          Block
          Panel
          RenderArea
          Gameboard
          PreviewArea
          Window


Build
-----------------------------

  - Using qmake (multiple platforms supported)
    Required tools:
      Qt 4+
      GNU make 3.82+
    Commands:
      $ qmake
      $ make

  - Using the pre-genrated Makefile (only for Linux users)
    Required tools:
      GNU make 3.82+
    Commands:
      $ make

  NOTE: Please make a COPY of the ORIGINAL Makefile into a safe place before executing qmake.


Usage
-----------------------------

  - open from command line
    - Linux
      In tetris/ directory, use:
        $ tetris
    - OS X
      Follow the build instructions above, then use:
        $ open tetris.app

  - open in file manager(or other similar facilities):
    Double click the icon of the executable (tetris or tetris.exe)


How to Play
-----------------------------
  
  - On Tetris
      In this game, blocks with 4 squares (a.k.a tetriminoes) will be dropped from the top of the window one at a time.
      The player needs to rotate and move the blocks (without moving upwards) so that they can be placed properly.
      A horizontal line with 10 squares all filled will disappear, and the blocks above will be shifted downwards.
      The more lines one eliminates, the more one scores.
      During this process, the level of difficulty will increase, causing the blocks to fall at faster speed.

  - Basic Key Press
    - Arrow UP          Start/restart game
    - Arrow DOWN        Move blocks down (faster than the normal speed)
    - Arrow LEFT        Move blocks left
    - Arrow RIGHT       Move blocks right
    - Z                 Rotate blocks clockwise
    - X                 Rotate blocks counterclockwise

  - Preview Area
    The shape of the next block will be shown in the upper left corner of the window.
    The player may use such information to guide his move.

  - Score Panel
    The total score, current level and the number of combo in the previos move will be shown in the lower left corner.

    Formulae:
      COMBO = # of lines eliminated due to a single block
      SCORE (incremented) = 10 * COMBO * COMBO
      LEVEL = MIN ( FLOOR ( SCORE / 100 ) + 1, 10 )
      FALLING TIME PER GRID (in ms) = 1000 - ( level - 1 ) * 100


Technical Details
-----------------------------

  - Tools involved
    - Qt                GUI library
    - git/github        source code management
    - valgrind          memory usage debugging

  - Project Organization
    The user interface and the internal logic of the game are seperated.

    The project is based on the following classes:

    - Window
      - Owner of all widgets for the user interface
      - Manage the communication between diplaying areas and Gameboard (logic handler), using the signal and slot mechanism of Qt
      - Accept keypress and pass to Gameboard
      - Show "Gameover" window when signaled by Gameboard

    - Gameboard
      - Handle all game related logic, including:
        - Generate new blocks randomly when the previous one is at bottom
        - Decrease the height of the current block by one periodically, using a QTimer
        - Accept block movement instructions from Window and validate it
        - Update the internal representation of the gameboard after a block movement is validated or some lines are eliminated

      - Emit signals to indicate that the user interface should be updated
      - Provide interface functions for each widget to obtain relevant information for displaying

    - Block
      - Handle the actual manipulation on blocks
      - Keep track of the color, shape, direction and center of the blocks
      - Encode the information of the block shape and direction in to a 5*5 grid map, and provide functions to get information in each grid
      - When a block is rotated, the direction property is changed and information in the grid map is updated
      - Provide converting function between Qt's predefined color code and the color code used in Block class

    - RenderArea
      - Draw the current active block and previous blocks on the game field using QPainter
      - Keep a background for the area as pixmap
      - When the UpdateRenderArea() signal emitted by Gameboard is detected, use getGridColor() to obtain the correct color and draw the corresponding square 

    - PreviewArea
      - Draw the next block in the preview area of the main window using QPainter
      - When the UpdatePreviewArea() signal emitted by Gameboard is detected, use getNextBlockColor() to obtain the color and shape of the next block

    - Panel
      - Display the current score, level and combo of the user using QLabel
      - When the updatePanel() signal emitted by the Gameboard is detected, use getScore/getLevel/getCombo to obtain the correponding information for displaying

  - Communication between modules
    - Use Qt's signal and slot mechanism to trigger update event of each widget
    - The displaying widget (RenderArea, PreviewArea and Panel) keeps a constant pointer to the Gameboard
    - When an update is needed, corresponding public functions of the Gameboard will be called to fetch relevent information

  - Communication with the user
    - Accept keypress from Window and call the corresponding function of the Gameboard to recalculate the appearance of the game field
    - Show a pop up window upon game over and ask if the user wants to continue


Deviation from the Sample
-----------------------------

  - A pop up window is showed upon game over


Troubleshooting
-----------------------------
  
  - The make command cannot build the source code properly.

    The provide Makefile is only for Linux system. You can use qmake to generate the platform specific Makefile based on the .pro file.

  - The qmake command reports some files are missing.

    Make sure all the files are in the correct directories, including header files, source code in .cpp, and the image for background.

  - The game does not start after I open the window.

    Press UP arrow key to start the game.


Bug Reporting
-----------------------------
  
  Any bug reports can be sent to <tzhangam@ust.hk> or <szhouan@ust.hk>

