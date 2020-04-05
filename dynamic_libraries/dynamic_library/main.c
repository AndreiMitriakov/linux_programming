#include "solution.h"

int main(){
    int cnt = 0;
    int length = stringStat("Noname", 2, &cnt);
    printf("Length is %i\n", length);
    printf("cnt is %i\n", cnt);
    return 0;
}
