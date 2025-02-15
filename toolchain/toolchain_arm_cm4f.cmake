set(CMAKE_SYSTEM_PROCESSOR arm-cm4f)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CROSSCOMPILING 1)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_C_FLAGS_INIT "")
set(CMAKE_CXX_FLAGS_INIT "")
set(CMAKE_EXE_LINKER_FLAGS_INIT "")

set(CMAKE_C_COMPILER ${TOOLCHAIN}arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_OBJCOPY ${TOOLCHAIN}arm-none-eabi-objcopy)
set(CMAKE_AR ${TOOLCHAIN}arm-none-eabi-ar)
set(CMAKE_RANLIB ${TOOLCHAIN}arm-none-eabi-ranlib)

if (NOT DEFINED SEPARATE_ELF_SECTIONS OR SEPARATE_ELF_SECTIONS)
    string(APPEND CMAKE_C_FLAGS_INIT " -ffunction-sections")
    string(APPEND CMAKE_C_FLAGS_INIT " -fdata-sections")
endif()

string(APPEND CMAKE_C_FLAGS_INIT " -fno-strict-aliasing")
string(APPEND CMAKE_C_FLAGS_INIT " -fno-builtin")

if (NOT DEFINED SEPARATE_ELF_SECTIONS OR SEPARATE_ELF_SECTIONS)
    string(APPEND CMAKE_CXX_FLAGS_INIT " -ffunction-sections")
    string(APPEND CMAKE_CXX_FLAGS_INIT " -fdata-sections")
endif()

string(APPEND CMAKE_CXX_FLAGS_INIT " -fno-strict-aliasing")
string(APPEND CMAKE_CXX_FLAGS_INIT " -fno-builtin")

# string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " --specs=nano.specs")
string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " --specs=nosys.specs")

if(CMAKE_TOOLCHAIN_PATH)
    set(TOOLCHAIN ${CMAKE_TOOLCHAIN_PATH}/)
else()
    set(TOOLCHAIN "")
endif()



string(APPEND CMAKE_C_FLAGS_INIT " -mthumb")
string(APPEND CMAKE_C_FLAGS_INIT " -mabi=aapcs")
string(APPEND CMAKE_C_FLAGS_INIT " -mcpu=cortex-m4")
string(APPEND CMAKE_C_FLAGS_INIT " -mfloat-abi=hard")
string(APPEND CMAKE_C_FLAGS_INIT " -mfpu=fpv4-sp-d16")

string(APPEND CMAKE_CXX_FLAGS_INIT " -mthumb")
string(APPEND CMAKE_CXX_FLAGS_INIT " -mabi=aapcs")
string(APPEND CMAKE_CXX_FLAGS_INIT " -mcpu=cortex-m4")
string(APPEND CMAKE_CXX_FLAGS_INIT " -mfloat-abi=hard")
string(APPEND CMAKE_CXX_FLAGS_INIT " -mfpu=fpv4-sp-d16")

string(APPEND CMAKE_ASM_FLAGS_INIT " -x assembler-with-cpp")

string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " -mthumb")
string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " -mabi=aapcs")
string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " -mcpu=cortex-m4")
string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " -mfloat-abi=hard")
string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " -mfpu=fpv4-sp-d16")
string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " -Wl,--gc-sections")

