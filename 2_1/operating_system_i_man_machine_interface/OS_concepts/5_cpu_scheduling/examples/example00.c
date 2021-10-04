#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 5

void* runner(void* params);

int main(int argc, char* argv[])
{
    int i;
    int scope;
    pthread_t tid[NUM_THREADS];
    pthread_attr_t attr;
    
    /* 기본 속성 가져오기 */
    pthread_attr_init(&attr);
    
    /* 현재 영역 확인 */
    if (pthread_attr_getscope(&attr, &scope) != 0) {
    	fprintf(stderr, "Unable to get scheduling scope\n");
    } else {
    	if (scope == PTHREAD_SCOPE_PROCESS) {
            printf("PTHREAD_SCOPE_PROCESS");
        } else if (scope == PTHREAD_SCOPE_SYSTEM) {
            printf("PTHREAD_SCOPE_SYSTEM");
        } else {
            fprintf(stderr, "Illegal scope value.\n");
        }
    }
    
    /* 스케줄링 알고리듬을 PCS 혹은 SCS로 설정 */
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    
    /* 스레드 생성 */
    for (i = 0; i < NUM_THREADS; ++i) {
    	pthread_create(&tid[i], &attr, runner, NULL);
    }
    
    /* 각 스레드 마다 조인 */
    for (i = 0; i < NUM_THREADS; ++i) {
    	pthread_join(tid[i], NULL);
    }
}

/* 각 스레드마다 이 함수에서 제어 시작 */
void* runner(void* params)
{
	/* 무언가를 함 */
	
	pthread_exit(0);
}