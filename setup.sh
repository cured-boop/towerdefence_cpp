#!/bin/bash

# Function to install SFML on Mac
install_sfml_mac() {
    brew install sfml
    brew install nlohmann-json
}

# Function to install SFML on Debian/Ubuntu
install_sfml_debian() {
    sudo apt-get update && sudo apt-get install libsfml-dev
    sudo apt-get install nlohmann-json3-dev
    # Install pkg-config if it is not installed
    if ! command -v pkg-config &> /dev/null; then
        echo "pkg-config not found. Installing pkg-config..."
        sudo apt-get install pkg-config
    fi
}

# Check for Operating System
OS="$(uname)"
case $OS in
  'Linux')
    # Assuming the use of Debian/Ubuntu, install SFML, nlohmann/json, and pkg-config
    install_sfml_debian
    ;;
  'Darwin') 
    # Check for Homebrew on Mac and install it if it's not installed
    if ! command -v brew &> /dev/null; then
        echo "Homebrew not found. Installing Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi
    # Check for pkg-config on Mac and install it if it's not installed
    if ! command -v pkg-config &> /dev/null; then
        echo "pkg-config not found. Installing pkg-config..."
        brew install pkg-config
    fi
    # Install SFML and nlohmann/json on Mac
    install_sfml_mac
    ;;
  *)
    echo "Unsupported operating system: $OS"
    exit 1
    ;;
esac
