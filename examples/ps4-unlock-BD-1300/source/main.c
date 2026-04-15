#include "ps4.h"

#define DEST_PATH "/system_ex/app/NPXS20113/bdjstack/lib/ext/00000.jar"

int _main(struct thread *td) {
  initKernel();
  initLibc();
  initSysUtil();

  jailbreak();
  mmap_patch();

  char fw_version[6] = {0};
  get_firmware_string(fw_version);
  if (strcmp(fw_version, "13.00") != 0) {
    printf_notification("[ERROR] for FW 13.00 only!\nDetected: %s", fw_version);
    return 0;
  }

  const char *paths[] = {
    "/mnt/usb0/00000.jar",
    "/mnt/usb1/00000.jar",
    "/mnt/usb2/00000.jar",
    "/mnt/usb3/00000.jar",
    "/mnt/usb4/00000.jar",
    "/mnt/disc/jar-1300/00000.jar",
    //"/mnt/disc/BDMV/JAR/00000.jar",
  };
  int count = sizeof(paths) / sizeof(paths[0]);

  for (int i = 0; i < count; i++) {
    if (file_exists(paths[i])) {
      unlink(DEST_PATH);
      rmdir(DEST_PATH);
      copy_file((char *)paths[i], DEST_PATH);
      const char *source = (i < 5) ? "USB" : "Disc";
      printf_notification("Unlock BD-JB successfully!\nJAR copied from %s", source);
      return 0;
    }
  }

  printf_notification("[ERROR] file not found on USB or Disc!");
  return 0;
}
