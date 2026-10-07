#include <stdio.h>
#include <string.h>

void make_new_name(char *new_name, char *original_name);
int is_alpha(char c);
int is_digit(char c);
int is_valid_password(char *password);
void perform_XOR(char *input_filename, char *output_filename, char *password);
void print_first_five(char *filename);

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage: ./A2 filename password");
		return 1;
	}
	char new_file_name[strlen(argv[1]) + 5];
	make_new_name(new_file_name, argv[1]);
	printf("New filename = %s", new_file_name);
	return 0;
}

void make_new_name(char *new_name, char *original_name) {
	const char* prefix = "new-";
	int a = 0;
	int b = 0;
	while (prefix[a] != '\0') {
		new_name[a] = prefix[a];
		a++;
	}
	while (original_name[b] != '\0') {
		new_name[a] = original_name[b];
		a++;
		b++;
	}
	new_name[a] = '\0';
}
