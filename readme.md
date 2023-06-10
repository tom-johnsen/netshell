# NetShell

NetShell is a simple network shell server that creates a TCP shell over a specified port.

**Disclaimer: This software should only be used for educational purposes, CTF challenges, and controlled environments. It is not intended for use in a production environment. Exposing a shell online can be dangerous and may lead to unauthorized access to your system. Use this software responsibly and at your own risk.**

## Table of Contents

- Features
- Prerequisites
- Installation
- Usage
- Examples
- Contributing
- License

## Features

- Establishes a TCP shell server on a specified port.
- Allows remote shell access through a TCP connection.
- Supports both single connection and multi-connection modes.
- Can be used for educational purposes, CTF challenges, and controlled environments.

## Prerequisites

- C compiler (gcc)
- Make utility

## Installation

1. Clone this repository:

   ```shell
   git clone https://github.com/tom-johnsen/netshell.git
   ```

2. Change to the project directory:

   ```shell
   cd netshell
   ```

3. Build the programs:

   ```shell
   make
   ```

4. Install the programs:

   ```shell
   sudo make install
   ```

## Usage

- To run the single connection version:

  ```shell
  netshell <port>
  ```

- To run the multi-connection version:

  ```shell
  netshell-multi <port>
  ```

  **Note:** `<port>` should be a valid port number between 1 and 65535.

## Examples

- Start the single connection version on port 1234:

  ```shell
  netshell 1234
  ```

- Start the multi-connection version on port 5678:

  ```shell
  netshell-multi 5678
  ```

## Contributing

Contributions are welcome! If you find any bugs or have suggestions for improvement, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License.
