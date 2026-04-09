chap5.pdf 내용
5.1
# 컴퓨터 시스템 구조
"바퀴를 두 번 발명하지 마라"

# 시스템 호출

# 시스템 호출 과정

# 시스템 호출 요약
표
메모리 걱정없이 프로그래밍 할 수 있고 빠른 프로그래밍언어 - 러스트?
시그널은 프로세스와 연관이 있다.

5.2
# 파일
연속된 바이트의 나열
리눅스는 하드웨어도 다 파일로 인식한다.

# 파일 열기 : open()
파일 디스크립터는 열린 파일을 나타내는 번호이다.
include 되는 것들 확인하기

# 파일 열기
oflag

# 파일 열기 예

# 파일 열기 : fopen.c

# 파일 생성 : creat()
include 되는 것들 확인하기

# 파일 닫기 : close()
fd가 나타내는 파일을 닫는다.

# 데이터 읽기 : read()
fd가 나타내는 파일에서
nbytes만큼의 데이터를 읽고
읽은 데이터는 buf에 저장한다.
ssize_t read ( int fd, void *buf, size_t nbytes ); 읽는 법

# 파일 크기 계산 : fsize.c

# 데이터 쓰기 : write()
buf에 있는 nbytes 만큼의 데이터를 fd가 나타내는 파일에 쓴다
ssize_t write (int fd, void *buf, size_t nbytes);

# 파일 복사 : copy.c

# 파일 디스크립터 복제
dup()/dup2() 호출은 기존의 파일 디스크립터를 복제한다.

# 파일 디스크립터 복제 : dup.c

5.3 임의 접근 파일

# 임의 접근 : Iseek()
임의의 위치로 파일 위치 포인터를 이동시킬 수 있다.
off_t lseek (int fd, off_t offset, int whence );
off_t 는 파일 내에서 “몇 바이트 떨어진 위치”를 표현하는 정수 타입


