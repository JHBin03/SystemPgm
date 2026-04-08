# 4장 C 표준 파일 입출력 정리

## 1. 시스템 호출 vs C 라이브러리

* **시스템 호출 (System Call)**

  * 커널에 서비스 요청
  * OS와 직접 상호작용
* **C 라이브러리 함수**

  * 시스템 호출을 감싼 함수 (wrapper)
  * 개발자는 보통 이것만 사용

→ 구조

```
프로그램 → C 라이브러리 → 시스템 호출 → 커널 → 하드웨어
```



---

## 2. 파일의 개념

### 파일이 필요한 이유

* 프로그램 종료 → 메모리 데이터 사라짐
* → 영속 저장 필요 → 파일 사용

### 파일 종류

1. **텍스트 파일**

   * 사람이 읽을 수 있음
   * 줄 단위 처리

2. **이진 파일 (Binary)**

   * 그대로 바이트 저장
   * 구조체 그대로 저장 가능

---

## 3. 파일 입출력 기본 흐름

1. `fopen()` → 파일 열기
2. 입출력 함수 사용
3. `fclose()` → 파일 닫기

---

## 4. fopen() 핵심

```c
FILE *fp = fopen("파일명", "모드");
```

### 주요 모드

| 모드 | 의미         |
| -- | ---------- |
| r  | 읽기         |
| w  | 쓰기 (기존 삭제) |
| a  | 추가         |
| r+ | 읽기/쓰기      |
| w+ | 새로 생성      |
| a+ | 추가 + 읽기    |

---

## 5. FILE 구조체 핵심

* 파일 상태 + 버퍼 정보 포함
* 내부적으로:

  * 버퍼 포인터
  * 파일 디스크립터
  * 현재 위치 등

→ 즉, **파일 + 버퍼 관리 객체**

---

## 6. 표준 입출력

| 스트림    | 의미    |
| ------ | ----- |
| stdin  | 키보드   |
| stdout | 화면    |
| stderr | 오류 출력 |

---

## 7. 문자 단위 입출력

```c
int c = fgetc(fp);
fputc(c, fp);
```

* EOF 만나면 종료

---

## 8. 줄 단위 입출력

```c
fgets(buffer, size, fp);
fputs(buffer, fp);
```

---

## 9. 포맷 입출력

```c
fprintf(fp, "%d", x);
fscanf(fp, "%d", &x);
```

---

## 10. 이진 파일 입출력

```c
fwrite(&data, sizeof(data), 1, fp);
fread(&data, sizeof(data), 1, fp);
```

* 구조체 그대로 저장 가능
* 속도 빠름

---

## 11. 파일 위치 (Random Access)

```c
fseek(fp, offset, 기준);
ftell(fp);
rewind(fp);
```

### 기준

* SEEK_SET : 시작
* SEEK_CUR : 현재
* SEEK_END : 끝

---

## 1. 대소문자 변환 프로그램

### 요구사항

* 대문자 → 소문자
* 소문자 → 대문자
* `0` 입력 시 종료

### 코드

```c
#include <stdio.h>
#include <ctype.h>

int main() {
    char ch;

    while (1) {
        printf("문자 입력 : ");
        scanf(" %c", &ch);

        if (ch == '0') break;

        if (isupper(ch)) {
            printf("%c의 소문자는 %c입니다.\n", ch, tolower(ch));
        } else if (islower(ch)) {
            printf("%c의 대문자는 %c입니다.\n", ch, toupper(ch));
        } else {
            printf("영문자가 아닙니다.\n");
        }
    }

    return 0;
}
```

---

## 2. 입출력 버퍼 (Buffer)

### 핵심 개념

* 입출력은 **즉시 처리되지 않음**
* → **버퍼에 모아서 한 번에 처리**

### 이유

* 성능 향상 (I/O는 느림)

### 문제 발생 상황

* 버퍼 때문에 출력이 늦게 보임
* 입력/출력 순서 꼬임

### 해결 방법

```c
fflush(stdout);
```

→ 버퍼 강제 비우기



---

## 3. 과제 맥락 (student / stcreate2 등)

PDF 흐름상 중요한 포인트:

* `student.h`
* `stcreate.c`
* `stprint.c`

### 흐름

1. 입력 → 구조체 저장
2. 파일에 기록 (`fwrite`)
3. 파일에서 읽기 (`fread`)
4. 출력

---

## 핵심 요약 (시험 포인트)

* 파일 입출력 3단계: `fopen → 처리 → fclose`
* 텍스트 vs 이진 차이
* FILE 구조체 = 버퍼 + 상태
* `fgetc / fgets / fprintf` 구분
* `fread / fwrite` → 구조체 저장
* `fseek` → 임의 접근
* 버퍼 → 성능 ↑ but 디버깅 주의

---

## Fact vs Analysis

### Fact

* C 파일 입출력은 `FILE*` 기반으로 동작 
* 버퍼는 내부적으로 자동 관리됨 
* fread/fwrite는 블록 단위 입출력 제공 

### Analysis

* 초보자가 겪는 출력 안 나오는 문제 대부분 **버퍼 때문**
* 텍스트 vs 이진 선택은:

  * 가독성 vs 성능 trade-off
