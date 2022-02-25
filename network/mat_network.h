#pragma once
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <cstring>
#include "base.h"
#include <unistd.h>
#include <cassert>
#include "../matrix/multithread.h"
#include "../matrix/tableau.h"

Matrix recv_block(int);
