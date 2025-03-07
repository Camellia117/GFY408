#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert_to_base(int32_t num, int base, char *output) {
   if (base == 10) {
       sprintf(output, "%d", num);
       return;
   }

   if (num == 0) {
       strcpy(output, "0");
       return ;
   }
   char buffer[32];
   int index = 0;
   int is_negative = num < 0;
   uint32_t abs_num = is_negative ? (uint32_t)(-num) : (uint32_t)num;

   while(abs_num > 0) {
       int rem = abs_num % base;
       char c;
       if (rem < 10) c = rem + '0';
           else c = rem - 10 + 'A';
       buffer[index++] = c;
       abs_num /= base;
   }
   if (is_negative) buffer[index++] = '-';

   for(int i = 0;i < index/2; i++) {
       char temp = buffer[i];
       buffer[i] = buffer[index - 1 -i];
       buffer[index - 1 - i] = temp;
   }
   buffer[index] = '\0';
   strcpy(output, buffer);
}
void get_twos_complement(int32_t num, char *buffer) {
    uint32_t u = (uint32_t)num;
    for (int i = 31;i >= 0;i--) {
        buffer[31 - i] = (u & (1UL << i)) ? '1' : '0';
    }
    buffer[32] = '\0';
}
void get_original_code(int32_t num, char *buffer) {
    if (num > 0) {
        get_twos_complement(num, buffer);
    }else {
        buffer[0] = '1';
        uint32_t abs_num = (uint32_t)(-num);
        for (int i = 30; i >= 0;i--) {
            buffer[31 - i] = (abs_num & (1UL << i)) ? '1' : '0';
        }
        buffer[32] = '\0';
    }
}

int main() {
  char input[100];
  long num_long;
  int base_out;
  char *endptr;
  printf("请输入数值（可带0b/0/0x前缀）: ");
  if(!fgets(input, sizeof(input), stdin)) {
    fprintf(stderr, "input error\n");
    return 1;
  }

  // convert to long
  num_long = strtol(input, &endptr, 0);
  if (endptr == input) {
      fprintf(stderr, "无法解析输入\n");
      return 1;
  }
  int32_t num = (int32_t)num_long;

  // 检查是否无法使用原码
  if (num == INT32_MIN) {
      fprintf(stderr, "err: -2147483648无原码表示\n");
      return 1;
  }
  // 获取输出进制
  printf("请选择输出进制（2/8/10/16）: ");
  if (scanf("%d", &base_out) != 1 || !(base_out == 2 || base_out == 8 || base_out == 10 || base_out == 16)) {
      fprintf(stderr, "无效进制\n");
      return 1;
  }
  // 进制转换
  char converted[32];
  convert_to_base(num, base_out, converted);

  // 获取编码信息
  char original[33], complement[33];
  get_original_code(num, original);
  get_twos_complement(num, complement);

  printf("\n转换结果: %s\n", converted);
  printf("原码: %s\n", original);
  printf("补码: %s\n", complement);

  return 0;
}
