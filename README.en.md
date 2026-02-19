# MO5 Project – Creating and Displaying Sprites in C

## 🧭 Project Purpose

This project aims to demonstrate **how to create sprites in C for the Thomson MO5** and how to use them in a program:

- Creating a sprite that respects MO5 graphical constraints
- Converting an image into usable C structures
- Displaying the sprite on screen
- Moving the sprite

The goal is to provide a simple foundation to get started with MO5 graphics development.

---

## ⚙️ Prerequisites

### 📦 In Codespaces

**Automatic setup** (recommended):

```bash
make setup-codespace
```

This command automatically installs:
- `flex` (required for lwtools)
- `Pillow` (for PNG image conversion)
- `lwtools` (6809 assembler)
- `CMOC` (C compiler for 6809)

Then, install the project SDK:

```bash
make install
```

**Manual setup** (alternative):

```bash
sudo apt update
sudo apt install flex
pip install Pillow
# Then manually install lwtools and CMOC (see section below)
```

---

### 🐧 On Linux / Raspberry Pi

Install compilation tools and dependencies:

```bash
sudo apt update
sudo apt install build-essential flex bison libboost-all-dev libxml2-dev zlib1g-dev wget tar
sudo apt install python3 python3-pip python3-venv python3-pil
```

---

## 🛠️ Tools Installation

### Installing lwtools

Download:

```bash
wget http://www.lwtools.ca/releases/lwtools/lwtools-4.24.tar.gz
```

Extract:

```bash
tar -xzf lwtools-4.24.tar.gz
cd lwtools-4.24
```

Build and install:

```bash
make
sudo make install
```

---

### Installing CMOC

Download the latest version:  
http://gvlsywt.cluster051.hosting.ovh.net/dev/cmoc.html#download

Download:

```bash
wget http://gvlsywt.cluster051.hosting.ovh.net/dev/cmoc-0.1.97.tar.gz
```

Extract:

```bash
tar -xzf cmoc-0.1.97.tar.gz
cd cmoc-0.1.97
```

Configure, build, and install:

```bash
./configure
make
sudo make install
```

---

## 🧰 MO5 Environment Installation

Before compiling for the first time, run:

```bash
make install
```

This command:

- Downloads and uses the **BootFloppyDisk** project to generate bootable floppy disk images  
  👉 https://github.com/OlivierP-To8/BootFloppyDisk.git

- Compiles **sdk_mo5**, based on helper code designed to simplify Thomson MO5 development  
  👉 https://github.com/thlg057/sdk_mo5.git

- Exports all necessary files into the folder:

```
tools/
```

Once completed, the environment is ready ✅

---

## 🎨 Creating and Converting a Sprite

A **32×32 pixel** sprite is provided in:

```
/assets
```

This sprite was designed respecting MO5 constraints:

- Maximum 2 colors per 8 pixels
- Limited to the 16 colors supported by the MO5

---

### Converting to a C Structure

To convert the PNG image into a usable C file:

```bash
make convert IMG=./assets/[sprite_name].png
```

This generates:

```
/include/assets/[sprite_name].h
```

---

### Generated File Content

Inside this `.h` file you will find:

- Binary definition of the **shape**
- **Color** definitions
- An example function call to display the sprite

Example provided: `perso.h`

---

## 🧪 Compiling the Project

Once the sprite is converted, simply compile:

```bash
make
```

This will:

- Compile the C program
- Generate the floppy disk image
- Allow execution on emulator or real hardware

---

## 🚀 Development

After these steps, you are ready to:

- Create new sprites
- Convert them
- Display them
- Handle their movement

Happy coding on MO5 ✨
