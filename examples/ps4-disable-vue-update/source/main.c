#include "ps4.h"

#define TASK_PATH "/user/bgft/task/"
#define TARGET_MAGIC "pdbmCUSA00960"
#define MAGIC_LEN 13

static int block_update(const char *dir_path) {
  char path[PATH_MAX];

  snprintf(path, sizeof(path), "%s/patch.pbm", dir_path);
  int fd = open(path, O_RDONLY, 0);
  if (fd < 0)
    return 0;

  char header[MAGIC_LEN];
  ssize_t n = read(fd, header, MAGIC_LEN);
  close(fd);

  if (n != MAGIC_LEN || memcmp(header, TARGET_MAGIC, MAGIC_LEN) != 0)
    return 0;

  snprintf(path, sizeof(path), "%s/patch.pkg", dir_path);
  unlink(path);
  return 1;
}

int _main(struct thread *td) {
  UNUSED(td);

  initKernel();
  initLibc();
  initSysUtil();

  DIR *dir = opendir(TASK_PATH);
  if (!dir) {
    printf_notification("[ERROR] Failed to blocked VUE update");
    return 1;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_name[0] == '.')
      continue;

    char full_path[PATH_MAX];
    snprintf(full_path, sizeof(full_path), "%s%s", TASK_PATH, entry->d_name);

    struct stat sb;
    if (stat(full_path, &sb) != 0 || !S_ISDIR(sb.st_mode))
      continue;

    if (block_update(full_path)) {
      closedir(dir);
      printf_notification("VUE update blocked");
      return 0;
    }
  }

  closedir(dir);
  printf_notification("No VUE update found\n1-Check for update manually\n2-Pause the download\n3-Run the payload again");
  return 0;
}
