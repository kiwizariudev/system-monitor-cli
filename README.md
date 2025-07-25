# 🖥️ System Monitor CLI (Windows)

A lightweight **C++/Python hybrid tool** to monitor CPU and RAM usage in real-time, directly from the Windows terminal.

## 🧰 Project Structure

- `src/cpp/monitor.cpp` – Collects CPU and RAM stats using Windows APIs  
- `src/python/main.py` – CLI interface using Rich  
- `bin/monitor.exe` – Compiled C++ binary  
- `docs/README.md` – This documentation

## ▶️ How to Run

1. **Compile the C++ file:**
   ```bash
   g++ src/cpp/monitor.cpp -o bin/monitor.exe -std=c++17 -static -I include
