
int fibonacci(int a, int b, int limit){

    if(b < a){
        b = a + b;
        printf(b);
        if(10000 < a + b)
            return b;
    }
    int ap1;
    ap1 = a+1;
    if(ap1<b){
        a = a + b;
        printf(a);
        if(10000 < a + b)
            return a;
    }

    return fibonacci(a, b, limit);
}

int main(){
    printf(0);
    printf(1);
    printf(1);

    printf(fibonacci(1,1,10000));

    int asd;
    asd = 123;
}