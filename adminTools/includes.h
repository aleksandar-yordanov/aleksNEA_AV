#pragma once
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QCryptographicHash>
#include <iostream>
#include <thread>
#include <string>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include "nlohmann/json.hpp"

using namespace std::chrono_literals;

using json = nlohmann::json;
