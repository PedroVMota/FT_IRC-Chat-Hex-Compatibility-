# ft_irc Project

## Index

1. [Introduction](#introduction)
2. [Project Overview](#project-overview)
3. [Technologies Used](#technologies-used)
4. [Project Difficulty](#project-difficulty)
5. [Implementation Details](#implementation-details)
6. [Building](#building)
7. [Usage Guide](#usage-guide)
8. [Using HexChat](#using-hexchat)
9. [Available Commands](#available-commands)
10. [Examples of Usage](#examples-of-usage)
11. [Conclusion](#conclusion)
12. [Reporting Issues](#reporting-issues)

---

## Introduction

Welcome to the **ft_irc project**! This project involves creating your own **IRC server** using **C++ 98**. An **IRC (Internet Relay Chat)** server allows multiple users to communicate in real-time using a text-based protocol. The project emphasizes understanding **network programming**, **socket management**, and the IRC protocol, which has been a foundational technology for internet-based communication.

## Project Overview

The goal of this project is to develop an **IRC server** that can handle multiple clients simultaneously. Users will connect to your server using an IRC client, authenticate, set nicknames, join channels, and communicate with each other. The server must adhere to specific **IRC protocol commands** and support both public and private messaging.

### Key Features:

- **Multi-client handling**: The server can manage multiple clients concurrently without crashing.
- **Non-blocking I/O**: All I/O operations must be non-blocking.
- **Command handling**: Implement essential IRC commands such as authentication, nickname setting, channel joining, private messaging, and more.
- **Operator commands**: Support for operator-specific commands like `KICK`, `INVITE`, `TOPIC`, and `MODE`.

## Technologies Used

This project is implemented in **C++ 98** and makes extensive use of **low-level network programming** functions. The project relies on the following system calls and functions:

- **socket**, **bind**, **listen**, **accept** for socket management.
- **poll** (or equivalents like **select**, **kqueue**, or **epoll**) for non-blocking I/O.
- **send**, **recv** for communication between the server and clients.

## Project Difficulty

The **ft_irc project** is considered to be of **high difficulty** due to the need for deep understanding of network programming, non-blocking I/O, and the IRC protocol. The project requires careful management of resources, such as file descriptors and memory, and a strong grasp of C++ 98. Additionally, the implementation must handle multiple clients simultaneously, which adds complexity to the project.

## Implementation Details

### Server Behavior

The server listens for incoming connections on a specified port and manages multiple clients simultaneously. It processes commands sent by clients, handles user authentication, and manages channel-based communication. Key implementation details include:

- **Non-blocking I/O**: All socket operations must be non-blocking to prevent the server from hanging.
- **Command Parsing**: The server parses and processes IRC commands, ensuring that they conform to the IRC protocol.
- **Error Handling**: The server must gracefully handle errors, such as partial data reception and low bandwidth.

### Mandatory Commands

The server must implement the following IRC commands:

- **NICK**: Set or change a user's nickname.
- **USER**: Specify the username and other details of a client.
- **JOIN**: Join a specific channel.
- **PRIVMSG**: Send a private message to a user or a channel.
- **PART**: Leave a channel.
- **QUIT**: Disconnect from the server.

### Operator Commands

In addition to basic commands, the server must support operator-specific commands:

- **KICK**: Eject a client from a channel.
- **INVITE**: Invite a client to a channel.
- **TOPIC**: Change or view the channel topic.
- **MODE**: Change the channel's mode (e.g., invite-only, topic restricted, etc.).

## Building

Before building the project, ensure that you have the necessary dependencies installed. Follow the instructions for your specific operating system:

### Debian/Ubuntu

Install the dependencies using:

```bash
sudo apt-get update
sudo apt-get install -y gcc g++ make
```

### Fedora

Install the dependencies using:

```bash
sudo dnf install gcc-c++ make
```

### Alpine Linux

Install the dependencies using:

```bash
sudo apk add gcc g++ make
```

### macOS

Install the dependencies using Homebrew:

```bash
brew install gcc make
```

After installing the dependencies, you can compile the project by running:

```bash
make
```

This will generate the `ircserv` executable.

## Usage Guide

### Running the Server

To start the server, run the following command:

```bash
./ircserv <port> <password>
```

- **port**: The port number on which your IRC server will listen for incoming connections.
- **password**: The connection password required for clients to connect.

### Connecting to the Server

Use an IRC client to connect to your server by specifying the server's IP address, port, and password.

### Exiting the Server

To gracefully shut down the server, use appropriate signals or commands depending on your implementation.

## Using HexChat

**HexChat** is a popular open-source IRC client that is available on multiple platforms, including Windows, macOS, and Linux. It provides a user-friendly interface for connecting to IRC servers, joining channels, and communicating with other users.

### Installing HexChat

- **Windows**: Download and install HexChat from the official website: [HexChat for Windows](https://hexchat.github.io/downloads.html).
- **macOS**: Install HexChat using Homebrew:
  ```bash
  brew install --cask hexchat
  ```
- **Linux**: Install HexChat using your distribution's package manager:
  - **Debian/Ubuntu**: 
    ```bash
    sudo apt-get install hexchat
    ```
  - **Fedora**: 
    ```bash
    sudo dnf install hexchat
    ```
  - **Alpine**:
    ```bash
    sudo apk add hexchat
    ```

### Connecting to Your IRC Server with HexChat

1. **Open HexChat**: Launch the HexChat application.
2. **Network List**: Upon opening, you'll see the "Network List" dialog. If not, you can access it by going to `HexChat > Network List`.
3. **Add a New Network**: Click the `Add` button to create a new network. Name it something relevant to your server.
4. **Edit the Network**: Highlight the new network and click `Edit`. Here, you will add the server details:
   - **Server address**: Enter your server's IP address followed by the port (e.g., `127.0.0.1/6667`).
   - **Password**: If your server requires a password, enter it in the server password field.
5. **Connect**: Click `Connect` to establish a connection to your IRC server.
6. **Join Channels**: Once connected, you can join channels by typing `/join #channelname` in the text box.

### Sending Commands in HexChat

You can send various IRC commands directly from the HexChat client. For example, to change your nickname, type:

```bash
/NICK MyNewNick
```

To send a private message to another user:

```bash
/PRIVMSG username :Hello there!
```

## Available Commands

The server supports a variety of IRC commands, including:

- **NICK**: Set or change your nickname.
- **USER**: Provide your username and other details.
- **JOIN**: Join a channel.
- **PRIVMSG**: Send a private message.
- **PART**: Leave a channel.
- **QUIT**: Disconnect from the server.

Operator-specific commands:

- **KICK**: Eject a user from a channel.
- **INVITE**: Invite a user to a channel.
- **TOPIC**: Set or view the topic of a channel.
- **MODE**: Change the mode of a channel.

## Examples of Usage

### `NICK` Command
- **Set your nickname**:
  ```bash
  NICK MyNickname
  ```

### `USER` Command
- **Set your username**:
  ```bash
  USER myusername 0 * :Real Name
  ```

### `JOIN` Command
- **Join a channel**:
  ```bash
  JOIN #mychannel
  ```

### `PRIVMSG` Command
- **Send a private message**:
  ```bash
  PRIVMSG #mychannel :Hello everyone!
  ```

### `KICK` Command
- **Kick a user from a channel**:
  ```bash
  KICK #mychannel user :Reason for kicking
  ```

## Conclusion

The **ft_irc project** offers an in-depth exploration of network programming and the IRC protocol, providing a valuable experience in building a robust and reliable server. By completing this project, you will enhance your understanding of C++ programming, socket management, and the challenges of real-time communication systems.

We hope that this project has been both challenging and rewarding, and that it has helped you grow as a programmer.

## Reporting Issues

If you encounter any issues or bugs while working on the ft_irc project, we encourage you to report them. Please create an issue in

 the project's repository with a detailed description of the problem, steps to reproduce, and any relevant screenshots or logs.

Your feedback is valuable and helps improve the project for everyone.
# FT_IRC-Chat-Hex-Compatibility-
