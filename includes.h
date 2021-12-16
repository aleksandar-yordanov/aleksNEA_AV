#pragma once

#include <fstream>
#include <vector>
#include <iostream>
#include <SQLAPI.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <QWidget>
#include <QMainWindow>
#include <QApplication>
#include <QString>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <qtimer.h>
#include <QFileSystemModel>
#include <regex>

#include <sys/kernel.h>

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include "common.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;


#include "common.h"
