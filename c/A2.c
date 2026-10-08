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
	printf("New filename = %s\n", new_file_name);
	if (!(is_valid_password(argv[2]))) {
		return 1;
	}
	printf("SUCCESS");
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

int is_alpha(char c) {
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) return 1;
	return 0;
}

int is_digit(char c) {
	if (c >= 48 && c <= 57) return 1;
	return 0;
}

int is_valid_password(char *password) {
	int password_length = strlen(password);
	int success = 1;
	printf("Password length = %d\n", password_length);
	if (!(password_length >= 8)) {
		printf("The password needs to have at least 8 characters.\n");
		success = 0;
	}
	int alpha_success = 0;
	for (int i = 0; i < password_length; i++) {
		if (is_alpha(password[i])) {
			alpha_success = 1;
		}
	}
	if (alpha_success == 0) {
		printf("The password needs to contain at least 1 alphabetical character.\n");
		success = 0;
	}
	int digit_success = 0;
	for (int i = 0; i < password_length; i++) {
		if (is_digit(password[i])) {
			digit_success = 1;
		}
	}
	if (digit_success == 0) {
		printf("The password needs to contain at least 1 digit.\n");
		success = 0;
	}
	return success;
}
