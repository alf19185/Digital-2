//Librería obtenida de electrosome.com

#include "LCD.h"
#include <pic16f887.h>
#define _XTAL_FREQ 8000000
#include <xc.h>
#include <stdint.h>

#define	EN PORTCbits.RC0
#define	RS PORTCbits.RC1

void Lcd_Port(char a) {
    PORTD = a;
}

void Lcd_Cmd(char a) {
    Lcd_Port(a);
    RS = 0; // => RS = 0
   
    EN = 1; // => E = 1
    __delay_ms(5);
    EN = 0; // => E = 0
}

Lcd_Clear() {
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b) {
    
    char temp;
    if (a == 1) {
        temp = 0x80 + b - 1;
        Lcd_Cmd(temp);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        Lcd_Cmd(temp);
    }
}

void Lcd_Init() {
    
    Lcd_Cmd(0x38);
    Lcd_Cmd(0x0C);
    Lcd_Cmd(0x06);
    Lcd_Cmd(0x80);
}

void Lcd_Write_Char(char a) {
    
   RS = 1;             // => RS = 1
   Lcd_Port(a);             //Data transfer
   EN = 1;
   __delay_us(40);
   EN = 0;
   RS = 0;
}

void Lcd_Write_String(char *a) {
   int i;
	for(i=0;a[i]!='\0';i++)
	   Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right() {
    Lcd_Cmd(0x1C);
   
}

void Lcd_Shift_Left() {
    Lcd_Cmd(0x18);
   
}

const char* CONV(uint8_t numero){
    switch(numero){
        case 0:
            return "000";
            break;
        case 1:
            return "001";
            break;
        case 2:
            return "002";
            break;
        case 3:
            return "003";
            break;
        case 4:
            return "004";
            break;
        case 5:
            return "005";
            break;
        case 6:
            return "006";
            break;
        case 7:
            return "007";
            break;
        case 8:
            return "008";
            break;
        case 9:
            return "009";
            break;   
         case 10:
            return "010";
            break;
        case 11:
            return "011";
            break;
        case 12:
            return "012";
            break;
        case 13:
            return "013";
            break;
        case 14:
            return "014";
            break;
        case 15:
            return "015";
            break;
        case 16:
            return "016";
            break;
        case 17:
            return "017";
            break;
        case 18:
            return "018";
            break;
        case 19:
            return "019";
            break;    
         case 20:
            return "020";
            break;
        case 21:
            return "021";
            break;
        case 22:
            return "022";
            break;
        case 23:
            return "023";
            break;
        case 24:
            return "024";
            break;
        case 25:
            return "025";
            break;
        case 26:
            return "026";
            break;
        case 27:
            return "027";
            break;
        case 28:
            return "028";
            break;
        case 29:
            return "029";
            break;   
         case 30:
            return "030";
            break;
        case 31:
            return "031";
            break;
        case 32:
            return "032";
            break;
        case 33:
            return "033";
            break;
        case 34:
            return "034";
            break;
        case 35:
            return "035";
            break;
        case 36:
            return "036";
            break;
        case 37:
            return "037";
            break;
        case 38:
            return "038";
            break;
        case 39:
            return "039";
            break;
         case 40:
            return "040";
            break;
        case 41:
            return "041";
            break;
        case 42:
            return "042";
            break;
        case 43:
            return "043";
            break;
        case 44:
            return "044";
            break;
        case 45:
            return "045";
            break;
        case 46:
            return "046";
            break;
        case 47:
            return "047";
            break;
        case 48:
            return "048";
            break;
        case 49:
            return "049";
            break;   
         case 50:
            return "050";
            break;
        case 51:
            return "051";
            break;
        case 52:
            return "052";
            break;
        case 53:
            return "053";
            break;
        case 54:
            return "054";
            break;
        case 55:
            return "055";
            break;
        case 56:
            return "056";
            break;
        case 57:
            return "057";
            break;
        case 58:
            return "058";
            break;
        case 59:
            return "059";
            break;   
         case 60:
            return "060";
            break;
        case 61:
            return "061";
            break;
        case 62:
            return "062";
            break;
        case 63:
            return "063";
            break;
        case 64:
            return "064";
            break;
        case 65:
            return "065";
            break;
        case 66:
            return "066";
            break;
        case 67:
            return "067";
            break;
        case 68:
            return "068";
            break;
        case 69:
            return "069";
            break;
         case 70:
            return "070";
            break;
        case 71:
            return "071";
            break;
        case 72:
            return "072";
            break;
        case 73:
            return "073";
            break;
        case 74:
            return "074";
            break;
        case 75:
            return "075";
            break;
        case 76:
            return "076";
            break;
        case 77:
            return "077";
            break;
        case 78:
            return "078";
            break;
        case 79:
            return "079";
            break;
         case 80:
            return "080";
            break;
        case 81:
            return "081";
            break;
        case 82:
            return "082";
            break;
        case 83:
            return "083";
            break;
        case 84:
            return "084";
            break;
        case 85:
            return "085";
            break;
        case 86:
            return "086";
            break;
        case 87:
            return "087";
            break;
        case 88:
            return "088";
            break;
        case 89:
            return "089";
            break;    
        case 90:
            return "090";
            break;
        case 91:
            return "091";
            break;
        case 92:
            return "092";
            break;
        case 93:
            return "093";
            break;
        case 94:
            return "094";
            break;
        case 95:
            return "095";
            break;
        case 96:
            return "096";
            break;
        case 97:
            return "097";
            break;
        case 98:
            return "098";
            break;
        case 99:
            return "099";
            break;    
        case 100:
            return "100";
            break;
        case 101:
            return "101";
            break;
        case 102:
            return "102";
            break;
        case 103:
            return "103";
            break;
        case 104:
            return "104";
            break;
        case 105:
            return "105";
            break;
        case 106:
            return "106";
            break;
        case 107:
            return "107";
            break;
        case 108:
            return "108";
            break;
        case 109:
            return "109";
            break;   
        case 110:
            return "110";
            break;
        case 111:
            return "111";
            break;
        case 112:
            return "112";
            break;
        case 113:
            return "113";
            break;
        case 114:
            return "114";
            break;
        case 115:
            return "115";
            break;
        case 116:
            return "116";
            break;
        case 117:
            return "117";
            break;
        case 118:
            return "118";
            break;
        case 119:
            return "119";
            break;  
        case 120:
            return "120";
            break;
        case 121:
            return "121";
            break;
        case 122:
            return "122";
            break;
        case 123:
            return "123";
            break;
        case 124:
            return "124";
            break;
        case 125:
            return "125";
            break;
        case 126:
            return "126";
            break;
        case 127:
            return "127";
            break;
        case 128:
            return "128";
            break;
        case 129:
            return "129";
            break;
        case 130:
            return "130";
            break;
        case 131:
            return "131";
            break;
        case 132:
            return "132";
            break;
        case 133:
            return "133";
            break;
        case 134:
            return "134";
            break;
        case 135:
            return "135";
            break;
        case 136:
            return "136";
            break;
        case 137:
            return "137";
            break;
        case 138:
            return "138";
            break;
        case 139:
            return "139";
            break;
        case 140:
            return "140";
            break;
        case 141:
            return "141";
            break;
        case 142:
            return "142";
            break;
        case 143:
            return "143";
            break;
        case 144:
            return "144";
            break;
        case 145:
            return "145";
            break;
        case 146:
            return "146";
            break;
        case 147:
            return "147";
            break;
        case 148:
            return "148";
            break;
        case 149:
            return "149";
            break;
        case 150:
            return "150";
            break;
        case 151:
            return "151";
            break;
        case 152:
            return "2";
            break;
        case 153:
            return "3";
            break;
        case 154:
            return "154";
            break;
        case 155:
            return "155";
            break;
        case 156:
            return "156";
            break;
        case 157:
            return "157";
            break;
        case 158:
            return "158";
            break;
        case 159:
            return "159";
            break;
        case 160:
            return "160";
            break;
        case 161:
            return "161";
            break;
        case 162:
            return "162";
            break;
        case 163:
            return "163";
            break;
        case 164:
            return "164";
            break;
        case 165:
            return "165";
            break;
        case 166:
            return "166";
            break;
        case 167:
            return "167";
            break;
        case 168:
            return "168";
            break;
        case 169:
            return "169";
            break;
        case 170:
            return "170";
            break;
        case 171:
            return "171";
            break;
        case 172:
            return "172";
            break;
        case 173:
            return "173";
            break;
        case 174:
            return "174";
            break;
        case 175:
            return "175";
            break;
        case 176:
            return "176";
            break;
        case 177:
            return "177";
            break;
        case 178:
            return "178";
            break;
        case 179:
            return "179";
            break; 
        case 180:
            return "180";
            break;
        case 181:
            return "181";
            break;
        case 182:
            return "182";
            break;
        case 183:
            return "183";
            break;
        case 184:
            return "184";
            break;
        case 185:
            return "185";
            break;
        case 186:
            return "186";
            break;
        case 187:
            return "187";
            break;
        case 188:
            return "188";
            break;
        case 189:
            return "189";
            break;   
        case 190:
            return "190";
            break;
        case 191:
            return "191";
            break;
        case 192:
            return "192";
            break;
        case 193:
            return "193";
            break;
        case 194:
            return "194";
            break;
        case 195:
            return "195";
            break;
        case 196:
            return "196";
            break;
        case 197:
            return "197";
            break;
        case 198:
            return "198";
            break;
        case 199:
            return "199";
            break;   
        case 200:
            return "20";
            break;
        case 201:
            return "201";
            break;
        case 202:
            return "202";
            break;
        case 203:
            return "203";
            break;
        case 204:
            return "204";
            break;
        case 205:
            return "205";
            break;
        case 206:
            return "206";
            break;
        case 207:
            return "207";
            break;
        case 208:
            return "208";
            break;
        case 209:
            return "209";
            break;
        case 210:
            return "210";
            break;
        case 211:
            return "211";
            break;
        case 212:
            return "212";
            break;
        case 213:
            return "213";
            break;
        case 214:
            return "214";
            break;
        case 215:
            return "215";
            break;
        case 216:
            return "216";
            break;
        case 217:
            return "217";
            break;
        case 218:
            return "218";
            break;
        case 219:
            return "219";
            break;
        case 220:
            return "220";
            break;
        case 221:
            return "221";
            break;
        case 222:
            return "222";
            break;
        case 223:
            return "223";
            break;
        case 224:
            return "224";
            break;
        case 225:
            return "225";
            break;
        case 226:
            return "226";
            break;
        case 227:
            return "227";
            break;
        case 228:
            return "228";
            break;
        case 229:
            return "229";
            break;   
        case 230:
            return "230";
            break;
        case 231:
            return "231";
            break;
        case 232:
            return "232";
            break;
        case 233:
            return "233";
            break;
        case 234:
            return "234";
            break;
        case 235:
            return "235";
            break;
        case 236:
            return "236";
            break;
        case 237:
            return "237";
            break;
        case 238:
            return "238";
            break;
        case 239:
            return "239";
            break;   
        case 240:
            return "240";
            break;
        case 241:
            return "241";
            break;
        case 242:
            return "242";
            break;
        case 243:
            return "243";
            break;
        case 244:
            return "244";
            break;
        case 245:
            return "245";
            break;
        case 246:
            return "246";
            break;
        case 247:
            return "247";
            break;
        case 248:
            return "248";
            break;
        case 249:
            return "249";
            break;
        case 250:
            return "250";
            break;
        case 251:
            return "251";
            break;
        case 252:
            return "252";
            break;
        case 253:
            return "253";
            break;
        case 254:
            return "254";
            break;
        case 255:
            return "255";
            break;
        
            
    }
}