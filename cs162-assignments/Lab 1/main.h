#ifndef main_h
#define main_h

struct mult_div_values {
	int mult;
	float div;
};

bool is_valid_dimensions(char *m, char *n);
mult_div_values** create_table(int m, int n);
void set_mult_values(mult_div_values **table, int m, int n);
void set_div_values(mult_div_values **table, int m, int n);
void delete_table(mult_div_values **table, int m);
void print_table(mult_div_values **table, int row, int col);


#endif