# **** WORK IN PROGRESS ****


# Generic ESB-HOME device firmware

Firmware is based on the NRF5 SDK which is included as a submodule (it is a copy I made for myself for archiving purposes). The firmware is aimed to exposed several generic esb-home-fw modules, which are used in my homebrew smart home ecosystem `esb-home`. It can be used as base for application specific firmware(s)

## ESB Commands

### Binary sensor
The firmware implements all commands of the ESB binary sensor, see `here` **TODO: Link to binary sensor repo**

### Application
`ESB_CMD_VERSION (0x10)`

    - Get firmware version
    - Params: None
    - Answer Payload: [3 x uint8] [vMajor, vMinor, vPatch]

`ESB_CFG_SET_CENTRAL_ADDR (0x83)`

    - Set ESB Pipeline Address to send notifications to
    - Params: [5x uint8] ESB Pipeline address of central device

`ESB_CFG_SAVE (0x84)`

    - Write current configuration to persistent memory if it has changed
    - Params: None
    - Answer Payload: None

