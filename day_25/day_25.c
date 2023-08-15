#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char int_to_snafu_digit(int val) {
  switch(val) {
    case -2:
      return '=';
    case -1:
      return '-';
    case 0:
      return '0';
    case 1:
      return '1';
    case 2:
      return '2';
    default:
      return 'x';
  }
}

int snafu_digit_to_int(char digit) {
  switch(digit) {
    case '=':
      return -2;
    case '-':
      return -1;
    case '0':
      return 0;
    case '1':
      return 1;
    case '2':
      return 2;
    default:
      printf("'%c', %d\n", digit, digit);
      return 1/0;
  }
}

char sum_snafu_digit(char a, char b, char c) {
  if(a == '\0') printf("sa\n");
  if(b == '\0') printf("sb\n");
  if(c == '\0') printf("sc\n");
  int sum = snafu_digit_to_int(a);
  sum    += snafu_digit_to_int(b);
  sum    += snafu_digit_to_int(c);

  if(sum > 2) {
    sum -= 5;
  } else if(sum < -2) {
    sum += 5;
  }
  return int_to_snafu_digit(sum);
}

char carry_snafu_digit(char a, char b, char c) {
  if(a == '\0') printf("ca\n");
  if(b == '\0') printf("cb\n");
  if(c == '\0') printf("cc\n");
  int sum = snafu_digit_to_int(a);
  sum    += snafu_digit_to_int(b);
  sum    += snafu_digit_to_int(c);

  if(sum > 2) {
    return '1';
  }
  if(sum < -2) {
    return '-';
  }
  return '0';
}

int snafu_to_int(char* snafu_number) {
  int acc = 0;
  for(int i = 0; snafu_number[i] != '\0'; i++) {
    acc *= 5;
    acc += snafu_digit_to_int(snafu_number[i]);
  }
  return acc;
}

char* seek_num_start(char* n) {
  while(n[0] == '0') {
    n++;
  }
  return n;
}

/* takes 2 snafu numbers as strings
   returns another snafu number as a string

   note that adding 2 numbers can have at most 1 more
   digit than the larger of 2 numbers, and only if
   they are the same size (with no leading 0s)
   */
char* add(char* sa, char* sb) {
  sa = seek_num_start(sa);
  sb = seek_num_start(sb);
  int sa_len = strlen(sa);
  int sb_len = strlen(sb);

  int sum_len = sa_len > sb_len ? sa_len : sb_len;
  sum_len++;
  char* sum = malloc(sizeof(char) * sum_len);

  char carry = '0';
  for(int i = 1; i <= sum_len; i++) {
    char sa_digit = '0';
    if(sa_len >= i) {
      sa_digit = sa[sa_len - i];
    }
    char sb_digit = '0';
    if(sb_len >= i) {
      sb_digit = sb[sb_len - i];
    }

    if(sa_digit == '\0' || sb_digit == '\0') {
      printf("i: %d, a_len: %d, a: %d, b_len: %d, b: %d\n", i, sa_len, sa_digit, sb_len, sb_digit);
    }

    sum[sum_len - i] = sum_snafu_digit(sa_digit, sb_digit, carry);
    carry = carry_snafu_digit(sa_digit, sb_digit, carry);
  }
  return sum;
}

void strip_newline(char* s) {
  char* newline = strchr(s, '\n');
  if(newline) {
    *newline = '\0';
  }
}

int main() {
  // getline allocates the buffer if the passed pointer is null and the size is 0
  // char* snafu_number = NULL;
  // size_t size = 0;
  // while(getline(&snafu_number, &size, stdin) != -1) {
  //   strip_newline(snafu_number);
  //   printf("%10s, %10d\n", snafu_number, snafu_to_int(snafu_number));
  // }
  char num[100];
  char* total = calloc(sizeof(char), 1);
  while(scanf("%s", num) != EOF) {
    char* next_total = add(num, total);
    free(total);
    total = next_total;
  }
  printf("%s\n", seek_num_start(total));
}
