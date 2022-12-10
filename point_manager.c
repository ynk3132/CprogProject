#define LEN 20
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct point{
    char name[LEN];
    char phone[12];
    int score;
    int stamp;
    char birth[6];
    struct point *next;
}point_t;

point_t* file_manage(FILE*, point_t*);
void Make_account(point_t**, point_t*(*func)(point_t*,char*));
void Save(point_t*, point_t*(*func)(point_t*,char*));
void Use(point_t*, point_t*(*func)(point_t*,char*));
void show_list(point_t* list_head,point_t*(*func)(point_t*,char*));
void delete(point_t**, point_t*(*func)(point_t*,char*));
point_t* search(point_t*,char*); 
void backup(FILE*, point_t*);
void close(point_t**);
void quit(FILE*, point_t*);
int choice();

void main(){
    int num=0;
	int q=0;
	int quit_num=0;
	point_t* list_head=NULL;
	FILE* fp=NULL;

    int mode;
	char name[LEN];
	char save;

    list_head = file_manage(fp, list_head);

	while(1){	
		q=choice();
		switch(q)
		{
			case 1:
				Make_account(&list_head,search);
				break;
			case 2:
				show_list(list_head,search);
				break;
			case 3:
				Save(list_head,search);
				break;
			case 4:
				Use(list_head,search);
				break;
			case 5:
				delete(&list_head,search);
				break;
			case 6:
				quit(fp,list_head);
				quit_num=1;
				break;
			default:
				printf("잘못된 숫자 입력\n");
				break;
		}
		if (quit_num == 1)
			break;
	}
}


point_t* file_manage(FILE* fp, point_t* list_head){
	point_t* new_node;

	//데이터 파일 열기
	fp = fopen ("data.dat", "r+");
	if (fp == NULL) {
		printf("파일 열기 에러\n");
		return NULL;
	}

	//데이터 파일 읽기
	while(1) {
		new_node = (point_t*) malloc (sizeof(point_t));
		fscanf(fp, "%s %s %s %d %d", new_node->phone, new_node->name, new_node->birth, &new_node->score, &new_node->stamp); 
		if(feof(fp)!=0)
			break;
		//노드 추가
		new_node->next = list_head;
		list_head = new_node;
	}

	fclose(fp);
	return list_head;
}

void Make_account(point_t** list_head,point_t*(*func)(point_t*,char*)){
    point_t* new_node;
	point_t* tmp_node;
	char phone[12];

    new_node = (point_t *)malloc(sizeof(point_t));

    new_node->stamp = 0;    //처음 stamp와 누적 금액은 0으로 초기화
    new_node->score = 0;
    printf("\n■ ■ ■ ■ ■ ■ 계 정  생 성 ■ ■ ■ ■ ■ ■\n");
    printf("전 화 번 호 : "); scanf("%s", new_node->phone);
    printf("성       함 : "); scanf("%s", new_node->name);
    printf("생       일 : "); scanf("%s", new_node->birth);

	strcpy(phone,new_node->phone);
	tmp_node=func(*list_head,phone);
    new_node->next = *list_head;

    *list_head = new_node;
    return;
}

void Save(point_t* list_head,point_t*(*func)(point_t*,char*)){
    char phones[12];
    int scores;
    point_t *tmp_node;
    printf("전 화 번 호 : "); scanf("%s", phones);
    printf("결 제 금 액 : "); scanf("%d", &scores);

	tmp_node = func(list_head,phones);

	if(tmp_node==NULL){
		printf("존재하지 않는 전화번호입니다.\n");
	}

	tmp_node->score += scores * 0.05; // 잔액에 결제 금액의 5% 적립
	tmp_node->stamp += 1;
	printf("도장 1개 적립!");
}

void Use(point_t* list_head,point_t*(*func)(point_t*,char*)){
    char phones[12];
    int scores;
    point_t *tmp_node;
    printf("전 화 번 호 : "); scanf("%s", phones);
    printf("사 용 금 액 : "); scanf("%d", &scores);

    tmp_node = func(list_head,phones);

	if(tmp_node==NULL){
		printf("존재하지 않는 전화번호입니다.\n");
	}

	if(tmp_node->score < scores){
		printf("사용 가능한 포인트를 초과하였습니다.\n");
	}
	else
		tmp_node->score -= scores; // 잔액에서 사용 금액 차감
}

void show_list(point_t* list_head,point_t*(*func)(point_t*,char*)){
	point_t* tmp_node;
	char phone[12];
	printf("찾고 싶은 계정 전화번호: ");
	scanf("%s", phone);
	tmp_node=func(list_head,phone);
	if(tmp_node) {
		printf("\n■ ■ ■ ■ ■ ■ 잔 액  조 회 ■ ■ ■ ■ ■ ■\n");
		printf("전 화 번 호 : %s\n", tmp_node->phone);
		printf("성       함 : %s님\n", tmp_node->name);
		printf("적 립 포 인 트 : %d원\n", tmp_node->score);
		printf("도       장 : %d개\n", tmp_node->stamp);
	}
	else
		printf("존재하지 않는 계정입니다.\n");
	return;
}

void backup(FILE* fp, point_t* list_head){
	point_t* tmp_node;
	
	fp = fopen ("data.dat", "w+");
	if (fp == NULL) {
		printf("파일 열기 에러\n");
		return;
	}
	while(list_head) {
		tmp_node = list_head;
		fprintf(fp, "%s %s %s %d %d\n", tmp_node->phone, tmp_node->name, tmp_node->birth, tmp_node->score, tmp_node->stamp); 
		list_head = list_head->next;	
	}

	fclose(fp);
	printf("\n파일 저장 완료\n");
}

point_t* search (point_t* list_head,char* phone) {
	point_t* tmp_node = list_head;
	while (tmp_node) {
		if (!strcmp(tmp_node->phone, phone)) {
			return tmp_node;
		}
		tmp_node = tmp_node->next;
	}
	return tmp_node;
}

void delete(point_t** list_head,point_t*(*func)(point_t*,char*)){	
	point_t* tmp_node;
	point_t* temp;
	point_t* pre;
	temp=*list_head;
	char phone[12];
	int del_choice;
	int num=0;
	printf("삭제하고 싶은 전화번호 : ");
	scanf("%s",phone);
	tmp_node=func(*list_head,phone);
	if(tmp_node==NULL)
	{
		printf("존재하지 않는 전화번호입니다.\n");
		return;
	}
	printf("정말 삭제하시겠습니까?[(1)yes/(2)no] : ");
	scanf("%d",&del_choice);
	if (del_choice==1)		
	{
		if(strcmp(temp->phone,phone)==0)
		{
			*list_head=temp->next;
			free(temp);
			printf("삭제되었습니다.\n");
		}
		else
		{
			while(temp!=NULL)
			{
				if(strcmp(temp->phone,phone)==0)	
				{
					pre->next=temp->next;
					free(temp);
					printf("삭제되었습니다.\n");
					break;
				}
				pre=temp;	
				temp=temp->next;
			}
		}
	}
}

void close(point_t** list_head){
	point_t* tmp_node;
	while(*list_head) {
		tmp_node = *list_head;
		*list_head = (*list_head)->next;
		free(tmp_node);
	}
	return;
}

void quit(FILE* fp, point_t* list_head){
	int quit_choice;
	printf("변경사항을 저장하시겠습니까?[(1)yes/(2)no] : ");
	scanf("%d",&quit_choice);
	if(quit_choice==1)
		backup(fp,list_head);
	close(&list_head);
	return;
}

int choice(){
	int choice;
	printf("\n■ ■ ■ ■ ■ ■ 기능을 선택해주세요 ■ ■ ■ ■ ■ ■\n");
	printf("1. 새로운 계정 등록\n");
	printf("2. 계정 검색\n");
	printf("3. 포인트 적립\n");
	printf("4. 포인트 사용\n");
	printf("5. 계정 삭제\n");
	printf("6. 종료\n");
    printf("\n");

	printf("기능의 번호를 선택해주세요 : ");
	scanf("%d",&choice);
	return choice;
}