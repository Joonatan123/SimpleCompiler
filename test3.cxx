int test(int a,int b){

    int c;
    c = a + b;
    if(100000 < c){
        return 0;
    }
    c = 0;
    if(b < a){
        c = a;
        a = b;
        b = c;
    }
    a = a + b;
    printf(a);
    test(a,b);
}
int main(){
    test(0,1);
}