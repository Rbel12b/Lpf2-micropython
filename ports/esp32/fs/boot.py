import hub,lpf2,machine,vfs,os

try:
    if hub.board.SD_MODE == 2:
        print("Initializing SD card in SD mode...")
        sd = machine.SDCard(slot=hub.board.SD_SLOT)
    elif hub.board.SD_MODE == 1:
        print("Initializing SD card in SPI mode...")
        sd = machine.SDCard(slot=hub.board.SD_SLOT, sck=hub.board.SD_SCK, mosi=hub.board.SD_MOSI, miso=hub.board.SD_MISO, cs=hub.board.SD_CS)
    else:
        print("No SD card mode configured for this board.")
        sd = None
    vfs.mount(sd, '/sd')
    print("SD card mounted at /sd")
except Exception as e:
    print("Failed to mount SD card:", e)