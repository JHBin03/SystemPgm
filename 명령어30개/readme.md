## 1. pwd

기능 : 사용자가 현재 머무르고 있는 작업 디렉토리의 전체 절대 경로를 화면에 출력합니다.

```c
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main() {
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd 오류");
        return 1;
    }

    return 0;
}

```

## 2. ls

기능 : 지정한 디렉토리 내부의 파일, 링크, 하위 디렉토리 목록을 읽어서 화면에 나열합니다. 디렉토리를 지정하지 않으면 현재 디렉토리(".")를 대상으로 합니다.

```c
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    char *target_dir = ".";

    if (argc > 1) {
        target_dir = argv[1];
    }

    dir = opendir(target_dir);
    if (dir == NULL) {
        perror("ls 오류");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s  ", entry->d_name);
    }
    printf("\n");

    closedir(dir);
    return 0;
}

```

## 3. cd

기능 : 현재 작업 디렉토리를 물리적으로 변경합니다.

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <이동할_디렉토리_경로>\n", argv[0]);
        return 1;
    }

    if (chdir(argv[1]) != 0) {
        perror("cd 오류");
        return 1;
    }

    return 0;
}

```

## 4. mkdir

기능 : 새로운 디렉토리를 파일 시스템 내에 생성합니다.

```c
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <생성할_디렉토리_명>\n", argv[0]);
        return 1;
    }

    if (mkdir(argv[1], 0755) != 0) {
        perror("mkdir 오류");
        return 1;
    }

    return 0;
}

```

## 5. rmdir

기능 : 비어 있는 디렉토리를 삭제합니다.

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <삭제할_디렉토리_명>\n", argv[0]);
        return 1;
    }

    if (rmdir(argv[1]) != 0) {
        perror("rmdir 오류");
        return 1;
    }

    return 0;
}

```

## 6. touch

기능 : 빈 파일을 생성하거나 기존 파일의 수정/접근 타임스탬프를 갱신합니다.

```c
#include <stdio.h>
#include <utime.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <파일명>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("touch 오류");
        return 1;
    }
    close(fd);

    if (utime(argv[1], NULL) != 0) {
        perror("touch 타임스탬프 갱신 오류");
        return 1;
    }

    return 0;
}

```

## 7. rm

기능 : 파일 또는 링크를 파일 시스템에서 삭제합니다.

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <삭제할_파일명>\n", argv[0]);
        return 1;
    }

    if (unlink(argv[1]) != 0) {
        perror("rm 오류");
        return 1;
    }

    return 0;
}

```

## 8. ln

기능 : 파일에 대한 하드 링크(Hard Link) 또는 심볼릭 링크(Symbolic Link)를 생성합니다.

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 3) {
        if (link(argv[1], argv[2]) != 0) {
            perror("ln 오류");
            return 1;
        }
    } else if (argc == 4 && strcmp(argv[1], "-s") == 0) {
        if (symlink(argv[2], argv[3]) != 0) {
            perror("ln 심볼릭 오류");
            return 1;
        }
    } else {
        fprintf(stderr, "사용법: %s [-s] <원본_파일> <대상_파일>\n", argv[0]);
        return 1;
    }

    return 0;
}

```

## 9. cp

기능 : 원본 파일의 데이터를 대상 파일로 복사합니다.

```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int fd_in, fd_out;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    if (argc < 3) {
        fprintf(stderr, "사용법: %s <원본_파일> <대상_파일>\n", argv[0]);
        return 1;
    }

    fd_in = open(argv[1], O_RDONLY);
    if (fd_in < 0) {
        perror("cp 원본 열기 오류");
        return 1;
    }

    fd_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0) {
        perror("cp 대상 열기 오류");
        close(fd_in);
        return 1;
    }

    while ((bytes_read = read(fd_in, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(fd_out, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("cp 쓰기 오류");
            close(fd_in);
            close(fd_out);
            return 1;
        }
    }

    close(fd_in);
    close(fd_out);
    return 0;
}

```

## 10. mv

기능 : 파일이나 디렉토리의 위치를 이동하거나 이름을 변경합니다.

```c
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "사용법: %s <원본_경로> <대상_경로>\n", argv[0]);
        return 1;
    }

    if (rename(argv[1], argv[2]) != 0) {
        perror("mv 오류");
        return 1;
    }

    return 0;
}

```
