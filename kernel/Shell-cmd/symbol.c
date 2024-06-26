// 명령어에서 다음 토큰(문자열로 된 단위)을 읽어와 해당하는 기호를 식별하여 반환
#include <stdio.h>
#include "common.h"

typedef enum {NEUTRAL, GTGT, INQUOTE, INWORD} STATUS;

SYMBOL getsymbol(char *word)
{
	STATUS state;
	int c;
	char *w;
	
	state = NEUTRAL;
	w = word;

	while ((c = getchar()) != EOF) 
	{
		switch (state) 
		{
			case NEUTRAL :
				switch (c) 
				{
					case ';' :
						return S_SEMI;

					case '&' :
						return S_AMP;

					case '|' :
						return S_BAR;

					case '<' :
						return S_LT;

					case '\n':
						return S_NL;

					case ' ' :
					case '\t':
						continue;

					case '>' : 
						state = GTGT;
						continue;

					case '"' : 
						state = INQUOTE;
						continue;

					default  : 
						state = INWORD;
						*w++ = c;
						continue;
				}

			case GTGT:
				if (c == '>')
				{
					return S_GTGT;
				}
				ungetc(c, stdin);
				return S_GT;

			case INQUOTE:
				switch (c) 
				{
					case '\\' : 
						*w++ = getchar();
						continue;

					case '"'  : 
						*w = '\0';
						return S_WORD;

					default   : 
						*w++ = c;
						continue;
				}

			case INWORD:
				switch (c ) 
				{
					case ';' :
					case '&' :
					case '|' :
					case '<' :
					case '>' :
					case '\n':
					case ' ' :
					case '\t': 
						ungetc(c, stdin);
						*w = '\0';
						return S_WORD;

					default  : 
						*w++ = c;
						continue;
				}
		}
	}

   return S_EOF;
}
