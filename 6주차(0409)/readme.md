# 컴퓨터 시스템 구조

"바퀴를 두 번 발명하지 마라"

## 핵심 개념

* 유닉스 커널(kernel)은 하드웨어를 관리하며 다음 서비스를 제공

  * 파일 관리 (File management)
  * 프로세스 관리 (Process management)
  * 메모리 관리 (Memory management)
  * 통신 관리 (Communication management)
  * 주변장치 관리 (Device management)
* 구조:

  * 응용 프로그램 → 시스템 호출 → 커널 → 하드웨어
    (3페이지 그림 구조 설명)

---

# 시스템 호출

## 정의

* 시스템 호출(System Call)은 **커널에 서비스 요청을 위한 프로그래밍 인터페이스**
* 응용 프로그램은 직접 하드웨어를 접근하지 않고 **시스템 호출을 통해 커널에 요청**

---

# 시스템 호출 과정

## 동작 흐름

(5페이지 그림 기반 설명)

1. 사용자 프로그램에서 함수 호출 (예: open())
2. 라이브러리 함수가 **trap 명령어 실행**
3. CPU가 커널 모드로 전환
4. 커널 내부 해당 시스템 호출 실행
5. 결과 반환 → 사용자 모드 복귀

## 핵심 특징

* 사용자 코드 ↔ 커널 코드 분리
* 시스템 호출 시 **모드 전환(user → kernel)** 발생

---

# 시스템 호출 요약

| 자원   | 주요 시스템 호출                                           |
| ---- | --------------------------------------------------- |
| 파일   | open(), close(), read(), write(), dup(), lseek()    |
| 프로세스 | fork(), exec(), exit(), wait(), getpid(), getppid() |
| 메모리  | malloc(), calloc(), free()                          |
| 시그널  | signal(), alarm(), kill(), sleep()                  |
| IPC  | pipe(), socket()                                    |

* 시그널은 프로세스와 연관이 있다.

---

# 파일 (5.2)

## 정의

* 연속된 바이트의 나열
* 특별한 포맷 없음
* 디스크뿐 아니라 **외부 장치 인터페이스 포함**

→ 리눅스 특징:

* **하드웨어도 파일로 인식**

---

# 파일 열기 : open()

## 기본

```c
int open(const char *path, int oflag, [mode_t mode]);
```

* 성공: 파일 디스크립터 반환
* 실패: -1 반환

## 파일 디스크립터

* 열린 파일을 나타내는 번호

## include

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
```

---

# 파일 열기

## oflag 옵션

### 기본 모드

* O_RDONLY : 읽기
* O_WRONLY : 쓰기
* O_RDWR : 읽기/쓰기

### 추가 옵션

* O_APPEND : 파일 끝에 추가
* O_CREAT : 파일 생성
* O_TRUNC : 기존 내용 삭제
* O_EXCL : 파일 존재 시 오류
* O_NONBLOCK : 논블로킹
* O_SYNC : 디스크에 실제 기록 후 반환

---

# 파일 열기 예

```c
fd = open("account", O_RDONLY);
fd = open(argv[1], O_RDWR);
fd = open(argv[1], O_RDWR | O_CREAT, 0600);
fd = open("tmpfile", O_WRONLY|O_CREAT|O_TRUNC, 0600);
fd = open("/sys/log", O_WRONLY|O_APPEND|O_CREAT, 0600);
```

---

# 파일 열기 : fopen.c

```c
if ((fd = open(argv[1], O_RDWR)) == -1)
    printf("파일 열기 오류\n");
else
    printf("파일 %s 열기 성공 : %d\n", argv[1], fd);
```

---

# 파일 생성 : creat()

```c
int creat(const char *path, mode_t mode);
```

## 특징

* 파일 생성 + 쓰기 모드
* 기존 파일 있으면 내용 삭제
* 내부적으로:

```c
open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
```

---

# 파일 닫기 : close()

```c
int close(int fd);
```

* fd가 나타내는 파일을 닫는다
* 성공: 0 / 실패: -1

---

# 데이터 읽기 : read()

```c
ssize_t read(int fd, void *buf, size_t nbytes);
```

## 동작

* fd에서 nbytes 읽기
* buf에 저장

## 반환값

* 읽은 바이트 수
* EOF: 0
* 실패: -1

---

# 파일 크기 계산 : fsize.c

## 핵심 로직

```c
while ((nread = read(fd, buffer, BUFSIZE)) > 0)
    total += nread;
```

* EOF까지 반복 읽기 → 총 바이트 합산

---

# 데이터 쓰기 : write()

```c
ssize_t write(int fd, void *buf, size_t nbytes);
```

* buf → 파일에 쓰기
* 반환: 실제 쓴 바이트 수 / 실패: -1

---

# 파일 복사 : copy.c

## 핵심 로직

```c
while ((n = read(fd1, buf, BUFSIZ)) > 0)
    write(fd2, buf, n);
```

* 읽고 → 바로 쓰기

---

# 파일 디스크립터 복제

## dup / dup2

```c
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```

## 특징

* 하나의 파일을 공유
* 같은 파일 위치 포인터 공유

---

# 파일 디스크립터 복제 : dup.c

```c
fd2 = dup(fd1);
write(fd2, "Bye! Linux", 10);
```

결과:

```
Hello! LinuxBye! Linux
```

---

# 5.3 임의 접근 파일

## 개념

* 원하는 위치로 바로 이동하여 읽기/쓰기 가능

---

# 파일 위치 포인터

* 현재 읽거나 쓸 위치
* (current file position)

---

# 임의 접근 : lseek()

```c
off_t lseek(int fd, off_t offset, int whence);
```

* 파일 위치 포인터 이동
* 성공: 현재 위치 반환 / 실패: -1

## off_t

* 파일 내 바이트 위치를 나타내는 정수 타입

---

# 파일 위치 이동 예

## 기본 이동

```c
lseek(fd, 0L, SEEK_SET); // 시작
lseek(fd, 100L, SEEK_SET); // 100바이트
lseek(fd, 0L, SEEK_END); // 끝
```

## 레코드 이동

```c
lseek(fd, n*sizeof(record), SEEK_SET);
lseek(fd, sizeof(record), SEEK_CUR);
lseek(fd, -sizeof(record), SEEK_CUR);
```

---

# 레코드 저장 예

```c
write(fd, &record1, sizeof(record));
write(fd, &record2, sizeof(record));
lseek(fd, sizeof(record), SEEK_END);
write(fd, &record3, sizeof(record));
```

---

# 학생 레코드 파일 예제

## 구조

```c
struct student {
    char name[MAX];
    int id;
    int score;
};
```

## 위치 계산

```
(record.id - START_ID) * sizeof(record)
```

---

# dbcreate.c (저장)

* 학번 기준 위치에 저장
* lseek + write 사용

---

# dbquery.c (조회)

* 학번 입력 → 해당 위치 이동
* read → 출력

---

# dbupdate.c (수정)

## 과정

1. 레코드 읽기
2. 수정
3. 원래 위치에 다시 write

```c
lseek(fd, -sizeof(record), SEEK_CUR);
write(fd, &record, sizeof(record));
```
