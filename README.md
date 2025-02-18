# Q-tris!<br>Just Tetris, but with multiplayer

The Q-tris is just tetris with single-player and multi-player modes. This game allows you play in classic tetris with friends(2-4 clients). You can also choose the appearance mode of figures. For instance, choose "Same" mode for the same figures for all clients during game or "Different" mode for different figures.

It works with Standard Thread Library and Socket API(for Linux).

Clients exchange data frames with server, and server handle all requests from users. All data are JSON objects.


# Dependencies
This project has [another repository](https://github.com/MihailPohodeev/Q-tris-backend.git) with Server-program for handling users.

# Gratitude
this project was implemented with next libraries:
1. [SFML](https://www.sfml-dev.org/)
2. [TGUI](https://github.com/texus/TGUI.git)
3. [nlohmann::json](https://github.com/nlohmann/json.git)


