Chap08
### find 명령어
- 파일 이름이나 속성을 이용하여 해당하는 파일을 찾는다.
```
$ find 디렉터리 [-옵션]
```
- 옵션의 검색 조건에 따라 지정된 디렉터리 아래에서 해당되는 파일들을 모두 찾아 출력한다.

### grep 명령어
```
$ grep 패턴 파일*
```
- 파일(들)을 대상으로 지정된 패턴의 문자열을 검색하고, 해당 문자열을 포함하는 줄들을 출력한다.

### 정규식
<img width="746" height="422" alt="image" src="https://github.com/user-attachments/assets/444d809e-01d5-4292-92a8-de09d1160aeb" />

### 정령: sort 명령어
```
$ sort [-옵션] 파일*

```
- 텍스트 파일(들)의 내용을 줄 단위로 정렬한다. 옵션에 따라 다양한 형태로
정렬한다.

### 파일 분할: split

### cat
- 텍스트 파일의 내용을 화면에 순차적으로 출력하거나 여러 파일을 하나로 병합

### past
- 여러 텍스트 파일의 각 줄을 병합하여 탭(Tab)으로 구분된 하나의 줄로 나란히 출력

Chap09
### cron
- 시스템 내에서 명령어(Command)를 예약된 시간에 주기적으로 수행하게 하는 스케줄링 시스템

### crontab 파일 예
- 30 18 * * * rm /home/chang/tmp/* 와 같이 분, 시, 일, 월, 요일 포맷에 맞추어 명령어를 등록

### 한번 실행: at
-명령어가 미래의 지정된 특정 시간에 단 한 번만 실행되도록 예약

## df
## du
## tar 아카이브
 - 파일 시스템의 디스크 사용 공간(df)과 디렉터리 사용량(du)을 점검하고, 백업을 위해 여러 파일을 하나로 묶는 아카이브(tar) 기능

### 파일 압축: gzip
- 대상 파일을 압축하여 .gz 확장자를 가진 파일로 변환
### 파일 압축2: compress
- 대상 파일을 압축하여 .Z 확장자를 가진 파일로 변환
### AWK
- 텍스트 파일의 각 줄을 필드(Field) 단위로 구분하여 데이터를 조작하는 스크립트 언어
### 액션(action)
- AWK 내에서 지정된 조건(Condition)을 만족할 때 수행되는 실행문
### 핵심 개념
- 유틸리티를 활용한 명령어 스케줄링, 디스크 관리, 텍스트 데이터의 효율적 제어

Chap 10
### Bash
- 다양한 운영 체제에서 기본 쉘(Shell)로 채택되어 사용자와 운영체제 간의 명령어를 처리한다.
### Bash 시작 과정
- /etc/profile 및 ~/.bashrc 등 시작 파일(Start-up file)을 차례로 읽고 실행한 뒤 로그인 프롬프트를 출력
### 별명
- alias 명령어
- 복잡한 명령어나 자주 쓰는 옵션 조합을 짧은 문자열로 새롭게 정의

### 히스토리
- 입력된 명령들을 기억하는 기능

### 재실행
- <img width="515" height="216" alt="image" src="https://github.com/user-attachments/assets/526ba306-b534-4eae-adb8-08edf0c64c83" />

Chap 11
### gedit: GNOME 환경의 기본 편집기로 프로그램 코드(Code)나 텍스트를 작성하기 좋은 GUI 문서 편집기

### 메이크 파일(Makefile): 다중 모듈 프로그램에서 실행 파일을 빌드(Build)하기 위해 타겟과 파일 간의 의존성(Dependencies)을 기술한 파일

### gdb: 정지점(Breakpoint) 설정과 단계별 소스 실행을 통해 버그를 잡는 GNU 디버거

### 핵심 개념: 편집기 활용, GCC 컴파일, 자동 빌드 도구 도입, 디버깅을 아우르는 전반적인 프로그래밍 환경

 Chap 12
 <img width="763" height="576" alt="image" src="https://github.com/user-attachments/assets/713190d1-9efc-415f-90ef-0121a9104cc0" />
### 링크(Link): 기존 파일에 접근하기 위해 부여하는 또 다른 독립적인 이름

### 하드링크와 하드링크 구현: 새로운 이름이 원본 파일을 대표하는 i-노드(i-node)를 직접 가리키도록 구조적으로 구현

### 심볼릭 링크(Symbolic Link): 원본 파일의 경로명(Path)을 내용으로 가지는 특수 파일로 간접 참조 역할

### 시스템 호출(System Call): 응용 프로그램이 파일 제어 등 운영체제 커널(Kernel)에 서비스를 요청하는 프로그래밍 인터페이스
 ### fopen() : 텍스트 파일 열기
<img width="696" height="315" alt="image" src="https://github.com/user-attachments/assets/bbc866d2-559c-42b8-a1a3-e3cac2d9d05a" />

Chap 13
### 프로세스 이미지
<img width="737" height="444" alt="image" src="https://github.com/user-attachments/assets/d57dd885-27fa-41a9-aa54-9284ecf49077" />

### size 명령어: 지정한 실행 파일이 메모리에서 차지할 영역별 크기(바이트)를 

### 프로세스 ID(PID): 운영 체제가 각각의 프로세스를 구별하기 위해 고유하게 부여하는 식별 번호

Chap14
### sudo: 일반 사용자 계정에서 관리자(root) 권한을 일시적으로 빌려 명령(Superuser do)을 수행하게 해줌

### 시스템 부팅(System Booting): fork와 exec 시스템 호출을 통해 진행되며 init 혹은 systemd가 지정된 런레벨(Runlevel)에 따라 환경을 초기화

### shutdown 명령어: 시스템을 안전하게 정지하거나 재부팅하도록 예약

### 데몬 프로세스(Daemon Process): 백그라운드에서 동작 대기 상태에 있다가 요청 시 특정 서비스(예: httpd, sshd)를 제공
