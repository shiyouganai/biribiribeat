![BiriBiriBeat](/web_assets/web_banner_500x120.png)

---

BiriBiriBeat is a miniature rhythm game experience in a microscopic 28KB package. Join your robotic guide Navi and groove together to square wave sounds as you tap your way to the top of the scoreboard! This game is designed and compiled for the Arduboy handheld game system.

---
## Game Download

![][ra] [Click here for the latest ready-to-play release!](https://github.com/shiyouganai/biribiribeat/releases/latest) ![][la]

## Other Links

![][ra] [Click here to preview the game in your web browser!*](https://felipemanga.github.io/ProjectABE/?url=http://shiyouganai.dev/biribiribeat/web_assets/biribiribeat_v100.hex) ![][la]

![][ra] [Click here to check out our Doxygen docs!](https://shiyouganai.dev/biribiribeat/doxy_html/index.html) ![][la]

![][ra] [Click here to learn about the Arduboy game system!](https://arduboy.com/) ![][la]

*Web emulator does not support audio.

---

## Game Manual
1. Controls
2. Main Menu
3. Mode/Difficulty Select
4. Gameplay
5. Results

### 1. Controls

To navigate the game's menus, move the cursor with ![left arrow][la] ![down arrow][da] ![up arrow][ua] ![right arrow][ra]. Select a menu entry with ![a button][ab]. Return to the previous screen with ![b button][bb]. On the Arduboy handheld, ![a button][ab] and ![b button][bb] are located under the "A" and "B" in the ARDUBOY logo, respectively.

### 2. Main Menu

![title_screen](/web_assets/title_screen.gif)

+ **Play:** Move to the mode and difficulty select menus.

+ **Options:** Move the the options menu.

    + **Sound:** Toggle all game audio ON or OFF. (Default: ON)
	
    + **Note Speed:** Toggle the speed at which notes travel across the screen. This option does not change the timing of notes, as notes traveling faster will travel longer distances. It is recommended to leave this setting at the default value. (Default: 1X)
	
    + **Clear Scores:** Clear all BiriBiriBeat high score data from the Arduboy. WARNING: This is not reversable! To protect against accidentally clearing scores, this option has an input timer: you must place the cursor over the menu entry, then hold ![a button][ab] for three seconds. After you do so, the screen will quickly flash white, and the scores will be cleared.

+ **Manual:** View the QR code for this website's url, game version, and copyright information.



### 3. Mode/Difficulty Select

![mode_select](/web_assets/mode_select.gif)

+ **Normal Mode:** Start a NORMAL MODE session. In NORMAL MODE, you will play through a two minute song with a predetermined note chart, at one of three selectable difficulties (EASY, MEDIUM, HARD). Since the note charts are always the same, aim to improve your accuracy each play, and strive to get a full combo!

+ **Chaos Mode:** Start a CHAOS MODE session. In CHAOS MODE, every playthrough is a new experience! The music from NORMAL MODE returns, but this time the note chart is randomly generated. In addition, every two minutes the tempo increases. See how long you can last, and aim for the highest score! Can you reach 999,999,999?

For each mode and difficulty, your highest score is saved. Improve your skills and watch the numbers grow!


### 4. Gameplay

![gameplay_easy](/web_assets/gameplay_easy.gif) ![gameplay_hard](/web_assets/gameplay_hard.gif)

+ **Gameplay Basics:** Tap to the beat! As the game begins, solid button shapes (![left arrow][la] ![down arrow][da] ![up arrow][ua] ![right arrow][ra] ![a button][ab] ![b button][bb]) will rise from the bottom of the screen. When these buttons overlap with the "score zone," the row of outlines at the top of the screen, press the corresponding button on your Arduboy to gain points. The button patterns are carefully tailored to the rhythm of the music, so keep the beat to succeed!

+ **Accuracy:** As you play the game, you will be graded on your accuracy. If you press buttons perfectly in time with the music and in line with the score zone, you will receive a grade of GREAT. A little off, and you will be graded GOOD. Pressing the wrong button, or skipping one entirely, will be graded a MISS.

    + **Charge Bar:** Each GREAT and GOOD grade will charge Navi's battery in the top left of the screen. A MISS will drain it. If the battery drains fully, it's game over, so keep the energy flowing!

	+ **Combo Counter:** Every additional GREAT or GOOD you hit without a MISS inbetween builds your combo count! Your current combo is displayed on the right of the screen. A MISS will break the combo, so be careful!


### 5. Results

![results_ok](/web_assets/results_ok.gif) ![results_bad](/web_assets/results_bad.gif)

+ **Scoring:** 
    + Each GREAT increases your score by 500 points.
	+ Each GOOD increases your score by 200 points.
	+ A MISS does not increase your score.
	+ MAX COMBO is the largest combo you achieved during the last play.


---

## Tech Specs

+ #### Library Dependencies:
    + Arduboy2 v5.2.1

+ #### Development Environment/Toolchain:
    + PlatformIO Home 3.1.0-rc.2
	+ PlatformIO Core 4.2.0rc1
	+ Atmel AVR Platform 2.0.0

---

## Credits
BiriBiriBeat, including all non-library code, sprites, and music is Copyright 2019-2020 shiyouganai.

The ![][ra][Squawk Library](https://github.com/stg/Squawk)![][la] is Copyright 2013 Davey Taylor, modified with permission for BiriBiriBeat.

Logo design, character design, and spritework by ![][ra][dr!p](https://rachelleviola.com/)![][la].

Button sprites derived from spritework by ![][ra][tytydraco](https://github.com/tytydraco/)![][la].

[la]: /web_assets/leftArrowFilled_14x14.png
[da]: /web_assets/downArrowFilled_14x14.png
[ua]: /web_assets/upArrowFilled_14x14.png
[ra]: /web_assets/rightArrowFilled_14x14.png
[ab]: /web_assets/aTileFilled_14x14.png
[bb]: /web_assets/bTileFilled_14x14.png
