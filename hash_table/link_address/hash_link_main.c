/*************************************************************************
	> File Name: hash_table_main.c
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: Fri 22 Mar 2013 11:17:25 AM CST
 ************************************************************************/

#include "hash_link.h"

typedef struct stu {

	char num[5];
	char name[32];
	int age;
} stu_t;

//使用学号来当作key进而产生hash index/bucket
//在这里学号是字符串，当然也可以将学号定义为int类型,此时要重新定义一个hash_int函数
unsigned int hash_str(unsigned int buckets, void* key)
{
	char *num = (char*)key;
	unsigned int index = 0;
	while (*num) {

		index = *num + 4 * index;
		num++;
	}

	return index % buckets;
}
//在这个例子中，key是学生学号，value是学生结构体
int main(void)
{
	stu_t stu_arr[] = {
		{ "1234", "AAAA", 20 },
		{ "6543", "BBBB", 23 },
		{ "7657", "AAAA", 19 }, 
	};

	hash_t* hash = hash_alloc(256, hash_str);

	int size = sizeof(stu_arr) / sizeof(stu_arr[0]);
	int i;
	for (i = 0; i < size; i++) {

		hash_add_entry(hash, stu_arr[i].num, strlen(stu_arr[i].num),
				&stu_arr[i], sizeof(stu_arr[i]));
	}

	stu_t *ptr = (stu_t*)hash_lookup_entry(hash, "6543", strlen("6543"));
	if (ptr) 
		printf("%s %s %d\n", ptr->num, ptr->name, ptr->age);	
	else
		printf("not found\n");

	
	hash_free_entry(hash, "1234", strlen("1234"));
	ptr = (stu_t*)hash_lookup_entry(hash, "1234", strlen("1234"));
	if (ptr) 
		printf("%s %s %d\n", ptr->num, ptr->name, ptr->age);	
	else
		printf("not found\n");

	return 0;
}
