
typedef enum tokens{lparen, rparen, mult, mod, division, add, sub, eos, operand, point}precedence;

int get_token(char *expr, int *index);
