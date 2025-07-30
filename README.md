# 🃏 Solitaire Game in C++

This is a command-line implementation of the classic **Solitaire** (Klondike) card game, written in C++. It simulates the full solitaire experience using object-oriented programming, custom data structures, and intuitive terminal output.

---

##  Features

- Complete deck creation and shuffling
- Tableau (7 columns), Foundation (4 stacks), Stock, and Waste piles
- Valid card movement checks (color, rank, suit)
- Commands to:
  - Draw cards
  - Move between piles and columns
  - Undo last move
- Win detection logic
- Console output with color-coded card suits (♠ ♥ ♦ ♣)
- Custom doubly-linked list and stack implementation

---

##  Technologies Used

- **Language:** C++
- **Headers:** `<iostream>`, `<string>`, `<windows.h>`, `<stdexcept>`, `<ctime>`, `<cctype>`
- **Data Structures:** 
  - Custom `List<T>` with iterators (doubly linked list)
  - Custom `Stack<T>`
  - Classes for `Card`, `Command`, and `Game`

---

##  How to Play

###  Controls

- **`s`**: Draw a card from the stockpile
- **`m,src,dest,num`**: Move cards (e.g. `m,c1,f2,1` moves 1 card from column 1 to foundation 2)
- **`z`**: Undo last move
- **`e`**: End game

### Column/Stack Codes

- `c1`, `c2`, ..., `c7`: Columns (tableau)
- `f1`, `f2`, ..., `f4`: Foundations
- `w`: Wastepile
- `s`: Stock (draw pile)

### Example Commands

- `m,c1,c3,2` → Move 2 cards from column 1 to column 3  
- `m,w,f1,1` → Move 1 card from wastepile to foundation 1  
- `z` → Undo the last move  
- `e` → End the game

---
## Author
Lumia Noman Qureshi<br>
BSCS – Computer Science Student<br>
FAST NUCES LHR
