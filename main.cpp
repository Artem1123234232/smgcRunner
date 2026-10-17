//#include <QCoreApplication>

//#include "smpbcore.h"

#include <iostream>
#include <format>
#include <cstdint>

// Математика
#include <cmath>

// Ядро и его компоненты
#include "Core/Config.h"
#include "Core/Core.h"

// SMGC
#include "SMGC/SMGC.h"

int main(int argc, char *argv[]) {
    Core core = Core();
    core.setDebugModeEnabled(true);
    core.appendComponent(std::make_unique<Config>(argc, argv));
    core.appendComponent(std::make_unique<SMGC>());

    core.init();

    int errorCode = core.cycle();

    if (errorCode == 0) {
        std::clog << "Program finished cleanly." << std::endl;
    } else {
        std::clog << "Program finished with error code " << std::to_string(errorCode) << "." << std::endl;
    }

    return errorCode;
}
