#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

const int BAR_LENGTH = 50;
const int MAX_TASKS = 50;

void clear_screen(){
	#ifdef _Win32
		system("cls");
	#else
		system("clear");
	#endif
}

typedef struct{
	int id;
	int progress;
	int step;
} Task;

void print_bar(Task task){
	int progress = task.progress;
	int id = task.id;
	
	
	int bars_to_show = (int)(progress * BAR_LENGTH * 0.01);
	
	printf("Task %2d: [", id);
		
	for (int i=0; i < BAR_LENGTH; i++){
		if(i<bars_to_show){
			printf("=");
		}
		else{
			printf(" ");
		}
	}
	
	printf("] %d%%\n", progress);
}

int main() {
	Task tasks[MAX_TASKS];
	srand(time(NULL));
	
	for (int i = 0; i< MAX_TASKS; i++){
		tasks[i].id = i + 1;
		tasks[i].progress = 0;
		tasks[i].step = rand() %20 + 2 ;
	}
	
	int tasks_incomplete = 1;
	while (tasks_incomplete){
		clear_screen();
		tasks_incomplete = 0;
		
		for (int i = 0; i< MAX_TASKS; i++){
			
			tasks[i].progress += tasks[i].step;
			
			if (tasks[i].progress > 100){
				tasks[i].progress = 100;
			} else if (tasks[i].progress < 100){
				tasks_incomplete = 1;
			}
			
			print_bar(tasks[i]);
		}
		
		sleep(1);
	}
	
	printf("\nAll tasks completed!\n");
	
	return 0;
}