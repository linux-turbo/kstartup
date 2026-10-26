# KStartup

KStartup is a lightweight, high-performance C++20 and Qt6 autostart manager designed for Linux and BSD desktop environments (GNOME, KDE Plasma, XFCE, LXQt, etc.).

It solves common session startup issues (such as audio volume resets or display server initialization delays) by allowing users to schedule custom commands or scripts with a precise execution delay after login.

---

## Features

- Delayed Execution: Configure startup delays from 0 to 60 seconds to ensure core desktop services are fully initialized.
- Flexible Target Selection: Execute standalone shell/Python scripts or raw custom commands (e.g., sound triggers, media playback, application launches).
- Privilege Escalation: Optional pkexec integration for administrative tasks requiring root access.
- Internationalization (i18n): Native multi-language support (English and French).
- Minimal Dependencies: Built strictly using standard C++20 and Qt6 (Core and Widgets).

---

## Prerequisites

To build KStartup from source, the following development tools and libraries are required:

- C++20 compatible compiler (GCC or Clang)
- CMake 3.16 or higher
- Qt6 Development Libraries (qt6-base, qt6-tools, qt6-l10n-tools)

---

## Installation

To build and install KStartup system-wide using the source installer:

```bash
git clone [https://github.com/linux-turbo/kstartup.git](https://github.com/linux-turbo/kstartup.git)
cd kstartup
sudo ./install.sh
