#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CODE_NL			"\r\n"
#define LABEL_DETECT	"Public Symbols Reference" CODE_NL
#define LEN_SIMBOL		64
#define LEN_LIST		400

typedef struct {
	char symbol[LEN_SIMBOL];
	unsigned long value;
	char type;
} LIST_SIMBOL;

typedef enum {
	ITEM_SYMBOL = 0,
	ITEM_VALUE,
	ITEM_TYPE,
	ITEM_MODULE,
} ITEM;

int main(int argc, char *argv[])
{
	FILE		*fpIn;
	char		buf[255];
	int			count = -1;
	int			rn = 0;
	LIST_SIMBOL	list[LEN_LIST];
	char*		token;
	int			item;
	char*		pt;
	char*		pv;
	char		value[16];
	int			sort;
	int			i;
	LIST_SIMBOL	tmp;

	if (argc != 2)
		goto error;

	if ((fpIn = fopen(argv[1], "rb")) == NULL) {
		printf("Cannot open input file.\n");
		return 1;
	}

	while (NULL != fgets(buf, 254, fpIn)) {
		if (strcmp(buf, LABEL_DETECT) == 0)
			count = 0;
		if (count >= 0) {
			if (strcmp(buf, CODE_NL) == 0)
				rn++;
			else
				rn = 0;
			if (rn == 2)
				break;
			if ((buf[0] != '$') && (buf[0] != '_'))
				continue;
			memset(&list[count], 0, sizeof(LIST_SIMBOL));
			token = strtok(buf, " ");
			item = 0;
			while (token != NULL) {
				switch (item) {
				case ITEM_SYMBOL:
					pt = token;
					if (*pt == '_')
						pt++;
					if (*pt == '$')
						pt++;
					if (*pt == '$')
						pt++;
					if (strlen(pt) < LEN_SIMBOL)
						strcpy(list[count].symbol, pt);
					item++;
					break;
				case ITEM_VALUE:
					pt = token;
					pv = value;
					while (*pt != 0) {
						if (*pt == ':') {
							pt++;
							continue;
						}
						*pv = *pt;
						pv++;
						pt++;
					}
					*pv = 0;
					list[count].value = strtoul(value, NULL, 16);
					item++;
					break;
				case ITEM_TYPE:
					if (strcmp(token, "CODE") == 0) {
						list[count].type = 'T';
					} else
					if (strcmp(token, "DATA") == 0) {
						list[count].type = 'D';
					} else
					if (strcmp(token, "TABLE") == 0) {
						list[count].type = 'R';
					} else {
						list[count].type = 'U';
					}
					item++;
					break;
				//case ITEM_MODULE:
				default:
					item++;
					break;
				}
				token = strtok(NULL, " ");
			}
			if (item == 4) {
				count++;
				if (count >= LEN_LIST)
					break;
				do {
					sort = 0;
					for (i = 0; i < (count - 1); i++) {
						if (list[i].value > list[i + 1].value) {
							sort = 1;
							tmp = list[i + 1];
							list[i + 1] = list[i];
							list[i] = tmp;
						}
					}
				} while (sort == 1);
			}
		}
	}

	for (i = 0; i < count; i++)
		printf("%08lx %C %s\r\n", list[i].value, list[i].type, list[i].symbol);

	fclose(fpIn);

	return 0;

error:
	printf("Parameter Error!\n\n");
	return -1;
}
