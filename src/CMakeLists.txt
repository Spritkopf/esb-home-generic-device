add_executable(generic-device)


target_include_directories(generic-device PRIVATE 
    ../inc
    ${NRF_SDK_HOME}/integration/nrfx
    ${NRF_SDK_HOME}/integration/nrfx/legacy
    ${NRF_SDK_HOME}/modules/nrfx/hal
    ${NRF_SDK_HOME}/modules/nrfx/drivers/include
    ${NRF_SDK_HOME}/components/libraries/delay
    ${NRF_SDK_HOME}/components/libraries/queue
    ${NRF_SDK_HOME}/components/libraries/log/src
    ${NRF_SDK_HOME}/components/libraries/atomic
)

target_sources(generic-device PUBLIC 
    main.c
    debug_swo.c
    timebase.c
    ${NRF_SDK_HOME}/modules/nrfx/mdk/gcc_startup_nrf52840.S
    ${NRF_SDK_HOME}/modules/nrfx/mdk/system_nrf52.c
    ${NRF_SDK_HOME}/modules/nrfx/drivers/src/nrfx_gpiote.c
    ${NRF_SDK_HOME}/modules/nrfx/drivers/src/nrfx_timer.c
    ${NRF_SDK_HOME}/modules/nrfx/drivers/src/nrfx_systick.c
    ${NRF_SDK_HOME}/components/proprietary_rf/esb/nrf_esb.c
    ${NRF_SDK_HOME}/components/libraries/queue/nrf_queue.c
    ${NRF_SDK_HOME}/components/libraries/atomic/nrf_atomic.c
    ${NRF_SDK_HOME}/components/libraries/util/app_util_platform.c
)

target_link_directories(generic-device PRIVATE ${NRF_SDK_HOME}/modules/nrfx/mdk)
target_link_libraries(generic-device PRIVATE -T${PROJECT_SOURCE_DIR}/toolchain/esb_low_power_prx_gcc_nrf52.ld)
target_link_libraries(generic-device PUBLIC esb-home-fw)


target_compile_definitions(generic-device PUBLIC
    "BSP_DEFINES_ONLY"
    "CONFIG_GPIO_AS_PINRESET"
    "ESB_PRESENT"
    "FLOAT_ABI_HARD"
    "NRF52840"
    "NRF52_PAN_74"
    "USE_APP_CONFIG"
)
