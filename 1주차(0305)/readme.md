# Chapter 1. Unix / Linux Introduction

## 1. Why Linux

### Unix/Linux의 등장과 중요성

* Unix 운영체제는 **1970년대 AT&T Bell Labs에서 개발된 이후 지속적으로 발전**하였다.
* 현재 **PC, 서버, 스마트폰, 슈퍼컴퓨터 등 다양한 시스템에서 사용**된다.
* 소프트웨어 산업에서 **핵심적인 운영체제 기반 기술**로 사용된다. 

### Unix/Linux 기반 운영체제

대표적인 Unix/Linux 기반 운영체제는 다음과 같다.

* Android
* iOS
* Mac OS X
* Linux
* BSD Unix
* System V
* Solaris
* IBM AIX
* HP-UX
* Cray Unicos

---

# Unix Design Philosophy

Unix는 다음과 같은 설계 철학을 기반으로 만들어졌다.

### 1. 단순성 (Simplicity)

* 최소한의 기능만 제공하도록 설계하다
* 시스템 자원을 **일관된 방식으로 다루도록 설계하다**

### 2. 이식성 (Portability)

* C 언어로 작성하여 **다양한 플랫폼에서 실행 가능하도록 설계하다**
* 스마트폰, PC, 서버, 슈퍼컴퓨터 등 여러 환경에서 사용 가능하다

### 3. 개방성 (Openness)

* 소스코드 공개와 같은 **개방적인 개발 환경을 지향하다**

---

# Unix Characteristics

Unix 운영체제는 다음과 같은 특징을 가진다.

### 1. Multi-user / Multi-process

* 여러 사용자가 동시에 시스템을 사용할 수 있다
* 여러 프로그램이 동시에 실행될 수 있다
* 시스템을 관리하는 **슈퍼유저(superuser)** 가 존재한다

### 2. Shell 기반 대화형 운영체제

* **Shell을 통해 사용자 명령을 해석하고 실행하다**
* Shell Script를 사용하여 자동화 프로그램을 작성하다

### 3. 계층적 파일 시스템

* 디렉터리 구조가 **트리 형태의 계층 구조**로 구성되다

### 4. 뛰어난 네트워킹 기능

* Unix에서 네트워크 기술이 발전하였다
* FTP, Telnet, WWW, X Window 등의 기술이 사용된다

---

# Unix System Architecture

Unix 시스템은 다음과 같은 구조로 이루어진다.

```
User
 ↓
Shell
 ↓
System Call
 ↓
Kernel
 ↓
Hardware
```

### Operating System

* 컴퓨터 하드웨어 자원을 관리하다
* 프로그램이 실행될 수 있는 환경을 제공하다

### Kernel

* 운영체제의 핵심 구성 요소이다
* 하드웨어 자원을 직접 관리한다

### System Call

* 프로그램이 커널 기능을 사용할 수 있도록 제공되는 인터페이스이다

### Shell

* 사용자와 운영체제 사이의 인터페이스 역할을 수행한다
* 사용자가 입력한 명령을 해석하고 실행한다

---

# Kernel Responsibilities

Kernel은 시스템 자원을 관리하는 핵심 구성요소이다.

### 1. Process Management

* 여러 프로그램이 동시에 실행되도록 관리하다
* CPU 스케줄링을 수행하다

### 2. File Management

* 저장장치에 파일 시스템을 구성하다
* 파일 생성, 삭제, 접근 등을 관리하다

### 3. Memory Management

* 메인 메모리를 효율적으로 사용하도록 관리하다

### 4. Communication Management

* 네트워크를 통해 데이터 통신을 관리하다

### 5. Device Management

* 모니터, 키보드, 마우스 등의 장치를 관리하다

---

# Unix History and Versions

### Unix의 개발 역사

* AT&T Bell Labs에서 개발되었다
* Ken Thompson이 **Assembly 언어로 초기 Unix를 개발하였다**
* Dennis Ritchie가 **C 언어로 다시 작성하였다**

이로 인해 Unix는 **C 컴파일러가 있는 환경이면 이식이 가능**하게 되었다. 

---

# Major Unix Branches

Unix는 크게 다음 세 가지 흐름으로 발전하였다.

### 1. System V

* Bell Labs에서 개발된 Unix 계열
* 대표적인 성공 사례
* 상업용 Unix의 기반이 되었다

대표적인 System V 기반 OS

* IBM AIX
* Sun Solaris
* HP-UX

---

### 2. BSD Unix

* Berkeley University에서 개발된 Unix 계열
* 주요 개선 사항

  * 메모리 관리 기능 향상
  * TCP/IP 네트워크 기능 추가
  * Socket 인터페이스 제공

BSD Unix는 이후 여러 운영체제의 기반이 되었다.

---

### 3. Linux

* 1991년 **Linus Torvalds**가 개발하였다
* Unix와 유사한 구조의 운영체제이다

특징

* 오픈소스 운영체제이다
* 전 세계 개발자가 참여하여 발전하였다
* 다양한 하드웨어 플랫폼에서 실행 가능하다
* GNU 소프트웨어와 함께 배포된다

이를 **GNU/Linux 시스템**이라고 한다.

---

# Unix-based Operating Systems

### Solaris

* Sun Microsystems에서 개발하였다
* System V 기반 운영체제이다
* 워크스테이션 환경에서 많이 사용된다

### Mac OS

* Apple에서 개발한 운영체제이다
* 최초로 개인용 컴퓨터에 GUI를 도입하였다

Mac OS X 특징

* NeXTSTEP + BSD Unix 기반
* 그래픽 및 멀티미디어 작업에 많이 사용된다

### Mobile Operating Systems

#### Android

* Linux 기반 모바일 운영체제이다
* 스마트폰, 태블릿 등에 사용된다
* 오픈소스 기반이다

#### iOS

* Mac OS X 기반 모바일 운영체제이다
* Apple 기기에서 사용된다

---

# Key Concepts

* Unix 시스템의 핵심 특징은 **단순성, 이식성, 개방성**이다.
* 운영체제는 **하드웨어 자원을 관리하고 프로그램 실행 환경을 제공한다**.
* Shell은 **사용자 명령을 해석하고 실행하는 인터페이스 역할을 수행한다**.
* Kernel은 **프로세스, 파일, 메모리, 통신, 장치 등을 관리하는 핵심 구성 요소이다**. 
