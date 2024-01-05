# Battleships Project

This project allows users to play the game Battleships with the following functionalities:

## Pre-game Configuration

- **Ship Configuration Format:** All ships' configurations should follow the format `A1 R L` without spaces after `L`.
  - `A1` denotes the initial tile.
  - `R` indicates the direction in which the ship expands (up, down, left, right).
  - `L` represents the ship's length.
- **Creating Configuration File:** Use the same format for creating your own configuration file.
- **File Path Format:** The standard way to input file paths is `C:\\Users\\Username\\Documents\\Battleships1.txt`.
- **Example Files:** Two example files with valid ship configurations are available in the project's compressed folder.

## Using Preset Boards (Optional)

- **Definition in .txt File:** Preset boards can be defined in a .txt file.
- **Error Handling:** If a user chooses to load from a file, any incorrect presets can be corrected.

## Board Builder

- **Manual Board Creation:** Allows players to create the board manually.
- **Functions:** Add new ships, edit existing ones, and view the current board layout.

## Gameplay

- **Turn-Based Attacks:** Players take turns attacking each other.
- **Board Visibility:** Each turn, the player can view their own board and the board showing hits.
- **Game End:** The game ends when a player destroys all of their opponent's ships.