#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* digit conversions */
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

/* digitwise addition, only the sum */
char sum_snafu_digit(char a, char b, char c) {
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

/* digitwise addition, only the carry */
char carry_snafu_digit(char a, char b, char c) {
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

/* whole number converions, only used to test */
int snafu_to_int(char* snafu_number) {
  int acc = 0;
  for(int i = 0; snafu_number[i] != '\0'; i++) {
    acc *= 5;
    acc += snafu_digit_to_int(snafu_number[i]);
  }
  return acc;
}

/* number reading helper - remove leading 0s */
char* seek_num_start(char* n) {
  while(n[0] == '0') {
    n++;
  }
  return n;
}

/* add 2 snafu numbers */
char* add(char* sa, char* sb) {
  sa = seek_num_start(sa);
  sb = seek_num_start(sb);
  int sa_len = strlen(sa);
  int sb_len = strlen(sb);

  int sum_len = sa_len > sb_len ? sa_len : sb_len;
  sum_len++; // the sum of 2 numbers is at most 1 digit longer
  char* sum = malloc(sizeof(char) * sum_len);

  char carry = '0';
  for(int i = 1; i <= sum_len; i++) {
    // simulate leading 0s
    char sa_digit = '0';
    if(sa_len >= i) {
      sa_digit = sa[sa_len - i];
    }
    char sb_digit = '0';
    if(sb_len >= i) {
      sb_digit = sb[sb_len - i];
    }

    sum[sum_len - i] = sum_snafu_digit(sa_digit, sb_digit, carry);
    carry = carry_snafu_digit(sa_digit, sb_digit, carry);
  }
  return sum;
}

/* stdin number reading helper - remove trailing newline */
void strip_newline(char* s) {
  char* newline = strchr(s, '\n');
  if(newline) {
    *newline = '\0';
  }
}

int main() {
  char num[100];
  char* total = calloc(sizeof(char), 1);
  while(scanf("%s", num) != EOF) {
    char* next_total = add(num, total);
    free(total);
    total = next_total;
  }
  printf("%s\n", seek_num_start(total));
}
