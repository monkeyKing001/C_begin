#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX_NUM_STUDENT 255

enum action {ADD, FIND, EXIT};

typedef struct {
	int ID; // 4 bytes
	char name[8]; // 8 bytes
	float score; // 4 bytes
} Student; // 16 bytes

int fileOpen(FILE** _fp, char* _fileName, char* _mode);
int selectAction(void);
int printStudentInfo(Student* _info);
int addStudentInfo(FILE* _fp, Student* _info);
long findStudent(FILE* _fp, Student* _info);

int fileOpen(FILE** _fp, char* _fileName, char* _mode){
	*_fp = fopen(_fileName, _mode);
	if(!*_fp){
		printf("failed to open file '%s'\n", _fileName);
		return -1;
	}
	return 0;
}

long findStudent(FILE *_fp, Student* _info){
	char name[255] = { 0 };
	printf("input Name you want to find : \n");
	scanf("%s", name); 
	getchar();
	
	int elementSize = sizeof(Student);
	fseek(_fp, 0, SEEK_SET);	//from head(SEEK_SET) index 0
	
	while(!feof(_fp)){
		fread(_info, elementSize, 1, _fp);
		if(strcmp(_info->name, name)==0){//find
			fseek(_fp, -elementSize, SEEK_CUR);
			return ftell(_fp);
		}
	}
	return -1;
}

int selectAction(void) {
	int sel = 0;
	printf("[%d]add [%d]find [%d]exit: \n", ADD, FIND, EXIT);
	scanf("%d", &sel);
	return sel;
}

int printStudentInfo(Student* _info) {
	printf("%d %s %.2f\n", _info->ID, _info->name, _info->score);
}

int addStudentInfo(FILE* _fp, Student* _info){
	printf("Enter ID Name Score (differentiate with space ' '): \n");
	scanf("%d %s %f", &_info->ID, &_info->name, &_info->score);
	getchar();
	
	fseek(_fp, 0, SEEK_END);
	fwrite(_info, sizeof(Student), 1, _fp);
	return 0;
}


int main(){
	FILE* fp = NULL;
	Student data = { 0 };
	fileOpen(&fp, "StudentDB", "ab+");
	
	while (1){
		switch (selectAction()){
			case ADD:
				addStudentInfo(fp, &data);
			break;
		case FIND:
			if (findStudent(fp, &data) < 0)
				printf("Cannot find the student\n");
			else
				printStudentInfo(&data);
			break;
		case EXIT:
		exit(0);
		}
	}
}

