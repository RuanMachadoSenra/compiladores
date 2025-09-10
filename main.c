#include <stdio.h>
#include "scanner.h"

int main() {
    FILE *fp = fopen("programa.p-", "r");
    if (!fp) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    Token t;
    do {
        t = getToken(fp);
        printf("[linha %d] TOKEN=%d, LEXEMA=\"%s\"\n", t.line, t.type, t.lexeme);
    } while (t.type != TOK_EOF);

    fclose(fp);
    return 0;
}