#pragma once

#define	 SERVER_IP										"127.0.0.1"
constexpr unsigned short SERVER_PORT = 3500;
constexpr unsigned short MAX_BUFFER = 1024;

constexpr int MAX_USER = 1000;
constexpr int MAX_NPC = 1000;
constexpr int MAX_CHARACTER = MAX_USER + MAX_NPC;