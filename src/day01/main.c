#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int DEGREES_PER_CYCLE = 100;

typedef struct Operation {
  char op;
  int deg;
} Operation;

Operation* parse_operations_from_file(FILE* fp, int* count) {
  int capacity = 1;
  *count = 0;

  Operation* ops = malloc(sizeof(Operation) * capacity);

  char line[10];
  while (fgets(line, sizeof(line), fp) != NULL) {
    Operation op;
    op.op = line[0];
    op.deg = atoi(line + 1);

    if (*count >= capacity) {
      capacity *= 2;
      ops = realloc(ops, sizeof(Operation) * capacity);
    }

    ops[*count] = op;
    (*count)++;
  }

  return ops;
}

int part01(FILE* fp) {
  int count;
  Operation* ops = parse_operations_from_file(fp, &count);

  int times_at_zero = 0, cur_deg = 50;

  for (int i = 0; i < count; i ++) {
    Operation op = ops[i];
    cur_deg = ((cur_deg + op.deg * (op.op == 'R' ? 1 : -1)) % DEGREES_PER_CYCLE + DEGREES_PER_CYCLE) % DEGREES_PER_CYCLE;
    if (cur_deg == 0) {
      times_at_zero ++;
    }
  }

  free(ops);

  return times_at_zero;
}

int part02(FILE* fp) {
  int count;
  Operation* ops = parse_operations_from_file(fp, &count);

  int times_at_zero = 0, cur_deg = 50;

  for (int i = 0; i < count; i ++) {
    Operation op = ops[i];
    int right = op.op == 'R';
    int count_pass_though_zero = 0;

    // 整圈处理
    count_pass_though_zero = op.deg / DEGREES_PER_CYCLE;

    // 残余部分
    int mod = op.deg % DEGREES_PER_CYCLE;
    if (right) {
      if (cur_deg + mod >= DEGREES_PER_CYCLE) {
        count_pass_though_zero ++;
      }
      cur_deg = (cur_deg + mod) % DEGREES_PER_CYCLE;
    }
    else {
      if (cur_deg > 0 && mod >= cur_deg) {
        count_pass_though_zero ++;
      }
      cur_deg = ((cur_deg - mod) % DEGREES_PER_CYCLE + DEGREES_PER_CYCLE) % DEGREES_PER_CYCLE;
    }
    times_at_zero += count_pass_though_zero;
  }

  free(ops);

  return times_at_zero;
}

int main(int argc, char* argv[]) {
  FILE* fp = fopen("input.in", "r");

  if (!fp) {
    fprintf(stderr, "Error: Cannot open input file.\n");
    return 1;
  }

  if (argc == 1 || strcmp(argv[1], "part01") == 0) {
    printf("%d\n", part01(fp));
  }
  else if (strcmp(argv[1], "part02") == 0) {
    printf("%d\n", part02(fp));
  }
  else {
    fprintf(stderr, "Error: Invalid argument.\n");
    return 1;
  }

  fclose(fp);
  return 0;
}