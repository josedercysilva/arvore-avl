# AVL Tree Implementation in C 🌳

![Language](https://img.shields.io/badge/language-C-blue.svg)
![Standard](https://img.shields.io/badge/standard-C89%2FANSI-brightgreen)
![Build](https://img.shields.io/badge/build-Make-orange)

A robust, self-balancing AVL (Adelson-Velsky and Landis) Binary Search Tree implemented in standard C. 
This project demonstrates low-level memory management, pointer manipulation, and professional software architecture.

## 🏗️ Architecture & Best Practices
This repository is structured following industry standards for C/C++ projects (like embedded systems):
- **Single Responsibility Principle (SRP):** Business logic is decoupled from CLI interactions.
- **Modularization:** Strict separation between the public API (`include/`) and the implementation (`src/`).
- **C89 Standards:** Variable declarations are placed at the top of their scopes for strict compliance, a common requirement in low-level and critical systems.
- **Doxygen Documentation:** Public APIs and internal logic are fully documented for maintainability.
- **Automated Build:** Configured with a `Makefile` for streamlined compilation.

## 📂 Project Structure
```text
arvore-avl/
├── include/
│   └── avl_tree.h      # Public API and structs
├── src/
│   ├── avl_tree.c      # Tree logic and rotations
│   └── main.c          # CLI and user interaction
├── build/              # Compiled artifacts (ignored by git)
├── Makefile            # Build automation script
└── .gitignore          # Git ignore rules
