## 5주차 예제 코드들

### 1. 파일 열기 예제

```c
FILE *fp;
fp = fopen("~/sp/text.txt", "r");

if (fp == NULL) {
    printf("파일 열기 오류\n");
}
```

```c
fp = fopen("outdata.txt", "w");
fp = fopen("outdata.txt", "a");
```

---

## 2. 문자 단위 입출력

### 2. cat.c (파일 내용 출력)

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int c;

    if (argc < 2)
        fp = stdin;
    else
        fp = fopen(argv[1],"r");

    c = getc(fp);

    while (c != EOF) {
        putc(c, stdout);
        c = getc(fp);
    }

    fclose(fp);
    return 0;
}
```

 기능: 파일 내용을 그대로 출력


---

## 3. 파일 복사

### 3. copy.c

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    char c;
    FILE *fp1, *fp2;

    if (argc !=3) {
        fprintf(stderr, "사용법: %s 파일1 파일2\n", argv[0]);
        return 1;
    }

    fp1 = fopen(argv[1], "r");
    if (fp1 == NULL) {
        fprintf(stderr, "파일 %s 열기 오류\n", argv[1]);
        return 2;
    }

    fp2 = fopen(argv[2], "w");

    while ((c = fgetc(fp1)) != EOF)
        fputc(c, fp2);

    fclose(fp1);
    fclose(fp2);

    return 0;
}
```

 기능: 파일 복사

---

## 4. 줄 단위 처리

### 4. line.c (줄 번호 출력)

```c
#include <stdio.h>
#define MAXLINE 80

int main(int argc, char *argv[])
{
    FILE *fp;
    int line = 0;
    char buffer[MAXLINE];

    if (argc != 2) {
        fprintf(stderr, "사용법:line 파일이름\n");
        exit(1);
    }

    if ((fp = fopen(argv[1],"r")) == NULL) {
        fprintf(stderr, "파일 열기 오류\n");
        exit(2);
    }

    while (fgets(buffer, MAXLINE, fp) != NULL) {
        line++;
        printf("%3d %s", line, buffer);
    }

    exit(0);
}
```

 기능: 파일에 줄 번호 붙이기

---

## 5. 텍스트 파일 저장

### 5. fprint.c (학생 정보 저장)

```c
#include <stdio.h>
#include "student.h"

int main(int argc, char* argv[])
{
    struct student rec;
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "사용법: %s 파일이름\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "w");

    printf("%-9s %-7s %-4s\n", "학번", "이름", "점수");

    while (scanf("%d %s %d", &rec.id, rec.name, &rec.score)==3)
        fprintf(fp, "%d %s %d ", rec.id, rec.name, rec.score);

    fclose(fp);
    return 0;
}
```

---

## 6. 텍스트 파일 읽기

### 6. fscan.c

```c
#include <stdio.h>
#include "student.h"

int main(int argc, char* argv[])
{
    struct student rec;
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "사용법: %s 파일이름\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");

    printf("%-9s %-7s %-4s\n", "학번", "이름", "점수");

    while (fscanf(fp,"%d %s %d", &rec.id, rec.name, &rec.score)==3)
        printf("%10d %6s %6d\n", rec.id, rec.name, rec.score);

    fclose(fp);
    return 0;
}
```

---

## 7. 이진 파일 저장

### 7. stcreate1.c

```c
#include <stdio.h>
#include "student.h"

int main(int argc, char* argv[])
{
    struct student rec;
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "사용법: %s 파일이름\n",argv[0]);
        exit(1);
    }

    fp = fopen(argv[1], "wb");

    printf("%-9s %-7s %-4s\n", "학번", "이름", "점수");

    while (scanf("%d %s %d", &rec.id, rec.name, &rec.score) == 3)
        fwrite(&rec, sizeof(rec), 1, fp);

    fclose(fp);
    exit(0);
}
```

---

### 8. student.h 구조체

```c
struct student {
    int id;
    char name[20];
    short score;
};
```

---

## 8. 이진 파일 읽기

### 9. stprint.c

```c
#include <stdio.h>
#include "student.h"

int main(int argc, char* argv[])
{
    struct student rec;
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "사용법: %s 파일이름\n", argv[0]);
        return 1;
    }

    if ((fp = fopen(argv[1], "rb")) == NULL ) {
        fprintf(stderr, "파일 열기 오류\n");
        return 2;
    }

    printf("-----------------------------------\n");
    printf("%10s %6s %6s\n", "학번", "이름", "점수");
    printf("-----------------------------------\n");

    while (fread(&rec, sizeof(rec), 1, fp) > 0)
        if (rec.id != 0)
            printf("%10d %6s %6d\n", rec.id, rec.name, rec.score);

    printf("-----------------------------------\n");

    fclose(fp);
    return 0;
}
```

---

### 10. 대소문자 변환 프로그램

```c
#include <stdio.h>
#include <ctype.h>

int main() {
    char ch;

    while (1) {
        printf("문자 입력 : ");
        scanf(" %c", &ch);

        if (ch == '0') break;

        if (isupper(ch))
            printf("%c의 소문자는 %c입니다.\n", ch, tolower(ch));
        else if (islower(ch))
            printf("%c의 대문자는 %c입니다.\n", ch, toupper(ch));
    }
}
```
