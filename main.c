#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DATA 100    //최대100명
#define FILE_PATH "/home/iot/CLionProjects/project_adbook.c/student_data.txt"
#define AUTO_FILE_PATH "/home/iot/CLionProjects/project_adbook.c/autosave.txt"
//성적데이터 입력기능 구현, 데이터리스트 간략:구체로 나눠서 출력, 에딧데이터에서 신상정보:성적정보구분해서 수정, 입력받은 성적데이터로 데이터리스트에서 평균학점출력해주기,
//전체 데이터 목록, 이름으로 검색,  데이터입력값이 숫자인지아닌지 확인,
//수정필요:

//학생 구조체
typedef struct {
    int id;          //학번으로 사용합니다.
    int grade;      //학년
    char name[50];  //이름
    char cellP[20];  //전화번호
    char major[50]; //학과

    int isUsed;     // 1이면 현재값 사용 중 0이면 비어있음으로 표시
} Student;

Student database[MAX_DATA];

void listData(int lang);
void sortDataByIDAsc();
void sortDataByIDDesc();
void insertData(int id, char* name, int grade, char* cellP, char* major, int lang);
void deleteData(int id, int lang);
void updateDataChar(int id, char ans, char* newData, int lang);
void updateDataInt(int id, char ans, int newData, int lang);
void updateData(int id, int lang);
void searchData(int id, int lang);
void saveData(int lang);
void loadData(int lang);
void programSetting(char ans, int* save, int* lang);
void clearConsole();

int main() {
    int id, grade, save, lang;
    char ans, choice;
    char name[50], cellP[20], major[50], path[100];

    //설정 정보 불러오기
    printf("1");
    FILE *fp = fopen("setting.txt", "r");
    printf("1");
    fscanf(fp, "%d, %d", &lang, &save);
    printf("2");
    fclose(fp);
    printf("3");

    while (1) {
        printf("4");
        if(lang == 2){
            printf("\n---- 메뉴 ----\n");
            printf("1. 데이터 목록\n");
            printf("2. 데이터 삽입\n");
            printf("3. 데이터 수정\n");
            printf("4. 데이터 삭제\n");
            printf("5. 데이터 검색\n");
            printf("7. 데이터 저장\n");
            printf("8. 데이터 불러오기\n");
            printf("9. 프로그램 설정\n");
            printf("C. 콘솔 클리어(WIP)\n");
            printf("Q. 종료\n");
        } else{
            printf("\n---- Menu ----\n");
            printf("1. Data List\n");
            printf("2. Data Insert\n");
            printf("3. Data Edit\n");
            printf("4. Data Delete\n");
            printf("5. Data Search\n");
            printf("7. Data Save\n");
            printf("8. Data Load\n");
            printf("9. Program Setting\n");
            printf("C. Clear Console(WIP)\n");
            printf("Q. Exit\n");
        }
        printf("\n-> ");
        scanf("%c", &choice);
        getchar(); // 버퍼에 남은 개행 문자 제거 즉, 엔터제거 효과가 있음 편법

        switch (choice) {
            case '1':
                listData(lang);
                break;
            case '2':
                if(lang == 2){
                    printf("\n추가할 대상의 학번을 입력해주세요.\n");
                    printf("\n-> ");
                } else{
                    printf("\nEnter the ID to insert.\n");
                    printf("\n-> ");
                }
                scanf("%d", &id);
                getchar(); // 버퍼에 남은 개행 문자 제거
                if(lang == 2){
                    printf("\n이름 : ");
                } else{
                    printf("Name : ");
                }
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // 개행 문자 제거
                if(lang == 2){
                    printf("학년 : ");
                } else{
                    printf("Grade : ");
                }
                scanf("%d", &grade);
                getchar(); // 버퍼에 남은 개행 문자 제거
                if(lang == 2){
                    printf("전화번호 : ");
                } else{
                    printf("Cellphone Number : ");
                }
                fgets(cellP, sizeof(cellP), stdin);
                cellP[strcspn(cellP, "\n")] = 0; // 개행 문자 제거
                if(lang == 2){
                    printf("학과 : ");
                } else{
                    printf("Major : ");
                }
                fgets(major, sizeof(major), stdin);
                major[strcspn(major, "\n")] = 0; // 개행 문자 제거
                insertData(id, name, grade, cellP, major, lang);
                break;
            case '3':
                if(lang == 2){
                    printf("\n수정할 대상의 학번을 입력해주세요.\n");
                    printf("\n-> ");
                } else{
                    printf("\nEnter the ID to edit.\n");
                    printf("\n-> ");
                }
                scanf("%d", &id);
                getchar(); // 버퍼에 남은 개행 문자 제거
                updateData(id, lang);
                break;
            case '4':
                if(lang == 2){
                    printf("\n삭제할 대상의 학번을 입력해주세요.\n");
                    printf("\n-> ");
                } else{
                    printf("\nEnter the ID to delete.\n");
                    printf("\n-> ");
                }
                scanf("%d", &id);
                getchar(); // 버퍼에 남은 개행 문자 제거
                deleteData(id, lang);
                break;
            case '5':
                if(lang == 2){
                    printf("\n검색할 대상의 학번을 입력해주세요.\n");
                    printf("\n-> ");
                } else{
                    printf("\nEnter the ID to search.\n");
                    printf("\n-> ");
                }
                scanf("%d", &id);
                getchar(); // 버퍼에 남은 개행 문자 제거
                searchData(id, lang);
                break;
            case '7':
                if(lang == 2){
                    printf("\n데이터를 저장하시겠습니까?\n");
                } else{
                    printf("\nDo you want to save the data?\n");
                }
                printf("\nY/N -> ");
                scanf("%c", &ans);
                getchar(); // 버퍼에 남은 개행 문자 제거
                if(ans == 'Y' || ans == 'y'){
                    saveData(lang);
                }
                break;
            case '8':
                if(lang == 2){
                    printf("\n데이터를 불러오시겠습니까?\n");
                    printf("데이터를 불러오면 저장되지 않은 데이터는 사라집니다.\n");
                    printf("하시겠습니까?\n");
                } else{
                    printf("\nDo you want to load the data?\n");
                    printf("Loading data will overwrite unsaved changes\n");
                    printf("Are you sure?\n");
                }
                printf("\nY/N -> ");
                scanf("%c", &ans);
                getchar(); // 버퍼에 남은 개행 문자 제거
                if(ans == 'Y' || ans == 'y'){
                    loadData(lang);
                }
                break;
            case '9':
                if(lang == 2) {
                    printf("\n---- 프로그램 설정 ----\n");
                    printf("1. 데이터 정렬 방식 변경\n");
                    printf("2. 언어(Language)\n");
                    printf("3. 자동저장\n");
                    printf("Q. 메뉴로 돌아가기\n");
                }
                else{
                    printf("\n---- Program Setting ----\n");
                    printf("1. Set data sorting method\n");
                    printf("2. Language\n");
                    printf("3. Auto Save\n");
                    printf("Q. Back to main menu\n");
                }

                printf("\n-> ");
                scanf("%c", &ans);
                getchar(); // 버퍼에 남은 개행 문자 제거
                programSetting(ans, &save, &lang);
                break;

            case 'c':
                if(lang == 2){
                    printf("\n콘솔을 지우시겠습니까?\n");
                }
                else{
                    printf("\nDo you want to clear the console?\n");
                }

                printf("\nY/N -> ");
                scanf("%c", &ans);
                getchar(); // 버퍼에 남은 개행 문자 제거
                if(ans == 'Y' || ans == 'y'){
                    clearConsole();
                }
                break;
            case 'q':
                if(lang == 2){
                    printf("\n프로그램을 종료합니다.\n저장되지 않은 데이터는 사라집니다.\n하시겠습니까?\n");
                } else{
                    printf("\nExiting the program.\nUnsaved data will be lost.\nAre you sure?\n");
                }
                printf("\nY/N -> ");
                scanf("%c", &ans);
                if(ans == 'Y' || ans == 'y'){
                    if(lang == 2){
                        printf("\n안녕히 가세요!\n");
                    } else{
                        printf("\nGood Bye!\n");
                    }
// 설정값 저장
                    // 설정 정보 저장
                    FILE *fp = fopen("setting.txt", "w");
                    fprintf(fp, "%d, %d\n", lang, save); // lang: 언어 설정 (0: 영어, 1: 한국어)
                    fclose(fp);
                    if(save == 1){
                        strcpy(path, AUTO_FILE_PATH);
                        FILE *fp = fopen(path, "w"); // write mode
                        for (int i = 0; i < MAX_DATA; i++) {
                            if (database[i].isUsed) { // using data save
                                fprintf(fp, "%d,%s,%d,%s,%s\n", database[i].id, database[i].name, database[i].grade, database[i].cellP, database[i].major);
                            }
                        }
                        fclose(fp); //close file.
                    }
                    return 0;
                }
                else{
                    if(lang == 2){
                        printf("\n나가기 취소됨.\n");
                    } else{
                        printf("\nExit cancelled.\n");
                    }
                    break;
                }
            default:
                if(lang == 2){
                    printf("\n잘못된 입력입니다. 다시 시도하십시오.\n");
                } else{
                    printf("\nInvalid input. Please try again.\n");
                }

        }
    }

    return 0;
}

void listData(int lang) {
    char ans;
    if(lang == 2){
        printf("\n1. 간단 목록\n2. 상세 목록\nQ. 취소\n");
    } else{
        printf("\n1. Basic List\n2. Detailed List\nQ. Cancel\n");
    }
    printf("\n-> ");
    scanf("%c", &ans);
    getchar(); // 버퍼에 남은 개행 문자 제거
    while (1) {
        switch (ans) {
            case '1':
                if(lang == 2){
                    printf("\n---- 데이터 목록 (간단) ----\n");
                } else{
                    printf("\n---- Data List (Basic) ----\n");
                }
                for (int i = 0; i < MAX_DATA; i++) {
                    if (database[i].isUsed && database[i].id != 0) {
                        if(lang == 2){
                            printf("- 학번 : %d  |  이름 : %s  | 학년 : %d\n", database[i].id, database[i].name,
                                   database[i].grade);
                            printf("------------------------------------------------\n");
                        } else{
                            printf("- ID : %d  |  NAME : %s  | GRADE : %d\n", database[i].id, database[i].name,
                                   database[i].grade);
                            printf("------------------------------------------------\n");
                        }
                    }
                }
                if(lang == 2){
                    printf("\n엔터를 눌러 진행하세요.");
                } else{
                    printf("\nPress ENTER to continue.");
                }
                getchar();
                return;
            case '2':
                if(lang == 2){
                    printf("\n---- 데이터 목록 (상세) ----\n");
                } else{
                    printf("\n---- Data List (Detailed) ----\n");
                }
                for (int i = 0; i < MAX_DATA; i++) {
                    if (database[i].isUsed && database[i].id != 0) {
                        if(lang == 2){
                            printf("- 학번 : %d  |  이름 : %s  | 학년 : %d\n", database[i].id, database[i].name,
                                   database[i].grade);
                            printf("- 전화번호 : %s  |  학과 : %s\n", database[i].cellP, database[i].major);
                            printf("------------------------------------------------\n");
                        } else{
                            printf("- ID : %d  |  NAME : %s  | GRADE : %d\n", database[i].id, database[i].name,
                                   database[i].grade);
                            printf("- CELL : %s  |  MAJOR : %s\n", database[i].cellP, database[i].major);
                            printf("------------------------------------------------\n");
                        }
                    }
                }
                if(lang == 2){
                    printf("\n엔터를 눌러 진행하세요.");
                } else{
                    printf("\nPress ENTER to Continue.");
                }

                getchar();
                return;
            case 'q':
                return;
            default:
                if(lang == 2){
                    printf("\n잘못된 입력입니다. 다시 시도하십시오.\n");
                } else{
                    printf("\nInvalid input. Please try again.\n");
                }
                return;
        }

    }
}

void sortDataByIDAsc() {
    for (int i = 0; i < MAX_DATA - 1; i++) {
        for (int j = 0; j < MAX_DATA - i - 1; j++) {
            if (database[j].isUsed && database[j + 1].isUsed && database[j].id > database[j + 1].id) {
                Student tmp = database[j];
                database[j] = database[j + 1];
                database[j + 1] = tmp;
            }
        }
    }
}

void sortDataByIDDesc() {
    for (int i = 0; i < MAX_DATA - 1; i++) {
        for (int j = 0; j < MAX_DATA - i - 1; j++) {
            if (database[j].isUsed && database[j + 1].isUsed && database[j].id < database[j + 1].id) {
                Student tmp = database[j];
                database[j] = database[j + 1];
                database[j + 1] = tmp;
            }
        }
    }
}

void insertData(int id, char* name, int grade, char* cellP, char* major, int lang) {
    for (int i = 0; i < MAX_DATA; i++) {
        if (!database[i].isUsed) {
            database[i].id = id;
            strcpy(database[i].name, name);
            database[i].grade = grade;
            strcpy(database[i].cellP, cellP);
            strcpy(database[i].major, major);
            database[i].isUsed = 1;
            if(lang == 2){
                printf("데이터 삽입됨 : %d, %s, %d, %s, %s\n", id, name, grade, cellP, major);
            } else{
                printf("Data Inserted : %d, %s, %d, %s, %s\n", id, name, grade, cellP, major);
            }

            return;
        }
    }
    if(lang == 2){
        printf("\"데이터베이스가 가득 찼습니다.\n");
    } else{
        printf("\"The database is full.\n");
    }

}

void deleteData(int id, int lang) {
    for (int i = 0; i < MAX_DATA; i++) {
        if (database[i].isUsed && database[i].id == id) {
            database[i].isUsed = 0;
            if(lang == 2){
                printf("데이터 삭제됨 : %s (%d)\n", database[i].name, id);
            } else{
                printf("Data Deleted : %s (%d)\n", database[i].name, id);
            }

            return;
        }
    }
    if(lang == 2){
        printf("데이터를 찾을 수 없습니다.\n");
    } else{
        printf("Data not found.\n");
    }
}

void updateDataChar(int id, char ans, char* newData, int lang) {
    for (int i = 0; i < MAX_DATA; i++) {
        if (database[i].isUsed && database[i].id == id) {
            switch (ans) {
                case '1':
                    strcpy(database[i].name, newData);
                    if(lang == 2){
                        printf("데이터 수정됨 : %d -> %s\n", id, newData);
                    } else{
                        printf("Data Edited : %d -> %s\n", id, newData);
                    }
                    break;
                case '3':
                    strcpy(database[i].cellP, newData);
                    if(lang == 2){
                        printf("데이터 수정됨 : %d -> %s\n", id, newData);
                    } else{
                        printf("Data Edited : %d -> %s\n", id, newData);
                    }
                    break;
                case '4':
                    strcpy(database[i].major, newData);
                    if(lang == 2){
                        printf("데이터 수정됨 : %d -> %s\n", id, newData);
                    } else{
                        printf("Data Edited : %d -> %s\n", id, newData);
                    }
                    break;
            }
            return;
        }
    }
    if(lang == 2){
        printf("데이터를 찾을 수 없습니다.\n");
    } else{
        printf("Data not found.\n");
    }
}

void updateDataInt(int id, char ans, int newData, int lang) {
    for (int i = 0; i < MAX_DATA; i++) {
        if (database[i].isUsed && database[i].id == id) {
            switch (ans) {
                case '2':
                    database[i].grade = newData;
                    if(lang == 2){
                        printf("데이터 수정됨 : %d -> %d\n", id, newData);
                    } else{
                        printf("Data Edited : %d -> %d\n", id, newData);
                    }

                    break;
            }
            return;
        }
    }
    if(lang == 2){
        printf("데이터를 찾을 수 없습니다.\n");
    } else{
        printf("Data not found.\n");
    }
}

void updateData(int id, int lang) {
    int grade, nomatch;
    char name[50], cellP[20], major[50];
    char ans;
    while (1){//편리하게 반복수정 할 수 있게 루프
        for (int i = 0; i < MAX_DATA; i++) {
            if (database[i].isUsed && database[i].id == id) {
                if(lang == 2){
                    printf("\n---- %s (%d)의 데이터 수정 ----\n", database[i].name, database[i].id);
                    printf("1. 개인정보수정\n2. 학점정보수정(WIP)\nQ. 취소\n");
                } else{
                    printf("\n---- Edit Data of %s (%d) ----\n", database[i].name, database[i].id);
                    printf("1. Edit Personal Data\n2. Edit Grade Data(WIP)\nQ. Cancel\n");
                }
                printf("\n-> ");
                scanf("%c", &ans);
                getchar(); // 버퍼에 남은 개행 문자 제거
                if(ans == '1'){//개인정보수정 진입. while로 여러가지 데이터를 이어서 편집.
                    if(lang == 2){
                        printf("\n---- 개인정보수정 ----\n");
                        printf("1. 이름 수정\n2. 학년 수정\n3. 전화번호 수정\n4. 학과 수정\nQ. 취소\n");
                    } else{
                        printf("\n---- Edit Personal Data ----\n");
                        printf("1. Edit Name\n2. Edit Grade\n3. Edit CellPhone Number\n4. Edit Major\nQ. Cancel\n");
                    }
                    printf("\n-> ");
                    scanf("%c", &ans);
                    getchar(); // 버퍼에 남은 개행 문자 제거
                    switch (ans) {
                        case '1':
                            if(lang == 2){
                                printf("\n현재 : %s", database[i].name);
                                printf("\n새로운 이름을 입력해 주세요. : ");
                            } else{
                                printf("\nCurrent : %s", database[i].name);
                                printf("\nPlease enter a new Name. : ");
                            }
                            fgets(name, sizeof(name), stdin);
                            name[strcspn(name, "\n")] = 0; // 개행 문자 제거
                            updateDataChar(id, ans, name, lang);
                            break;
                        case '2':
                            if(lang == 2){
                                printf("\n현재 : %d", database[i].grade);
                                printf("\n새로운 학년을 입력해 주세요. : ");
                            } else{
                                printf("\nCurrent : %d", database[i].grade);
                                printf("\nPlease enter a new Grade. : ");
                            }
                            scanf("%d", &grade);
                            getchar(); // 버퍼에 남은 개행 문자 제거
                            updateDataInt(id, ans, grade, lang);
                            break;
                        case '3':
                            if(lang == 2){
                                printf("\n현재 : %s", database[i].cellP);
                                printf("\n새로운 전화번호를 입력해 주세요. : ");
                            } else{
                                printf("\nCurrent : %s", database[i].cellP);
                                printf("\nPlease enter a new CellPhone Number. : ");
                            }
                            fgets(cellP, sizeof(cellP), stdin);
                            cellP[strcspn(cellP, "\n")] = 0; // 개행 문자 제거
                            updateDataChar(id, ans, cellP, lang);
                            break;
                        case '4':
                            if(lang == 2){
                                printf("\n현재 : %s", database[i].major);
                                printf("\n새로운 학과를 입력해 주세요. : ");
                            } else{
                                printf("\nCurrent : %s", database[i].major);
                                printf("\nPlease enter a new Major. : ");
                            }
                            fgets(major, sizeof(major), stdin);
                            major[strcspn(major, "\n")] = 0; // 개행 문자 제거
                            updateDataChar(id, ans, major, lang);
                            break;
                        case 'q':
                            continue;
                        default:
                            if(lang == 2){
                                printf("\n잘못된 입력입니다. 다시 시도하십시오.\n");
                            } else{
                                printf("\nInvalid input. Please try again.\n");
                            }
                    }
                }
                else if(ans == '2'){//성적 데이터 수정

                }
                else if(ans == 'q'){
                    return;
                }
                return;
            }
        }

    }

}

void searchData(int id, int lang) {
    for (int i = 0; i < MAX_DATA; i++) {
        if (database[i].isUsed && database[i].id == id) {
            if(lang == 2){
                printf("데이터 찾음 : %d, %s\n", id, database[i].name);
            } else{
                printf("Data Found : %d, %s\n", id, database[i].name);
            }
            return;
        }
    }
    if(lang == 2){
        printf("데이터를 찾을 수 없습니다.\n");
    } else{
        printf("Data not found.\n");
    }
}

void saveData(int lang) {
    char ans;
    char path[150];
    if(lang == 2){
        printf("\n파일 저장 경로\n");
        printf("1. 기본 경로 사용 (/home/iot/CLionProjects/project_adbook.c/student_data.txt)\n");
        printf("2. 경로 수정\n");
        printf("Q. 취소\n");
    } else{
        printf("\nFile Save Path\n");
        printf("1. Use Default Path (/home/iot/CLionProjects/project_adbook.c/student_data.txt)\n");
        printf("2. Modify Path\n");
        printf("Q. Cancel\n");
    }
    printf("\n-> ");
    scanf("%c", &ans);
    getchar(); // 버퍼에 남은 개행 문자 제거8
    switch (ans) {
        case '1':
            strcpy(path, FILE_PATH);
            break;
        case '2':
            if(lang == 2){
                printf("새로운 경로를 입력해 주세요.\n");
            } else{
                printf("Please enter the new path.\n");
            }
            printf("\n-> ");
            fgets(path, sizeof(path), stdin);
            path[strcspn(path, "\n")] = 0; // 개행 문자 제거
            break;
        case 'q':
            return;
        default:
            if(lang == 2){
                printf("\n잘못된 입력입니다. 다시 시도하십시오.\n");
            } else{
                printf("\nInvalid input. Please try again.\n");
            }
            return;

    }
    FILE *fp = fopen(path, "w"); // write mode
    if (fp == NULL) {
        if(lang == 2){
            printf("파일을 열 수 없습니다.\n");
        } else{
            printf("Can not open this File.\n");
        }
        return;
    }

    for (int i = 0; i < MAX_DATA; i++) {
        if (database[i].isUsed) { // using data save
            fprintf(fp, "%d,%s,%d,%s,%s\n", database[i].id, database[i].name, database[i].grade, database[i].cellP, database[i].major);
        }
    }

    fclose(fp); //close file.
    if(lang == 2){
        printf("데이터 저장됨\n");
        printf("\n엔터를 눌러 진행하세요.");
    } else{
        printf("Data Saved.\n");
        printf("\nPress ENTER to continue.");
    }

    getchar();
    return;
}

void loadData(int lang) {
    char ans;
    char path[150];
    int id, grade;
    char name[50], cellP[20], major[50];
    if(lang == 2){
        printf("\n파일 불러오기 경로\n");
        printf("1. 기본 경로 사용 (/home/iot/CLionProjects/project_adbook.c/student_data.txt)\n");
        printf("2. 경로 수정\n");
        printf("3. 자동저장\n");
        printf("Q. 취소\n");
    } else{
        printf("\nFile Load Path\n");
        printf("1. Use Default Path (/home/iot/CLionProjects/project_adbook.c/student_data.txt)\n");
        printf("2. Modify Path\n");
        printf("3. Auto Save\n");
        printf("Q. Cancel\n");
    }
    printf("\n-> ");
    scanf("%c", &ans);
    getchar(); // 버퍼에 남은 개행 문자 제거
    switch (ans) {
        case '1':
            strcpy(path, FILE_PATH);
            break;
        case '2':
            if(lang == 2){
                printf("새로운 경로를 입력해 주세요.\n");
            } else{
                printf("Please enter the new path.\n");
            }
            printf("\n-> ");
            fgets(path, sizeof(path), stdin);
            path[strcspn(path, "\n")] = 0; // 개행 문자 제거
            break;
        case '3':
            strcpy(path, AUTO_FILE_PATH);
            break;
        case 'q':
            return;
        default:
            if(lang == 2){
                printf("\n잘못된 입력입니다. 다시 시도하십시오.\n");
            } else{
                printf("\nInvalid input. Please try again.\n");
            }
            return;
    }
    FILE *fp = fopen(path, "r"); //read mode open
    if (fp == NULL) {
        if(lang == 2){
            printf("파일을 열 수 없습니다.\n");
        } else{
            printf("Can not open this File.\n");
        }
        return;
    }

    memset(database, 0, sizeof(database)); //data reset

    while (fscanf(fp, "%d,%49[^,],%d,%19[^,],%49[^\n]\n", &id, name, &grade, cellP, major) == 5) {
        // 파일에서 읽은 데이터를 데이터베이스에 저장합니다.
        insertData(id, name, grade, cellP, major, lang);
    }

    fclose(fp); //close file
    if(lang == 2){
        printf("데이터 불러옴\n");
        printf("\n엔터를 눌러 진행하세요.");
    } else{
        printf("Data loaded.\n");
        printf("\nPress ENTER to continue.");
    }
    getchar();
    return;
}

void programSetting(char ans, int* save, int* lang) {
    switch (ans) {
        case '1': {
            if(*lang == 2){
                printf("\n정렬 방식 선택:\n");
                printf("1. 오름차순 정렬\n");
                printf("2. 내림차순 정렬\n");
                printf("3. 취소\n");
            } else{
                printf("\nChoose sorting method:\n");
                printf("1. Ascending order\n");
                printf("2. Descending order\n");
                printf("3. Cancel\n");
            }
            printf("\n-> ");
            scanf("%c", &ans);
            getchar(); // 버퍼에 남은 개행 문자 제거
            switch (ans) {
                case '1':
                    sortDataByIDAsc(); // 오름차순으로 데이터 정렬
                    if(*lang == 2){
                        printf("오름차순으로 정렬되었습니다.\n");
                    } else{
                        printf("Sorted by ascending order.\n");
                    }
                    break;
                case '2':
                    sortDataByIDDesc(); // 내림차순으로 데이터 정렬
                    if(*lang == 2){
                        printf("내림차순으로 정렬되었습니다.\n");
                    } else{
                        printf("Sorted in descending order.\n");
                    }
                    break;
                case 'q':
                    break;
                default:
                    if(*lang == 2){
                        printf("\n잘못된 입력입니다. 다시 시도하십시오.\n");
                    } else{
                        printf("\nInvalid input. Please try again.\n");
                    }
            }
            break;
        }
        case '2':
            if(*lang == 2){
                printf("\n언어 선택\n");
                printf("1. English\n");
                printf("2. 한국어\n");
            } else{
                printf("\nChoose language\n");
                printf("1. English\n");
                printf("2. 한국어\n");
            }
            printf("\n-> ");
            scanf("%c", &ans);
            getchar(); // 버퍼에 남은 개행 문자 제거
            switch (ans) {
                case '1':
                    *lang = 1;
                    break;
                case '2':
                    *lang = 2;
                    break;
                default:
                    if(*lang == 2){
                        printf("\n잘못된 입력입니다. 다시 시도하십시오.\n");
                    } else{
                        printf("\nInvalid input. Please try again.\n");
                    }
                    break;
            }
            break;
        case '3':
            if(*lang == 2){
                printf("\n자동저장\n");
                if(*save == 0){
                    printf("현재 : 꺼짐\n");
                    printf("자동 저장 기능을 켜시겠습니까?\n");
                    printf("\nY/N -> ");
                    scanf("%c", &ans);
                    getchar(); // 버퍼에 남은 개행 문자 제거
                    if(ans == 'Y' || ans == 'y'){
                        *save = 1;
                    }
                }
                else if(*save == 1){
                    printf("현재 : 켜짐\n");
                    printf("자동 저장 기능을 끄시겠습니까?\n");
                    printf("\nY/N -> ");
                    scanf("%c", &ans);
                    getchar(); // 버퍼에 남은 개행 문자 제거
                    if(ans == 'Y' || ans == 'y'){
                        *save = 0;
                    }
                }
            } else{
                printf("\nAuto Save\n");
                if(*save == 0){
                    printf("Current : OFF\n");
                    printf("Do you want to turn on the auto save?\n");
                    printf("\nY/N -> ");
                    scanf("%c", &ans);
                    getchar(); // 버퍼에 남은 개행 문자 제거
                    if(ans == 'Y' || ans == 'y'){
                        *save = 1;
                    }
                }
                else if(*save == 1){
                    printf("Current : ON\n");
                    printf("Do you want to turn off the auto save?\n");
                    printf("\nY/N -> ");
                    scanf("%c", &ans);
                    getchar(); // 버퍼에 남은 개행 문자 제거
                    if(ans == 'Y' || ans == 'y'){
                        *save = 0;
                    }
                }
            }
            break;
        case 'q':
            return;
        default:
            if(*lang == 2){
                printf("\n잘못된 입력입니다. 다시 시도하십시오.\n");
            } else{
                printf("\nInvalid input. Please try again.\n");
            }
            break;
    }
}

void clearConsole() {
    printf("\033[2J");
    printf("\033[H");
}


