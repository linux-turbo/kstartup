#!/bin/bash

if [ "$EUID" -ne 0 ]; then
    echo "Error: Please run this script with root privileges (sudo ./uninstall.sh)." >&2
    exit 1
fi

echo "=== KStartup Uninstaller ==="

if [ -f "/usr/bin/kstartup" ]; then
    rm -f /usr/bin/kstartup
    echo "Removed binary from /usr/bin/kstartup"
fi

if [ -f "/usr/share/applications/kstartup.desktop" ]; then
    rm -f /usr/share/applications/kstartup.desktop
    echo "Removed desktop entry file"
fi

echo "=== Uninstallation complete! ==="
