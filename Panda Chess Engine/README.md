# Panda - Chess Engine
Made by: Sebastiano Rebonato-Scott

Current elo: ~1400

Reasons for the name:
- pandas are black and white (like a chessboard)
- pandas are friendly and not very dangerous (you can't exactly have an engine rated 1400 and call it something like Black Panther)
- pandas are pretty slow, kinda like my array-based move generation

Latest Update (recapture search, negamax, bug fix):
- replaced minimax with negamax for easier use in other functions
- updated evaluation to being from side-to-move's perspective to work in negamax
- implemented recapture search to prevent horizon effect (mostly)
- fixed bug with castling

Todo:
- move ordering
- more detailed evaluation
- opening book
- uci protocol


