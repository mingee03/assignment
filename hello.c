/*
Programming Studio C003
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int findRoom(
    int persons[5]); // 5개의 호실 중 빈 베드가 있는 방을 찾아낸다. (리턴값 1~5)
void printReport(char mn[10][20], int mr[10], int mc, char wn[10][20],
                 int wr[10], int wc); // 배정 결과를 출력한다.

int main() {
  char mnames[10][20];        // 남학생명단(최대 10명)
  int mroom[10] = {0};              // 남학생명단별 호실 배정 목록
  char wnames[10][20];        // 여학생명단(최대 10명)
  int wroom[10] = {0};              // 여학생명단별 호실 배정 목록
  int person[2][5] = {0};     // 2개 층별 5개 호실의 배정 인원 수
  int mcount = 0, wcount = 0; // 인원 합계 (남, 여)
  int menu;

  srand(time(0));
  printf("===========================================\n");
  printf("생활관 호실 배정 프로그램\n");
  printf("===========================================\n");
  while (1) {
    printf("메뉴 : 1.남학생 등록 2.여학생 등록 0.종료 > ");
    scanf("%d", &menu);
    if (menu == 0)
      break;
    else if (menu == 1) {
      if (mcount >= 10) {
        printf("정원 초과입니다. 등록불가!\n");
      } else {
        int mroomno = findRoom(person[0]);//continue를 없애고 변수를 남녀로 나누어 각각 정원 초과 될시 함수에서 0을 리턴하게 해서 등록 불가하게 만들었다. 
        if(mroomno == 0){
          printf("정원 초과입니다. 등록불가!\n");
        }
        else{
          printf("학생 이름은? > ");
        scanf("%s", mnames[mcount]);
          mroom[mcount] = 100 + mroomno;
          printf("%s 학생 %d호실 배정되었습니다.\n", mnames[mcount],
                 mroom[mcount]);
          mcount++;
          
        }
        
      }
    } else if (menu == 2) {
      if (wcount >= 10) {
        printf("정원 초과입니다. 등록불가!\n");
      } else {
        int wroomno = findRoom(person[1]);
        if(wroomno == 0){
          printf("정원 초과입니다. 등록불가!\n");
        }
        else{
          printf("학생 이름은? > ");
        scanf("%s", wnames[wcount]);
          wroom[wcount] = 200 + wroomno;
          printf("%s 학생 %d호실 배정되었습니다.\n", wnames[wcount],
                 wroom[wcount]);
          wcount++;

        }

      }
    } 
  }

  printf("===========================================\n");
  printf("생활관 호실 배정 결과는 다음과 같습니다.\n");
  printf("===========================================\n");
  printReport(mnames, mroom, mcount, wnames, wroom, wcount);

  return 0;
}

int findRoom(int persons[5]) {
  // 이 곳에 생각 정리와 코드 구현 == 호실을 배정 받기 위해서는 자리가 1 or 2개
  // 빈 방을 찾아야 한다. 그러기 위해선 person 목록 중에 0이나 1인 호실을 찾아
  // 거기에 인원을 할당하고 그 호실에 1을 더해야 한다. for 이 필요할듯. rand
  // 또한 이 함수에 추가 해야한다. 
  int i=0;
  int num=0;
  int room=0;
    
  for (i = 0; i < 5; i++) {
    num = rand() % 5;
    if (persons[num] < 2) {
      persons[num]++;
      return num + 1;
    }
    }
  return 0;
}

void printReport(char mn[10][20], int mr[10], int mc, char wn[10][20],
                 int wr[10], int wc) {
  // 이 곳에 생각 정리와 코드 구현 == 이 부분은 배졍결과를 출력하는 것이니 각
  // 요소에서 맞는 수를 뽑아내어 방에 맞는 인원의 이름과 총 합을 구해내어야
  // 한다. 그를 위해서 이미 프로그램에 방번호와 인원에 맞게 숫자가 할당되어
  // 있으니 그걸 따라 printf를 사용하여 출력하면 된다. 남자의 경우는 mcount,
  // 여자의 경우에는 wcount를 사용하면 된다. 
  //계속해보니 문제는 한 두개가 아니었다. 남녀 학생명단까지는 위의 방법으로 커버가 되지만 호실별
  //배정명단 부분에서는 방에 두명이 있을 경우 반복문을 돌리면 같은호실 같은 멤버가 두번 출력된다
  //이를 해결하기위해 따로 호실을 저장한다음, 반복문을 돌려 이번에 출력할 호실이 같은 경우 넘어가게
  //만들어야 한다. 또한 츨력 순서도 정렬해야 하기에 함수 앞부분에 버블정리를 사용해야 한다. 
  int i, j;
  int mpaper[5] = {0};
  int wpaper[5] = {0};
  int match = 0;
  for (i = 0; i < mc - 1; i++) {
    for (j = i + 1; j < mc; j++) {
        if (mr[i] > mr[j]) {
            int tmroom = mr[i];
            mr[i] = mr[j];
            mr[j] = tmroom;
            char tmname[20];
            strcpy(tmname, mn[i]);
            strcpy(mn[i], mn[j]);
            strcpy(mn[j], tmname);
        }
    }
  }

  for (i = 0; i < wc - 1; i++) {
    for (j = i + 1; j < wc; j++) {
        if (wr[i] > wr[j]) {
            int twroom = wr[i];
            wr[i] = wr[j];
            wr[j] = twroom;
            char twname[20];
            strcpy(twname, wn[i]);
            strcpy(wn[i], wn[j]);
            strcpy(wn[j], twname);
        }
    }
  }


  printf("남학생 명단 ( %d명 )\n", mc);
  if (mc > 0) {
    for (i = 0; i < mc; i++) {
      printf(" %d. %s [%d호]\n", i + 1, mn[i], mr[i]);
    }
  }
  printf("\n여학생 명단 ( %d명 )\n", wc);
  if (wc > 0) {
    for (i = 0; i < wc; i++) {
      printf(" %d. %s [%d호]\n", i + 1, wn[i], wr[i]);
    }
  }
  printf("\n호실별 배정 명단\n");
  for(i=0; i<mc; i++){
    match = 0;
    for(j=0; j<mc; j++){
      if(mpaper[j] == mr[i]){
        match = 1;
        continue;
    } 
    }if(match == 0&&mr[i]>0){
        printf("%d호 : ", mr[i]);
        mpaper[i] = mr[i];
      for(j=0;j<mc; j++){
        if(mr[j] == mr[i]){
        printf("%s ", mn[j]);
      }
      }
      printf("\n");
    }
      
       
  }
  for(i=0; i<wc; i++){
    match = 0;
    for(j=0; j<wc; j++){
      if(wpaper[j] == wr[i]){
        match = 1;
        continue;
    } 
    }if(match == 0&&wr[i]>0){
        printf("%d호 : ", wr[i]);
        wpaper[i] = wr[i];
      for(j=0;j<wc; j++){
        if(wr[j] == wr[i]){
        printf("%s ", wn[j]);
      }
      }
      printf("\n");
    }
     

  }
      
      
}