#include <stdio.h>

#include "tokens.h"

#define YYLMAX 200
#define BUFSIZE 100
enum states {
		STATE0,
		STATE1,
		STATE2,
		STATE3,
		STATE4,
		STATE5,
		STATE6,
		STATE7,
		STATE8,
		STATE9,
		STATE10,
		STATE11,
		STATE12,
		STATE13,
		STATE14,
		STATE15,
		STATE16,
		STATE17,
		STATE18,
		STATE19,
		STATE20,
		STATE21,
		STATE22,
		STATE23,
		STATE24,
		STATE25,
		STATE26,
		STATE27,
		STATE28,
		STATE29,
		STATE30,
		STATE31,
		STATE32,
		STATE33,
		STATE34,
		STATE35,
		STATE36,
		STATE37,
		STATE38,
		STATE39,
		STATE40,
		STATE41,
		STATE42,
		STATE43,
		STATE44,
		STATE45,
		STATE46,
		STATE47,
		STATE48,
		STATE49,
		STATE50,
		STATE51,
		STATE52,
		STATE53,
		STATE54,
		STATE55,
		STATE56,
		STATE57,
		STATE58,
		STATE59,
		STATE60,
		STATE61,
		STATE62,
		STATE63,
		STATE64,
		STATE65,
		STATE66,
		STATE67,
		STATE68,
		STATE69,
		STATE70,
		STATE71,
		STATE72,
		STATE73,
		STATE74,
		STATE75,
		STATE76,
		STATE77,
		STATE78,
		STATE79,
		STATE80,
		STATE81,
		STATE82,
		STATE83,
		STATE84,
		STATE85,
		STATE86,
		STATE87,
		STATE88,
		STATE89,
		STATE90,
		STATE91,
		STATE92,
		STATE93,
		STATE94,
		STATE95,
		STATE96,
		STATE97,
		STATE98,
		STATE99,
		STATE100,
		STATE101,
		STATE102,
		STATE103,
		STATE104,
		STATE105,
		STATE106,
		STATE107,
		STATE108,
		STATE109,
		STATE110,
		STATE111,
		STATE112,
		STATE113,
		STATE114,
		STATE115,
		STATE116,
		STATE117,
		STATE118,
		STATE119,
		STATE120,
		STATE121,
		STATE122,
		STATE123,
		STATE124,
		STATE125,
		STATE126,
		STATE127,
		STATE128,
		STATE129,
		STATE130,
		STATE131,
		STATE132,
		STATE133,
		STATE134,
		STATE135,
		STATE136,
		STATE137,
		STATE138,
		STATE139,
		STATE140,
		STATE141,
		STATE142,
		STATE143,
		STATE144,
		STATE145,
		STATE146,
		STATE147,
		STATE148,
		STATE149,
		STATE150,
		STATE151,
		STATE152,
		STATE153,
		STATE154,
		STATE155,
		STATE156,
		STATE157,
		STATE158,
		STATE159,
		STATE160,
		STATE161,
		STATE162,
		STATE163,
		STATE164,
		STATE165,
		STATE166,
		STATE167,
		STATE168,
		STATE169,
		STATE170,
		STATE171,
		STATE172,
		STATE173,
		STATE174,
		STATE175,
		};
int state = STATE0;
FILE *yyin = stdin;
FILE *yyout = stdout;
char yytext[YYLMAX];
int yyleng = 0;

char buf[BUFSIZE];
int bufp = 0
char input(){
	return (bufp > 0) ? buf[bufp--] : getc(yyin);
}

void unput(int c){
	if(bufp >= BUFSIZE-1)
		fprintf(stderr, "ERROR: BUFFER is full\n");
	else
		buf[++bufp] = c;
}

int installID(){
	/*function to install the id

	*/
}

int installNum(){
	/*function to install the num

	*/
}

int yylex(){
	state = STATE0;
	char *p = yytext;
	while(1){
		int c = input();
		if(EOF == c)
			return c;
		switch(state){
			case STATE1:
				break;
			case STATE2:
				break;
			case STATE3:
				break;
			case STATE4:
				break;
			case STATE5:
				break;
			case STATE6:
				break;
			case STATE7:
				break;
			case STATE8:
				break;
			case STATE9:
				break;
			case STATE10:
				break;
			case STATE11:
				break;
			case STATE12:
				break;
			case STATE13:
				break;
			case STATE14:
				break;
			case STATE15:
				break;
			case STATE16:
				break;
			case STATE17:
				break;
			case STATE18:
				break;
			case STATE19:
				break;
			case STATE20:
				break;
			case STATE21:
				break;
			case STATE22:
				break;
			case STATE23:
				break;
			case STATE24:
				break;
			case STATE25:
				break;
			case STATE26:
				break;
			case STATE27:
				break;
			case STATE28:
				break;
			case STATE29:
				break;
			case STATE30:
				break;
			case STATE31:
				break;
			case STATE32:
				break;
			case STATE33:
				break;
			case STATE34:
				break;
			case STATE35:
				break;
			case STATE36:
				break;
			case STATE37:
				break;
			case STATE38:
				break;
			case STATE39:
				break;
			case STATE40:
				break;
			case STATE41:
				break;
			case STATE42:
				break;
			case STATE43:
				break;
			case STATE44:
				break;
			case STATE45:
				break;
			case STATE46:
				break;
			case STATE47:
				break;
			case STATE48:
				break;
			case STATE49:
				break;
			case STATE50:
				break;
			case STATE51:
				break;
			case STATE52:
				break;
			case STATE53:
				break;
			case STATE54:
				break;
			case STATE55:
				break;
			case STATE56:
				break;
			case STATE57:
				break;
			case STATE58:
				break;
			case STATE59:
				break;
			case STATE60:
				break;
			case STATE61:
				break;
			case STATE62:
				break;
			case STATE63:
				break;
			case STATE64:
				break;
			case STATE65:
				break;
			case STATE66:
				break;
			case STATE67:
				break;
			case STATE68:
				break;
			case STATE69:
				break;
			case STATE70:
				break;
			case STATE71:
				break;
			case STATE72:
				break;
			case STATE73:
				break;
			case STATE74:
				break;
			case STATE75:
				break;
			case STATE76:
				break;
			case STATE77:
				break;
			case STATE78:
				break;
			case STATE79:
				break;
			case STATE80:
				break;
			case STATE81:
				break;
			case STATE82:
				break;
			case STATE83:
				break;
			case STATE84:
				break;
			case STATE85:
				break;
			case STATE86:
				break;
			case STATE87:
				break;
			case STATE88:
				break;
			case STATE89:
				break;
			case STATE90:
				break;
			case STATE91:
				break;
			case STATE92:
				break;
			case STATE93:
				break;
			case STATE94:
				break;
			case STATE95:
				break;
			case STATE96:
				break;
			case STATE97:
				break;
			case STATE98:
				break;
			case STATE99:
				break;
			case STATE100:
				break;
			case STATE101:
				break;
			case STATE102:
				break;
			case STATE103:
				break;
			case STATE104:
				break;
			case STATE105:
				break;
			case STATE106:
				break;
			case STATE107:
				break;
			case STATE108:
				break;
			case STATE109:
				break;
			case STATE110:
				break;
			case STATE111:
				break;
			case STATE112:
				break;
			case STATE113:
				break;
			case STATE114:
				break;
			case STATE115:
				break;
			case STATE116:
				break;
			case STATE117:
				break;
			case STATE118:
				break;
			case STATE119:
				break;
			case STATE120:
				break;
			case STATE121:
				break;
			case STATE122:
				break;
			case STATE123:
				break;
			case STATE124:
				break;
			case STATE125:
				break;
			case STATE126:
				break;
			case STATE127:
				break;
			case STATE128:
				break;
			case STATE129:
				break;
			case STATE130:
				break;
			case STATE131:
				break;
			case STATE132:
				break;
			case STATE133:
				break;
			case STATE134:
				break;
			case STATE135:
				break;
			case STATE136:
				break;
			case STATE137:
				break;
			case STATE138:
				break;
			case STATE139:
				break;
			case STATE140:
				break;
			case STATE141:
				break;
			case STATE142:
				break;
			case STATE143:
				break;
			case STATE144:
				break;
			case STATE145:
				break;
			case STATE146:
				break;
			case STATE147:
				break;
			case STATE148:
				break;
			case STATE149:
				break;
			case STATE150:
				break;
			case STATE151:
				break;
			case STATE152:
				break;
			case STATE153:
				break;
			case STATE154:
				break;
			case STATE155:
				break;
			case STATE156:
				break;
			case STATE157:
				break;
			case STATE158:
				break;
			case STATE159:
				break;
			case STATE160:
				break;
			case STATE161:
				break;
			case STATE162:
				break;
			case STATE163:
				break;
			case STATE164:
				break;
			case STATE165:
				break;
			case STATE166:
				break;
			case STATE167:
				break;
			case STATE168:
				break;
			case STATE169:
				break;
			case STATE170:
				break;
			case STATE171:
				break;
			case STATE172:
				break;
			case STATE173:
				break;
			case STATE174:
				break;
			case STATE175:
				break;
		}
}
	}
