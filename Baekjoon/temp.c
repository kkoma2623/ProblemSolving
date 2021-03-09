#include <stdio.h>
#include <string.h>

void eliminateChar(char *str, char ch){
  for(; *str != '\0'; ++str){
    if(*str != ch) continue;
    strcpy(str, str+1);
    --str;
  }
}

int main(){
  char str[20];
  char cities[100001][20];
  int pos = 0;
  scanf("%s", str);
  eliminateChar(str, '"');
  eliminateChar(str, '[');
  eliminateChar(str, ',');
  strcpy(cities[0], str);
  int idx = 1;
  while(str[strlen(str)-1] != ']'){
    scanf("%s", str);
    eliminateChar(str, '"');
    eliminateChar(str, ',');
    strcpy(cities[idx++], str);
  }
  eliminateChar(cities[idx-1], ']');

  for(int i=0; i<idx; ++i){
    printf("%s ", cities[i]);
  }
  return 0;
}

// int main() {
//   char fuck[3][25] = {'\0'};
//   char k;
//   int i=0, j=0;
//   while(1){
//     k = getchar();
//     if(k=='[' || k=='"' || k==']' || k==',') continue;
//     else if(k=='\n') break;
//     else fuck[i][j++] = k;
//   }

//   for(int i=0; i<3; ++i)
//     printf("%s ", fuck[i]);
// }