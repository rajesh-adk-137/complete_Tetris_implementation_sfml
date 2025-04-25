
# 🎮 SFML Tetris – A C++ Game

A classic **Tetris game** built using **C++** and **SFML (Simple and Fast Multimedia Library)** as part of an academic programming project. This project showcases object-oriented design, real-time game logic, and multimedia integration using SFML.

## 📸 Screenshots

- **Main Menu**  
  ![Main Menu](https://github.com/user-attachments/assets/b1284bce-3ae8-4ba1-a640-faf1aa37de56)

- **Gameplay**  
  ![Gameplay](https://github.com/user-attachments/assets/bbc14792-eee4-4598-b1ee-da2f4663a730)

- **Pause Menu**  
  ![Pause Menu](https://github.com/user-attachments/assets/30a56dc4-9f95-4a4e-8ff6-d621c631fee8)

- **Game Over**  
  ![Game Over](https://github.com/user-attachments/assets/72d5692b-21a5-4498-aedf-c48a3c3edff7)

## 🛠 Features

- Classic single-player Tetris mechanics
- Rotatable tetromino blocks (O, J, L, Z, S, I, T)
- Score tracking with top 5 high scores
- Real-time input for moving, rotating, and dropping blocks
- Pause, resume, and music toggle functionality
- Simple UI with menus and instructions
- Game over detection with restart options
- Object-oriented structure and basic file handling


## ⚙️ Getting Started

### Requirements

- **Visual Studio (2019 or later)**
- **SFML 2.5.x**
- C++17 or above

### Setup Instructions

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/sfml-tetris.git
   cd sfml-tetris
   ```

2. **Open the solution**:
   ```
   sample workspace.sln
   ```

3. **Configure SFML**:
   - Set include and lib paths to your SFML installation.
   - Link required SFML libraries:
     - `sfml-graphics.lib`
     - `sfml-window.lib`
     - `sfml-system.lib`
     - `sfml-audio.lib`

> ⚠️ **Note:** Setting up SFML for the first time in Visual Studio can be frustrating.  
> It’s highly recommended to follow a YouTube tutorial to ensure proper setup.

4. **Build and run** from Visual Studio.

## 🎮 Controls

| Key         | Action                  |
|-------------|--------------------------|
| ← / →       | Move tetromino left/right |
| ↑           | Rotate tetromino         |
| ↓           | Soft drop                |
| Space       | Hard drop                |
| P           | Pause game               |
| M           | Toggle music             |
| Esc         | Return to main menu      |

## 🔮 Known Limitations

- No multiplayer support
- High score system does not store player names
- Basic UI with limited visual effects

## 🌱 Future Plans

- Add player name input for score records
- Clean up and refactor codebase for better readability
- Enhance animations and transitions
- Add multiplayer mode over LAN/internet
- Implement difficulty levels or challenge modes

## 📜 License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

---

> 🎓 Developed as part of an Object-Oriented Programming course to explore C++ and game development using SFML.
