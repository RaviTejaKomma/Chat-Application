#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

struct data{
	int size;
	char message[50];
};

FILE *fp_to_read;
FILE *fp_to_write;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *read(void *args){

	struct data actual_data;
	while (1){
		int return_value = fread(&actual_data, sizeof(struct data), 1, fp_to_read);
		if(return_value)
			printf("\nReceived message is : %s\n", actual_data.message);
	}
	return NULL;
}

void *write(void *args)  // writes data into fp1 file
{
	struct data *actual_data;
	while (1){
		actual_data = (struct data*)malloc(sizeof(struct data));
		scanf("%s", actual_data->message);
		actual_data->size = strlen(actual_data->message);
		fwrite(actual_data, sizeof(struct data), 1, fp_to_write);
		fflush(fp_to_write);
	}
	return NULL;
}

int main(){

	/*char *file1,*file2;
	file1 = (char*)malloc(20 * sizeof(char));
	file2 = (char*)malloc(20 * sizeof(char));

	printf("\nEnter file to write : ");
	scanf("%s", file1);

	printf("\nEnter file to read : ");
	scanf("%s", file2);*/

	fp_to_write = fopen("F:/RnD/Summer/6-06-2017/ChatApplication/database2.txt", "ab");
	fp_to_read = fopen("F:/RnD/Summer/6-06-2017/ChatApplication/database1.txt", "rb");

	pthread_t  user1,user2;

	pthread_create(&user1, NULL, write, NULL);
	pthread_create(&user2, NULL, read, NULL);
	pthread_join(user1, NULL);
	pthread_join(user2, NULL);

	fclose(fp_to_write);
	fclose(fp_to_read);
	getchar();
	return 0;
}