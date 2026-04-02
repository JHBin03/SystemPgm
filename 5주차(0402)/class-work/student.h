//fprint.c를 위해 gpt가 구현해준 student.h
#ifndef STUDENT_H
#define STUDENT_H

struct student {
    int id;         // 학번
    char name[20];  // 이름 (문자열)
    int score;      // 점수
};

#endif