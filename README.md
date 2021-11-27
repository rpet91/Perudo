# Perudo
Perudo is an existing game designed by Richard Borg. You can find the game [here](https://boardgamegeek.com/boardgame/45/perudo) on boardgamegeek. All the inspiration and knowledge I got is from the real game. What I am doing here is recreating the game for my own pleasure and practice on the pc in C++98. Everything is text based (for now at least) so don't expect a nice working game with fancy graphics.

# Adjustments
For the most part I implemented the rules from the original game. But here is a list of small differences:
- Changed the call 'dudo' to 'bluff'.
- Changed the value name of 'aces' to 'jokers'.
- Changed the rule where you can bid 'jokers' only once per round to unlimited.
- Changed the rule when there are only two players left, palafico isn't possible to possible.
- Changed the call 'calza' to 'perudo'.
- Changed the rule that perudo can't be called by the next player to only the next player.

# Instructions
Compile the program with ```make``` or ```make game``` to launch the game. A list of instructions is shown which will help you through to get started. You'll need at least two players with a maximum of five. When the game is launched you have a list of options you can perform.
