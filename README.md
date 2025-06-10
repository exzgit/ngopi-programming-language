# Ngopi - Programming Language

Ngopi adalah proyek sumber terbuka yang dikembangkan oleh para kontributor untuk eksperimen dan pembelajaran mengenai cara kerja bahasa pemrograman, mulai dari proses parsing, kompilasi, hingga eksekusi kode. Proyek ini bertujuan menjadi referensi dan sarana belajar bersama tentang pembuatan bahasa pemrograman dari nol.

## Fitur Utama
- Struktur modular dan mudah dipelajari
- Implementasi lexer, parser, AST, dan virtual machine
- Dukungan ekstensi melalui modul opsional
- Kode sumber terbuka dan dapat dikembangkan bersama

## Struktur Direktori
```
├── CMakeLists.txt         # Konfigurasi build CMake
├── README.md              # Dokumentasi proyek
├── build/                 # Output hasil build (direkomendasikan di-gitignore)
├── docs/                  # Dokumentasi tambahan
├── src/                   # Kode sumber utama
│   ├── main.cpp, main.hpp # Entry point
│   ├── compiler/          # Komponen lexer, parser, AST
│   ├── core/              # Fitur inti (OS, proses, crypto)
│   ├── optionals/         # Modul opsional (math, syscore)
│   ├── shared/            # Struktur data bersama
│   ├── tool/              # Alat bantu (CLI, build)
│   ├── utils/             # Utilitas (JSON, dll)
│   └── vm/                # Virtual machine
└── test/                  # Skrip dan sumber pengujian
```

## Cara Build & Menjalankan

### Prasyarat
- CMake >= 3.10
- Compiler C++17 (GCC/Clang/MSVC)

### Build di Windows (PowerShell)
```powershell
# Dari root folder proyek
mkdir build
cd build
cmake .. -G "NMake Makefiles"
nmake
```

### Build di Linux/MacOS
```sh
mkdir build
cd build
cmake ..
make
```

### Menjalankan
Setelah proses build selesai, jalankan executable:

- **Windows:**
  ```powershell
  .\ngopi.exe
  ```
- **Linux/MacOS:**
  ```sh
  ./ngopi
  ```

## Kontribusi
Proyek ini terbuka untuk siapa saja yang ingin belajar, berkontribusi, atau bereksperimen. Silakan fork, buat pull request, atau diskusikan ide Anda di issues.

## Lisensi
Proyek ini dirilis di bawah lisensi MIT. Silakan gunakan, modifikasi, dan distribusikan sesuai kebutuhan.

---

> Dibangun bersama oleh komunitas untuk belajar dan berbagi.
