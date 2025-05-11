# VaultVizier

VaultVizier is a C++ terminal-based healthcare request and management system, featuring a user-doctor workflow, authentication, request handling, and digital signature functionality — all built with the **FTXUI** TUI library.

---

## **Features**

- Login authentication system for **Users** and **Doctors**
- Patient **entry, search, and editing**
- **Equipment request management** (Users send requests to Doctors)
- **Signature system** for Doctors (Accept/Reject)
- **Transcript system** to log signed requests
- Built with **FTXUI** for a modern terminal UI
- **Experimental light mode** theme

---

## **Build Instructions**

### Prerequisites

- CMake
- A C++ compiler (g++, clang++, MSVC)
- Git (optional)
- FTXUI (can be installed via CMake or fetched in your project)

---

### Building the Project

1. Install [CMake](https://cmake.org/download/) if you haven't already.
2. Open a terminal in your project directory.
3. Run the following commands:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

4. Run the executable:

- On Windows:  
  Navigate to `build/Debug/` and run `VaultVizier.exe`

- On Linux/macOS:  
  Run `./VaultVizier` from the appropriate build output directory

---

## **Important Notes**

- Ignore `#include` warnings **unless the code fails to compile.**
- **Do not upload** the `build/` folder or `.exe` files to GitHub.
- Always **test the application locally** before pushing.

---

<details>
<summary>🛠 Project Team Notes (for members only - remove later)</summary>

- Bhai please don’t commit binaries.
- Run a full test after building — especially request & signature flows.

</details>
