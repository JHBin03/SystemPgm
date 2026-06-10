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

## 11. chmod

기능 : 파일 또는 디렉토리의 접근 권한(Permission Bits)을 변경합니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "사용법: %s <8진수_권한> <파일명>\n", argv[0]);
        return 1;
    }

    mode_t mode = strtol(argv[1], NULL, 8);

    if (chmod(argv[2], mode) != 0) {
        perror("chmod 오류");
        return 1;
    }

    return 0;
}

```

## 12. chown

기능 : 파일 또는 디렉토리의 소유자(UID) 및 소유 그룹(GID)을 변경합니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "사용법: %s <UID> <GID> <파일명>\n", argv[0]);
        return 1;
    }

    uid_t uid = atoi(argv[1]);
    gid_t gid = atoi(argv[2]);

    if (chown(argv[3], uid, gid) != 0) {
        perror("chown 오류");
        return 1;
    }

    return 0;
}

```

## 13. cat

기능 : 파일 내용을 처음부터 끝까지 순차적으로 표준 출력 스트림에 인쇄합니다.

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <파일명>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("cat 오류");
        return 1;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return 0;
}

```

## 14. head

기능 : 파일의 시작 부분부터 지정한 라인 수(10줄)만큼만 읽어 출력합니다.

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n = 10;
    FILE *file;

    if (argc < 2) {
        fprintf(stderr, "사용법: %s <파일명>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("head 오류");
        return 1;
    }

    char buffer[1024];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL && count < n) {
        printf("%s", buffer);
        count++;
    }

    fclose(file);
    return 0;
}

```

## 15. tail

기능 : 파일의 끝 부분부터 지정한 라인 수(10줄)만큼 역산하거나 추출하여 출력합니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES 10
#define MAX_LEN 1024

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <파일명>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("tail 오류");
        return 1;
    }

    char buffer[LINES][MAX_LEN];
    int count = 0;

    while (fgets(buffer[count % LINES], MAX_LEN, file) != NULL) {
        count++;
    }

    int start = count > LINES ? count % LINES : 0;
    int total = count > LINES ? LINES : count;

    for (int i = 0; i < total; i++) {
        printf("%s", buffer[(start + i) % LINES]);
    }

    fclose(file);
    return 0;
}

```

## 16. wc

기능 : 파일 내의 총 줄 수, 단어 수, 바이트(글자) 수를 카운트하여 출력합니다.

```c
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <파일명>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("wc 오류");
        return 1;
    }

    int lines = 0, words = 0, bytes = 0;
    int in_word = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        bytes++;
        if (ch == '\n') {
            lines++;
        }
        if (isspace(ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }

    printf("%d %d %d %s\n", lines, words, bytes, argv[1]);

    fclose(file);
    return 0;
}

```

## 17. echo

기능 : 명령줄 인자로 전달받은 문자열 데이터를 표준 출력에 그대로 덤프합니다.

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        printf("%s", argv[i]);
        if (i < argc - 1) {
            printf(" ");
        }
    }
    printf("\n");
    return 0;
}

```

## 18. basename

기능 : 전체 파일 경로 스트림에서 디렉토리 경로를 떼어내고 순수 파일명만 추출합니다.

```c
#include <stdio.h>
#include <libgen.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <경로>\n", argv[0]);
        return 1;
    }

    char *base = basename(argv[1]);
    printf("%s\n", base);

    return 0;
}

```

## 19. dirname

기능 : 전체 파일 경로 스트림에서 파일명을 제외한 상위 디렉토리 경로만 추출합니다.

```c
#include <stdio.h>
#include <libgen.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <경로>\n", argv[0]);
        return 1;
    }

    char *dir = dirname(argv[1]);
    printf("%s\n", dir);

    return 0;
}

```

## 20. tr

기능 : 표준 입력으로 들어오는 텍스트의 특정 문자 세트를 다른 문자로 치환합니다.

```c
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "사용법: %s <찾을문자열> <바꿀문자열>\n", argv[0]);
        return 1;
    }

    char *set1 = argv[1];
    char *set2 = argv[2];
    int map[256];

    for (int i = 0; i < 256; i++) {
        map[i] = i;
    }

    int len = strlen(set1);
    for (int i = 0; i < len; i++) {
        map[(unsigned char)set1[i]] = set2[i];
    }

    int ch;
    while ((ch = fgetc(stdin)) != EOF) {
        putchar(map[ch]);
    }

    return 0;
}

```

## 21. ps

기능 : 현재 실행 중인 프로세스들의 상태와 PID 스냅샷을 구성하여 보여줍니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc");
    if (dir == NULL) {
        perror("ps 오류");
        return 1;
    }

    printf("PID\tCMD\n");

    while ((entry = readdir(dir)) != NULL) {
        if (isdigit(entry->d_name[0])) {
            char path[256];
            char cmd[256];
            FILE *fp;

            snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);
            fp = fopen(path, "r");
            if (fp != NULL) {
                if (fgets(cmd, sizeof(cmd), fp) != NULL) {
                    for (int i = 0; cmd[i] != '\0'; i++) {
                        if (cmd[i] == '\n') {
                            cmd[i] = '\0';
                            break;
                        }
                    }
                    printf("%s\t%s\n", entry->d_name, cmd);
                }
                fclose(fp);
            }
        }
    }

    closedir(dir);
    return 0;
}

```

## 22. kill

기능 : 특정 PID를 가진 프로세스에 무작위 시그널(Signal)을 송신하여 제어/종료합니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "사용법: %s <시그널번호> <PID>\n", argv[0]);
        return 1;
    }

    int sig = atoi(argv[1]);
    pid_t pid = atoi(argv[2]);

    if (kill(pid, sig) != 0) {
        perror("kill 오류");
        return 1;
    }

    return 0;
}

```

## 23. sleep

기능 : 지정된 초(Seconds) 단위 시간 동안 호출 프로세스의 실행을 일시 중단합니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <초>\n", argv[0]);
        return 1;
    }

    unsigned int seconds = atoi(argv[1]);
    sleep(seconds);

    return 0;
}

```

## 24. wait

기능 : 부모 프로세스가 자식 프로세스의 상태 변화(종료 등)를 감지할 때까지 대기합니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork 오류");
        return 1;
    } else if (pid == 0) {
        sleep(2);
        return 0;
    } else {
        int status;
        wait(&status);
    }

    return 0;
}

```

## 25. whoami

기능 : 현재 프로세스를 실행 중인 유효 사용자의 이름을 시스템에서 조회해 출력합니다.

```c
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

int main() {
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);

    if (pw) {
        printf("%s\n", pw->pw_name);
    } else {
        perror("whoami 오류");
        return 1;
    }

    return 0;
}

```

## 26. hostname

기능 : 시스템 고유의 호스트 이름을 조회하여 화면에 표기합니다.

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printf("%s\n", hostname);
    } else {
        perror("hostname 오류");
        return 1;
    }

    return 0;
}

```

## 27. date

기능 : 시스템의 현재 날짜와 표준 시간대 정보를 포맷에 맞게 출력합니다.

```c
#include <stdio.h>
#include <time.h>

int main() {
    time_t t;
    struct tm *tm_info;
    char buffer[256];

    time(&t);
    tm_info = localtime(&t);

    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Z %Y", tm_info);
    printf("%s\n", buffer);

    return 0;
}

```

## 28. cal

기능 : 캘린더 알고리즘을 사용해 지정된 달 혹은 현재 달의 달력을 정렬하여 출력합니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_day_of_week(int year, int month) {
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    int k = year % 100;
    int j = year / 100;
    int h = (1 + 13 * (month + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    return (h + 5) % 7;
}

int get_days_in_month(int year, int month) {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        return 29;
    }
    return days[month - 1];
}

int main(int argc, char *argv[]) {
    int year, month;

    if (argc == 3) {
        month = atoi(argv[1]);
        year = atoi(argv[2]);
    } else {
        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);
        year = tm_info->tm_year + 1900;
        month = tm_info->tm_mon + 1;
    }

    printf("     %02d %d\n", month, year);
    printf("Su Mo Tu We Th Fr Sa\n");

    int start_day = get_day_of_week(year, month);
    int days = get_days_in_month(year, month);

    for (int i = 0; i < start_day; i++) {
        printf("   ");
    }

    for (int day = 1; day <= days; day++) {
        printf("%2d ", day);
        if ((day + start_day) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    return 0;
}

```

## 29. uptime

기능 : 시스템이 부팅된 이후 경과한 누적 시간 및 평균 부하 등을 계산하여 출력합니다.

```c
#include <stdio.h>
#include <sys/sysinfo.h>

int main() {
    struct sysinfo info;

    if (sysinfo(&info) == 0) {
        long uptime = info.uptime;
        long days = uptime / 86400;
        long hours = (uptime / 3600) % 24;
        long mins = (uptime / 60) % 60;

        printf("up %ld days, %ld:%02ld\n", days, hours, mins);
    } else {
        perror("uptime 오류");
        return 1;
    }

    return 0;
}

```

## 30. clear

기능 : 터미널 가상 화면의 텍스트 버퍼를 모두 지우고 커서를 최상단 좌측으로 이동합니다.

```c
#include <stdio.h>

int main() {
    printf("\033[H\033[2J");
    return 0;
}

```
